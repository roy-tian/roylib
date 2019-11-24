#include "royshell.h"
#include "trivials/roypointer.h"
#include "trivials/roypair.h"

static void parse(RoyShell * shell);

enum {
  MAX_LEN = 255,
  ARG_LEN = 63
};

void pair_deleter(RoyPair * pair) {
  roy_string_delete(pair->key);
  free(pair->value);
  free(pair);
  pair = NULL;
}

RoyShell *
roy_shell_new(void) {
  RoyShell * ret = (RoyShell *)malloc(sizeof(RoyShell));
  ret->prompt    = roy_string_new("> ");
  ret->ibuffer   = roy_string_new("");
  ret->obuffer   = roy_string_new("");
  ret->dict      = roy_map_new((RCompare)roy_string_compare, (ROperate)pair_deleter);
  ret->argv      = roy_deque_new((ROperate)roy_string_delete);
  ret->ihistory  = roy_deque_new((ROperate)roy_string_delete);
  ret->ohistory  = roy_deque_new((ROperate)roy_string_delete);
  return ret;
}

void
roy_shell_delete(RoyShell * shell) {
  roy_string_delete(shell->prompt);
  roy_string_delete(shell->ibuffer);
  roy_string_delete(shell->obuffer);
  roy_map_delete(shell->dict);
  roy_deque_delete(shell->argv);
  roy_deque_delete(shell->ihistory);
  roy_deque_delete(shell->ohistory);
  free(shell);
  shell = NULL;
}

void
roy_shell_start(RoyShell * shell) {
  while (true) {
    roy_string_print(shell->prompt);
    roy_string_clear(shell->ibuffer);
    fgets(roy_string_str(shell->ibuffer), MAX_LEN, stdin);
    roy_string_erase(shell->ibuffer,
                     roy_string_size(shell->ibuffer) - 1,
                     1);
    if (!roy_string_match(shell->ibuffer, "\\s+")) {
      parse(shell);
      void (* func)(RoyShell *) = 
      roy_pointer_get(roy_map_at(shell->dict,
                                 roy_shell_argument_at(shell, 0),
                                 RoyPointer));
      if (func) {
        roy_shell_log_clear(shell);
        func(shell);
        roy_string_println(shell->obuffer);
      }
      roy_deque_push_back(shell->ihistory, shell->ibuffer);
      roy_deque_push_back(shell->ohistory, shell->obuffer);
    }
  }
}

RoyShell *
roy_shell_command_add(RoyShell   * shell,
                      const char * cmd,
                      void      (* operate)(RoyShell *)) {
  RoyPointer func;
  roy_map_insert(shell->dict,
                 roy_string_new(cmd),
                 roy_pointer_set(&func, operate));
  return shell;
}

RoyShell *
roy_shell_set_prompt_text(RoyShell   * shell,
                          const char * prompt) {
  roy_string_assign(shell->prompt, prompt);
  return shell;
}

size_t
roy_shell_argument_count(const RoyShell * shell) {
  return roy_deque_size(shell->argv);
}

const char *
roy_shell_argument_at(const RoyShell * shell,
                      size_t           position) {
  return (const char *) roy_deque_cpointer(shell->argv, position);
}

int
roy_shell_argument_find(const RoyShell * shell,
                        const char     * regex) {
  RoyString * arg = roy_string_new(NULL);
  for (size_t i = 0; i != roy_shell_argument_count(shell); i++) {
    roy_string_assign(arg, roy_shell_argument_at(shell, i));
    if (roy_string_match(arg, regex)) {
      roy_string_delete(arg);
      return i;
    }
  }
  roy_string_delete(arg);
  return -1; // not found. (0 indicates the cmd itself)
}

RoyShell *
roy_shell_log_clear(RoyShell * shell) {
  memset(shell->obuffer, '\0', MAX_LEN);
  return shell;
}

RoyShell *
roy_shell_log_append(RoyShell   * shell,
                     const char * format,
                     ...) {
  va_list args;
  va_start(args, format);
  vsprintf(roy_string_str(shell->obuffer), format, args);
  va_end(args);
  return shell;
}

size_t
roy_shell_history_count(const RoyShell * shell) {
  return roy_deque_size(shell->ihistory);
}

const char *
roy_shell_ihistory_at(const RoyShell * shell,
                      int              position) {
  if (position < 0) {
    position = roy_deque_size(shell->ihistory) + position;
  }
  return (const char *) roy_deque_cpointer(shell->ihistory, position);
}

const char *
roy_shell_ohistory_at(const RoyShell * shell,
                      int              position) {
  if (position < 0) {
    position = roy_deque_size(shell->ohistory) + position;
  }
  return (const char *) roy_deque_cpointer(shell->ohistory, position);
}

/* PRIVATE FUNCTIONS */

static void
parse(RoyShell  * shell) {
  roy_deque_clear(shell->argv);
  const char * phead = roy_string_str(shell->ibuffer);
  const char * ptail = roy_string_str(shell->ibuffer);
  while (*phead != '\0') {
    if (!isgraph(*phead)) {
      phead++;
    } else {
      ptail = phead;
      do { ptail++; } while (isgraph(*ptail));
      char arg[MAX_LEN + 1] = "\0";
      strncpy(arg, phead, ptail - phead);
      roy_deque_push_back(shell->argv, arg);
      phead = ptail;
    }
  }
  if (roy_shell_argument_count(shell) != 0 &&
      !roy_map_find(shell->dict, roy_shell_argument_at(shell, 0))) {
    roy_deque_push_front(shell->argv, "");
  }
}
