#include "../include/royshell.h"
#include "../include/roypointer.h"

static void default_parse(RoyShell * shell, const char * line);

RoyShell *
roy_shell_new(void) {
  RoyShell * ret = (RoyShell *)malloc(sizeof(RoyShell));
  *ret->prompt = '\0';
  strcpy(ret->prompt, "> ");
  ret->argv = roy_deque_new(sizeof(char) * (STRING_CAPACITY + 1));
  ret->dict = roy_map_new(sizeof(char) * STRING_CAPACITY + 1,
                          sizeof(RoyPointer),
                          ROY_COMPARE(strcmp));
  ret->parse = default_parse;                          
  return ret;
}

void
roy_shell_delete(RoyShell * shell) {
  roy_deque_delete(shell->argv);
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
      shell->parse(shell, line);
      const void * func = roy_pointer_get(
        roy_map_at(shell->dict,
                   RoyPointer,
                   roy_shell_argument_at(shell, 0)));
      if (func) {
        ((void(*)(RoyShell *))func)(shell);
      }
    }
  }
}

RoyShell *
roy_shell_add_command(RoyShell   * shell,
                      const char * cmd,
                      void      (* operate)(RoyShell *)) {
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
default_parse(RoyShell   * shell,
              const char * line) {
  roy_deque_clear(shell->argv);
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
      roy_deque_push_back(shell->argv, arg);
      phead = ptail;
    }
  }
  if (!roy_map_find(shell->dict, roy_deque_const_front(shell->argv))) {
    roy_deque_push_front(shell->argv, "");
  }
}
