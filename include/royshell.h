#include "royinit.h"
#include "roydeque.h"
#include "roymap.h"

struct _RoyShell {
  char       prompt[STRING_CAPACITY + 1];
  char       cmd[STRING_CAPACITY + 1];
  RoyDeque * argv;
  RoyMap   * dict;
};

// RoyShell: A simulated shell with simple function.
typedef struct _RoyShell RoyShell;

// Returns a pointer to a newly build RoyShell.
RoyShell * roy_shell_new(void);

// Deallocates the memory allocated by 'roy_shell_new'.
void roy_shell_delete(RoyShell * shell);

// Starts a simulation.
void roy_shell_start(RoyShell * shell);

// Adds a new command 'cmd' with function 'operate' into command dictionary of 'shell'.
// A RoyShell must have at least a default command "" (empty string) in order to perform 'roy_shell_start'.
RoyShell * roy_shell_add_command(RoyShell * shell, const char * cmd, void(*operate)(RoyShell *));

// Sets the shell prompt to any string you like, "> " by default.
RoyShell * roy_shell_set_prompt_text(RoyShell * shell, const char * prompt);

// Counts the number of arguments of current line, the main command is included even if its empty.
size_t roy_shell_argument_count(const RoyShell * shell);

// Returns the text of the 'position'-th arguments.
const char * roy_shell_argument_at(const RoyShell * shell, int position);

// Returns the text of the 0th argument - the main command.
const char * roy_shell_command(const RoyShell * shell);

// Returns the current line, all spaces are trimed.
const char * roy_shell_line_without_space(const RoyShell * shell);