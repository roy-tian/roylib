#include "royinit.h"
#include "roydeque.h"
#include "roymap.h"

struct _RoyShell {
  char     * prompt;
  char     * buffer;
  RoyMap   * dict;
  RoyDeque * argv;
  RoyDeque * input_history;
  RoyDeque * output_history;
};

// RoyShell: A simulated shell with simple function.
typedef struct _RoyShell RoyShell;

// When a command is committed, an operator will be invacated.
// If you want to show some info on the result of the operation, pass it into 'output'(make sure it's initialized and redundant).
typedef void (* RoyShellOperator)(RoyShell * shell);

// Returns a pointer to a newly build RoyShell.
RoyShell * roy_shell_new(void);

// Deallocates the memory allocated by 'roy_shell_new'.
void roy_shell_delete(RoyShell * shell);

// Starts a simulation.
void roy_shell_start(RoyShell * shell);

// Adds a new command 'cmd' with function 'operate' into command dictionary of 'shell'.
// A RoyShell must have at least a default command "" (empty string) in order to perform 'roy_shell_start'.
RoyShell * roy_shell_command_add(RoyShell * shell, const char * cmd, RoyShellOperator operate);

// Sets the shell prompt to any string you like, "> " by default.
RoyShell * roy_shell_set_prompt_text(RoyShell * shell, const char * prompt);

// Counts the number of arguments of current line, the main command is included even if its empty.
size_t roy_shell_argument_count(const RoyShell * shell);

// Returns the text of the 'position'-th arguments.
const char * roy_shell_argument_at(const RoyShell * shell, int position);

RoyShell * roy_shell_output_append(RoyShell * shell, const char * output);
