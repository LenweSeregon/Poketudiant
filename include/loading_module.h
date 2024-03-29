#ifndef __LOADING_MODULE_H__
#define __LOADING_MODULE_H__

/*
 * @name   : load_base_poketudiant
 * @arg    : table_poke , hash table that'll contain all base poketudiant for futur generation
 * @arg    : file_name , file name where are stock base poketudiant
 * @desc   : This function is used to fill the hash table that'll contain all base poketudiant
 *
 * @return : no return;
 */
void load_base_poketudiant(Hash_table* table_poke, const char* file_name);

/*
 * @name   : load_base_attack
 * @arg    : table_attack , hash table that'll contain all base attack for futur generation
 * @arg    : file_name , file name where are stock base attack
 * @desc   : This function is used to fill the hash table that'll contain all base attack
 *
 * @return : no return;
 */
void load_base_attack(Hash_table* table_attack, const char* file_name);

/*
 * @name   : load_base_weakness
 * @arg    : weakness , 
 * @arg    : file_name , file name where are stock base attack
 * @desc   : 
 *
 * @return : no return;
 */
void load_base_weakness(Weakness* weakness, const char* file_name);

/*
 * @name   : load_diploma_trainers
 * @arg    : weakness , 
 * @arg    : file_name , file name where are stock base attack
 * @desc   : This function load all diploma trainers contained in file
 *
 * @return : return the dynamic array containing all diploma trainers
 */

Trainer** load_diploma_trainers(Poketudiant_factory* factory, int* nb_trainer, const char* file_name);

#endif
