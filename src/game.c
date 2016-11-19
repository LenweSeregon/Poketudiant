#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
#include "weakness.h"
#include "command_handler.h"

#define COMMAND_SEPARATOR " "
#define BASE_USER 10
#define LEVEL_POKETUDIANT_CATCH_COMMAND 1

Game* create_game(const char* trainer_name)
{
  Poketudiant* first_poke;
  Poketudiant* second_poke;

  Poketudiant* poke_cafe1;
  Poketudiant* poke_cafe2;
  Poketudiant* poke_cafe3;
  Game* game = malloc(sizeof(Game));
  /* Initiliaze base collection */
  game->base_poke = create_hash_table(20);
  game->base_att = create_hash_table(20);
  
  game->base_poke->hash_fct = hash_poketudiant_fct_from_poketudiant;
  game->base_poke->print_fct_linked_list = print_poketudiant_fct;
  game->base_poke->free_fct_linked_list = delete_poketudiant_fct;
  game->base_poke->cmp_fct_linked_list = cmp_poketudiant_fct_via_variety;
  game->base_att->hash_fct = hash_attack_fct;
  game->base_att->print_fct_linked_list = print_attack_fct;
  game->base_att->free_fct_linked_list = delete_attack_fct;
  game->base_att->cmp_fct_linked_list = cmp_attack_fct_via_type;
 
  load_base_attack(game->base_att,"init/attacks_file");
  load_base_poketudiant(game->base_poke,"init/pokemons_file");
  
  /* Init game control structure */
  game->weakness = create_weakness();
  load_base_weakness(game->weakness,"init/weakness_file");
  game->factory_poke = create_poketudiant_factory(game->base_poke, game->base_att);
  game->evolve_center = create_evolve_center(game->base_poke);
  game->battle_module = create_battle_module(game->factory_poke,game->evolve_center,game->weakness);
  
  
  /* Init trainer */
  game->trainer = create_trainer(trainer_name,0);
  first_poke = generate_poketudiant_from_name(game->factory_poke,"Enseignant-dresseur",1);
  second_poke = generate_random_capturable_poketudiant(game->factory_poke,1);
  poke_cafe1 = generate_random_capturable_poketudiant(game->factory_poke,1);
  poke_cafe2 = generate_random_capturable_poketudiant(game->factory_poke,1);;
  poke_cafe3 = generate_random_capturable_poketudiant(game->factory_poke,1);;
  add_poketudiant_to_team(game->trainer,first_poke);
  add_poketudiant_to_team(game->trainer,second_poke);
  add_poketudiant_to_team(game->trainer,poke_cafe1);
  add_poketudiant_to_team(game->trainer,poke_cafe2);
  add_poketudiant_to_team(game->trainer,poke_cafe3);
  return game;
}

void delete_game(Game* game)
{
  delete_weakness(game->weakness);
  delete_trainer(game->trainer);
  delete_battle_module(game->battle_module);
  delete_evolve_center(game->evolve_center);
  delete_poketudiant_factory(game->factory_poke);
  delete_hash_table(game->base_poke);
  delete_hash_table(game->base_att);
  free(game);
}

int processing_catch(Game* game)
{
  int accept_command = 1;
  char* nb_poke = strtok(NULL,COMMAND_SEPARATOR);
  /* Verification */
  if(!check_argument_is_integer(nb_poke))
    {
      printf("Your first argument must be an integer representing number of poketudiant\n");
      accept_command = 0;
    }
  if(strtok(NULL,COMMAND_SEPARATOR) != NULL)
    {
      printf("You have more than 1 argument !\n");
      accept_command = 0;
    }
  /* Processing */
  if(accept_command)
    {
      int i;
      char* tmp;
      int nb = strtol(nb_poke,&tmp,BASE_USER);
      for(i = 0; i < nb; i++)
	{
	  Poketudiant* poke = generate_random_capturable_poketudiant(game->factory_poke,
								     LEVEL_POKETUDIANT_CATCH_COMMAND);
	  
	  add_poketudiant_to_team(game->trainer,poke);
	}
      return 1;
    }
  else
    {
      printf("Catch aborted because of command error\n");
      return 1;
    }
}

