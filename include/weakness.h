#ifndef __WEAKNESS_H__
#define __WEAKNESS_H__

typedef int** Weakness;

/* Il faudra voir à stocker le nombre de type quelque part ou à ajouter un last a l'enum Typepoke*/

/*
 * @name   : create_weakness
 * @desc   : This function is use to allocate a 2D int array representing all weakness in game
             This function use define NB_TYPE_POKE for array size
 *
 * @return : pointer on allocated 2D array of weakness
 */
Weakness* create_weakness();

/* type 1 est faible par rapport au type 2 */

/*
 * @name   : add_weakeness
 * @arg    : type1 , enum type representing weak type
 * @arg    : type2 , enum type representing strong type
 * @arg    : weakness , weak array representing all weakness that we want to add new weakness
 * @desc   : This function is use to add a new weakness to the array
 *
 * @return : no return
 */
void add_weakness(Weakness* weakness, Type_poke type1, Type_poke type2);

/* est-ce que type1 est faible par rapport au type2*/

/*
 * @name   : is_weak
 * @arg    : weakness , weakness array representing all weakness in game
 * @arg    : type1 , enum type representing the poketudiant attacked 
 * @arg    : type2 , enum type reresenting the poketudiant attacker
 * @desc   : This function is use to if type 1 is weak agains't type2. type1 is basically 
             representing the attacked poketudiant and type is representing attacker poketudiant
 *
 * @return : return 1 if type1 is weak to type2, 0 otherwise
 */
int is_weak(Weakness* weakness, Type_poke type1, Type_poke type2);

/*
 * @name   : delete_weakness
 * @arg    : weakness , weakness array that's we want to delete and free
 * @desc   : This function is use to delete the 2D array of weakness and ensure no memory leak
 *
 * @return : no return
 */
void delete_weakness(Weakness* weakness);

#endif
