#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "math_utils.h"
#include "container.h"
#include "linked_list.h"
#include "hash_table.h"
#include "type_poke.h"
#include "attack.h"
#include "poketudiant.h"
#include "trainer.h"
#include "factories.h"
#include "generic_control_function.h"
#include "evolve_module.h"
#include "battle_module.h"

#define XP_START_WILD_POKE 300

Battle_module* create_battle_module(Poketudiant_factory* ref_poke_facto,
				    Evolve_center* ref_evolve_center)
{
  Battle_module* battle = malloc(sizeof(Battle_module));
  battle->ref_poke_factory = ref_poke_facto;
  battle->ref_evolve_center = ref_evolve_center;
  return battle;
}


void empty_buffer()
{
  int c = 0;
  while (c != '\n' && c != EOF)
    {
      c = getchar();
    }
}
void delete_battle_module(Battle_module* battle_module)
{
  free(battle_module);
}

void display_entrance_mesage(const char* name_1, const char* name_2)
{
  printf("Battle starting between %s and %s !\n",name_1, name_2);
}

void display_opponents(Poketudiant* poke_player, Poketudiant* poke_ia)
{
  printf("Your poketudiant :\n");
  print_complete_poketudiant(poke_player);
  printf("Enemy poketudiant :\n");
  print_complete_poketudiant(poke_ia);
}

void display_battle_menu_vs_wild_poketudiant()
{
  printf("What do you want to do ?\n");
  printf("1 : First attack\n");
  printf("2 : Second attack\n");
  printf("3 : Change poketudiant\n");
  printf("4 : Try to capture poketudiant\n");
  printf("5 : Try to escape\n");
}

void display_battle_menu_vs_trainer()
{
  printf("1 : First attack\n");
  printf("2 : Second attack\n");
  printf("3 : Change poketudiant\n");
}

State_action manage_order_vs_wild_poketudiant()
{
  int valid = 0;
  State_action action;
  while(!valid)
    {
      int answer;
      scanf("%d",&answer);
      switch(answer)
	{
	case 1:
	  valid = 1;
	  action = FIRST_ATTACK;
	  break;
	case 2:
	  valid = 1;
	  action = SECOND_ATTACK;
	  break;
	case 3:
	  valid = 1;
	  action = CHANGE_POKE;
	  break;
	case 4:
	  valid = 1;
	  action = TRY_CAPTURE;
	  break;
	case 5:
	  valid = 1;
	  action = TRY_ESCAPE;
	  break;
	default:
	  printf("Your answer is unavailable please make choice according to menu\n");
	  empty_buffer();
	  display_battle_menu_vs_wild_poketudiant();
	  break;
	}
    }
  
  return action;
}

State_action manage_order_vs_trainer()
{
int valid = 0;
  State_action action;
  while(!valid)
    {
      int answer;
      scanf("%d",&answer);
      switch(answer)
	{
	case 1:
	  valid = 1;
	  action = FIRST_ATTACK;
	  break;
	case 2:
	  valid = 1;
	  action = SECOND_ATTACK;
	  break;
	case 3:
	  valid = 1;
	  action = CHANGE_POKE;
	  break;
	default:
	  printf("Your answer is unavailable please make choice according to menu\n");
	  empty_buffer();
	  display_battle_menu_vs_trainer();
	  break;
	}
    }
  
  return action;
}

void distribute_xp_to_poketudiants(Battle_module* battle_module, Container* all_poke, int total_xp)
{
  unsigned int xp_per_poke = (int)round(total_xp/(float)all_poke->current);
  unsigned int i;
  printf("Experience won = %d\n",total_xp);
  printf("Experience per poke = %d\n",xp_per_poke);
  for(i = 0; i < all_poke->current; i++)
    {
      if(earn_experience((Poketudiant*)all_poke->list[i],xp_per_poke))
	{
	  make_poketudiant_upgrade(battle_module->ref_evolve_center,
				   (Poketudiant*)all_poke->list[i]);
	}
    }
}

int attack_poketudiant(Poketudiant* poke_att, Poketudiant* poke_def, Attack* att)
{
  /* Attaque avec les resistances etc a voir */
  double rand_multi = random_double_in_poke_range();
  int damage = rand_multi * ((float)poke_att->attack / poke_def->defense) * att->pow;
  
  
  return take_damage(poke_def,damage);
}