int processing_xp(Game* game)
{
  int accept_command = 1;
  char* id = strtok(NULL,COMMAND_SEPARATOR);
  char* nb = strtok(NULL,COMMAND_SEPARATOR);

  /* Checking */
  if(!check_argument_is_integer(id))
    {
      printf("Your first argument must be an integer representing number of poketudiant\n");
      accept_command = 0;
    }
  if(!check_argument_is_integer(nb))
    {
      printf("Your second argument must be an integer representing number of poketudiant\n");
      accept_command = 0;
    }
  if(strtok(NULL,COMMAND_SEPARATOR) != NULL)
    {
      printf("You have more than 2 argument !\n");
      accept_command = 0;
    }
  /* Processing */
  if(accept_command)
    {
      char* tmp;
      Poketudiant* poke;
      int id_i = strtol(id,&tmp,BASE_USER);
      int nb_i = strtol(nb,&tmp,BASE_USER);
      
      poke = select_poketudiant_by_id_in_trainer(game->trainer,id_i);
      if(poke != NULL)
	{
	  if(earn_experience(poke,nb_i))
	    {
	      make_poketudiant_upgrade(game->evolve_center,poke);
	    }
	}
      else
	{
	  printf("There is no poketudiant with that's id in trainer team or cafetaria !\n");
	}
      return 1;
    }
  else
    {
      printf("Xp aborted because of command error\n");
      return 1;
    }
}

int processing_exit(Game* game)
{
  if(strtok(NULL,COMMAND_SEPARATOR) != NULL || game == NULL)
    {
      printf("You have an argument that's not needed\n");
      return 1;
    }
  return 0;
}

int processing_wild_command(Game* game)
{
  int accept_command = 1;
  char* min_level = strtok(NULL,COMMAND_SEPARATOR);
  char* max_level = strtok(NULL,COMMAND_SEPARATOR);
  /* Verification */
  if(!check_argument_is_integer_in_range(min_level,1,10))
    {
      printf("First argument unavailable or inexistent\n");
      accept_command = 0;
    }
  if(!check_argument_is_integer_in_range(max_level,1,10))
    {
      printf("Second argument unavailable or inexistent\n");
      accept_command = 0;
    }
  if(strtok(NULL,COMMAND_SEPARATOR) != NULL)
    {
      printf("You have more than 2 arguments !\n");
      accept_command = 0;
    }
  /* Processing*/
  if(accept_command)
    {
      char* tmp;
      int min = strtol(min_level,&tmp,BASE_USER);
      int max = strtol(max_level,&tmp,BASE_USER);
      if(min > max)
	{
	  printf("You min level is higher than your max level..\n");
	  return 1;
	}
      else
	{
	  int res = trainer_versus_random_wild_poketudiant(game->battle_module,game->trainer,min,max); 
	  empty_buffer();
	  return res; 
	}
    }
  else
    {
      printf("Battle aborted because of command error\n");
      return 1;
    }
}

int processing_rival_command(Game* game)
{
  int accept_command = 1;
  char* min_level = strtok(NULL,COMMAND_SEPARATOR);
  char* max_level = strtok(NULL,COMMAND_SEPARATOR);
  /* Verification */
  if(!check_argument_is_integer_in_range(min_level,1,10))
    {
      printf("First argument unavailable or inexistent\n");
      accept_command = 0;
    }
  if(!check_argument_is_integer_in_range(max_level,1,10))
    {
      printf("Second argument unavailable or inexistent\n");
      accept_command = 0;
    }
  if(strtok(NULL,COMMAND_SEPARATOR) != NULL)
    {
      printf("You have more than 2 arguments !\n");
      accept_command = 0;
    }
  /* Processing*/
  if(accept_command)
    {
      char* tmp;
      int min = strtol(min_level,&tmp,BASE_USER);
      int max = strtol(max_level,&tmp,BASE_USER);
      if(min > max)
	{
	  printf("You min level is higher than your max level..\n");
	  return 1;
	}
      else
	{
	  int res = trainer_versus_random_trainer(game->battle_module,game->trainer,min,max);
	  empty_buffer();
	  return res;
	}
    }
  else
    {
      empty_buffer();
      return 1;
    }
}

