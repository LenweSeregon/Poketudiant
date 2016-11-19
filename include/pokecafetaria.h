#ifndef __POKECAFETARIA_H__
#define __POKECAFETARIA_H__

/* Number of table in the pokecafetaria */
#define NB_TABLE_POKECAFETARIA 3

/* Max number of pokemon on a table */
#define MAX_POKETUDIANT_BY_TABLE 4

/*
 * @name  : Pokecafetaria
 * @desc  : This struct is use to simply store a dynamic array representing a 2D array for
            cafetaria by giving all method to linear the array. It prevent memory responsablity
	    and all function need for pokecafetaria manipulation
 *
 */
typedef struct Pokecafetaria
{
  Poketudiant** list;
}Pokecafetaria;

/*
 * @name   : create_pokecafetaria
 * @arg    : none
 * @desc   : This function allocate memory for a pokecafetaria
 *
 * @return : Pointer on generated pokecafetaria;
 */
Pokecafetaria* create_pokecafetaria();

/*
 * @name   : add_poketudiant_to_cafetaria
 * @arg    : caf, pointer on pokecafetaria that will receive the poketudiant
 * @arg    : etu, pointer on poketudiant that we will add to the pokecafetaria
 * @desc   : This function add a poketudiant in the first free position in the pokecafetaria and do nothing is there is no free position
 *
 * @return : return 1 if there were a free position, 0 otherwise
 */
int add_poketudiant_to_cafetaria(Pokecafetaria* caf, Poketudiant* etu);

/*
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
 * @name   : add_poketudiant_to_cafetaria_by_table_position
 * @arg    : caf, pointer on pokecafetaria that will receive the poketudiant
 * @arg    : etu, pointer on poketudiant that we will add to the pokecafetaria
 * @arg    : t, table where we will add the poketudiant
 * @desc   : This function add a poketudiant on the position in the pokecafetaria and do nothing if this is not a free position
 *
 * @return : return 1 if it were a free position, 0 otherwise
 */
int add_poketudiant_to_cafetaria_by_table_position(Pokecafetaria* caf, Poketudiant* etu, int t);

/*
 * @name   : heal_all_pokecafetaria
 * @arg    : caf, pointer on pokecafetaria where we want to heal all poketudiant
 * @desc   : This function is heal all poketudiant that are in pokecafetaria
 *
 * @return : no return;
 */
void heal_all_pokecafetaria(Pokecafetaria* caf);

/*
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
 * @name   : get_poketudiant_from_cafetaria_by_id
 * @arg    : caf, pointer on pokecafetaria where we will get the poketudiant
 * @arg    : id , id of poketudiant that we are looking for
 * @desc   : This function get a poketudiant with id in the pokecafetaria
 *
 * @return : pointer on the poketudiant if there is one, NULL otherwise
 */
Poketudiant* get_poketudiant_from_cafetaria_by_id(Pokecafetaria* caf, int id);


/*
 * @name   : get_position_of_poketudiant_id_in_cafetaria
 * @arg    : caf, pointer on pokecafetaria where we will get the position
 * @arg    : id , id of poketudiant that we are looking for
 * @desc   : This function get position of poketudiant according to id in the pokecafetaria
 *
 * @return : position of poketudiant, -1 if not found
 */
int get_position_poketudiant_id_in_cafetaria(Pokecafetaria* caf, unsigned int id);

/*
 * @name   : swap_position_poketudiant_in_cafetaria
 * @arg    : caf, pointer on pokecafetaria that we will modify
 * @arg    : t1,t2,c1,c2, position of the poketudiants
 * @desc   : This function swap 2 poketudiants in the pokecafetaria
 *
 * @return : none
 */
void swap_position_poketudiant_in_cafetaria(Pokecafetaria* caf, int t1, int c1, int t2, int c2);


/*
 * @name   : swap_position_poketudiant_in_cafetaria_via_id
 * @arg    : caf, pointer on pokecafetaria that we will modify
 * @arg    : id_1 , id of first poketudiant that we want to swap
 * @arg    : id_2 , id of second poketudiant that we want to swap
 * @desc   : This function swap 2 poketudiants in the pokecafetaria via id
 *
 * @return : none
 */
int swap_position_poketudiant_in_cafetaria_via_id(Pokecafetaria* caf, int id_1, int id_2);

/*
 * @name   : pop_poketudiant_from_cafetaria
 * @arg    : caf, pointer on pokecafetaria that we will modify
 * @arg    : t,c position of the poketudiant
 * @desc   : This function remove the pointer of a poketudiant from the pokecafetaria but do not free the memory
 *
 * @return : pointer on the poketudiant removed from the pokecafetaria
 */
Poketudiant* pop_poketudiant_from_cafetaria(Pokecafetaria* caf, int t, int c);

/*
 * @name   : pop_poketudiant_from_cafetaria
 * @arg    : caf, pointer on pokecafetaria that we will modify
 * @arg    : id , id of poketudiant that we want to pop from cafetaria
 * @desc   : This function remove the pointer of a poketudiant from the pokecafetaria but do not free the memory
 *
 * @return : pointer on the poketudiant removed from the pokecafetaria
 */
Poketudiant* pop_poketudiant_from_cafetaria_via_id(Pokecafetaria* caf, int id);

/*
 * @name   : delete_poketudiant_from_table
 * @arg    : caf, pointer on pokecafetaria that we will modify
 * @arg    : t,c position of the poketudiant
 * @desc   : This function remove the pointer of a poketudiant from the pokecafetaria and free the memory
 *
 * @return : none
 */
void delete_poketudiant_from_table(Pokecafetaria* caf, int t, int c);

/*
 * @name   : delete_poketudiant_from_cafetaria_by_id
 * @arg    : caf, pointer on pokecafetaria that we will modify
 * @arg    : id , id of poketudiant that we want to delete
 * @desc   : This function remove the pointer of a poketudiant from the pokecafetaria and free the memory
 *
 * @return : none
 */
void delete_poketudiant_from_cafetaria_by_id(Pokecafetaria* caf, int id);


/*
 * @name   : delete_pokecafetaria
 * @arg    : caf, pointer on pokecafetaria that we will delete
 * @desc   : delete the pokecafetaria and free the memory
 *
 * @return : none
 */
void delete_pokecafetaria(Pokecafetaria* caf);

/*
 * @name   : calcul_pos_pokecafetaria
 * @arg    : c,t position of a poketudiant
 * @desc   : calcul the position of the poketudiant 
 *
 * @return : the position
 */
int calcul_pos_pokecafetaria(int t, int c);

/*
 * @name   : print_pokecafetaria
 * @arg    : caf, pointer on a pokecafetaria
 * @desc   : print the table of the pokecafetaria 
 *
 * @return : none
 */
void print_pokecafetaria(Pokecafetaria* caf);

/*
 * @name   : print_table_pokecafetaria
 * @arg    : caf, pointer on a pokecafetaria
 * @arg    : t, position of a table in the pokecafetaria
 * @desc   : print the poketudiants in tha table 
 *
 * @return : none
 */
void print_table_pokecafetaria(Pokecafetaria* caf, int t);
#endif
