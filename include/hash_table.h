#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

/*
 * @author : Nicolas
 * @date   : 27 / 10 / 2016
 * 
 * @name   : Hash_table
 * @desc   : This structure is a basic hash table structure use as data structure.
             Basically, and at the moment, this structure is use to stock every attack
             and pokemons as base models for easy creation and access to attributs.
             Collision are manage thanks to Linked_list so you can stock all type of data
	     Care : hash_fct, cmp_fct_linked_list and print_fct_linked_list have to be
	     initiliaze with logic contents according to data
 */
struct Hash_table
{
  unsigned int size;
  Linked_list** array;
  
  int (*hash_fct)(void* element);
  
  int (*cmp_fct_linked_list)(void*,void*);
  void (*print_fct_linked_list)(void*);
  void (*free_fct_linked_list)(void*);
};
typedef struct Hash_table Hash_table;

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : create_hash_table
 * @arg    : size , size that's we want to set for our hash table
 * @desc   : This function is use to create dynamically an hash table with a precise size
 *
 * @return : pointer on hash table allocated;
 */
Hash_table* create_hash_table(unsigned int size);


/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : delete_hash_table
 * @arg    : table , pointer on hash table that's we want to delete
 * @desc   : This function is use to delete properly an hash table. It ensure to properly delete
             all element in hash table and hash table itselft without memory leak
 *
 * @return : no return;
 */
void delete_hash_table(Hash_table* table);


/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : add_to_hash_table
 * @arg    : table , pointer on hash table where  we want to add element
 * @arg    : element , element to add in hash table using linked list for collision
 * @desc   : This function is use to add an element in hash table according hash function
 *
 * @return : no return;
 */
void add_to_hash_table(Hash_table* table,void* element);


/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : get_element_in_hash_table
 * @arg    : table , pointer on hash table where we are looking for element
 * @desc   : This function is use to get a pointer on the element that's we are looking for
             Take care, this function only give a pointer but u shoudn't delete ourself this
             pointer, just use it because hash table has already memory responsabily of this
	     element
 *
 * @return : pointer on the element that's we are looking for. If not found, return NULL;
 */
void* get_element_in_hash_table(Hash_table* table, void* element);


/*
 * @author : Nicolas
 * @date   : 01 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : get_random_element_in_hash_table
 * @arg    : table , pointer on hash table where we are looking for element
 * @desc   : This function is use to get a pointer on a random element contain in hash table
 *
 * @return : pointer on the element that's we are looking for. If hash table is empty return NULL;
 */
void* get_random_element_in_hash_table(Hash_table* table);


/*
 * @author : Nicolas
 * @date   : 01 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : get_random_element_with_criteria_in_hash_table
 * @arg    : table , pointer on hash table where we are looking for element
 * @arg    : criteria , pointer on something to make criteria on search, according to cmp_fct
 * @desc   : This function is use to get a pointer on a random element contain in hash table
             according to criteria given in parameter
 *
 * @return : pointer on the element that's we are looking for. If not found, return NULL;
 */
void* get_random_element_with_criteria_in_hash_table(Hash_table* table, void* criteria);

/*
 * @author : Nicolas
 * @date   : 01 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : set_cmp_fct_for_hash_table
 * @arg    : table , pointer on hash table where we want to change compare function
 * @arg    : cmp , compare function that we want to set on hash table and spread to all linked list
 * @desc   : This function is use to set the compare function of hash table and linked list
 *
 * @return : no return;
 */
void set_cmp_fct_for_hash_table(Hash_table* table, int (*cmp)(void*,void*));

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : print_linked_list
 * @arg    : list, pointer on linked list that's we want to display
 * @desc   : This function can be use to print linked list element using the fct 
             initiliaze in linked list structure
 *
 * @return : no return;
 */
void print_hash_table(const Hash_table* table);

#endif
