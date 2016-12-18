#ifndef __TRAINER_H__
#define __TRAINER_H__

/*
 * @name   : Trainer
 * @desc   : This structure is use to store all attributs needed in a trainer.
             Trainer is compose of 3 poketudiant in maximum store in generic container
	     Trainer has a name, and a pokecafeteria to store a maximum of other poketudiant
	     His last argument is to know if this trainer is an ia_trainer
 */
struct Trainer
{
  char* name;
  Container* team;
  Pokecafetaria* cafetaria;
  int ia_trainer;
  int has_move;
};
typedef struct Trainer Trainer;



/*
 * @name   : create_trainer
 * @arg    : name , name of trainer
 * @arg    : ia_trainer , value to specify if trainer is an ia trainer or not
 * @desc   : This function is use to allocate a trainer and to made ready all his attributs
             such as his container or his pokecafetaria according to parameters
 *
 * @return : pointer representing allocated trainer
*/
Trainer* create_trainer(const char* name, int ia_trainer);

/*
 * @name   : delete_trainer
 * @arg    : trainer , pointer on trainer that's we want to delete and free
 * @desc   : This function is use to delete a trainer gave in parameter, it ensure to 
             avoid memory leak by righty freeing the attack structure.
 *
 * @return : no return
*/
void delete_trainer(Trainer* trainer);

/*
 * @name   : add_poketudiant_to_team
 * @arg    : trainer , pointer on trainer where we want to add poketuidant
 * @desc   : This function is use to add pokeutidant in trainer team. That's mean this function
             will first try to add poketudiant to 3-poke team trainer. If there is no more place
	     in his team, it'll try to add poketudiant in his cafetaria. Finally if there is no
	     place in pokecafetaria, poketudiant will run away and being freed before.
	     If trainer is not an IA trainer, function ensure to give him an unique id
 *
 * @return : return 1 if poketudiant has been rightly add in team, 0 otherwise (no more place)
*/
int add_poketudiant_to_team(Trainer* trainer, Poketudiant* poke);

/*
 * @name   : poketudiant_movement_from_cafet_to_trainer
 * @arg    : trainer , pointer on trainer that's we want to make movement
 * @arg    : poke , poketudiant that's we want to add to trainer
 * @desc   : This function is use to try adding a poketudiant to team such as add_poketudiant, but
             here, the function doesn't take care about creation of an unique ID. That's mean you 
	     shouldn't use this function if you want to add a new poketudiant to team.
	     Use it to make some transfer from trainer pokecafetaria to trainer team for example.
	     Mean use it with a poketudiant which has already an id
 *
 * @return : return 1 if poketudiant has rightly move to team (there is place) , 0 otherwise
*/
int poketudiant_movement_from_cafet_to_trainer(Trainer* trainer, Poketudiant* poke);

/*
 * @name   : remove_poketudiant_from_team
 * @arg    : trainer , pointer on trainer where we want to remove poketudiant by id
 * @arg    : id , id of poketudiant that's we want to remove
 * @desc   : This function is use to remove a specify poketudiant in team according to id given
             in parameter. Take care this function return the poketudiant removed, it's mean
	     trainer team container is not anymore responsable of memory you must free it
 *
 * @return : pointer on poketudiant removed from team
*/
Poketudiant* remove_poketudiant_from_team(Trainer* trainer, int id); 

/*
 * @name   : heal_all_team
 * @arg    : trainer , pointer on trainer that's we want to heal all poketudiant
 * @desc   : This function is use to heal all poketudiant owning by a trainer that's mean
             This function heal all poketudiant in trainer team and in trainer cafetaria
 *
 * @return : no return
*/
void heal_all_team(Trainer* trainer);

/*
 * @name   : drop_to_pokecafetaria
 * @arg    : trainer , pointer on trainer where we want to drop poketudiant
 * @arg    : id , id of poketudiant that's we want to drop from team to pokecafetaria
 * @desc   : This function is use to drop a poketudiant from trainer team to trainer cafetaria.
             this function ensure if insertion in cafetaria succeed (mean there is places in 
	     cafetaria and function found poketudiant representing by id) to remove poketudiant 
	     from team and to insert him in cafetaria by transfering memory responsability
 *
 * @return : no return
*/
void drop_to_pokecafetaria(Trainer* trainer, int id);

/*
 * @name   : pick_from_pokecafetaria
 * @arg    : trainer , pointer on trainer where we want to pick poketudiant
 * @arg    : id , id of poketudiant that's we want to pick from pokecafetaria to team
 * @desc   : This function is use to pick a poketudiant from cafeteria to trainer team.
             this function ensure if insertion in trainer team succeed (mean there is places in 
	     cafetaria and function found poketudiant representing by id) to remove poketudiant 
	     from cafeteria and to insert him in team by transfering memory responsability
 *
 * @return : no return
*/
void pick_from_pokecafetaria(Trainer* trainer, int id);

