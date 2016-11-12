#ifndef __COMMAND_HANDLER_H__
#define __COMMAND_HANDLER_H__

typedef int (*processing_fct)(Game* game);
int lol_fct(Game*g);

static char* token_list[] = {"wild","rival","nurse","show","switch",
			     "move_table","drop","pick","release","exit",NULL};
static int (*fct_list[])(Game*) = {processing_wild_command,
				   processing_rival_command,
				   processing_nurse,
				   processing_show,
				   processing_switch,
				   processing_move_table,
				   processing_drop,
				   processing_pick,
				   processing_release,
				   processing_exit,
						    /*processing_wild_command,
						      processing_rival_command,
						      processing_nurse_command,
						      processing_show_command,
						      processing_switch_command,
						      processing_move-table_command,
						      processing_drop_command,
						      processing_pick_command,
						      processig_release_command,*/
};

int check_argument_is_integer(char* argument);
int check_argument_is_integer_in_range(char* argument, int min, int max);

processing_fct get_action_from_command(const char* command);
char* get_command_from_user();

#endif
