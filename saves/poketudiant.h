#ifndef __POKETUDIANT_H__
#define __POKETUDIANT_H__

struct Poketudiant
{
  unsigned int unique_id;
  
  char* name;
  char* evolution;

  int capturable;
  
  double coeff_attack;
  double coeff_defense;
  double coeff_hp;
  
  unsigned int attack;
  unsigned int defense;
  unsigned int hp_max;
  unsigned int current_hp;
  
  unsigned int lvl;
  unsigned int current_xp;
  unsigned int xp_next_lvl;
};
typedef struct Poketudiant Poketudiant;

Poketudiant* create_poketudiant(char* name, char* evol, int capt, unsigned int att, unsigned int def, unsigned int hp_max, double coef_att, double coeff_def, double coeff_hp);
void delete_poketudiant(Poketudiant* poketudiant);

int take_damage(Poketudiant* poketudiant, unsigned int quantity);
int evolve(Poketudiant* poketudiant);
void up_level(Poketudiant* poketudiant);
void get_experience(Poketudiant* poketudiant, unsigned int quantity);

void print_complete_poketudiant_informations(const Poketudiant* poketudiant);
void print_concive_poketudiant_informations(const Poketudiant* poketudiant);
#endif
