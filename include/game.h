#ifndef __GAME_H__
#define __GAME_H__


struct Game
{
  Hash_table* base_poke;
  Hash_table* base_att;

  Poketudiant_factory* factory_poke;
  Evolve_center* evolve_center;
  Battle_module* battle_module;
  Trainer* trainer;
  
};
typedef struct Game Game;

int processing_catch(Game* game);
int processing_xp(Game* game);
int processing_exit(Game* game);

int processing_wild_command(Game* game);
int processing_rival_command(Game* game);
int processing_nurse(Game* game);
int processing_show(Game* game);
int processing_switch(Game* game);
int processing_move_table(Game* game);
int processing_drop(Game* game);
int processing_pick(Game* game);
int processing_release(Game* game);


Game* create_game(const char* trainer_name);
void delete_game(Game* game);
void launch_game(Game* game);

#endif
