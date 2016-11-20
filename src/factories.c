#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "math_utils.h"
#include "type_poke.h"
#include "container.h"
#include "linked_list.h"
#include "hash_table.h"
#include "attack.h"
#include "poketudiant.h"
#include "generic_control_function.h"
#include "pokecafetaria.h"
#include "trainer.h"
#include "constantes.h"
#include "factories.h"

Poketudiant_factory* create_poketudiant_factory(Hash_table* ref_poke, Hash_table* ref_att)
{
  Poketudiant_factory* factory = malloc(sizeof(Poketudiant_factory));
  factory->ref_poketudiant_base = ref_poke;
  factory->ref_attack_base = ref_att;

  return factory;
}

void delete_poketudiant_factory(Poketudiant_factory* factory)
{
  free(factory);
}

Poketudiant* generate_poketudiant(Poketudiant_factory* factory, Poketudiant* base_poke, int level)
{
  if(level < MIN_LEVEL_POKETUDIANT || level > MAX_LEVEL_POKETUDIANT)
    {
      printf("We only can generated poketudiant in range level %d to %d.\n",MIN_LEVEL_POKETUDIANT,MAX_LEVEL_POKETUDIANT);
      return NULL;
    }
  else if(base_poke == NULL)
    {
      printf("Unfined base poketudiant, error\n");
      return NULL;
    }
  else
    {
      Poketudiant* poke = NULL;
      
      double level_multiplier;
      double r_att, r_def, r_hp;
      Attack* att_1;
      Attack* att_2;
      int (*save_cmp_fct)(void*,void*) = factory->ref_attack_base->cmp_fct_linked_list;
      /* We save the cmp fct from the hash table */
      
      /* First build basic poketudiant */ 
      poke = create_poketudiant_from_another(base_poke);
	  /* Now let's apply some random modifier */
      r_att = random_double_in_poke_range();
      r_def = random_double_in_poke_range();
      r_hp =  random_double_in_poke_range();
      level_multiplier = 1+((level/10.0)-0.1);
      poke->attack = (int)floor(poke->attack * r_att);
      poke->defense = (int)floor(poke->defense * r_def);
      poke->hp_max = (int)floor(poke->hp_max * r_hp);
      poke->hp = poke->hp_max;
      
      /* let up to level in parameter */
      poke->level = level;
      if(level > MIN_LEVEL_POKETUDIANT)
	{
	  poke->xp = 500 * ((1 + (float)(poke->level-1)) / 2); 
	}
      /* Ensure to has a logic xp next */
      if(poke->level == MAX_LEVEL_POKETUDIANT)
	poke->xp_next = NEXT_LEVEL_CALC(poke->level-1);
      else
	poke->xp_next = NEXT_LEVEL_CALC(poke->level);
      
      poke->attack *= level_multiplier;
      poke->defense *= level_multiplier;
      poke->hp_max *= level_multiplier;
      poke->hp = poke->hp_max;
      /*Finally, let's build attacks for our poketudiant randomly
	For it, we need an attack with same type as poketudiant and another random
	except Teacher type */
      set_cmp_fct_for_hash_table(factory->ref_attack_base,cmp_attack_fct_via_type);
      att_1 = get_random_element_with_criteria_in_hash_table(factory->ref_attack_base,
							     &(poke->type));
	  
      set_cmp_fct_for_hash_table(factory->ref_attack_base,
				 cmp_attack_fct_via_type_refuse_and_no_teacher);
      att_2 = get_random_element_with_criteria_in_hash_table(factory->ref_attack_base,
							     &(poke->type));
      
      set_cmp_fct_for_hash_table(factory->ref_attack_base,save_cmp_fct);
      poke->ref_attack_1 = att_1;
      poke->ref_attack_2 = att_2;
      return poke;
    }
}

Poketudiant* generate_random_poketudiant(Poketudiant_factory* factory, int level)
{
  Poketudiant* getter_base = NULL;
  getter_base = get_random_element_in_hash_table(factory->ref_poketudiant_base);
  
  return generate_poketudiant(factory,getter_base,level);
}


