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
#include "loading_module.h"

#include "evolve_module.h"
#include "factories.h"

#include "battle_module.h"
#include "game.h"
#include "command_handler.h"


#define MAX_SIZE_USER_COMMAND 100
#define BASE_USER 10

int lol_fct(Game* g)
{
  if(g != NULL)
    printf("lol");
  return 1;
}

processing_fct get_action_from_command(const char* command)
{
  int i = 0;
  char* current = token_list[i];
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

int check_argument_is_integer(char* argument)
{
  char* tmp;
  long value;
  
  errno = 0;
  if(argument == NULL)
    return 0;
  
  value = strtol(argument,&tmp,BASE_USER);
  
  return (errno == 0 && value >= INT_MIN && value <= INT_MAX);
}
int check_argument_is_integer_in_range(char* argument, int min, int max)
{
  char* tmp;
  long value;
  
  errno = 0;
  if(argument == NULL)
    return 0;
  
  value = strtol(argument,&tmp,BASE_USER);
  
  return (errno == 0 && value >= min && value <= max);
}
