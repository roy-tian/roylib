#include "royinit.h"
#include "roydeque.h"
#include "roymap.h"

struct _RoyShell {
  RoyDeque * line_history;
  RoyDeque * line_parsed;
  RoyMap   * cmd_dict;
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
RoyShell * roy_shell_add_command(RoyShell * shell, const char * cmd, void(*operate)(void *));