Poketudiant* generate_random_capturable_poketudiant(Poketudiant_factory* factory, int level)
{
  Poketudiant* getter_base = NULL;
  int capturable_value = 1;

  /* Prepare for getting with criteria */
  int (*save_cmp_fct_poke)(void*,void*) = factory->ref_poketudiant_base->cmp_fct_linked_list;  
  set_cmp_fct_for_hash_table(factory->ref_poketudiant_base,cmp_poketudiant_fct_via_capturable);
  
  getter_base = get_random_element_with_criteria_in_hash_table(factory->ref_poketudiant_base,
							       &capturable_value);
  /* Reinit with saved function */
  set_cmp_fct_for_hash_table(factory->ref_poketudiant_base,save_cmp_fct_poke);
    
  return generate_poketudiant(factory,getter_base,level);
}

Poketudiant* generate_random_poketudiant_without_teacher(Poketudiant_factory* factory, int level)
{
  Poketudiant* getter_base = NULL;
  Type_poke restrict_teacher = TEACHER;
  int (*save_cmp_fct_poke)(void*,void*) = factory->ref_poketudiant_base->cmp_fct_linked_list;
  int (*save_hash)(void*) = factory->ref_poketudiant_base->hash_fct;
  
  /* prepare for getting from string */
  set_cmp_fct_for_hash_table(factory->ref_poketudiant_base,cmp_poketudiant_fct_via_type_refuse);
  factory->ref_poketudiant_base->hash_fct = hash_poketudiant_fct_from_string;
  
  getter_base = get_random_element_with_criteria_in_hash_table(factory->ref_poketudiant_base,
							       &restrict_teacher); 
  /* Reinit with saved function */
  factory->ref_poketudiant_base->hash_fct = save_hash;
  set_cmp_fct_for_hash_table(factory->ref_poketudiant_base,save_cmp_fct_poke);
  
  return generate_poketudiant(factory, getter_base,level);
}

Poketudiant* generate_poketudiant_from_name(Poketudiant_factory* factory, char* name, int level)
{
  Poketudiant* getter_base = NULL;
  int (*save_cmp_fct_poke)(void*,void*) = factory->ref_poketudiant_base->cmp_fct_linked_list;
  int (*save_hash)(void*) = factory->ref_poketudiant_base->hash_fct;
  
  /* prepare for getting from string */
  set_cmp_fct_for_hash_table(factory->ref_poketudiant_base,cmp_poketudiant_fct_via_variety);
  factory->ref_poketudiant_base->hash_fct = hash_poketudiant_fct_from_string;
  
  getter_base = get_element_in_hash_table(factory->ref_poketudiant_base,name);
  
  /* Reinit with saved function */
  factory->ref_poketudiant_base->hash_fct = save_hash;
  set_cmp_fct_for_hash_table(factory->ref_poketudiant_base,save_cmp_fct_poke);
  
  return generate_poketudiant(factory,getter_base,level);
}

Trainer* generate_random_trainer(Poketudiant_factory* factory, int level)
{
  Trainer* trainer;
  Poketudiant* ia_1;
  Poketudiant* ia_2;
  Poketudiant* ia_3;

  trainer = create_trainer("IA trainer",1);
  ia_1 = generate_poketudiant_from_name(factory,"Enseignant-dresseur",level);
  ia_2 = generate_random_poketudiant_without_teacher(factory,level);
  ia_3 = generate_random_poketudiant_without_teacher(factory,level);

  if(ia_1->level == MIN_LEVEL_POKETUDIANT)
    ia_1->xp = XP_START_WILD_POKE;
  if(ia_2->level == MIN_LEVEL_POKETUDIANT)
    ia_2->xp = XP_START_WILD_POKE;
  if(ia_3->level == MIN_LEVEL_POKETUDIANT)
    ia_3->xp = XP_START_WILD_POKE;

  add_poketudiant_to_team(trainer,ia_1);
  add_poketudiant_to_team(trainer,ia_2);
  add_poketudiant_to_team(trainer,ia_3);

  return trainer;
}
