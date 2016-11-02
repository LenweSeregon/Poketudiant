#ifndef __ATTACK_H__
#define __ATTACK_H__

struct Attack
{
  char* name;
  Type_poke type;
  unsigned int pow;
};
typedef struct Attack Attack;

Attack* create_attack(char* name, Type_poke type, unsigned int pow);
void delete_attack(Attack* attack);

void print_attack(const Attack* attack);

#endif