Poketudiant* change_current_poketudiant_fighter(Trainer* trainer, Poketudiant* current_fighter)
{
  int id;
  char term;
  int valid = 0;
  Poketudiant* new_fighter = NULL;

  if(!is_still_poketudiant_alive(trainer))
    {
      return new_fighter;
    }
  while(!valid)
    {
      printf("Which poketudiant do you want to make as fighter ? Select id\n");
      print_team_alive_except_current_fighter(trainer,current_fighter);
      
      
      if(scanf("%d%c", &id, &term) != 2 || term != '\n')
	{
	  printf("You enter an invalide integer, please enter integer value for id value\n");
	  empty_buffer();
	}
      else
	{
	  int pos_in_team = get_index_of_poketudiant_id(trainer,id);
	  if(id == -1)
	    {
	      printf("Poketudiant change cancel.\n");
	      valid = 1;
	    }
	  if(pos_in_team == -1)
	    {
	      printf("This poketudiant doesn't exist in your team, enter correct id !\n");
	    }
	  else if((Poketudiant*)trainer->team->list[pos_in_team] == current_fighter)
	    {
	      printf("This poketudiant is already at fighting position !\n");
	    }
	  else if(((Poketudiant*)trainer->team->list[pos_in_team])->hp < 1)
	    {
	      printf("This poketudiant is dead and can't participate to battle !\n");
	    }
	  else
	    {
	      new_fighter = (Poketudiant*)trainer->team->list[pos_in_team];
	      valid = 1;
	    }
	}
    }
  
  return new_fighter;
}

int try_to_capture(Poketudiant* poketudiant_ia)
{
  double probability = (2 * max((0.5-((float)poketudiant_ia->hp/poketudiant_ia->hp_max)),0));
  double random_val = random_double(0.0,1.0);

  return random_val <= probability;
}

int try_to_escape(Poketudiant* poketudiant_player, Poketudiant* poketudiant_ia)
{
  int level_difference = poketudiant_player->level - poketudiant_ia->level;
  int random = random_int(0,100);
  int gonna_escape = 0;
  if(level_difference <= -3)
    gonna_escape = 0;
  else if(level_difference == -2 && random <= 25)
    gonna_escape = 1;
  else if(level_difference == -1 && random <= 40)
    gonna_escape = 1;
  else if(level_difference == 0 && random <= 50)
    gonna_escape = 1;
  else if(level_difference == 1 && random <= 75)
    gonna_escape = 1;
  else if(level_difference == 2 && random <= 95)
    gonna_escape = 1;
  else if(level_difference >= 3)
    gonna_escape = 1;
  else
    gonna_escape = 0;
  
  return gonna_escape;
}

