#ifndef __EVOLVE_MODULE_H__
#define __EVOLVE_MODULE_H__

struct Evolve_center
{
  Hash_table* ref_poketudiant_base;
};
typedef struct Evolve_center Evolve_center;

Evolve_center* create_evolve_center(Hash_table* ref_poke_base);
void delete_evolve_center(Evolve_center* center);


#endif
