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
#include "generic_control_function.h"
#include "evolve_module.h"


Evolve_center* create_evolve_center(Hash_table* ref_poke_base)
{
  Evolve_center* center = malloc(sizeof(Evolve_center));
  center->ref_poke_base = ref_poke_base;
  
  return center;
}

void delete_evolve_center(Evolve_center* center)
{
  free(center);
  return;
}


int make_poketudiant_evolve(Evolve_center* center, 
			    Poketudiant* poke,
			    double coeff_att,
			    double coeff_def,
			    double coeff_hp)
{
  Poketudiant* getter_evolution = get_element_in_hash_table(center->ref_poke_base,poke->evolution);
  
  if(getter_evolution == NULL)
    {
      printf("Error, this evolution doesn't exist !\n");
      return 0;
    }
  else
    {
      double random_value = random_double(0.0,100.0);
      int must_evolve = 0;
      /* We'll check if pokemon is ready to evolve */ 
      if(poke->level == 3 && random_value <= 20)
	{
	  must_evolve = 1;
	}
      else if(poke->level == 4 && random_value <= 37.5)
	{
	  must_evolve = 1;
	}
      else if(poke->level == 5)
	{
	  must_evolve = 1;
	}
      else
	{
	  must_evolve = 0;
	}
      
      /* Manage if pokemon is ready to evolve */
      if(must_evolve)
	{
	  double level_multiplier = 1+((poke->level/10.0)-0.1);
	  unsigned int size_variety = strlen(getter_evolution->variety) + 1;
	  unsigned int size_evolution = strlen(getter_evolution->evolution) + 1;
	  poke->variety = realloc(poke->variety,size_variety * sizeof(char));
	  poke->evolution = realloc(poke->evolution,size_evolution * sizeof(char));

	  strcpy(poke->variety,getter_evolution->variety);
	  strcpy(poke->evolution,getter_evolution->evolution);
	  poke->capturable = getter_evolution->capturable;
	  poke->attack = (getter_evolution->attack * coeff_att) * level_multiplier;
	  poke->defense = (getter_evolution->defense * coeff_def) * level_multiplier;
	  poke->hp_max = (getter_evolution->hp_max * coeff_hp) * level_multiplier;
	  poke->hp = poke->hp_max;
	  return 1;
	} 
      else
	{
	  return 0;
	}
    }
}

void make_poketudiant_upgrade(Evolve_center* center, Poketudiant* poke)
{
  Poketudiant* base_poke;

  double coeff_att;
  double coeff_def;
  double coeff_hp;
  double level_multiplier;

  int (*hash_save)(void*) = center->ref_poke_base->hash_fct;
  int (*cmp_save)(void*,void*) = center->ref_poke_base->cmp_fct_linked_list;

  center->ref_poke_base->hash_fct = hash_poketudiant_fct_from_string;
  set_cmp_fct_for_hash_table(center->ref_poke_base,cmp_poketudiant_fct_via_variety);

  base_poke = get_element_in_hash_table(center->ref_poke_base,poke->variety);
  level_multiplier = 1+((poke->level/10.0)-0.1);
  coeff_att = poke->attack  / (double)(base_poke->attack * level_multiplier);
  coeff_def = poke->defense / (double)(base_poke->defense * level_multiplier);
  coeff_hp =  poke->hp_max  / (double)(base_poke->hp_max * level_multiplier);

 /* Leveling phase 
     We have to follow those rules :
     attack, defense and hp_max upgrade to 10% from level 1 value
     xp next evolve as : 500 * ((1 + level) / 2)
  */
  poke->level++;
  if(poke->level < 10) /* If poketudiant level is 10, we don't need to update anymore xp_next */
    {
      poke->xp_next = (int)round(500 * ((float)(1 + poke->level) / 2));
    }
  poke->attack += (int)round(((int)(base_poke->attack * coeff_att)*10)/100);
  poke->defense += (int)round(((int)(base_poke->defense * coeff_def)*10)/100);
  poke->hp_max += (int)round(((int)(base_poke->hp_max * coeff_hp)*10)/100);
  poke->hp = poke->hp_max;
  printf("Your poketudiant has evolved to level %d\n",poke->level);

  if(poke->level >= 3 && poke->level <= 5 && strcmp(poke->evolution,"none") != 0)
    {
      int res;
      unsigned int size_old_variety = strlen(poke->variety) + 1;
      char* old_variety = malloc(size_old_variety * sizeof(char));
      strcpy(old_variety,poke->variety);
      
      res = make_poketudiant_evolve(center,poke,coeff_att,coeff_def,coeff_hp);
      if(res)
	{
	  printf("Congratulation !\nYour %s evolved to %s !\n",old_variety,poke->variety);
	}
    }

  center->ref_poke_base->hash_fct = hash_save;
  center->ref_poke_base->cmp_fct_linked_list = cmp_save;

  /* If poketudiant has enought xp to reupgrade a second time */
  if(poke->xp >= poke->xp_next)
    {
      if(poke->level < 10)
	{
	  make_poketudiant_upgrade(center,poke);
	} 
      else
	{
	  poke->xp = poke->xp_next;
	}
    }
}
