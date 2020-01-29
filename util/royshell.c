#include "royshell.h"
#include "../trivial/roypair.h"

// Tokens will be pushed into argv.
static void tokenize(RoyShell * shell);

enum {
  MAX_LEN = 1023,
};

void pair_deleter(RoyPair * pair) {
  roy_string_delete(pair->key);
  free(pair);
  pair = NULL;
}

int pair_comparer(const RoyPair * lhs,
                  const RoyPair * rhs) {
  return roy_string_compare(lhs->key, rhs->key);
}

RoyShell *
roy_shell_new(void) {
  RoyShell * ret = malloc(sizeof(RoyShell));
  ret->dict      = roy_map_new((RCompare)pair_comparer, (ROperate)pair_deleter);
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
  enum { BUFFER_SIZE = 1024 };
  while (true) {
    roy_string_print(shell->prompt);
    roy_string_scan(shell->ibuffer, BUFFER_SIZE);
    if (roy_string_match(shell->ibuffer, "[\\w\\s]+")) {
      roy_string_clear(shell->obuffer);
      tokenize(shell);
      // Gets the first token from argv
      ROperate func = roy_map_find(shell->dict, roy_shell_argv_at(shell, 0));
      if (func) {
        func(shell); 
        // Clients take the resposibility to select useful outputs,
        // and push them to 'obuffer' in 'func'.
      }
      roy_deque_push_back(shell->ihistory,
                          roy_string_new(roy_string_cstr(shell->ibuffer)));
      roy_deque_push_back(shell->ohistory,
                          roy_string_new(roy_string_cstr(shell->obuffer)));
    }
  }
}

RoyShell *
roy_shell_command_add(RoyShell   * shell,
                      const char * cmd,
                      ROperate     operate) {
  roy_map_insert(shell->dict, roy_string_new(cmd), operate);
  return shell;
}

RoyShell *
roy_shell_set_prompt_text(RoyShell   * shell,
                          const char * prompt) {
  roy_string_assign(shell->prompt, prompt);
  return shell;
}

size_t
roy_shell_argc(const RoyShell * shell) {
  return roy_deque_size(shell->argv);
}

RoyString *
roy_shell_argv_at(const RoyShell * shell,
                      size_t           position) {
  return roy_deque_at(shell->argv, position, RoyString);
}

int
roy_shell_argv_find(const RoyShell * shell,
                        const char     * regex) {
  for (size_t i = 0; i != roy_shell_argc(shell); i++) {
    if (roy_string_match(roy_shell_argv_at(shell, i), regex)) {
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
roy_shell_log(RoyShell   * shell,
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
roy_shell_in_at(const RoyShell * shell,
                      size_t           position) {
  return roy_deque_at(shell->ihistory, position, RoyString);
}

RoyString *
roy_shell_out_at(const RoyShell * shell,
                      size_t           position) {
  return roy_deque_at(shell->ohistory, position, RoyString);
}

/* PRIVATE FUNCTIONS */

static void
tokenize(RoyShell  * shell) {
  roy_deque_clear(shell->argv);
  const char * phead = roy_string_cstr(shell->ibuffer);
  const char * ptail = roy_string_cstr(shell->ibuffer);
  while (*phead != '\0') {
    if (!isgraph(*phead)) {
      phead++;
    } else {
      ptail = phead;
      do {
        ptail++;
      } while (isgraph(*ptail));
      char arg[ptail - phead + 1];
      strncpy(arg, phead, ptail - phead);
      arg[ptail - phead] = '\0';
      roy_deque_push_back(shell->argv, roy_string_new(arg));
      phead = ptail;
    }
  }
  if (roy_shell_argc(shell) != 0 &&
      !roy_map_find(shell->dict, roy_shell_argv_at(shell, 0))) {
    roy_deque_push_front(shell->argv, roy_string_new(NULL));
  }
}
