#ifndef __BATTLE_MODULE_H__
#define __BATTLE_MODULE_H__

enum State_action
  {
    FIRST_ATTACK,
    SECOND_ATTACK,
    CHANGE_POKE,
    TRY_CAPTURE,
    TRY_ESCAPE
  };
typedef enum State_action State_action;

struct Battle_module
{
  Poketudiant_factory* ref_poke_factory;
  Evolve_center* ref_evolve_center;
};
typedef struct Battle_module Battle_module;

Battle_module* create_battle_module(Poketudiant_factory* ref_poke_facto,
				    Evolve_center* ref_evolve_center);
void delete_battle_module(Battle_module* battle_module);

void distribute_xp_to_poketudiants(Battle_module* battle_module, Container* all_poke, int total_xp);
int attack_poketudiant(Poketudiant* poke_att, Poketudiant* poke_def, Attack* att);
int try_to_capture(Poketudiant* poketudiant_ia);
int try_to_escape(Poketudiant* poketudiant_player, Poketudiant* poketudiant_ia);
Poketudiant* change_current_poketudiant_fighter(Trainer* trainer, Poketudiant* current_fighter);

void empty_buffer();
void display_opponents(Poketudiant* poke_player, Poketudiant* poke_ia);
void display_entrance_message(const char* name_1, const char* name_2);
void display_battle_menu_vs_wild_poketudiant();
void display_battle_menu_vs_trainer();

State_action manage_order_vs_wild_poketudiant();

/*State_action manage_order_vs_trainer();*/

int trainer_versus_random_wild_poketudiant(Battle_module* battle_module,
					    Trainer* trainer, 
					    int min_level, 
					    int max_level);


int trainer_versus_random_trainer(Battle_module* battle_module,
				   Trainer* trainer, 
				   int min_level,
				   int max_level);

/*int trainer_versus_trainer(Battle_module* battle_module,
			    Trainer* trainer,
			    Trainer* ia);
*/
#endif
