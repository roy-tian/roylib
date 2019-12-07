#include "trivials/royinit.h"
#include "roydeque.h"
#include "roymap.h"
#include "roystring.h"

struct RoyShell_ {
  RoyMap    * dict;
  RoyString * prompt;
  RoyString * ibuffer;
  RoyString * obuffer;
  RoyDeque  * argv;
  RoyDeque  * ihistory;
  RoyDeque  * ohistory;
};

// RoyShell: A simulated shell with simple function.
typedef struct RoyShell_ RoyShell;

// Returns a pointer to a newly build RoyShell.
RoyShell * roy_shell_new(void);

// De-allocates the memory allocated by 'roy_shell_new'.
void roy_shell_delete(RoyShell * shell);

// Starts a simulation.
void roy_shell_start(RoyShell * shell);

// Adds a new command 'cmd' with function 'operate' into command dictionary of 'shell'.
// A RoyShell must have at least a default command "" (empty string) in order to perform 'roy_shell_start'.
RoyShell * roy_shell_command_add(RoyShell * shell, const char * cmd, ROperate operate);

// A convenient #define for 'roy_shell_command_add'.
#define roy_shell_add(shell, cmd) roy_shell_command_add(shell, #cmd, cmd)

// A convenient #define for 'roy_shell_command_add' replaces roy_shell_command_add(shell, "", cmd).
#define roy_shell_default(shell, cmd) roy_shell_command_add(shell, "", cmd)

// Sets the shell prompt to any string you like, "> " by default.
RoyShell * roy_shell_set_prompt_text(RoyShell * shell, const char * prompt);

// Counts the number of arguments of current line, the main command is included even if it's empty.
size_t roy_shell_argument_count(const RoyShell * shell);

// Returns the text of the 'position'-th arguments.
RoyString * roy_shell_argument_at(const RoyShell * shell, size_t position);

// Returns whether the current command line has any argument matches 'regex' or not.
int roy_shell_argument_find(const RoyShell * shell, const char * regex);

// Clears the log buffer for a new info to be logged.
RoyShell * roy_shell_log_clear(RoyShell * shell);

// Adds new log to the information flow, at the end of each round, the info will be printed to console and push into 'ohistory' in one time.
RoyShell * roy_shell_log_append(RoyShell * shell, const char * format, ...);

// Returns the number of input/output operations.
size_t roy_shell_history_count(const RoyShell * shell);

// Shows input history anytime you like, position < 0 will show reversely.
RoyString * roy_shell_ihistory_at(const RoyShell * shell, size_t position);

// Shows output history anytime you like, position < 0 will show reversely.
RoyString * roy_shell_ohistory_at(const RoyShell * shell, size_t position);