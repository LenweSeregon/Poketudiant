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

/*
 * @name   : Battle_module
 * @desc   : This structure is use to store all reference structure needed for a battle.
             Indeed, we need to be able to create poketudiant, to make evolve a poketudiant that
	     earn some xp and to check weaknesses during attack function.
	     This structure simply prevent an interface with thoses references
 */
struct Battle_module
{
  Poketudiant_factory* ref_poke_factory;
  Evolve_center* ref_evolve_center;
  Weakness* ref_weakness;
};
typedef struct Battle_module Battle_module;


/*
 * @name   : create_battle_module
 * @arg    : ref_poke_facto , reference on poketudiant factory to create random poketud or trainer
 * @arg    : ref_evolve_center , reference on evolve center if needed when poketud earn xp
 * @arg    : ref_weakness , reference on weakness for attack function and multiplier calculation
 * @desc   : This function is use to create and allocate a battle module. Take care, this structure
             is containing in reality only references on modules needed so this structure is not 
	     responsable of their memory
 *
 * @return : return a pointer on allocated battle module
*/
Battle_module* create_battle_module(Poketudiant_factory* ref_poke_facto,
				    Evolve_center* ref_evolve_center,
				    Weakness* ref_weakness);

/*
 * @name   : create_attack
 * @arg    : battle_module , battle_module that's we want to delete and free
 * @desc   : This function is use to delete battle_module and ensure no memory leak.
             Remind, battle_module attributs are only references so their are not freed.
 *
 * @return : no return
*/
void delete_battle_module(Battle_module* battle_module);

/*
 * @name   : distribute_xp_to_poketudiant
 * @arg    : battle_module , pointer on battle_module that contain reference needed 
 * @arg    : all_poke , container that contain all poketudiant that take part of a battle and 
             should earn experience
 * @arg    : total_xp , total amount of experience for poketudiant, function ensure to divide and
             distrib
 * @desc   : This function is use to distribute xp at all poketudiant not dead that's take 
             part in a battle agains't a poketudiant and distribute fairly xp to all poketudiant.
	     This amount of experience earn by a poketudiant is simply total_xp / all_poke
 *
 * @return : no return
*/
void distribute_xp_to_poketudiants(Battle_module* battle_module, Container* all_poke, int total_xp);

/*
 * @name   : attack_poketudiant
 * @arg    : b_module , pointer on battle_module that contain reference needed 
 * @arg    : poke_att , pointer on poketudiant who is attacking other poketudiant
 * @arg    : poke_def , pointer on poketudiant who is going to get attack by attacker
 * @arg    : att , pointer on attack choosen between both available
 * @desc   : This function is use to simulate an attack between two poketudiant,
             this function take care to manage every factor needed in the calculation
	     (ie : weaknesses, def, attack of poketudiants)
 *
 * @return : return 1 if poke_def is dead, return 0 otherwise
*/
int attack_poketudiant(Battle_module* b_module,
		       Poketudiant* poke_att,
		       Poketudiant* poke_def, 
		       Attack* att);

/*
 * @name   : create_attack
 * @arg    : poketudiant_ia , poketudiant that's we are facing of. He's needed because capture
             chance is according to his current hp
 * @desc   : This function is use to simulate capture, and according to current hp return a
             result to say if capture is a success or not.
 *
 * @return : return 1 if capture is a success, 0 otherwise
*/
int try_to_capture(Poketudiant* poketudiant_ia);

/*
 * @name   : try_to_escape
 * @arg    : poketudiant_player , our current poketudiant fighter 
 * @arg    : poketudiant_ia , enemy poketudiant fighter
 * @desc   : This function is use to simulate an escape, and according to our poketudiant level
             and enemy poketudiant level, function return a result to say if escape is a success
	     or not
 *
 * @return : return 1 if escape is a success, 0 otherwise
*/
int try_to_escape(Poketudiant* poketudiant_player, Poketudiant* poketudiant_ia);

