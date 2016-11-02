#ifndef __POKETUDIANT_H__
#define __POKETUDIANT_H__

/*
 * @author : Nicolas
 * @date   : 31 / 10 / 2016
 *
 * @name   : Poketudiant
 * @desc   : This structure store all need attributs for a poketudiant
             We chose to only store current attack/defense/hp and another module will 
	     manage evolution etc with correct datas.
	     NOTE : CARE !! ref_attack_1 and ref_attack_2 are reference to an unique pointer
	     that represent all type of attack so you mustn't free yourself those pointer,
	     they gonna be free in a specific structure, you just need to work with but don't
	     manage memory on it
 */
struct Poketudiant
{
  unsigned int id;
  
  Type_poke type;
  char* variety;
  char* evolution;
  int capturable;

  Attack* ref_attack_1;
  Attack* ref_attack_2;
  
  unsigned int attack;
  unsigned int defense;
  unsigned int hp_max;
  unsigned int hp;
  
  unsigned int level;
  unsigned int xp;
  unsigned int xp_next;
};
typedef struct Poketudiant Poketudiant;

/*
 * @author : Nicolas
 * @date   : 31 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : create_poketudiant
 * @arg    : type , type of poketudiant in range [NOISY,LAZY,MOTIVATED,TEACHER]
`* @arg    : variety , char array that represent the variety name of poketudiant
 * @arg    : att_1 && att_2 , reference to attacks that poketudiant own 
 * @arg    : att && def && hp_max , basic caracteristics of poketudiant
 * @desc   : This function allocate memory for a poketudiant, build it properly
             according to parameters as a new poketudiant and return it as a pointer
 *
 * @return : Pointer on generated poketudiant;
 */
Poketudiant* create_poketudiant(Type_poke type, char* variety, 
				Attack* att_1, Attack* att_2,
				unsigned int att, unsigned int def, unsigned int hp_max,
				int capturable, char* evolution,int real_poketudiant);


/*
 * @author : Nicolas
 * @date   : 31 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : create_poketudiant_from_another
 * @arg    : pok , poketudiant that we want to copy for our new poketudiant
 * @desc   : This function allocate memory for a poketudiant, build it properly
             according to poketudiant gave inparameters as a new poketudiant and
	     return it as a pointer
 *
 * @return : Pointer on generated poketudiant;
 */
Poketudiant* create_poketudiant_from_another(const Poketudiant* pok);

/*
 * @author : Nicolas
 * @date   : 31 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : delete_poketudiant
 * @arg    : poketudiant , pointer on poketudiant that we want to delete
 * @desc   : This function is use to delete a poketudiant and ensure no memory leak on it
 *
 * @return : no return;
 */
void delete_poketudiant(Poketudiant* pok);

/*
 * @author : Nicolas
 * @date   : 31 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : take_damage
 * @arg    : poketudiant , pointer on poketudiant that we want to inflict damage
 * @arg    : damage ,  amount of damage that we want to inflict
 * @desc   : This function is use to inflict an amount of damage on a poketudiant and ensure
             to get hp to 0 if poketudiant is dead
 *
 * @return : return 1 if poketudiant is dead, 0 otherwise;
 */
int take_damage(Poketudiant* pok, unsigned int damage);


/*
 * @author : Nicolas
 * @date   : 31 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : earn_experience
 * @arg    : poketudiant , pointer on poketudiant that we want to earn experience
 * @arg    : experience ,  amount of experience that we want to earn
 * @desc   : This function is use to add an amount of experience on a poketudiant
 *
 * @return : return 1 if poketudiant is ready to level up, 0 otherwise;
 */
int earn_experience(Poketudiant* pok, unsigned int experience);


/*
 * @author : Nicolas
 * @date   : 31 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : print_complete_poketudiant
 * @arg    : poketudiant , pointer on poketudiant that we want to print
 * @desc   : This function is use to print a pokemon in it complete version
 *
 * @return : no return
 */
void print_complete_poketudiant(const Poketudiant* pok);

/*
 * @author : Nicolas
 * @date   : 31 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : print_concise_poketudiant
 * @arg    : poketudiant , pointer on poketudiant that we want to print
 * @desc   : This function is use to print a pokemon in it concise version
 *
 * @return : no return
 */
void print_concise_poketudiant(const Poketudiant* pok);

#endif
