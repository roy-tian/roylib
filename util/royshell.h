#include "../trivial/royinit.h"
#include "../list/roydeque.h"
#include "../tree/roymap.h"
#include "roystring.h"

struct RoyShell_ {
  RoyMap    * dict;
  RoyString * prompt;
  RoyString * ibuffer;
  RoyString * obuffer;
  RoyDeque  * argv;
  RoyDeque  * ivector;
  RoyDeque  * ovector;
};

/// @brief RoyShell: A simulated shell with simple function.
typedef struct RoyShell_ RoyShell;

/**
 * @brief Creates a RoyShell.
 * @return a pointer to a newly build RoyShell.
 */
RoyShell * roy_shell_new(void);

/**
 * @brief Releases all memory of the given RoyShell.
 * @note - Always call this function after the work is done to get rid of memory leaking.
 */
void roy_shell_delete(RoyShell * shell);

/// @brief Starts a simulation.
void roy_shell_start(RoyShell * shell);

/**
 * @brief Adds a new command into command dictionary of 'shell'.
 * @param cmd - a string literal represented the new command.
 * @param operate - a function pointer to do the operation with current arg vector.
 * @note - A RoyShell must have at least a default command "" (empty string) in order to perform 'roy_shell_start'.
 */
RoyShell * roy_shell_command_add(RoyShell * shell, const char * cmd, ROperate operate);

/// @brief A convenient #define for 'roy_shell_command_add' with identical name of cmd and 'operate' function.
#define roy_shell_add(shell, cmd) roy_shell_command_add(shell, #cmd, (ROperate)cmd)

/// @brief A convenient #define for roy_shell_command_add(shell, "", cmd).
#define roy_shell_default(shell, cmd) roy_shell_command_add(shell, "", (ROperate)cmd)

/**
 * @brief Sets the text of shell prompt, "> " by default.
 * @param prompt - function to set prompt as a new string literal.
 */
void roy_shell_set_prompt(RoyShell * shell, ROperate prompt);

/**
 * @brief Counts the number of arguments of current line.
 * @note The main command is included even if it's empty.
 */
size_t roy_shell_argc(const RoyShell * shell);

/**
 * @brief Returns the text content of specified argument of current argv.
 * @param position - where the argument takes place in current argv.
 */
RoyString * roy_shell_argv_at(const RoyShell * shell, size_t position);

/**
 * @brief Finds specified argument in 'shell'.
 * @param pattern - the argument to be found, regular expressions are supported.
 * @retval N - the position of the found argument.
 * @retval 0 - the cmd itself.
 * @retval -1 - argument not found.
 */
int roy_shell_argv_find(const RoyShell * shell, const char * pattern);

/**
 * @brief Test the specified argument is match the given pattern or not.
 * @param position - the position of the argument vector, 0 represent the cmd itself, argv starts from 1.
 * @param pattern - the argument to be found, regular expressions are supported.
 */
bool roy_shell_argv_match(const RoyShell * shell, size_t position, const char * pattern);

/**
 * @brief Adds new log to the information flow.
 * @param format - a string literal specifying how to interpret the data.
 * @note - The flow can be printed to console and automatically pushed into 'output history' at the end of each round.
 */
RoyShell * roy_shell_log(RoyShell * shell, const RoyString * log);

/**
 * @param position - where the input takes place in input history.
 * @return - the text content of specified input, NULL if position exceeds.
 */
RoyString * roy_shell_in_at(const RoyShell * shell, size_t position);

/**
 * @param position - where the input takes place in output history.
 * @return - the text content of specified output, NULL if position exceeds.
 */
RoyString * roy_shell_out_at(const RoyShell * shell, size_t position);

/// @brief Counts the input/output rounds in shell.
size_t roy_shell_rounds(const RoyShell * shell);