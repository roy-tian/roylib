#include "royshell.h"
#include "trivials/royfunction.h"
#include "trivials/roypair.h"

static void tokenize(RoyShell * shell);

enum {
  MAX_LEN = 1023,
};

void pair_deleter(RoyPair * pair) {
  roy_string_delete(pair->key);
  roy_function_delete(pair->value);
  free(pair);
  pair = NULL;
}

RoyShell *
roy_shell_new(void) {
  RoyShell * ret = (RoyShell *)malloc(sizeof(RoyShell));
  ret->dict      = roy_map_new((RCompare)roy_string_compare, (ROperate)pair_deleter);
  ret->prompt    = roy_string_new("> ");
  ret->ibuffer   = roy_string_new("");
  ret->obuffer   = roy_string_new("");
  ret->argv      = roy_deque_new((ROperate)roy_string_delete);
  ret->ihistory  = roy_deque_new((ROperate)roy_string_delete);
  ret->ohistory  = roy_deque_new((ROperate)roy_string_delete);
  return ret;
}

void
roy_shell_delete(RoyShell * shell) {
  roy_deque_delete(shell->ohistory);
  roy_deque_delete(shell->ihistory);
  roy_deque_delete(shell->argv);
  roy_string_delete(shell->obuffer);
  roy_string_delete(shell->ibuffer);
  roy_string_delete(shell->prompt);
  roy_map_delete(shell->dict);
  free(shell);
}

void
roy_shell_start(RoyShell * shell) {
  enum { BUFFER_SIZE = 1023 };
  while (true) {
    roy_string_print(shell->prompt);
    roy_string_clear(shell->ibuffer);
    fgets(roy_string_str(shell->ibuffer), BUFFER_SIZE, stdin);
    roy_string_erase_right(shell->ibuffer, 1); // trims '\n' at tail.
    if (roy_string_match(shell->ibuffer, "\\s+")) {
      roy_string_clear(shell->obuffer);
      tokenize(shell);
      RoyString * buf = NULL;
      roy_shell_argument_at(buf, shell, 0);
      ROperate func = 
        roy_function_get( roy_map_at(shell->dict, buf, RoyFunction) );
      if (func) {
        func(shell); // clients should push all output to obuffer in func.
      }
      roy_deque_push_back(shell->ihistory, shell->ibuffer);
      roy_deque_push_back(shell->ohistory, shell->obuffer);
    }
  }
}

RoyShell *
roy_shell_command_add(RoyShell   * shell,
                      const char * cmd,
                      ROperate     operate) {
  roy_map_insert(shell->dict, roy_string_new(cmd), roy_function_new(operate));
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

RoyString *
roy_shell_argument_at(RoyString      * dest,
                      const RoyShell * shell,
                      size_t           position) {
  dest = roy_deque_at(shell->argv, position, RoyString);
  return dest;
}

int
roy_shell_argument_find(const RoyShell * shell,
                        const char     * regex) {
  for (size_t i = 0; i != roy_shell_argument_count(shell); i++) {
    RoyString * buf = NULL;
    if (roy_string_match( roy_shell_argument_at(buf, shell, i), regex) ) {
      return i;
    }
  }
  return -1; // not found. (0 indicates the cmd itself)
}

RoyShell *
roy_shell_log_clear(RoyShell * shell) {
  roy_string_clear(shell->obuffer);
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

RoyString *
roy_shell_ihistory_at(RoyString      * dest,
                      const RoyShell * shell,
                      size_t           position) {
  dest = roy_deque_at(shell->ihistory, position, RoyString);
  return dest;
}

RoyString *
roy_shell_ohistory_at(RoyString      * dest,
                      const RoyShell * shell,
                      size_t           position) {
  dest = roy_deque_at(shell->ohistory, position, RoyString);
  return dest;
}

/* PRIVATE FUNCTIONS */

static void
tokenize(RoyShell  * shell) {
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
  RoyString * buf = NULL;
  roy_shell_argument_at(buf, shell, 0);
  if (roy_shell_argument_count(shell) != 0 && !roy_map_find(shell->dict, buf)) {
    roy_deque_push_front(shell->argv, "");
  }
}
