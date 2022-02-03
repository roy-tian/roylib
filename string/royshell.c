#include "royshell.h"
#include "../util/rpair.h"

struct RoyShell_ {
  RoyMap    * dict;
  RoyString * prompt;
  RoyString * ibuffer;
  RoyString * obuffer;
  RoyDeque  * argv;
  RoyDeque  * ivector;
  RoyDeque  * ovector;
};

static void pair_deleter(RoyPair * pair, void * user_data);
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
roy_shell_delete(RoyShell * shell,
                 void     * user_data) {
  roy_deque_delete (shell->ovector, user_data);
  roy_deque_delete (shell->ivector, user_data);
  roy_deque_delete (shell->argv,    user_data);
  roy_string_delete(shell->obuffer, user_data);
  roy_string_delete(shell->ibuffer, user_data);
  roy_string_delete(shell->prompt,  user_data);
  roy_map_delete   (shell->dict,    user_data);
  free(shell);
}

void
roy_shell_start(RoyShell * shell) {
  while (true) {
    roy_string_print(shell->prompt);
    roy_string_scan(shell->ibuffer, R_BUF_SIZE);
    roy_deque_clear(shell->argv, NULL);
    if (roy_string_split(shell->argv, shell->ibuffer, "\\s+") > 0) {
      // If cmd (aka first token in argv) cannot be found in dict,
      // push_front a nil string to use default func:
      if (!roy_map_find(shell->dict, roy_shell_argv_at(shell, 0))) {
        roy_deque_push_front(shell->argv, roy_string_new(""));
      }
      // Clears the out buffer for new info to fill with:
      roy_string_clear(shell->obuffer);
      // Gets the cmd (aka the first token in argv):
      ROperate func = roy_map_find(shell->dict, roy_shell_argv_at(shell, 0));
      if (func) {
        func(shell, NULL); 
        // Clients take the resposibility to select useful outputs,
        // and push them to 'obuffer' inside 'func'.
      }
      roy_deque_push_back(shell->ivector, roy_string_copy(shell->ibuffer));
      roy_deque_push_back(shell->ovector, roy_string_copy(shell->obuffer));
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
  prompt ? prompt(shell->prompt, NULL) : roy_string_assign(shell->prompt, "> ");
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
roy_shell_log(RoyShell        * restrict shell,
              const RoyString * restrict log) {
  roy_string_assign(shell->obuffer, roy_string_cstr(log, 0));
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

size_t
roy_shell_rounds(const RoyShell * shell) {
  return roy_deque_size(shell->ivector);
}

/* PRIVATE FUNCTIONS DOWN HERE */

static void
pair_deleter(RoyPair * pair,
             void    * user_data) {
  roy_string_delete(pair->key, user_data);
  free(pair);
  pair = NULL;
}

static int
pair_comparer(const RoyPair * lhs,
              const RoyPair * rhs) {
  return roy_string_compare(lhs->key, rhs->key);
}