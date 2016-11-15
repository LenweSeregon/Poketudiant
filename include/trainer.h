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
int poketudiant_movement_from_cafet_to_trainer(Trainer* trainer, Poketudiant* poke);
Poketudiant* remove_poketudiant_from_team(Trainer* trainer, int id); 

void heal_all_team(Trainer* trainer);
void drop_to_pokecafetaria(Trainer* trainer, int id);
void pick_from_pokecafetaria(Trainer* trainer, int id);
void release_from_pokecafetaria(Trainer* trainer, int id);

Poketudiant* select_poketudiant_by_id_in_trainer(const Trainer* trainer, int id);
Poketudiant* select_first_poketudiant_in_life(Trainer* trainer);
int is_still_poketudiant_alive(Trainer* trainer);
int swap_poketudiant(Trainer* trainer, int id_1, int id_2);
int swap_position_poketudiant_by_id(Trainer* trainer, int id_1, int id_2);
int get_index_of_poketudiant_id(const Trainer* trainer,int id);

void print_poketudiant_id_from_trainer(const Trainer* trainer, int id);
void print_team_alive(const Trainer* trainer);
void print_team_alive_except_current_fighter(const Trainer* trainer, Poketudiant* fighter);
void print_team(const Trainer* trainer);
void print_trainer_cafetaria(const Trainer* trainer);
void print_trainer_revision_table_t(const Trainer* trainer, int t);

#endif
