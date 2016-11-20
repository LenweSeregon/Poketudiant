#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "type_poke.h"
#include "attack.h"
#include "constantes.h"
#include "poketudiant.h"

Poketudiant* create_poketudiant(Type_poke type, char* variety, 
				Attack* att_1, Attack* att_2,
				unsigned int att, unsigned int def, unsigned int hp_max,
				int capturable, char* evolution)
{

  Poketudiant* poketudiant = malloc(sizeof(Poketudiant));
  unsigned int size_variety = strlen(variety) + 1;
  unsigned int size_evolution = strlen(evolution) + 1;
   
  poketudiant->id = -1;

  poketudiant->variety = malloc(size_variety * sizeof(char));
  poketudiant->evolution = malloc(size_evolution * sizeof(char));
  strcpy(poketudiant->variety,variety);
  strcpy(poketudiant->evolution,evolution);
  poketudiant->type = type;
 
  poketudiant->ref_attack_1 = att_1;
  poketudiant->ref_attack_2 = att_2;

  poketudiant->attack = att;
  poketudiant->defense = def;
  poketudiant->hp_max = hp_max;
  poketudiant->hp = hp_max;

  poketudiant->capturable = capturable;

  poketudiant->level = 1;
  poketudiant->xp = 0;
  poketudiant->xp_next = XP_NEEDED_LEVEL_1;
 
  poketudiant->ref_attack_1 = NULL;
  poketudiant->ref_attack_2 = NULL;
  
  return poketudiant;
}

Poketudiant* create_poketudiant_from_another(const Poketudiant* pok)
{
  Poketudiant* new_poke = create_poketudiant(pok->type,pok->variety,
					     pok->ref_attack_1,pok->ref_attack_2,
					     pok->attack,pok->defense,pok->hp_max,
					     pok->capturable,pok->evolution);
  return new_poke;
}

void delete_poketudiant(Poketudiant* pok)
{
  free(pok->variety);
  free(pok->evolution);
  free(pok);
}

int take_damage(Poketudiant* pok, unsigned int damage)
{
  pok->hp -= damage;
  
  if(pok->hp <= 0)
    {
      pok->hp = 0;
      return 1;
    } 
  return 0;
}

int earn_experience(Poketudiant* pok, unsigned int experience)
{
  if(pok->level < MAX_LEVEL_POKETUDIANT)
    {
      pok->xp += experience;
      if(pok->xp >= pok->xp_next)
	{
	  return 1;
	}
    }
  else
    {
      pok->xp = pok->xp_next;
    }
  return 0;
}

void print_complete_poketudiant(const Poketudiant* pok)
{
  printf("*******************************************************\n");
  printf("\tCARACTERISTICS:\n");
  printf("ID = %d | Variety = %s | Type = %s\n",pok->id,pok->variety,string_from_enum_type_poke(pok->type));
  printf("Attack = %d | Defense = %d | Hp = %d / %d\n",pok->attack,pok->defense,pok->hp,pok->hp_max);
  printf("Level = %d | XP = %d / %d\n",pok->level,pok->xp,pok->xp_next);
  printf("\tATTACKS :\n");
  print_attack(pok->ref_attack_1);
  print_attack(pok->ref_attack_2);
  printf("*******************************************************\n");
}

void print_concise_poketudiant(const Poketudiant* pok)
{
  printf("*******************************************************\n");
  printf("\tCARACTERISTICS:\n");
  printf("ID = %d | Variety = %s\n",pok->id,pok->variety);
  printf("Hp = %d / %d\n",pok->hp,pok->hp_max);
  printf("Level = %d\n",pok->level);
  printf("*******************************************************\n");
}
