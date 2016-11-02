#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "math_utils.h"
#include "string_utils.h"

#include "container.h"
#include "linked_list.h"
#include "hash_table.h"

#include "type_poke.h"
#include "attack.h"
#include "poketudiant.h"

#include "generic_control_function.h"
#include "loading_module.h"

#include "factories.h"

int main(void)
{
  Hash_table* att;
  Hash_table* poke;
  Poketudiant_factory* factory_poke;
  Poketudiant* test;
  init_seed_to_null();
  /*Poketudiant *poketudiant_1, *poketudiant_2;
  Attack *att_1, *att_2, *att_3, *att_4;

  att_1 = create_attack("Flemme",LAZY,10);
  att_2 = create_attack("Boucan",NOISY,10);
  att_3 = create_attack("Silence",MOTIVATED,10);
  att_4 = create_attack("Interro",TEACHER,20);

  poketudiant_1 = create_poketudiant(LAZY,"Someilprofon",att_1,att_3,10,10,20,1,"lol");
  poketudiant_2 = create_poketudiant(MOTIVATED,"AlleEnCours",att_3,att_2,10,10,30,1,"mdr");

  print_complete_poketudiant(poketudiant_1);
  printf("#######\n");
  print_complete_poketudiant(poketudiant_2);
  
  delete_poketudiant(poketudiant_1);
  delete_poketudiant(poketudiant_2);
  delete_attack(att_1);
  delete_attack(att_2);
  delete_attack(att_3);
  delete_attack(att_4);
  */

  att = create_hash_table(20);
  poke = create_hash_table(20);
  poke->hash_fct = hash_poketudiant_fct_from_poketudiant;
  poke->print_fct_linked_list = print_poketudiant_fct;
  poke->free_fct_linked_list = delete_poketudiant_fct;
  poke->cmp_fct_linked_list = cmp_poketudiant_fct_via_variety;
  att->hash_fct = hash_attack_fct;
  att->print_fct_linked_list = print_attack_fct;
  att->free_fct_linked_list = delete_attack_fct;
  att->cmp_fct_linked_list = cmp_attack_fct_via_type;
  
  load_base_attack(att,"init/attacks_file");
  load_base_poketudiant(poke,"init/pokemons_file");
  
  factory_poke = create_poketudiant_factory(poke,att);
  
  /* test = generate_poketudiant_from_name(factory_poke,"Nuidebou"); */
  test = generate_random_poketudiant(factory_poke);

  print_complete_poketudiant(test);
  /*print_hash_table(poke);
  printf("\n\n##########\n\n");
  print_hash_table(att);
  */
  delete_poketudiant(test);
  delete_poketudiant_factory(factory_poke);
  delete_hash_table(poke);
  delete_hash_table(att);
  return 0;
}