int trainer_versus_random_wild_poketudiant(Battle_module* battle_module,
					   Trainer* trainer,
					   int min_level,
					   int max_level)
{
  Container* container_poke_participate;
  int random_level = random_int(min_level,max_level);
  Poketudiant* current_opponent;
  Poketudiant* current_fighter;
  int win;

  container_poke_participate = create_container(DYNAMIC,3,0);
  current_opponent = generate_random_capturable_poketudiant(battle_module->ref_poke_factory,random_level);
  current_fighter = select_first_poketudiant_in_life(trainer);
 
  container_poke_participate->cmp_fct = cmp_poketudiant_fct_via_id;
  container_poke_participate->delete_fct = delete_poketudiant_fct;
  add_to_container_if_not_exist(container_poke_participate,current_fighter);
  win = 0;

  /* If poketudiant is level 1 let's make him with 300 xp to allow player to gain xp
     XP_START_WILD_POKE has value 300 */
  if(current_opponent->level == 1)
    {
      current_opponent->xp = XP_START_WILD_POKE;
    }

  if(current_fighter == NULL)
    {
      printf("You doesn't have poketudiant able to fight ...\n");
      printf("You lose this battle\n");
      win = 0;
    }
  else
    {
      int battle_ended = 0;
      while(!battle_ended)
	{
	  State_action action_player;
	  /* Trainer play */
	  /* Before making action, we need to check if our fighter is still able to fight 
	     if he isn't player has to choose a new poketudiant and do nothing for this turn
	  */
	  if(current_fighter->hp < 1)
	    {
	      printf("Your %s is dead !\n",current_fighter->variety);
	      current_fighter = change_current_poketudiant_fighter(trainer,current_fighter);
	      if(current_fighter == NULL)
		{
		  printf("All your poketudiant are dead ...\n");
		  printf("You lose this battle\n");
		  win = 0;
		  battle_ended = 1;
		}
	      else
		{
		  /* Add to container if not exist */
		  add_to_container_if_not_exist(container_poke_participate,current_fighter);
		}
	    }
	  /* In this case, we're sure that our fighter have at least 1 hp, so player can make
	     choice in menu
	  */
	  else
	    {
	      display_opponents(current_fighter, current_opponent);
	      display_battle_menu_vs_wild_poketudiant();
	      action_player = manage_order_vs_wild_poketudiant();
	      
	      switch(action_player)
		{
		case FIRST_ATTACK:
		  {
		    int res = attack_poketudiant(current_fighter,current_opponent,current_fighter->ref_attack_1);
		    if(res)
		      {
			battle_ended = 1;
			win = 1;
			printf("Congratuation, you won this battle.\n");
		      }
		    break;
		  }
		case SECOND_ATTACK:
		  { 
		    int res = attack_poketudiant(current_fighter,current_opponent,current_fighter->ref_attack_2);
		    if(res)
		      {
			battle_ended = 1;
			win = 1;
			printf("Congratuation, you won this battle.\n");
		      }
		    break;
		  }
		case CHANGE_POKE:
		  {
		    Poketudiant* new_pok = change_current_poketudiant_fighter(trainer,current_fighter);
		    if(new_pok != NULL)
		      {
			current_fighter = new_pok;
			add_to_container_if_not_exist(container_poke_participate,current_fighter);
		      }
		    break;
		  }
		case TRY_CAPTURE:
		  {
		    int res = try_to_capture(current_opponent);
		    if(res)
		      {
			printf("Capture succeed ! You capture %s , level %d\n",current_opponent->variety,current_opponent->level);
			battle_ended = 1;
			win = 1;
		      }
		    break;
		  }
		case TRY_ESCAPE:
		  {
		    int res = try_to_escape(current_fighter, current_opponent);
		    if(res)
		      {
			printf("You succeed to escape battle !\n");
			battle_ended = 1;
			win = 1;
		      }
		    break;
		  }
		}
	    }
	  
	  /* If battle is no ended that mean damage have been inflict and to escape or capture */
	  if(!battle_ended)
	    {
	      /* Wild poketudiant play */
	      int random_choice_ia = random_int(1,2);
	      if(random_choice_ia == 1)
		{
		  attack_poketudiant(current_opponent,current_fighter,current_opponent->ref_attack_1);
		}
	      else
		{
		  attack_poketudiant(current_opponent,current_fighter,current_opponent->ref_attack_2);
		}
	    }
	}
    }

  if(win)
    {
      unsigned int xp_won = (int)round((current_opponent->xp * 10)/100.0); /* 10% of enemy exp */
      distribute_xp_to_poketudiants(battle_module,container_poke_participate,xp_won);
    }

  delete_container(container_poke_participate);
  delete_poketudiant(current_opponent);
  return win;
}


