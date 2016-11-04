#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "type_poke.h"
#include "attack.h"
#include "poketudiant.h"

#include "generic_control_function.h"

int hash_poketudiant_fct_from_poketudiant(void* element)
{
  Poketudiant* p = (Poketudiant*)element;
  int hash = 0;
  int i;
  for(i = 0; p->variety[i] != '\0'; i++)
    {
      hash += p->variety[i];
    }
  
  return hash;
}

int hash_poketudiant_fct_from_string(void* element)
{
  char* s = (char*)element;
  int hash = 0;
  int i;
  for(i = 0; s[i] != '\0'; i++)
    {
      hash += s[i];
    }
  return hash;
}

void print_poketudiant_fct(void* element)
{
  Poketudiant* p = (Poketudiant*)element;
  print_concise_poketudiant(p);
}

void delete_poketudiant_fct(void* element)
{
  Poketudiant* p = (Poketudiant*)element;
  delete_poketudiant(p);
}

int cmp_poketudiant_fct_via_type(void* a, void* b)
{
  Poketudiant* aBis = (Poketudiant*)a;
  Type_poke type = *((Type_poke*)b);
  
  if(aBis->type == type) return 0;
  else return 1;
}

int cmp_poketudiant_fct_via_variety(void* a, void* b)
{
  Poketudiant* aBis = (Poketudiant*)a;
  char* string = (char*)b;

  if(strcmp(aBis->variety,string) == 0)
    return 0;
  else
    return 1;
}

int cmp_poketudiant_fct_via_id(void* a, void* b)
{
  Poketudiant* aBis = (Poketudiant*)a;
  unsigned int id = *((int*)b);

  if(aBis->id == id)
    return 0;
  else
    return 1;
}

int cmp_poketudiant_fct_via_capturable(void* a, void* b)
{
  Poketudiant* aBis = (Poketudiant*)a;
  int capt = *((int*)b);

  if(aBis->capturable == capt)
    return 0;
  else
    return 1;
}

int hash_attack_fct(void* element)
{
  Attack* p = (Attack*)element;
  int hash = 0;
  int i;
  for(i = 0; p->name[i] != '\0'; i++)
    {
      hash += p->name[i];
    }
  
  return hash;
}

void print_attack_fct(void* element)
{
  Attack* a = (Attack*)element;
  print_attack(a);
}

void delete_attack_fct(void* element)
{
  Attack* a = (Attack*)element;
  delete_attack(a);
}

int cmp_attack_fct_via_type(void* a, void* b)
{
  Attack* aBis = (Attack*)a;
  Type_poke type = *((Type_poke*)b);
  
  if(aBis->type == type) return 0;
  else return 1;

}

int cmp_attack_fct_via_type_and_no_teacher(void* a, void* b)
{
  Attack* aBis = (Attack*)a;
  Type_poke type = *((Type_poke*)b);

  if(aBis->type == type && aBis->type != TEACHER) return 0;
  else return 1;
}

int cmp_attack_fct_via_type_refuse(void* a, void* b)
{
  Attack* aBis = (Attack*)a;
  Type_poke type = *((Type_poke*)b);
  
  if(aBis->type == type) return 1;
  else return 0;

}

int cmp_attack_fct_via_type_refuse_and_no_teacher(void* a, void* b)
{
  Attack* aBis = (Attack*)a;
  Type_poke type = *((Type_poke*)b);
  
  if(aBis->type == type || aBis->type == TEACHER) return 1;
  else return 0;
}