/*
 * @name   : change_current_poketudiant_fighter
 * @arg    : trainer , our trainer that's take part in the battle
 * @arg    : current_fighter , our current fighter in battle
 * @arg    : mandatory_chance , this parameter signal if chance can be cancel or no
 * @desc   : This function is use to change current poketudiant fighter during a battle.
             This function ensure the user to select an acceptable choice that mean a 
	     poketudiant id present in team and different from the current fighter
 *
 * @return : return pointer on the new poketudiant fighter
*/
Poketudiant* change_current_poketudiant_fighter(Trainer* trainer,
						Poketudiant* current_fighter,
						int mandatory_change);

/*
 * @name   : display_opponents
 * @arg    : poke_player , pointer on our current poketudiant fighter 
 * @arg    : poke_ia , pointer on current poketudiant enemy fighter
 * @desc   : This function is use to display opponents
 *
 * @return : no return
*/
void display_opponents(Poketudiant* poke_player, Poketudiant* poke_ia);


/*
 * @name   : display_battle_menu_vs_wild_poketudiant
 * @desc   : This function is use to display battle menu agains't a wild poketudiant
             that's mean we can attack him but also escape and capture in menu display
 *
 * @return : no return
*/
void display_battle_menu_vs_wild_poketudiant();

/*
 * @name   : display_battle_menu_vs_wild_poketudiant
 * @desc   : This function is use to display battle menu agains't a rival trainer
             that's mean we only can attack him and no escape or capture in menu display
 *
 * @return : no return
*/
void display_battle_menu_vs_trainer();

/*
 * @name   : manage_order_vs_wild_poketudiant
 * @desc   : This function is use ask a choice to user according to menu vs wild poketudiant
             display. The function ask the user an integer value representing a menu value
	     and check if this answer is available. Since she's not, function ask again to user
 *
 * @return : return the state action choose by user in enum range State_action
*/
State_action manage_order_vs_wild_poketudiant();

/*
 * @name   : manage_order_vs_trainer
 * @desc   : This function is use ask a choice to user according to menu vs trainer
             display. The function ask the user an integer value representing a menu value
	     and check if this answer is available. Since she's not, function ask again to user
 *
 * @return : return the state action choose by user in enum range State_action
*/
State_action manage_order_vs_trainer();


/*
 * @name   : trainer_versus_random_wild_poketudiant
 * @arg    : battle_module , pointer on battle_module that contain reference needed 
 * @arg    : trainer , our trainer that's gonna fight a random poketudiant
 * @arg    : min_level , minimum level of wild poketudiant that's we gonna face
 * @arg    : max_level , maximum level of wild poketudiant that's we gonna face
 * @desc   : This function is use to simulate a battle between our trainer and a random 
             poketudiant. The function ensure the game to work well by facing poketudiant,
	     giving damage and earning experience. This function return a result to know if
	     our trainer won the battle or not
 *
 * @return : return 1 if trainer won the battle , 0 otherwise
*/
int trainer_versus_random_wild_poketudiant(Battle_module* battle_module,
					    Trainer* trainer, 
					    int min_level, 
					    int max_level);


/*
 * @name   : trainer_versus_random_trainer
 * @arg    : battle_module , pointer on battle_module that contain reference needed 
 * @arg    : trainer , our trainer that's gonna fight a random poketudiant
 * @arg    : min_level , minimum level of trainer that's we gonna face
 * @arg    : max_level , maximum level of trainer that's we gonna face
 * @desc   : This function is use to simulate a battle between our trainer and a random enemy
             trainer. This function ensure the game to work well by facing poketudiant,
	     giving damage and earning experience. This function return a result to know if
	     our trainer won the battle or not
 *
 * @return : return 1 if trainer won the battle , 0 otherwise
*/
int trainer_versus_random_trainer(Battle_module* battle_module,
				   Trainer* trainer, 
				   int min_level,
				   int max_level);


#endif