/*
 * @author : Nicolas
 * 
 * @name   : release_from_cafecataria
 * @arg    : trainer , pointer on trainer where we want to release poketudiant
 * @desc   : This function is use to release a specific poketudiant according to id given
             in parameter. Care this function can't relese a poketudiant which is currently in
	     team. Only usable to release a poketudiant from trainer's pokecafetaria.
	     Function call in this function ensure if poketudiant has been found to free memory
 *
 * @return : no return
*/
void release_from_pokecafetaria(Trainer* trainer, int id);

/*
 * @name   : move_table_poketudiant
 * @arg    : trainer , pointer on trainer where we want to make move-table operation on cafeteria
 * @arg    : id , id representing poketudiant that's we want to move in table specify in parameter
 * @arg    : t , int representing table number where we want to move our poketudiant 
 * @desc   : This function is use to move-table a poketudiant from team or cafeteria.
             This function can no opere move-table if there is no place in table or if 
	     poketudiant has not been found
 *
 * @return : return 1 if move-table has work, 0 otherwise
*/
int move_table_poketudiant(Trainer* trainer, int id, int t);

/*
 * @name   : select_poketudiant_by_id_in_trainer
 * @arg    : trainer , pointer on trainer where we want select by id
 * @arg    : id , id of poketudiant that's we want to select
 * @desc   : This function is use to select a poketudiant by id in trainer team or in 
             trainer pokecafeteria. If there is no poketudiant found by this ID in both
	     return NULL
 *
 * @return : return pointer on poketudiant if found , NULL otherwise
*/
Poketudiant* select_poketudiant_by_id_in_trainer(const Trainer* trainer, int id);

/*
 * @name   : select_first_poketudiant_in_life
 * @arg    : trainer , pointer on trainer where we want to select first poketudiant in life
 * @desc   : This function is use to select first poketudiant in life in trainer team. If all
             possible poketudiant in trainer team are dead, return NULL
 *
 * @return : return pointer on poketudiant if found , NULL otherwise
*/
Poketudiant* select_first_poketudiant_in_life(Trainer* trainer);

/*
 * @name   : is_still_poketudiant_alive
 * @arg    : trainer , pointer on trainer where we want to see if there is poketudiant alive
 * @desc   : This function is use to know if there is still poketudiant alive in trainer team
 *
 * @return : return 1 if there is still poketudiant alive, 0 otherwise
*/
int is_still_poketudiant_alive(Trainer* trainer);

/*
 * @name   : swap_poketudiant
 * @arg    : trainer , pointer on trainer where we want to swap 2 poketudiants by id
 * @arg    : id_1 , id of first poketudiant we want to swap
 * @arg    : id_2 , id of second poketudiant we want to swap
 * @desc   : This function is use to swap 2 poketudiants that's can be in trainer team or 
             in trainer cafetaria. 
 *
 * @return : return 1 if swap has succeed, 0 otherwise
*/
int swap_poketudiant(Trainer* trainer, int id_1, int id_2);

/*
 * @name   : swap_position_poketudiant_by_id
 * @arg    : trainer , pointer on trainer where we want to swap position of trainer poketudiant
 * @arg    : id_1 , id of first poketudiant we want to swap
 * @arg    : id_2 , id of second poketudiant we want to swap
 * @desc   : This function is use to swap 2 poketudiant that's only are in trainer team.
 *
 * @return : return 1 if swap has succeed, 0 otherwise
*/
int swap_position_poketudiant_by_id(Trainer* trainer, int id_1, int id_2);

/*
 * @name   : get_index_of_poketudiant_id
 * @arg    : trainer , pointer on trainer where we are looking for poketudiant
 * @arg    : id , id of poketudiant we are looking for
 * @desc   : This function is use to get index position of poketudiant id in trainer team 
             according to id given in parameter
 *
 * @return : return position of poetudiant if in trainer team container if found, -1 otherwise
*/
int get_index_of_poketudiant_id(const Trainer* trainer,int id);

void print_poketudiant_id_from_trainer(const Trainer* trainer, int id);
void print_team_alive(const Trainer* trainer);
void print_team_alive_except_current_fighter(const Trainer* trainer, Poketudiant* fighter);
void print_team(const Trainer* trainer);
void print_trainer_cafetaria(const Trainer* trainer);
void print_trainer_revision_table_t(const Trainer* trainer, int t);

#endif