int trainer_versus_random_trainer(Battle_module* battle_module,
				   Trainer* trainer, 
				   int min_level,
				   int max_level)
{

  Container* container_poke_participate;
  Trainer* opponent_trainer;
  int random_level;
  Poketudiant* current_fighter;
  Poketudiant* current_opponent;
  int win;

  random_level = random_int(min_level,max_level);
  opponent_trainer = generate_random_trainer(battle_module->ref_poke_factory,random_level);

  container_poke_participate = create_container(DYNAMIC,3,0);
  current_opponent = select_first_poketudiant_in_life(opponent_trainer);
  current_fighter = select_first_poketudiant_in_life(trainer);
 
  container_poke_participate->cmp_fct = cmp_poketudiant_fct_via_id;
  container_poke_participate->delete_fct = delete_poketudiant_fct;
  add_to_container_if_not_exist(container_poke_participate,current_fighter);
  win = 0;


  if(current_fighter == NULL)
    {
      printf("You doesn't have poketudiant able to fight ...\n");
      printf("You lose this battle\n");
      win = 0;
    }
  else
    {
      int battle_ended = 0;
      while(!battle_ended)
	{
	  State_action action_player;
	  /* Trainer play */
	  /* Before making action, we need to check if our fighter is still able to fight 
	     if he isn't player has to choose a new poketudiant and do nothing for this turn
	  */
	  if(current_fighter->hp < 1)
	    {
	      printf("Your %s is dead !\n",current_fighter->variety);
	      current_fighter = change_current_poketudiant_fighter(trainer,current_fighter);
	      if(current_fighter == NULL)
		{
		  printf("All your poketudiant are dead ...\n");
		  printf("You lose this battle\n");
		  win = 0;
		  battle_ended = 1;
		}
	      else
		{
		  add_to_container_if_not_exist(container_poke_participate,current_fighter);
		}
	    }
	  /* In this case, we're sure that our fighter have at least 1 hp, so player can make
	     choice in menu
	  */
	  else
	    {
	      display_opponents(current_fighter, current_opponent);
	      display_battle_menu_vs_trainer();
	      action_player = manage_order_vs_trainer();
	      
	      switch(action_player)
		{
		case FIRST_ATTACK:
		  {
		    int res = attack_poketudiant(current_fighter,current_opponent,current_fighter->ref_attack_1);
		    if(res)
		      {
			printf("Congratz ! %s has fallen\n",current_opponent->variety);
		      }
		    break;
		  }
		case SECOND_ATTACK:
		  { 
		    int res = attack_poketudiant(current_fighter,current_opponent,current_fighter->ref_attack_2);
		    if(res)
		      {
			printf("Congratz ! %s has fallen.\n",current_opponent->variety);
		      }
		    break;
		  }
		case CHANGE_POKE:
		  {
		    Poketudiant* new_pok = change_current_poketudiant_fighter(trainer,current_fighter);
		    if(new_pok != NULL)
		      {
			current_fighter = new_pok;
			add_to_container_if_not_exist(container_poke_participate,current_fighter);
		      }
		    break;
		  }
		case TRY_CAPTURE:
		  {
		    int res = try_to_capture(current_opponent);
		    if(res)
		      {
			printf("Capture succeed ! You capture %s , level %d\n",current_opponent->variety,current_opponent->level);
			battle_ended = 1;
			win = 1;
		      }
		    break;
		  }
		case TRY_ESCAPE:
		  {
		    int res = try_to_escape(current_fighter, current_opponent);
		    if(res)
		      {
			printf("You succeed to escape battle !\n");
			battle_ended = 1;
			win = 1;
		      }
		    break;
		  }
		}
	    }
	  
	  /* If battle is no ended that mean damage have been inflict and to escape or capture */
	  if(!battle_ended)
	    {
	      /* Wild poketudiant play */
	      /* Before making action, we need to check if our fighter is still able to fight 
		 if he isn't player has to choose a new poketudiant and do nothing for this turn
	      */
	      if(current_opponent->hp < 1)
		{
		  unsigned int xp_won = (int)round((current_opponent->xp * 10)/100.0); /* 10%*/
		  distribute_xp_to_poketudiants(battle_module,container_poke_participate,xp_won);
		  empty_container(container_poke_participate);
		  add_to_container_if_not_exist(container_poke_participate,current_fighter);
 		  
		  current_opponent = select_first_poketudiant_in_life(opponent_trainer);
		  if(current_opponent == NULL)
		    {
		      printf("All enemy's poketudiant are dead ...\n");
		      printf("You win this battle\n");
		      win = 1;
		      battle_ended = 1;
		    }
		}
	      /* Here current opponent poketudiant is not dead, so ia can play round as attacker */
	      else
		{
		  int random_choice_ia = random_int(1,2);
		  if(random_choice_ia == 1)
		    {
		  attack_poketudiant(current_opponent,current_fighter,current_opponent->ref_attack_1);
		    }
		  else
		    {
		      attack_poketudiant(current_opponent,current_fighter,current_opponent->ref_attack_2);
		    }
		}
	    }
	}
    }

  delete_container(container_poke_participate);
  delete_trainer(opponent_trainer);
  return win;
}

/*int trainer_versus_trainer(Battle_module* battle_module,
			    Trainer* trainer,
			    Trainer* ia)
{

}
*/
