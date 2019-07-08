#include "../include/royshell.h"

static RoyShell * parse(RoyShell * shell, const char * line);

RoyShell *
roy_shell_new(void) {
  RoyShell * ret = (RoyShell *)malloc(sizeof(RoyShell));
  ret->current = roy_deque_new(sizeof(char) * (STRING_CAPACITY + 1));
  ret->history = roy_deque_new(sizeof(char) * (STRING_CAPACITY + 1));
  ret->dict = roy_map_new(STRING_CAPACITY + 1,
                          sizeof(void(*)(RoyDeque *)),
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
    printf("> ");
    fgets(line, STRING_CAPACITY, stdin);
    if (strlen(line) > 1) { // more than only a '\n'
      *(line + strlen(line) - 1) = '\0';
      roy_deque_push_back(shell->history, line);
      parse(shell, line);
      
      void * func = roy_map_find(shell->dict,
                                 roy_deque_const_front(shell->current));
      (*(void(*)(RoyDeque *))func)(shell->current);
    }
  }
}

RoyShell *
roy_shell_add_command(RoyShell   * shell,
                      const char * cmd,
                      void      (* operate)(RoyDeque *)) {
  roy_map_insert(shell->dict, cmd, operate);
  return shell;
}

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
  if (roy_map_find(shell->dict, roy_deque_const_front(shell->current)) == NULL) {
    roy_deque_push_front(shell->current, "");
  }
  return shell;
}