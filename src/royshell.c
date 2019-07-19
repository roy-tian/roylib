#include "../include/royshell.h"
#include "../include/roypointer.h"

static void parse(RoyShell * shell, const char * line);

RoyShell *
roy_shell_new(void) {
  RoyShell * ret = (RoyShell *)malloc(sizeof(RoyShell));
  ret->prompt = (char *)calloc(STRING_CAPACITY + 1, sizeof(char));
  roy_shell_set_prompt_text(ret, "> ");
  ret->dict = roy_map_new(sizeof(char) * STRING_CAPACITY + 1,
                          sizeof(RoyPointer),
                          ROY_COMPARE(strcmp));
  ret->argv = roy_deque_new(sizeof(char) * (STRING_CAPACITY + 1));
  ret->input_history = roy_deque_new(sizeof(char) * (STRING_CAPACITY + 1));
  ret->output_history = roy_deque_new(sizeof(char) * (STRING_CAPACITY + 1));
  return ret;
}

void
roy_shell_delete(RoyShell * shell) {
  free(shell->prompt);
  roy_map_clear(shell->dict);
  roy_deque_delete(shell->argv);
  roy_deque_delete(shell->input_history);
  roy_deque_delete(shell->output_history);
  free(shell);
}

void
roy_shell_start(RoyShell * shell) {
  char input[STRING_CAPACITY + 1] = "\0";
  char output[STRING_CAPACITY + 1] = "\0";
  while (true) {
    printf("%s", shell->prompt);
    fgets(input, STRING_CAPACITY, stdin);
    *(input + strlen(input) - 1) = '\0'; // trims '\n'
    roy_deque_push_back(shell->input_history, input);
    parse(shell, input);
    if (roy_shell_argument_count(shell) != 0) {
      RoyShellOperator func = (RoyShellOperator)roy_pointer_get(
        roy_map_at(shell->dict, RoyPointer, roy_shell_argument_at(shell, 0)));
      if (func) {
        func(shell, output);
        roy_deque_push_back(shell->output_history, output);
        puts(output);
      }
    }
  }
}

RoyShell *
roy_shell_add_command(RoyShell         * shell,
                      const char       * cmd,
                      RoyShellOperator   operate) {
  RoyPointer func;
  roy_map_insert(shell->dict, cmd, roy_pointer_set(&func, operate));
  return shell;
}

RoyShell *
roy_shell_set_prompt_text(RoyShell   * shell,
                          const char * prompt) {
  strcpy(shell->prompt, prompt);
  return shell;
}

size_t
roy_shell_argument_count(const RoyShell * shell) {
  return roy_deque_size(shell->argv);
}

const char *
roy_shell_argument_at(const RoyShell * shell,
                      int              position) {
  return (const char *)roy_deque_const_pointer(shell->argv, position);
}

/* PRIVATE FUNCTIONS */

static void
parse(RoyShell   * shell,
      const char * line) {
  roy_deque_clear(shell->argv);
  const char * phead = line;
  const char * ptail = line;
  while (*phead != '\0') {
    if (!isgraph(*phead)) {
      phead++;
    } else {
      ptail = phead;
      do { ptail++; } while (isgraph(*ptail));      
      ROY_STRING(arg, STRING_CAPACITY)
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
