#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type_poke.h"
#include "attack.h"

Attack* create_attack(char* name, Type_poke type, unsigned int pow)
{
  Attack* attack = malloc(sizeof(Attack));
  unsigned int size_name = strlen(name) + 1;
  attack->name = malloc(size_name * sizeof(char));
  strcpy(attack->name,name);
  attack->type = type;
  attack->pow = pow;

  return attack;
}

void delete_attack(Attack* attack)
{
  free(attack->name);
  free(attack);
}

void print_attack(const Attack* attack)
{
  printf("Name = %s | Type = %s | Pow = %d\n",attack->name,
	                                    string_from_enum_type_poke(attack->type),
	                                    attack->pow);
}
