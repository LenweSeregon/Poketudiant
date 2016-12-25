#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#include "math_utils.h"
#include "string_utils.h"

#include "container.h"
#include "linked_list.h"
#include "hash_table.h"

#include "type_poke.h"
#include "attack.h"
#include "poketudiant.h"

#include "pokecafetaria.h"
#include "trainer.h"
#include "weakness.h"


#include "generic_control_function.h"
#include "evolve_module.h"
#include "factories.h"
#include "loading_module.h"


#include "battle_module.h"
#include "constantes.h"
#include "map.h"
#include "game.h"
#include "command_handler.h"

static char* token_list[] = {"wild","rival","nurse","show","switch",
			     "move-table","drop","pick","release","exit","catch","xp",
			     "z","s","q","d",NULL};
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
				   processing_catch,
				   processing_xp,
				   processing_z_move,
				   processing_s_move,
				   processing_q_move,
				   processing_d_move
};


processing_fct get_action_from_command(const char* command)
{
  int i = 0;
  char* current = token_list[i];

  if(command == NULL)
    {
      return NULL;
    }

  while(current)
    {
      if(strcmp(current,command) == 0)
	{
	  return fct_list[i];
	}
      current = token_list[++i]; 
    }
  return NULL;
}

char* get_command_from_user()
{
  char user_command[MAX_SIZE_USER_COMMAND] = {0};
  
  if(fgets(user_command,MAX_SIZE_USER_COMMAND,stdin) != NULL)
    {
      char* position_end_line = strchr(user_command, '\n');
      if(position_end_line != NULL)
	{
	  char* string = malloc(sizeof(char) * MAX_SIZE_USER_COMMAND);
	  strcpy(string,user_command);
	  return string;
	}
      else
	{
	  printf("Bad boy ! Commands doesn't need so much character ! Tring an overflow is not cool !\n");
	  empty_buffer();
	  return NULL;
	}
    }
  else
    {
      printf("Error in reading commands, respect commands's format\n");
      empty_buffer();
      return NULL;
    }
}

int is_real_integer(const char* string)
{
  char* c;
  if(string == NULL)
    {
      return 0;
    }
  
  c = (char*)string;
  if(*c == '-' || *c == '+')
    {
      c++;
    }
  while(*c != '\0')
    {
      if(!(*c >= '0' && *c <= '9'))
	{
	  return 0;
	} 
      c++;
    }
  return 1;
}

int check_argument_is_integer(char* argument)
{
  char* tmp;
  long value;
  
  errno = 0;
  if(argument == NULL)
    return 0;
  
  value = strtol(argument,&tmp,BASE_USER);
  
  return (is_real_integer(argument) && errno == 0 && value >= INT_MIN && value <= INT_MAX);
}
int check_argument_is_integer_in_range(char* argument, int min, int max)
{
  char* tmp;
  long value;
  
  errno = 0;
  if(argument == NULL)
    return 0;
  
  value = strtol(argument,&tmp,BASE_USER);
  
  return (is_real_integer(argument) && errno == 0 && value >= min && value <= max);
}
