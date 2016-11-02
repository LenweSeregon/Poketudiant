#ifndef __LOADING_MODULE_H__
#define __LOADING_MODULE_H__

/*
 * @author : Nicolas
 * @date   : 01 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : load_base_poketudiant
 * @arg    : table_poke , hash table that'll contain all base poketudiant for futur generation
 * @arg    : file_name , file name where are stock base poketudiant
 * @desc   : This function is used to fill the hash table that'll contain all base poketudiant
 *
 * @return : no return;
 */
void load_base_poketudiant(Hash_table* table_poke, const char* file_name);

/*
 * @author : Nicolas
 * @date   : 01 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : load_base_poketudiant
 * @arg    : table_attack , hash table that'll contain all base attack for futur generation
 * @arg    : file_name , file name where are stock base attack
 * @desc   : This function is used to fill the hash table that'll contain all base attack
 *
 * @return : no return;
 */
void load_base_attack(Hash_table* table_attack, const char* file_name);

#endif