int processing_nurse(Game* game)
{
  if(strtok(NULL,COMMAND_SEPARATOR) != NULL)
    {
      printf("This action shoudn't take arguments !\n");
    }
  else
    {
      heal_all_team(game->trainer);
    }
  return 1;
}

int processing_show(Game* game)
{
  char* arg_1 = strtok(NULL,COMMAND_SEPARATOR);
  char* arg_2 = strtok(NULL,COMMAND_SEPARATOR);

  if(arg_1 == NULL)
    {
      printf("You need at least 1 argument for show !\n");
      return 1;
    }
  
  if(strcmp(arg_1,"team") == 0)
    {
      if(arg_2 != NULL)
	{
	  printf("You don't need any other argument for show team !\n");
	  return 1;
	}
      /* Action */
      print_team(game->trainer);
      return 1;
    }
  else if(strcmp(arg_1,"pokecafeteria") == 0)
    {
      if(arg_2 != NULL)
	{
	  printf("You don't need any other argument for show pokecafeteria !\n");
	  return 1;
	}
      /* Action */
      print_trainer_cafetaria(game->trainer);
      return 1;
    }
  else if(strcmp(arg_1,"revision-table") == 0)
    {
      if(!check_argument_is_integer(arg_2))
	{
	  printf("Argument i in show revision-table i must be an integer\n");
	  return 1;
	}
      else
	{
	  char* tmp;
	  int table = strtol(arg_2,&tmp,BASE_USER);
	  print_trainer_revision_table_t(game->trainer,table);
	  return 1;
	}
    }
  else if(strcmp(arg_1,"ma-bite") == 0)
    {
      printf("Ca passe pas dans l'écran !\n");
      return 1;
    }
  else /* We want to show a special poketudiant by id */
    {
      if(arg_2 != NULL)
	{
	  printf("You don't need any other argument for show i !\n");
	  return 1;
	}
      else /* Action */
	{
	  if(!check_argument_is_integer(arg_1))
	    {
	      printf("Argument i in show i must be an integer\n");
	      return 1;
	    }
	  else
	    {
	      char* tmp;
	      int id = strtol(arg_1,&tmp,BASE_USER);
	      print_poketudiant_id_from_trainer(game->trainer,id);
	      return 1;
	    }
	}
    }
}

int processing_switch(Game* game)
{
  int accept_command = 1;
  char* id_1 = strtok(NULL,COMMAND_SEPARATOR);
  char* id_2 = strtok(NULL,COMMAND_SEPARATOR);
  /* Verification */
  if(!check_argument_is_integer(id_1))
    {
      printf("First argument unavailable or inexistent\n");
      accept_command = 0;
    }
  if(!check_argument_is_integer(id_2))
    {
      printf("First argument unavailable or inexistent\n");
      accept_command = 0;
    }
  if(strtok(NULL,COMMAND_SEPARATOR) != NULL)
    {
      printf("You have more than 2 arguments !\n");
      accept_command = 0;
    }

  if(accept_command)
    {
      char* tmp;
      int id_1_i = strtol(id_1,&tmp,BASE_USER);
      int id_2_i = strtol(id_2,&tmp,BASE_USER);
      swap_poketudiant(game->trainer,id_1_i,id_2_i);
    }
  else
    {
      printf("Switch aborted because of command error\n");
    }
  
  return 1;
}

