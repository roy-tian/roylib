#include "royshell.h"
#include "../trivial/roypair.h"

static void pair_deleter(RoyPair * pair);
static int pair_comparer(const RoyPair * lhs, const RoyPair * rhs);

RoyShell *
roy_shell_new(void) {
  RoyShell * ret = malloc(sizeof(RoyShell));
  ret->dict      = roy_map_new((RCompare)pair_comparer, (ROperate)pair_deleter);
  ret->prompt    = roy_string_new("> ");
  ret->ibuffer   = roy_string_new("");
  ret->obuffer   = roy_string_new("");
  ret->argv      = roy_deque_new((ROperate)roy_string_delete);
  ret->ivector   = roy_deque_new((ROperate)roy_string_delete);
  ret->ovector   = roy_deque_new((ROperate)roy_string_delete);
  return ret;
}

void
roy_shell_delete(RoyShell * shell) {
  roy_deque_delete (shell->ovector);
  roy_deque_delete (shell->ivector);
  roy_deque_delete (shell->argv);
  roy_string_delete(shell->obuffer);
  roy_string_delete(shell->ibuffer);
  roy_string_delete(shell->prompt);
  roy_map_delete   (shell->dict);
  free(shell);
}

void
roy_shell_start(RoyShell * shell) {
  while (true) {
    roy_string_print(shell->prompt);
    roy_string_scan(shell->ibuffer, R_BUF_SIZE);
    if (roy_string_split(shell->argv, shell->ibuffer, "\\s+") > 0) {
      // Clears the out buffer for new info
      roy_string_clear(shell->obuffer);
      // Gets the first token from argv
      ROperate func = roy_map_find(shell->dict, roy_shell_argv_at(shell, 0));
      if (func) {
        func(shell); 
        // Clients take the resposibility to select useful outputs,
        // and push them to 'obuffer' inside 'func'.
      }
      roy_deque_push_back(shell->ivector, roy_string_copy(shell->ibuffer));
      roy_deque_push_back(shell->ovector, roy_string_copy(shell->obuffer));
      roy_deque_clear(shell->argv);
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

void
roy_shell_set_prompt(RoyShell   * shell,
                     ROperate     prompt) {
  prompt ? prompt(shell->prompt) : roy_string_assign(shell->prompt, "> ");
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
                    const char     * pattern) {
  for (size_t i = 0; i != roy_shell_argc(shell); i++) {
    if (roy_shell_argv_match(shell, i, pattern)) {
      return i;
    }
  }
  return -1; // not found. (0 indicates the cmd itself)
}

bool
roy_shell_argv_match(const RoyShell * shell,
                     size_t           position,
                     const char     * pattern) {
  return roy_string_match(roy_shell_argv_at(shell, position), pattern);
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
  vsprintf(roy_string_str(shell->obuffer, 0), format, args);
  va_end(args);
  return shell;
}

RoyString *
roy_shell_in_at(const RoyShell * shell,
                size_t           position) {
  return roy_deque_at(shell->ivector, position, RoyString);
}

RoyString *
roy_shell_out_at(const RoyShell * shell,
                 size_t           position) {
  return roy_deque_at(shell->ovector, position, RoyString);
}

/* PRIVATE FUNCTIONS DOWN HERE */

static void pair_deleter(RoyPair * pair) {
  roy_string_delete(pair->key);
  free(pair);
  pair = NULL;
}

static int pair_comparer(const RoyPair * lhs,
                  const RoyPair * rhs) {
  return roy_string_compare(lhs->key, rhs->key);
}