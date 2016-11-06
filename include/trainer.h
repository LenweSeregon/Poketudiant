#ifndef __TRAINER_H__
#define __TRAINER_H__

struct Trainer
{
  char* name;
  Container* team;
  Pokecafetaria* cafetaria;
  int ia_trainer;
};
typedef struct Trainer Trainer;

Trainer* create_trainer(const char* name, int ia_trainer);
void delete_trainer(Trainer* trainer);

int add_poketudiant_to_team(Trainer* trainer, Poketudiant* poke);
Poketudiant* remove_poketudiant_from_team(Trainer* trainer, int id); 

Poketudiant* select_first_poketudiant_in_life(Trainer* trainer);
int is_still_poketudiant_alive(Trainer* trainer);
int swap_poketudiant_position(Trainer* trainer, int i, int j);
int get_index_of_poketudiant_id(Trainer* trainer,int id);

void print_team_alive(const Trainer* trainer);
void print_team_alive_except_current_fighter(const Trainer* trainer, Poketudiant* fighter);
void print_team(const Trainer* trainer);

#endif
