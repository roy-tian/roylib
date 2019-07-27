#include "../include/royshell.h"
#include "../include/roypointer.h"

static void parse(RoyShell shell, const char * line);

RoyShell
roy_shell_new(void) {
  RoyShell ret = (RoyShell)malloc(sizeof(struct _RoyShell));
  ret->prompt = roy_string_new_with_content("> ");
  ret->buffer = roy_string_new();
  ret->dict = roy_map_new(sizeof(struct _RoyString),
                          sizeof(struct _RoyPointer),
                          ROY_COMPARE(strcmp));
  ret->argv = roy_deque_new(sizeof(struct _RoyString));
  ret->input_history = roy_deque_new(sizeof(struct _RoyString));
  ret->output_history = roy_deque_new(sizeof(struct _RoyString));
  return ret;
}

void
roy_shell_delete(RoyShell shell) {
  roy_string_delete(shell->prompt);
  roy_string_delete(shell->buffer);
  roy_map_clear(shell->dict);
  roy_deque_delete(shell->argv);
  roy_deque_delete(shell->input_history);
  roy_deque_delete(shell->output_history);
  free(shell);
}

void
roy_shell_start(RoyShell shell) {
  char input[STRING_CAPACITY + 1] = "\0";
  while (true) {
    printf("%s", roy_string_str(shell->prompt));
    fgets(input, STRING_CAPACITY, stdin);
    *(input + strlen(input) - 1) = '\0'; // trims '\n'
    roy_deque_push_back(shell->input_history, input);
    parse(shell, input);
    if (roy_shell_argument_count(shell) != 0) {
      RoyShellOperator func = (RoyShellOperator)roy_pointer_get(
        roy_map_at(shell->dict, RoyPointer, roy_shell_argument_at(shell, 0)));
      if (func) {
        roy_shell_log_clear(shell);
        func(shell);
        roy_deque_push_back(shell->output_history, shell->buffer);
        if (roy_string_size(shell->buffer) != 0) {
          puts(roy_string_str(shell->buffer));
        }
      }
    }
  }
}

RoyShell
roy_shell_command_add(RoyShell          shell,
                      const char       * cmd,
                      RoyShellOperator   operate) {
  RoyPointer func;
  roy_map_insert(shell->dict, ROY_ELEMENT(cmd), roy_pointer_set(func, operate));
  return shell;
}

RoyShell
roy_shell_set_prompt_text(RoyShell    shell,
                          const char * prompt) {
  roy_string_assign(shell->prompt, prompt);
  return shell;
}

size_t
roy_shell_argument_count(const RoyShell shell) {
  return roy_deque_size(shell->argv);
}

RoyString
roy_shell_argument_at(const RoyShell shell,
                      int              position) {
  return (RoyString)roy_deque_const_pointer(shell->argv, position);
}

RoyShell
roy_shell_log_clear(RoyShell shell) {
  memset(shell->buffer, '\0', STRING_CAPACITY);
  return shell;
}

RoyShell
roy_shell_log_append(RoyShell    shell,
                     const char * format,
                     ...) {
  va_list args;
  va_start(args, format);
  vsprintf(roy_string_str(shell->buffer), format, args);
  va_end(args);
  return shell;
}

RoyString
roy_shell_log_at(const RoyShell shell,
                 int              position) {
  if (position < 0) {
    position += roy_deque_size(shell->output_history);
  }
  return (RoyString)roy_deque_const_pointer(shell->output_history, position);
}

/* PRIVATE FUNCTIONS */

static void
parse(RoyShell    shell,
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
      char arg[STRING_CAPACITY + 1] = "\0";
      strncpy(arg, phead, ptail - phead);
      roy_deque_push_back(shell->argv, arg);
      phead = ptail;
    }
  }
  if (roy_shell_argument_count(shell) != 0 &&
      !roy_map_find(shell->dict, roy_shell_argument_at(shell, 0))) {
    roy_deque_push_front(shell->argv, roy_string_new_with_content(""));
  }
}
