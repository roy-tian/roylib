#include "royinit.h"
#include "roydeque.h"
#include "roymap.h"

struct _RoyShell {
  char     * prompt;
  char     * ibuffer;
  char     * obuffer;
  RoyMap   * dict;
  RoyDeque * argv;
  RoyDeque * ihistory;
  RoyDeque * ohistory;
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
RoyShell * roy_shell_command_add(RoyShell * shell, const char * cmd, void (* operate)(RoyShell *));

// Sets the shell prompt to any string you like, "> " by default.
RoyShell * roy_shell_set_prompt_text(RoyShell * shell, const char * prompt);

// Counts the number of arguments of current line, the main command is included even if it's empty.
size_t roy_shell_argument_count(const RoyShell * shell);

// Returns the text of the 'position'-th arguments.
const char * roy_shell_argument_at(const RoyShell * shell, int position);

// Returns whether the argument 'arg' is in 'shell'.
int roy_shell_argument_find(const RoyShell * shell, const char * regex);

// Clears the log buffer for a new info to be logged.
RoyShell * roy_shell_log_clear(RoyShell * shell);

// Adds new info to the info flow, at the end of each round, all info will be print to console and push into 'ohistory' in one time.
RoyShell * roy_shell_log_append(RoyShell * shell, const char * format, ...);

// Returns the number of input/output operations.
size_t roy_shell_history_count(const RoyShell * shell);

// Shows input history anytime you like, position < 0 will show reversely.
const char * roy_shell_ihistory_at(const RoyShell * shell, int position);

// Shows output history anytime you like, position < 0 will show reversely.
const char * roy_shell_ohistory_at(const RoyShell * shell, int position);