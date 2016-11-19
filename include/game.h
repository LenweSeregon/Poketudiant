#ifndef __GAME_H__
#define __GAME_H__

/*
 * @name   : Game
 * @desc   : This structure is use to store every entities needed in game.
             Here, there is not reference so every entites gonna be release at the end of the game
	     when delete game is called.
 */
struct Game
{
  Hash_table* base_poke;
  Hash_table* base_att;

  Poketudiant_factory* factory_poke;
  Evolve_center* evolve_center;
  Battle_module* battle_module;
  Trainer* trainer;
  Weakness* weakness;
  
};
typedef struct Game Game;

/*
 * @name   : processing_catch
 * @arg    : game , pointer on game that contain every entites needed for make actions
 * @desc   : This function is use as an action for processing catch action in game loop
 *
 * @return : return 1 because this function can't stop the game
 */
int processing_catch(Game* game);

/*
 * @name   : processing_xp
 * @arg    : game , pointer on game that contain every entites needed for make actions
 * @desc   : This function is use as an action for processing xp action in game loop
 *
 * @return : return 1 because this function can't stop the game
 */
int processing_xp(Game* game);

/*
 * @name   : processing_exit
 * @arg    : game , pointer on game that contain every entites needed for make actions
 * @desc   : This function is use as an action for processing exit action in game loop
 *
 * @return : return 1 if command is rightly writen, 0 otherwise
 */
int processing_exit(Game* game);

/*
 * @name   : processing_wild_command
 * @arg    : game , pointer on game that contain every entites needed for make actions
 * @desc   : This function is use as an action for processing wild battle action in game loop
 *
 * @return : return 1 if game must continue (mean trainer won battle), 0 otherwise
 */
int processing_wild_command(Game* game);

/*
 * @name   : processing_rival_command
 * @arg    : game , pointer on game that contain every entites needed for make actions
 * @desc   : This function is use as an action for processing rival batle action in game loop
 *
 * @return : return 1 if game must continue (mean trainer won battle), 0 otherwise
 */
int processing_rival_command(Game* game);

/*
 * @name   : processing_nurse
 * @arg    : game , pointer on game that contain every entites needed for make actions
 * @desc   : This function is use as an action for processing catch action in game loop
 *
 * @return : return 1 because this function can't stop the game
 */
int processing_nurse(Game* game);

/*
 * @name   : processing_show
 * @arg    : game , pointer on game that contain every entites needed for make actions
 * @desc   : This function is use as an action for processing show action in game loop.
             This function handle different type of show with for example show pokecafeteria,
	     show id, show team ,etc ...
 *
 * @return : return 1 if game must continue, 0 otherwise
 */
int processing_show(Game* game);

/*
 * @name   : processing_switch
 * @arg    : game , pointer on game that contain every entites needed for make actions
 * @desc   : This function is use as an action for processing switch action in game loop
 *
 * @return : return 1 because this function can't stop the game
 */
int processing_switch(Game* game);

/*
 * @name   : delete_attack
 * @arg    : game , pointer on game that contain every entites needed for make actions
 * @desc   : This function is use as an action for processing move_table action in game loop
 *
 * @return : return 1 because this function can't stop the game
 */
int processing_move_table(Game* game);

/*
 * @name   : delete_attack
 * @arg    : game , pointer on game that contain every entites needed for make actions
 * @desc   : This function is use as an action for processing drop action in game loop
 *
 * @return : return 1 because this function can't stop the game
 */
int processing_drop(Game* game);

/*
 * @name   : delete_attack
 * @arg    : game , pointer on game that contain every entites needed for make actions
 * @desc   : This function is use as an action for processing pick action in game loop
 *
 * @return : return 1 because this function can't stop the game
 */
int processing_pick(Game* game);

/*
 * @name   : delete_attack
 * @arg    : game , pointer on game that contain every entites needed for make actions
 * @desc   : This function is use as an action for processing release action in game loop
 *
 * @return : return 1 because this function can't stop the game
 */
int processing_release(Game* game);

/*
 * @name   : create_game
 * @arg    : trainer_name , name of ur trainer
 * @desc   : This function is use to allocate a new game structure. In this function all
             game's attribut gonna be initialize and allocate too
 *
 * @return : return allocated pointer of game structure
 */
Game* create_game(const char* trainer_name);

/*
 * @name   : delete_game
 * @arg    : game , pointer on game that we want to delete
 * @desc   : This function is use to delete game structure in parameter and ensure no memory leak
             after calling this function
 *
 * @return : no return 
 */
void delete_game(Game* game);

/*
 * @name   : launch_game
 * @arg    : game , pointer on game that contain every entites needed for make actions
 * @desc   : This function is use to launch the game. It mean this function ensure to continue
             the game since we have no losing battle or typing "exit" command
 *
 * @return : no return
 */
void launch_game(Game* game);

#endif
