#include "../include/royshell.h"
#include "../include/roypointer.h"
#include "../include/roystring.h"

static void parse(RoyShell * shell, const char * line);

enum {
  MAX_LEN = 255,
  ARG_LEN = 63
};

RoyShell *
roy_shell_new(void) {
  RoyShell * ret = (RoyShell *)malloc(sizeof(RoyShell));
  ret->prompt    = (char *)calloc(MAX_LEN + 1, sizeof(char));
  roy_shell_set_prompt_text(ret, "> ");
  ret->ibuffer   = (char *)calloc(MAX_LEN + 1, sizeof(char));
  ret->obuffer   = (char *)calloc(MAX_LEN + 1, sizeof(char));
  ret->dict      = roy_map_new(sizeof(char) * (ARG_LEN + 1),
                               sizeof(RoyPointer),
                               ROY_COMPARE(strcmp));
  ret->argv      = roy_deque_new(sizeof(char) * (ARG_LEN + 1));
  ret->ihistory  = roy_deque_new(sizeof(char) * (MAX_LEN + 1));
  ret->ohistory  = roy_deque_new(sizeof(char) * (MAX_LEN + 1));
  return ret;
}

void
roy_shell_delete(RoyShell * shell) {
  free(shell->prompt);
  free(shell->ibuffer);
  free(shell->obuffer);
  roy_map_clear(shell->dict);
  roy_deque_delete(shell->argv);
  roy_deque_delete(shell->ihistory);
  roy_deque_delete(shell->ohistory);
  free(shell);
}

static bool str_all_space(const char * str) {
  while (*str != '\0') {
    if (!isspace(*str)) {
      return false;
    }
    str++;
  }
  return true;
}

void
roy_shell_start(RoyShell * shell) {
  while (true) {
    printf("%s", shell->prompt);
    memset(shell->ibuffer, '\0', MAX_LEN);
    fgets(shell->ibuffer, MAX_LEN, stdin);
    *(shell->ibuffer + strlen(shell->ibuffer) - 1) = '\0'; // trims '\n'
    if (strlen(shell->ibuffer) != 0 && !str_all_space(shell->ibuffer)) {
      parse(shell, shell->ibuffer);
      void (* func)(RoyShell *) = 
      roy_pointer_get(roy_map_at(shell->dict,
                                 RoyPointer,
                                 roy_shell_argument_at(shell, 0)));
      if (func) {
        roy_shell_log_clear(shell);
        func(shell);
        if (strlen(shell->obuffer) != 0) {
          puts(shell->obuffer);
        }
      }
      roy_deque_push_back(shell->ihistory, shell->ibuffer);
      roy_deque_push_back(shell->ohistory, shell->obuffer);
    }
  }
}

RoyShell *
roy_shell_command_add(RoyShell   * shell,
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
                      size_t           position) {
  return (const char *) roy_deque_cpointer(shell->argv, position);
}

int
roy_shell_argument_find(const RoyShell * shell,
                        const char     * regex) {
  RoyString * arg = roy_string_new();
  for (size_t i = 0; i != roy_shell_argument_count(shell); i++) {
    roy_string_assign(arg, roy_shell_argument_at(shell, i));
    if (roy_string_match(arg, regex)) {
      roy_string_delete(arg);
      return i;
    }
  }
  roy_string_delete(arg);
  return -1; // not found. (0 indicates the cmd itself)
}

RoyShell *
roy_shell_log_clear(RoyShell * shell) {
  memset(shell->obuffer, '\0', MAX_LEN);
  return shell;
}

RoyShell *
roy_shell_log_append(RoyShell   * shell,
                     const char * format,
                     ...) {
  va_list args;
  va_start(args, format);
  vsprintf(shell->obuffer, format, args);
  va_end(args);
  return shell;
}

const char *
roy_shell_ihistory_at(const RoyShell * shell,
                      size_t           position) {
  return (const char *) roy_deque_cpointer(shell->ihistory, position);
}

const char *
roy_shell_ohistory_at(const RoyShell * shell,
                      size_t           position) {
  return (const char *) roy_deque_cpointer(shell->ohistory, position);
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
