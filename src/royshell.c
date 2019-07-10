#include "../include/royshell.h"
#include "../include/roypointer.h"

static RoyShell * parse(RoyShell * shell, const char * line);

RoyShell *
roy_shell_new(void) {
  RoyShell * ret = (RoyShell *)malloc(sizeof(RoyShell));
  strcpy(ret->prompt, "> ");
  ret->current = roy_deque_new(sizeof(char) * (STRING_CAPACITY + 1));
  ret->history = roy_deque_new(sizeof(char) * (STRING_CAPACITY + 1));
  ret->dict = roy_map_new(sizeof(char) * STRING_CAPACITY + 1,
                          sizeof(RoyPointer),
                          ROY_COMPARE(strcmp));
  return ret;
}

void
roy_shell_delete(RoyShell * shell) {
  roy_deque_delete(shell->current);
  roy_deque_delete(shell->history);
  roy_map_clear(shell->dict);
  free(shell);
}

void
roy_shell_start(RoyShell * shell) {
  ROY_STRING(line, STRING_CAPACITY)
  while (true) {
    printf("%s", shell->prompt);
    fgets(line, STRING_CAPACITY, stdin);
    if (strlen(line) > 1) { // more than only a '\n'
      *(line + strlen(line) - 1) = '\0';
      roy_deque_push_back(shell->history, line);
      parse(shell, line);
      const void * func = roy_pointer_get(
        roy_map_at(shell->dict,
                   RoyPointer,
                   roy_deque_const_front(shell->current)));
      if (func) {
        ((void(*)(RoyDeque *))func)(shell->current);
      }
    }
  }
}

RoyShell *
roy_shell_add_command(RoyShell   * shell,
                      const char * cmd,
                      void      (* operate)(RoyDeque *)) {
  RoyPointer func;
  roy_map_insert(shell->dict, cmd, roy_pointer_set(&func, operate));
  return shell;
}

RoyShell * roy_shell_set_prompt_text(RoyShell * shell, const char * prompt) {
  strcpy(shell->prompt, prompt);
  return shell;
}

/* PRIVATE FUNCTIONS */

static RoyShell *
parse(RoyShell   * shell,
      const char * line) {
  roy_deque_clear(shell->current);
  const char * phead = line;
  const char * ptail = line;
  while (*phead != '\0') {
    if (!isgraph(*phead)) {
      phead++;
    } else {
      ptail = phead;
      do {
        ptail++;
      } while (isgraph(*ptail));
      ROY_STRING(arg, STRING_CAPACITY)
      strncpy(arg, phead, ptail - phead);
      roy_deque_push_back(shell->current, arg);
      phead = ptail;
    }
  }
  if (!roy_map_find(shell->dict, roy_deque_const_front(shell->current))) {
    roy_deque_push_front(shell->current, "");
  }
  return shell;
}
