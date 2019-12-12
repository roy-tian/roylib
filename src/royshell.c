#include "royshell.h"
#include "trivials/royfunction.h"
#include "trivials/roypair.h"

static void tokenize(RoyShell * shell);
static void pos_correct(const RoyDeque * deque, size_t * position);

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
  shell = NULL;
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
      ROperate func = 
        roy_function_get( roy_map_at(shell->dict,
                                     roy_shell_argument_at(shell, 0),
                                     RoyFunction) );
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
roy_shell_argument_at(const RoyShell * shell,
                      size_t           position) {
  pos_correct(shell->argv, &position);
  return roy_deque_at(shell->argv, position, RoyString);
}

int
roy_shell_argument_find(const RoyShell * shell,
                        const char     * regex) {
  for (size_t i = 0; i != roy_shell_argument_count(shell); i++) {
    if (roy_string_match(roy_shell_argument_at(shell, i), regex)) {
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
roy_shell_ihistory_at(const RoyShell * shell,
                      size_t           position) {
  pos_correct(shell->ihistory, &position);
  return roy_deque_at(shell->ihistory, position, RoyString);
}

RoyString *
roy_shell_ohistory_at(const RoyShell * shell,
                      size_t           position) {
  pos_correct(shell->ohistory, &position);
  return roy_deque_at(shell->ohistory, position, RoyString);
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
  if (roy_shell_argument_count(shell) != 0 &&
      !roy_map_find(shell->dict, roy_shell_argument_at(shell, 0))) {
    roy_deque_push_front(shell->argv, "");
  }
}

static void
pos_correct(const RoyDeque * deque,
            size_t         * position) {
  if (*position >= roy_deque_size(deque)) {
    *position = roy_deque_size(deque) - 1;
  } 
}