int processing_move_table(Game* game)
{
  int accept_command = 1;
  char* id_1 = strtok(NULL,COMMAND_SEPARATOR);
  char* id_2 = strtok(NULL,COMMAND_SEPARATOR);
  /* Verification */
  if(!check_argument_is_integer(id_1))
    {
      printf("First argument unavailable or inexistent\n");
      accept_command = 0;
    }
  if(!check_argument_is_integer(id_2))
    {
      printf("First argument unavailable or inexistent\n");
      accept_command = 0;
    }
  if(strtok(NULL,COMMAND_SEPARATOR) != NULL)
    {
      printf("You have more than 2 arguments !\n");
      accept_command = 0;
    }

  if(accept_command)
    {
      char* tmp;
      int id_1_i = strtol(id_1,&tmp,BASE_USER);
      int id_2_i = strtol(id_2,&tmp,BASE_USER);
      /* Somethings */
      
      move_table_poketudiant(game->trainer,id_1_i,id_2_i);
    }
  else
    {
      printf("Move-table aborted because of command error\n");
    }

  return 1;
}

int processing_drop(Game* game)
{
  int accept_command = 1;
  char* id_s = strtok(NULL,COMMAND_SEPARATOR);
  /* Verification */
  if(!check_argument_is_integer(id_s))
    {
      printf("First argument unavailable or inexistent\n");
      accept_command = 0;
    }
  if(strtok(NULL,COMMAND_SEPARATOR) != NULL)
    {
      printf("You have more than 2 arguments !\n");
      accept_command = 0;
    }
  /* Processing*/
  if(accept_command)
    {
      char* tmp;
      int id = strtol(id_s,&tmp,BASE_USER);
      drop_to_pokecafetaria(game->trainer,id);
      return 1;
    }
  else
    {
      printf("Battle aborted because of command error\n");
      return 1;
    }
}

int processing_pick(Game* game)
{
  int accept_command = 1;
  char* id_s = strtok(NULL,COMMAND_SEPARATOR);
  /* Verification */
  if(!check_argument_is_integer(id_s))
    {
      printf("First argument unavailable or inexistent\n");
      accept_command = 0;
    }
  if(strtok(NULL,COMMAND_SEPARATOR) != NULL)
    {
      printf("You have more than 2 arguments !\n");
      accept_command = 0;
    }
  /* Processing*/
  if(accept_command)
    {
      char* tmp;
      int id = strtol(id_s,&tmp,BASE_USER);
      pick_from_pokecafetaria(game->trainer,id);
      return 1;
    }
  else
    {
      printf("Battle aborted because of command error\n");
      return 1;
    }
}

int processing_release(Game* game)
{
  int accept_command = 1;
  char* id_s = strtok(NULL,COMMAND_SEPARATOR);
  /* Verification */
  if(!check_argument_is_integer(id_s))
    {
      printf("First argument unavailable or inexistent\n");
      accept_command = 0;
    }
  if(strtok(NULL,COMMAND_SEPARATOR) != NULL)
    {
      printf("You have more than 2 arguments !\n");
      accept_command = 0;
    }
  /* Processing*/
  if(accept_command)
    {
      char* tmp;
      int id = strtol(id_s,&tmp,BASE_USER);
      release_from_pokecafetaria(game->trainer,id);
      return 1;
    }
  else
    {
      printf("Battle aborted because of command error\n");
      return 1;
    }
}


void launch_game(Game* game)
{
  int game_continue = 1;
  printf("Game is launching . . .\n");

  while(game_continue)
    {
      char* command = NULL;
      processing_fct action = NULL;
      printf("Enter command :\n");
      command = get_command_from_user();
      if(command != NULL && strcmp(command,"") != 0)
	{
	  char* split_command;
	  remove_occurences(command,'\n');
	  remove_occurences(command,'\t');
	  split_command = strtok(command,COMMAND_SEPARATOR);
	  action = get_action_from_command(split_command);
	  if(action == NULL)
	    {
	      printf("You enter an invalid command !\n");
	    }
	  else
	    {
	      game_continue = action(game);
	    }
	}
      /* Delete command pointer */
      if(command != NULL)
	{
	  free(command);
	}
    }
}
