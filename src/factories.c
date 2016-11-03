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

Poketudiant* generate_random_poketudiant(Poketudiant_factory* factory)
{
  Poketudiant* poke = NULL;
  Poketudiant* getter_base = NULL;

  getter_base = get_random_element_in_hash_table(factory->ref_poketudiant_base);

  if(getter_base == NULL)
    {
      return NULL;
    }
  else
    {
      double r_att, r_def, r_hp;
      Attack* att_1;
      Attack* att_2;
      int (*save_cmp_fct)(void*,void*) = factory->ref_attack_base->cmp_fct_linked_list;
      /* We save the cmp fct from the hash table */
      
      /* First build basic poketudiant */ 
      poke = create_poketudiant_from_another(getter_base);
      /* Now let's apply some random modifier */
      r_att = random_double_in_poke_range();
      r_def = random_double_in_poke_range();
      r_hp =  random_double_in_poke_range();
      poke->attack = (int)round(poke->attack * r_att);
      poke->defense = (int)round(poke->defense * r_def);
      poke->hp_max = (int)round(poke->hp_max * r_hp);
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
    }
  return poke;
}

Poketudiant* generate_poketudiant_from_name(Poketudiant_factory* factory,char* name)
{
  Poketudiant* poke = NULL;
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

  if(getter_base == NULL)
    {
      return NULL;
    }
  else
    {
      double r_att, r_def, r_hp;
      Attack* att_1;
      Attack* att_2;
      int (*save_cmp_fct)(void*,void*) = factory->ref_attack_base->cmp_fct_linked_list;
      /* We save the cmp fct from the hash table */
      
      /* First build basic poketudiant */ 
      poke = create_poketudiant_from_another(getter_base);
      /* Now let's apply some random modifier */
      r_att = random_double_in_poke_range();
      r_def = random_double_in_poke_range();
      r_hp =  random_double_in_poke_range();
      poke->attack = (int)round(poke->attack * r_att);
      poke->defense = (int)round(poke->defense * r_def);
      poke->hp_max = (int)round(poke->hp_max * r_hp);
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
    }
  return poke;
}
