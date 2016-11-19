#ifndef __ATTACK_H__
#define __ATTACK_H__

/*
 * @name   : Attack
 * @desc   : This structure is use to store a poketudiant attack, that's mean containing a name
             a type and a power stat. 
	     It's gonna be use in poketudiant to represent an attack.
 */
struct Attack
{
  char* name;
  Type_poke type;
  unsigned int pow;
};
typedef struct Attack Attack;

/*
 * @name   : create_attack
 * @arg    : name , representing the attack's name 
 * @arg    : type , representing the attack's type in range of type_poke enum
 * @arg    : pow , representing an unsigned int value for attack's power
 * @desc   : This function is use to create and allocate an attack. It's provide to set all
             structure attribut with values specify in parameters
 *
 * @return : return a pointer on allocated attack
*/
Attack* create_attack(char* name, Type_poke type, unsigned int pow);

/*
 * @name   : delete_attack
 * @arg    : attack , attack that's we want to delete and free
 * @desc   : This function is use to delete an attack gave in parameter, it ensure to 
             avoid memory leak by righty freeing the attack structure.
 *
 * @return : no return
 */
void delete_attack(Attack* attack);

/*
 * @name   : print_attack
 * @arg    : attack , attack that's we want to print
 * @desc   : This function is use to print attack gave in parameter, as displaying his name,
             his type and his power
 *
 * @return : no return
*/
void print_attack(const Attack* attack);

#endif
