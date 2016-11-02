#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "attack.h"


Attack *create_attack(char* name, unsigned int power)
{
  unsigned int name_size;
  Attack* attack = NULL;
  attack = malloc(sizeof(Attack));
  
  name_size = strlen(name) + 1;
  attack->name = malloc(sizeof(char) * name_size);
  strcpy(attack->name, name);
  attack->power = power;

  return attack;
}

void delete_attack(Attack* attack)
{
  free(attack->name);
  free(attack);
}

void print_attack_informations(const Attack* attack)
{
  printf("Attack = %s; Power = %d\n",attack->name,attack->power);
}
