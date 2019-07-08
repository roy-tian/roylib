#include "royinit.h"
#include "roydeque.h"
#include "roymap.h"

struct _RoyShell {
  RoyDeque * current;
  RoyDeque * history;
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
// A RoyShell must have at least a default cmd "" (empty string) in order to perform 'roy_shell_start'.
RoyShell * roy_shell_add_command(RoyShell * shell, const char * cmd, void(*operate)(RoyDeque *));