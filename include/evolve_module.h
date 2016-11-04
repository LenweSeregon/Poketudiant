#ifndef __EVOLVE_MODULE_H__
#define __EVOLVE_MODULE_H__

struct Evolve_center
{
  Hash_table* ref_poke_base;
};
typedef struct Evolve_center Evolve_center;

Evolve_center* create_evolve_center(Hash_table* ref_poke_base);
void delete_evolve_center(Evolve_center* center);

int make_poketudiant_evolve(Evolve_center* center, 
			    Poketudiant* poke, 
			    double coeff_att,
			    double coeff_def,
			    double coeff_hp);

void make_poketudiant_upgrade(Evolve_center* center, Poketudiant* poke);
#endif
