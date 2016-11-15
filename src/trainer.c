#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "container.h"

#include "type_poke.h"
#include "attack.h"
#include "poketudiant.h"
#include "generic_control_function.h"
#include "pokecafetaria.h"
#include "trainer.h"


#define MAX_POKE_IN_TEAM 3
Trainer* create_trainer(const char* name, int ia_trainer)
{
  unsigned int size_name = strlen(name) + 1;
  Trainer* trainer = malloc(sizeof(Trainer));
  trainer->name = malloc(size_name * sizeof(char));
  strcpy(trainer->name,name);

  trainer->team = create_container(STATIC,3,1);
  trainer->team->display_element_fct = print_poketudiant_fct;
  trainer->team->delete_fct = delete_poketudiant_fct;
  trainer->team->cmp_fct = cmp_poketudiant_fct_via_id;

  trainer->ia_trainer = ia_trainer;
  if(ia_trainer)
    {
      trainer->cafetaria = NULL;
    }
  else
    {
      trainer->cafetaria = create_pokecafetaria();
    }
  
  return trainer;
}

void delete_trainer(Trainer* trainer)
{
  free(trainer->name);
  delete_container(trainer->team);
  if(trainer->cafetaria != NULL)
    {
      delete_pokecafetaria(trainer->cafetaria);
    }
  free(trainer);
}


void heal_all_team(Trainer* trainer)
{
  unsigned int i;
  /* Heal current Team */
  for(i = 0; i < trainer->team->current; i++)
    {
      ((Poketudiant*)trainer->team->list[i])->hp = ((Poketudiant*)trainer->team->list[i])->hp_max;
    }
  /* Heal poketudiant in cafetaria */
  heal_all_pokecafetaria(trainer->cafetaria);
}

void drop_to_pokecafetaria(Trainer* trainer, int id)
{
  Poketudiant* to_drop;
  int index;
  
  index = get_index_of_poketudiant_id(trainer,id);
  if(index != -1)
    {
      /* we need to know if there is some place for new poketudiant */
      to_drop = (Poketudiant*)trainer->team->list[index];
      
      if(to_drop->type == TEACHER)
	{
	  printf("You can't drop your teacher in pokecafeteria !\n");
	  return;
	}
      if(add_poketudiant_to_cafetaria(trainer->cafetaria,to_drop))
	{
	  remove_to_container(trainer->team,to_drop);
	}
      else
	{
	  printf("There is no more place in cafetaria for poketudiant ... drop cancel\n");
	}
    }
  else
    {
      printf("There is no poketudiant with this id in your team\n");
    }
}

void pick_from_pokecafetaria(Trainer* trainer, int id)
{
  if(trainer->team->current <= 2)
    {
      Poketudiant* to_pick = pop_poketudiant_from_cafetaria_via_id(trainer->cafetaria,id);
      if(to_pick == NULL)
	{
	  printf("There is no poketudiant with this id in trainer's cafetaria\n");
	}
      else
	{
	  poketudiant_movement_from_cafet_to_trainer(trainer,to_pick);
	}
    }
  else
    {
      printf("No more places for pick a poketudiant from cafetaria... pick cancel\n");
    }
}

void release_from_pokecafetaria(Trainer* trainer, int id)
{
  delete_poketudiant_from_cafetaria_by_id(trainer->cafetaria,id);
}

int add_poketudiant_to_team(Trainer* trainer, Poketudiant* poke)
{
  static int id = 0;
  
  int succeed = 1;
  if(!add_to_container(trainer->team,poke))
    {
      succeed = 0;
      printf("No more space in your team . . . Sending %s to pokecafetaria.\n",poke->variety);
      if(!add_poketudiant_to_cafetaria(trainer->cafetaria,poke))
	{
	  printf("No more space in your cafetaria . . . %s run away in wild.\n",poke->variety);
	  succeed = 0;
	}
      else
	{
	  printf("Your %s has well arrived to pokecafetaria.\n",poke->variety);
	  succeed = 1;
	}
    }
  
  /* Impossible to add poketudiant to team or cafeteria, he run away we have to free it */
  if(!succeed)
    {
      delete_poketudiant(poke);
      return 0;
    }
  /* Insertion has succeed, we shoud give an appropriate id for our poketudiant because we know 
     he'll be atleast for a time durable in game */
  if(!trainer->ia_trainer)
    {
      poke->id = id++;
    }
  return 1;
}

int poketudiant_movement_from_cafet_to_trainer(Trainer* trainer, Poketudiant* poke)
{
  if(!add_to_container(trainer->team,poke))
    {
      printf("There is no more space in your team to add poketudiant !\n");
      return 0;
    }
  return 1;
}

Poketudiant* remove_poketudiant_from_team(Trainer* trainer, int id)
{
  void* removed = NULL;
  int (*cmp_save)(void*,void*) = trainer->team->cmp_fct;
  trainer->team->cmp_fct = cmp_poketudiant_fct_via_id;
  /* We first check that we don't remove our teacher type poketudiant */
  if(((Poketudiant*)search_in_container(trainer->team,&id))->type == TEACHER)
    {
      printf("You can't remove your teacher poketudiant !\n");
    }
  else
    {
      removed = remove_to_container(trainer->team,&id);
      if(removed == NULL)
	{
	  printf("This poketudiant doesn't exist in your team !\n");
	}
    }
   
  trainer->team->cmp_fct = cmp_save;
  return (Poketudiant*)removed;
}

