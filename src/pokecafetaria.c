#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "type_poke.h"
#include "attack.h"
#include "poketudiant.h"

#include "pokecafetaria.h"


Pokecafetaria* create_pokecafetaria()
{
  Pokecafetaria* caf = malloc(sizeof(Pokecafetaria));
  caf->list = calloc(MAX_POKETUDIANT_BY_TABLE*NB_TABLE_POKECAFETARIA,sizeof(Poketudiant*));
  return caf; 
}

int add_poketudiant_to_cafetaria(Pokecafetaria* caf, Poketudiant* etu)
{
  int i;
  for(i=0;i<MAX_POKETUDIANT_BY_TABLE*NB_TABLE_POKECAFETARIA;i++)
  {
    if(caf->list[i]==NULL)
    {
	caf->list[i] = etu;
	return 1;
    }
  }
  return 0;
}

int add_poketudiant_to_cafetaria_by_position(Pokecafetaria* caf, Poketudiant* etu, int t, int c)
{
  int pos = calcul_pos_pokecafetaria(t,c);
  if(caf->list[pos]!=NULL) caf->list[pos]=etu;

  return 0;/* pour les warning */
}

Poketudiant* get_poketudiant_from_cafetaria_by_position(Pokecafetaria* caf, int t, int c)
{
  return caf->list[calcul_pos_pokecafetaria(t,c)];
}

void swap_position_poketudiant_in_cafetaria(Pokecafetaria* caf, int t1, int c1, int t2, int c2)
{
  Poketudiant* tmp;
  int pos1, pos2;
  pos1 = calcul_pos_pokecafetaria(t1,c1);
  pos2 = calcul_pos_pokecafetaria(t2,c2);

  tmp = caf->list[pos1];
  caf->list[pos1] = caf->list[pos2];
  caf->list[pos2] = tmp; 
}

Poketudiant* pop_poketudiant_from_cafetaria(Pokecafetaria* caf, int t, int c)
{
  int pos1;
  Poketudiant* tmp;
  pos1 = calcul_pos_pokecafetaria(t,c);
  tmp = caf->list[pos1];
  caf->list[pos1] = NULL;
  return tmp;
}

/*void delete_poketudiant_from_table(Pokecafetaria* caf, int t, int c)
{

}*/

void delete_pokecafetaria(Pokecafetaria* caf)
{
  int i;
  for(i=0;i<NB_TABLE_POKECAFETARIA*MAX_POKETUDIANT_BY_TABLE;i++)
  {
    Poketudiant* poke = caf->list[i];
    if(poke!=NULL) delete_poketudiant(poke);
  }
  free(caf->list);
  free(caf);
}

int calcul_pos_pokecafetaria(int t, int c)
{
  return t*MAX_POKETUDIANT_BY_TABLE+c;
}
