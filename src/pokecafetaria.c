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
  
  if(caf->list[pos]==NULL&&pos!=-1)
    {
      caf->list[pos]=etu;
      return 1;
    }
  return 0;
}

void heal_all_pokecafetaria(Pokecafetaria* caf)
{
  int i;
  for(i=0;i<MAX_POKETUDIANT_BY_TABLE*NB_TABLE_POKECAFETARIA;i++)
    {
      if(caf->list[i] != NULL)
	{
	  caf->list[i]->hp = caf->list[i]->hp_max;
	}
    }
}

Poketudiant* get_poketudiant_from_cafetaria_by_id(Pokecafetaria* caf, int id)
{
  int position = get_position_poketudiant_id_in_cafetaria(caf,id);
  if(position == -1)
    return NULL;
  else
    return caf->list[position];
}

int get_position_poketudiant_id_in_cafetaria(Pokecafetaria* caf, unsigned int id)
{
  int i;
  for(i=0;i<MAX_POKETUDIANT_BY_TABLE*NB_TABLE_POKECAFETARIA;i++)
    {
      if(caf->list[i] != NULL && caf->list[i]->id == id)
	{
	  caf->list[i]->hp = caf->list[i]->hp_max;
	}
    }
  return -1;
}

Poketudiant* get_poketudiant_from_cafetaria_by_position(Pokecafetaria* caf, int t, int c)
{
  int pos = calcul_pos_pokecafetaria(t,c);
  if(pos!=-1)
    return caf->list[pos];
  else
    return NULL;
}

void swap_position_poketudiant_in_cafetaria_via_id(Pokecafetaria* caf, int id_1, int id_2)
{
  int pos_1 = get_position_poketudiant_id_in_cafetaria(caf,id_1);
  int pos_2 = get_position_poketudiant_id_in_cafetaria(caf,id_2);
  Poketudiant* tmp;
  if(pos_1 == -1)
    {
      printf("There is no poketudiant in cafetaria with ID = %d. Swap impossible\n",id_1);
      return;
    }
  if(pos_2 == -1)
    {
      printf("There is no poketudiant in cafetaria with ID = %d. Swap impossible\n",id_2);
      return;
    }

  tmp = caf->list[pos_1];
  caf->list[pos_1] = caf->list[pos_2];
  caf->list[pos_2] = tmp;
}

void swap_position_poketudiant_in_cafetaria(Pokecafetaria* caf, int t1, int c1, int t2, int c2)
{
  Poketudiant* tmp;
  int pos1, pos2;
  pos1 = calcul_pos_pokecafetaria(t1,c1);
  if(pos1==-1) return;
  pos2 = calcul_pos_pokecafetaria(t2,c2);
  if(pos2==-1) return;
  tmp = caf->list[pos1];
  caf->list[pos1] = caf->list[pos2];
  caf->list[pos2] = tmp; 
}

Poketudiant* pop_poketudiant_from_cafetaria_via_id(Pokecafetaria* caf, int id)
{
  int pos = get_position_poketudiant_id_in_cafetaria(caf,id);
  Poketudiant* to_pop;
  if(pos == -1)
    {
      printf("Poketudiant with that id is not present in cafetaria, pop is impossible.\n");
      return NULL;
    }
  
  to_pop = caf->list[pos];
  caf->list[pos] = NULL;
  return to_pop;
}

Poketudiant* pop_poketudiant_from_cafetaria(Pokecafetaria* caf, int t, int c)
{
  int pos;
  Poketudiant* tmp;
  pos = calcul_pos_pokecafetaria(t,c);
  if(pos==-1) return NULL;
  tmp = caf->list[pos];
  caf->list[pos] = NULL;
  return tmp;
}

void delete_poketudiant_from_table(Pokecafetaria* caf, int t, int c)
{
  Poketudiant* tmp = pop_poketudiant_from_cafetaria(caf,t,c);
  if(tmp!=NULL) delete_poketudiant(tmp);
}

void delete_poketudiant_from_cafetaria_by_id(Pokecafetaria* caf, int id)
{
  int pos = get_position_poketudiant_id_in_cafetaria(caf,id);
  Poketudiant* to_remove;
  if(pos == -1)
    {
      printf("Poketudiant with that id is not present in cafetaria, delete is impossible.\n");
      return;
    }
  to_remove = caf->list[pos];
  caf->list[pos] = NULL;
  delete_poketudiant(to_remove);
}

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
  if(t<0||c<0||t>=NB_TABLE_POKECAFETARIA||c>=MAX_POKETUDIANT_BY_TABLE)
    {
      printf("Bad position\n");
      return -1;
    }
  return t*MAX_POKETUDIANT_BY_TABLE+c;
}

void print_pokecafetaria(Pokecafetaria* caf)
{
  int i;
  printf("POKECAFETARIA : \n");
  for(i=0;i<NB_TABLE_POKECAFETARIA;i++)
    {
      print_table_pokecafetaria(caf,i);
    }
}

void print_table_pokecafetaria(Pokecafetaria* caf, int t)
{
  int i;
  if(t>NB_TABLE_POKECAFETARIA-1)
    {
      printf("No table %d\n",t);
      return;
    }
  printf("Table %d\n",t);
  for(i=0;i<MAX_POKETUDIANT_BY_TABLE;i++)
    {
      Poketudiant* tmp = get_poketudiant_from_cafetaria_by_position(caf,t,i);
      printf("\tSeat %d : ",i);
      if(tmp!=NULL)
	{
	  printf("\n");
	  print_concise_poketudiant(tmp);
	  printf("\n");
	}
      else printf("Empty\n");
    }
}