Poketudiant* select_poketudiant_by_id_in_trainer(const Trainer* trainer, int id)
{
  /* Try to get poketudiant in team */
  Poketudiant* poke;
  int index = get_index_of_poketudiant_id(trainer,id);
  if(index != -1)
    {
      return ((Poketudiant*)trainer->team->list[index]);
    }
  /* Try to get poketudiant in pokecafetaria */
  poke = get_poketudiant_from_cafetaria_by_id(trainer->cafetaria,id);
  if(poke != NULL)
    {
      return poke;
    }
  /* There is no poketudiant with this id */
  return NULL;
}

Poketudiant* select_first_poketudiant_in_life(Trainer* trainer)
{
  unsigned int i;
  for(i = 0; i < trainer->team->current; i++)
    {
      if(((Poketudiant*)trainer->team->list[i])->hp >= 1)
	{
	  return trainer->team->list[i];
	}
    }
  return NULL;
}

int is_still_poketudiant_alive(Trainer* trainer)
{
  return (select_first_poketudiant_in_life(trainer) != NULL);
}

int swap_poketudiant(Trainer* trainer, int id_1, int id_2)
{
  if(swap_position_poketudiant_by_id(trainer,id_1,id_2) ||
     swap_position_poketudiant_in_cafetaria_via_id(trainer->cafetaria,id_1,id_2))
    {
      return 1;
    }
  else
    {
      int pos_1_in_team = get_index_of_poketudiant_id(trainer,id_1);
      int pos_2_in_team = get_index_of_poketudiant_id(trainer,id_2);
      int pos_1_in_cafe = get_position_poketudiant_id_in_cafetaria(trainer->cafetaria,id_1);
      int pos_2_in_cafe = get_position_poketudiant_id_in_cafetaria(trainer->cafetaria,id_2);
      
      int in_team = -1;
      int in_cafe = -1;
      if(pos_1_in_team != -1) in_team = pos_1_in_team;
      else if(pos_2_in_team != -1) in_team = pos_2_in_team;
      
      if(pos_1_in_cafe != -1) in_cafe = pos_1_in_cafe;
      else if(pos_2_in_cafe != -1) in_cafe = pos_2_in_cafe;

      if(in_team == -1 || in_cafe == -1)
	{
	  printf("There is no poketudiants with thoses ids, check before trying switch\n");
	  return 0;
	}
      else if(((Poketudiant*)trainer->team->list[in_team])->type == TEACHER)
	{
	  printf("You can't switch your teacher poketudiant to set it in pokecafeteria\n");
	  return 0;
	} 
      else
	{
	  /* Swap */
	  Poketudiant* tmp = (Poketudiant*)trainer->team->list[in_team];
	  trainer->team->list[in_team] = trainer->cafetaria->list[in_cafe];
	  trainer->cafetaria->list[in_cafe] = tmp;
	  return 1;
	}
    }
}

int swap_position_poketudiant_by_id(Trainer* trainer, int id_1, int id_2)
{
  int position_first = get_index_of_poketudiant_id(trainer,id_1);
  int position_second = get_index_of_poketudiant_id(trainer,id_2);
  if(position_first == -1 || position_second == -1)
    {
      return 0;
    }
  else
    {
      void* tmp = trainer->team->list[position_first];
      trainer->team->list[position_first] = trainer->team->list[position_second];
      trainer->team->list[position_second] = tmp;

      return 1;
    }
}

int get_index_of_poketudiant_id(const Trainer* trainer,int id)
{
  int position;
  int (*cmp_save)(void*,void*) = trainer->team->cmp_fct;
 
  trainer->team->cmp_fct = cmp_poketudiant_fct_via_id;
  position = search_position_in_container(trainer->team,&id);

  trainer->team->cmp_fct = cmp_save;
  return position;
}

void print_poketudiant_id_from_trainer(const Trainer* trainer, int id)
{
  int index;
  Poketudiant* poke;
  /* Trying to print id from trainer team */
  if((index = get_index_of_poketudiant_id(trainer,id)) != -1)
    {
      print_complete_poketudiant((Poketudiant*)trainer->team->list[index]);
      return;
    }
  /* Trying to print id from trainer pokecafetaria */
  if((poke = get_poketudiant_from_cafetaria_by_id(trainer->cafetaria,id)) != NULL)
    {
      print_complete_poketudiant(poke);
      return;
    }
  printf("There is no poketudiant in your team or your poketudiant with ID = %d\n",id);
}

void print_team_alive(const Trainer* trainer)
{
  unsigned int i;
  printf("%s's team alive\n",trainer->name);
  for(i = 0; i < trainer->team->current; i++)
    {
      if(((Poketudiant*)trainer->team->list[i])->hp >= 1)
	{
	  print_complete_poketudiant(trainer->team->list[i]);
	}
    }
}

void print_team_alive_except_current_fighter(const Trainer* trainer, Poketudiant* fighter)
{
  unsigned int i;
  printf("%s's team alive\n",trainer->name);
  for(i = 0; i < trainer->team->current; i++)
    {
      if(((Poketudiant*)trainer->team->list[i])->hp >= 1 && (Poketudiant*)trainer->team->list[i] != fighter)
	{
	  print_complete_poketudiant(trainer->team->list[i]);
	}
    }
}

void print_team(const Trainer* trainer)
{
  printf("%s's team\n",trainer->name);
  print_container(trainer->team);
}

void print_trainer_cafetaria(const Trainer* trainer)
{
  print_pokecafetaria(trainer->cafetaria);
}

void print_trainer_revision_table_t(const Trainer* trainer, int t)
{
  print_table_pokecafetaria(trainer->cafetaria,t);
}
