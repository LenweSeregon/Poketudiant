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

#include "pokecafetaria.h"
#include "trainer.h"

#include "generic_control_function.h"
#include "loading_module.h"

#include "evolve_module.h"
#include "factories.h"

#include "battle_module.h"

/* lol  mdr */
int main(void)
{
  Hash_table* att;
  Hash_table* poke;
  Poketudiant_factory* factory_poke;
  Poketudiant* test;
  Poketudiant* test2;
  Poketudiant* test3;
  Poketudiant* test4;
  /*Poketudiant* to_remove;*/
  Poketudiant *g0,*g1,*g2,*g3;
  Evolve_center* center;
  Pokecafetaria* cafe;
  Trainer* trainer;
  Battle_module* battle;
  init_seed_to_null();

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
  
  center = create_evolve_center(poke);
  factory_poke = create_poketudiant_factory(poke,att);
  battle = create_battle_module(factory_poke,center);
  
  test = generate_poketudiant_from_name(factory_poke,"Enseignant-dresseur",1);
  test2 = generate_random_capturable_poketudiant(factory_poke,1);
  test3 = generate_random_capturable_poketudiant(factory_poke,5);
  test4 = generate_random_capturable_poketudiant(factory_poke,1);

  trainer = create_trainer("Josh",0);
  add_poketudiant_to_team(trainer,test);
  add_poketudiant_to_team(trainer,test2);
  add_poketudiant_to_team(trainer,test3);
  add_poketudiant_to_team(trainer,test4);
  
  /*print_team(trainer);
   */
  /*trainer_versus_random_wild_poketudiant(battle,trainer,1,2);
   */
  trainer_versus_random_trainer(battle,trainer,1,1);
  print_team(trainer);
  heal_all_team(trainer);
  print_team(trainer);


  g0 = generate_random_poketudiant(factory_poke,1);
  g1 = generate_random_poketudiant(factory_poke,1);
  g2 = generate_random_poketudiant(factory_poke,1);
  g3 = generate_random_poketudiant(factory_poke,1);
  cafe = create_pokecafetaria();
  

  add_poketudiant_to_cafetaria(cafe,g0);
  add_poketudiant_to_cafetaria_by_position(cafe,g1,0,3);
  add_poketudiant_to_cafetaria_by_position(cafe,g2,2,0);
  add_poketudiant_to_cafetaria(cafe,g3);
  
  /*print_pokecafetaria(cafe);*/

  delete_trainer(trainer);
  delete_pokecafetaria(cafe);
  delete_battle_module(battle);
  delete_poketudiant_factory(factory_poke);
  delete_evolve_center(center);
  delete_hash_table(poke);
  delete_hash_table(att);
  return 0;
}
