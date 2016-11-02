#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "math_utils.h"
#include "attack.h"
#include "poketudiant.h"

Poketudiant* create_poketudiant(char* name, char* evol, int capt, unsigned int att, unsigned int def, unsigned int hp_max, double coeff_att, double coeff_def, double coeff_hp)
{
  /* Static variable for unique_id generator */
  static int unique_id = 0;
  
  unsigned int size_name, size_evol;
  Poketudiant* poketudiant = NULL;

  poketudiant = malloc(sizeof(Poketudiant));
  if(poketudiant == NULL)
    {
      fprintf(stderr, "%s\n", "Poketudiant dynamic allocation failed");
      return NULL;
    }
  poketudiant->unique_id = unique_id++;
  size_name = strlen(name) + 1; 
  size_evol = strlen(evol) + 1;
  poketudiant->name = malloc(sizeof(char) * size_name);
  poketudiant->evolution = malloc(sizeof(char) * size_evol);
  strcpy(poketudiant->name , name);
  strcpy(poketudiant->evolution , evol);
  poketudiant->capturable = capt;
  poketudiant->coeff_attack = coeff_att;
  poketudiant->coeff_defense = coeff_def;
  poketudiant->coeff_hp = coeff_hp;
  poketudiant->attack = att;
  poketudiant->defense = def;
  poketudiant->hp_max = hp_max;
  poketudiant->current_hp = hp_max;
  poketudiant->lvl = 1;
  poketudiant->current_xp = 0;
  poketudiant->xp_next_lvl = 500 * (( 1 + poketudiant->lvl) / 2);

  return poketudiant;
}

void delete_poketudiant(Poketudiant* poketudiant)
{
  free(poketudiant->name);
  free(poketudiant->evolution);
  free(poketudiant);
}


int take_damage(Poketudiant* poketudiant, unsigned int quantity)
{
  poketudiant->current_hp -= quantity;
  if(poketudiant->current_hp <= 0)
    {
      poketudiant->current_hp = 0;
      return 1;
    }
  else
    {
      return 0;
    }
}
int evolve(Poketudiant* poketudiant)
{
  if(poketudiant->lvl == 5)
    {
      return 1;
    }
  else if(poketudiant->lvl == 4)
    {
      double rand_value = random_float(0.0,100.0);
      if(rand_value <= 20.0)
	{
	  return 1;
	}
      return 0;
    }
  else if(poketudiant->lvl == 3)
    {
      double rand_value = random_float(0.0,100.0);
      if(rand_value <= 37.5)
	{
	  return 1;
	}
      return 0;
    }
  else
    {
      return 0;
    }
}
void up_level(Poketudiant* poketudiant)
{
  poketudiant->lvl++;
  poketudiant->attack += floor((poketudiant->attack/1+((float)(poketudiant->lvl - 1)/10.0))*0.1);
  poketudiant->defense += floor((poketudiant->defense/1+((float)(poketudiant->lvl - 1)/10.0))*0.1);
  poketudiant->hp_max += floor((poketudiant->hp_max/1+((float)(poketudiant->lvl - 1)/10.0))*0.1);
  
  if(poketudiant->lvl >= 3 && poketudiant->lvl <= 5)
    {
      int res = evolve(poketudiant);
      if(res)
	{
	  printf("Evolution . . .\n");
	}
      else
	{
	  printf("No evolution . . .\n");
	}
    }

  poketudiant->current_hp = poketudiant->hp_max;
  poketudiant->xp_next_lvl += floor(500 * ((float)(1+poketudiant->lvl) / 2.0));  
}

void get_experience(Poketudiant* poketudiant, unsigned int quantity)
{
  if(quantity > (poketudiant->xp_next_lvl - poketudiant->current_xp))
    {
      unsigned int diff_xp = quantity - (poketudiant->xp_next_lvl - poketudiant->current_xp);
      poketudiant->current_xp = poketudiant->xp_next_lvl;
      up_level(poketudiant);
      get_experience(poketudiant,diff_xp);
    } 
  else
    {
      poketudiant->current_xp += quantity;
    }
}

void print_complete_poketudiant_informations(const Poketudiant* poketudiant)
{
  printf("Informations about poketudiant :\n");
  printf("\tID = %d ; Name = %s\n",poketudiant->unique_id,poketudiant->name);
  printf("\tLevel = %d ; XP = %d ; XP needed = %d\n",poketudiant->lvl, poketudiant->current_xp, poketudiant->xp_next_lvl);
  printf("\tEvolution = %s ; Capturable = %s\n",poketudiant->evolution, ((poketudiant->capturable) ? ("Yes") : ("No")));
  printf("\tAttack = %d ; Defense = %d ; PV max = %d ; Actual PV = %d\n",poketudiant->attack,poketudiant->defense,poketudiant->hp_max,poketudiant->current_hp);
}

void print_concive_poketudiant_informations(const Poketudiant* poketudiant)
{
  printf("Informations about poketudiant :\n");
  printf("\tID = %d ; Name = %s\n",poketudiant->unique_id,poketudiant->name);
  printf("\tLevel = %d\n",poketudiant->lvl);
  printf("\tActual PV = %d ; Max PV = %d\n",poketudiant->current_hp, poketudiant->hp_max);
}
