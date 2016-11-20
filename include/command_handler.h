#ifndef __COMMAND_HANDLER_H__
#define __COMMAND_HANDLER_H__

struct Game;
typedef int (*processing_fct)(struct Game* game);

/*
 * @name   : check_argument_is_integer
 * @arg    : argument , char* argument that's we want to check if he is an integer
 * @desc   : This function is use to see if an argument of char* type can be consider as an
             integer value. Ie : this function return true only if the argument string contain
	     only number where just the first caracter can be '+' or '-', has in value in
	     INT_MIN and INT_MAX range and have no errno error when trying to convert with strtol
 *
 * @return : return 1 if argument is integer, 0 otherwise
*/
int check_argument_is_integer(char* argument);

/*
 * @name   : check_argument_is_integer_in_range
 * @arg    : argument , char* argument that's we want to check if he is an integer in range
 * @arg    : min , min range that's we want to check for integer
 * @arg    : max , max range that's we want to check for integer
 * @desc   : This function is use to see if an argument of char* type can be consider as an
             integer value in specific range. Ie : this function return true only if the 
	     argument string contain only number where just the first caracter can be '+' or '-',
	     has in value in min and max range and have no errno error when trying to 
	     convert with strtol
 *
 * @return : return 1 if argument is integer, 0 otherwise
*/
int check_argument_is_integer_in_range(char* argument, int min, int max);

/*
 * @name   : get_action_from_command
 * @arg    : command, command that's we want to test to convert as a function
 * @desc   : This function is use to get a function from a command by associating char* to
             a function pointer. This function use static global variables declare in this header
	     with associability by index
 * 
 * @return : function pointer on action to make, NULL if command cannot be associate
*/
processing_fct get_action_from_command(const char* command);

/*
 * @name   : get_command_from_user
 * @desc   : This function is use to get a command from user. Define in head of the C file 
             is define as 100 for max size user command input because there is no need for more
	     This function simply return the enter command as an allocate pointer so take care to
	     free him if he's not null
 *
 * @return : return pointer on char* if command is valid, NULL otherwise
*/
char* get_command_from_user();

#endif
