#ifndef __POKECAFETARIA_H__
#define __POKECAFETARIA_H__

/* Number of table in the pokecafetaria */
#define NB_TABLE_POKECAFETARIA 3

/* Max number of pokemon on a table */
#define MAX_POKETUDIANT_BY_TABLE 4

typedef struct Pokecafetaria
{
  Poketudiant** list;
} Pokecafetaria;

/*
 * @author : Gabriel
 * @date   : 02 / 11 / 2016
 * @state  : [not tested]
 * 
 * @name   : create_pokecafetaria
 * @arg    : none
 * @desc   : This function allocate memory for a pokecafetaria
 *
 * @return : Pointer on generated pokecafetaria;
 */
Pokecafetaria* create_pokecafetaria();

/*
 * @author : Gabriel
 * @date   : 02 / 11 / 2016
 * @state  : [not tested]
 * 
 * @name   : add_poketudiant_to_cafetaria
 * @arg    : caf, pointer on pokecafetaria that will recieve the poketudiant
 * @arg    : etu, pointer on poketudiant that we will add to the pokecafetaria
 * @desc   : This function add a poketudiant in the first free position in the pokecafetaria and do nothing is there is no free position
 *
 * @return : return 1 if there were a free position, 0 otherwise
 */
int add_poketudiant_to_cafetaria(Pokecafetaria* caf, Poketudiant* etu);

/*
 * @author : Gabriel
 * @date   : 03 / 11 / 2016
 * @state  : [not tested]
 * 
 * @name   : add_poketudiant_to_cafetaria_by_postion
 * @arg    : caf, pointer on pokecafetaria that will recieve the poketudiant
 * @arg    : etu, pointer on poketudiant that we will add to the pokecafetaria
 * @arg    : t, table where we will add the poketudiant
 * @arg    : c, position on the table where we will add the poketudiant
 * @desc   : This function add a poketudiant on the position in the pokecafetaria and do nothing is this is not a free position
 *
 * @return : return 1 if it were a free position, 0 otherwise
 */
int add_poketudiant_to_cafetaria_by_position(Pokecafetaria* caf, Poketudiant* etu, int t, int c);

/*
 * @author : Gabriel
 * @date   : 03 / 11 / 2016
 * @state  : [not tested]
 * 
 * @name   : get_poketudiant_from_cafetaria_by_position
 * @arg    : caf, pointer on pokecafetaria where we will get the poketudiant
 * @arg    : t, table where we will get the poketudiant
 * @arg    : c, position on the table where we will get the poketudiant
 * @desc   : This function get a poketudiant on the position in the pokecafetaria
 *
 * @return : pointer on the poketudiant if there is one, NULL otherwise
 */
Poketudiant* get_poketudiant_from_cafetaria_by_position(Pokecafetaria* caf, int t, int c);

/*
 * @author : Gabriel
 * @date   : 03 / 11 / 2016
 * @state  : [not tested]
 * 
 * @name   : swap_position_poketudiant_in_cafetaria
 * @arg    : caf, pointer on pokecafetaria that we will modify
 * @arg    : t1,t2,c1,c2, position of the poketudiants
 * @desc   : This function swap 2 poketudiants in the pokecafetaria
 *
 * @return : none
 */
void swap_position_poketudiant_in_cafetaria(Pokecafetaria* caf, int t1, int c1, int t2, int c2);

/*
 * @author : Gabriel
 * @date   : 03 / 11 / 2016
 * @state  : [not tested]
 * 
 * @name   : pop_poketudiant_from_cafetaria
 * @arg    : caf, pointer on pokecafetaria that we will modify
 * @arg    : t,c position of the poketudiant
 * @desc   : This function remove the pointer of a poketudiant from the pokecafetaria but do not gree the memory
 *
 * @return : pointer on the poketudiant removed from the pokecafetaria
 */
Poketudiant* pop_poketudiant_from_cafetaria(Pokecafetaria* caf, int t, int c);

/*
 * @author : Gabriel
 * @date   : 03 / 11 / 2016
 * @state  : [not implemented]
 * 
 * @name   : delete_poketudiant_from_table
 * @arg    : caf, pointer on pokecafetaria that we will modify
 * @arg    : t,c position of the poketudiant
 * @desc   : This function remove the pointer of a poketudiant from the pokecafetaria and free the memory
 *
 * @return : none
 */

/*
void delete_poketudiant_from_table(Pokecafetaria* caf, int t, int c);
*/

/*
 * @author : Gabriel
 * @date   : 03 / 11 / 2016
 * @state  : [not tested]
 * 
 * @name   : delete_pokecafetaria
 * @arg    : caf, pointer on pokecafetaria that we will delete
 * @desc   : delete the pokecafetaria and free the memory
 *
 * @return : none
 */
void delete_pokecafetaria(Pokecafetaria* caf);

/*
 * @author : Gabriel
 * @date   : 03 / 11 / 2016
 * @state  : [not tested]
 * 
 * @name   : calcul_pos_pokecafetaria
 * @arg    : c,t position of a poketudiant
 * @desc   : calcul the position of the poketudiant 
 *
 * @return : the position
 */
int calcul_pos_pokecafetaria(int t, int c);
#endif
