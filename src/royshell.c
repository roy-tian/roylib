#include "../include/royshell.h"

static RoyDeque * parse(RoyDeque * parsed, const char * line);

RoyShell *
roy_shell_new(void) {
  RoyShell * ret = (RoyShell *)malloc(sizeof(RoyShell));
  ret->line_history = roy_deque_new(sizeof(char) * (STRING_CAPACITY + 1));
  ret->line_parsed = roy_deque_new(sizeof(char) * (STRING_CAPACITY + 1));
  ret->cmd_dict = roy_map_new(STRING_CAPACITY + 1,
                              sizeof(void(*)(void *)),
                              ROY_COMPARE(strcmp));
  return ret;
}

void
roy_shell_delete(RoyShell * shell) {
  roy_deque_delete(shell->line_history);
  roy_deque_delete(shell->line_parsed);
  roy_map_clear(shell->cmd_dict);
  free(shell);
}

void
roy_shell_start(RoyShell * shell) {
  ROY_STRING(line, STRING_CAPACITY)
  while (true) {
    printf("> ");
    fgets(line, STRING_CAPACITY, stdin);
    roy_deque_push_back(shell->line_history, line);
    parse(shell->line_parsed, line);
    
    void * func = roy_map_find(shell->cmd_dict,
                               roy_deque_const_front(shell->line_parsed));
    if (!func) {
      func = roy_map_find(shell->cmd_dict, "");
    }
    ((void(*)(RoyDeque *))func)(shell->line_parsed);
  }
}

RoyShell *
roy_shell_add_command(RoyShell * shell, const char * cmd, void(*operate)(void *)) {
  roy_map_insert(shell->cmd_dict, cmd, operate);
  return shell;
}

static RoyDeque *
parse(RoyDeque   * parsed,
      const char * line) {
  roy_deque_clear(parsed);
  const char * phead = line;
  const char * ptail = line;
  while (*phead != '\n') {
    if (!isgraph(*phead)) {
      phead++;
    } else {
      ptail = phead;
      do {
        ptail++;
      } while (isgraph(*ptail));
      ROY_STRING(arg, STRING_CAPACITY)
      strncpy(arg, phead, ptail - phead);
      roy_deque_push_back(parsed, arg);
      phead = ptail;
    }
  }
  return parsed;
}