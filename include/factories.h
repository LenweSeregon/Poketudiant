#ifndef __FACTORIES_H__
#define __FACTORIES_H__

/*
 * @author : Nicolas
 * @date   : 01 / 11 / 2016
 * 
 * @name   : Poketudiant_factory
 * @desc   : This structure is a structure that contain a reference to hash table containing
             all base poketudiant and another containing all base attacks. This structure 
	     with thoses reference will be able to work as a factory to create poketudiant
 */
struct Poketudiant_factory
{
  Hash_table* ref_poketudiant_base;
  Hash_table* ref_attack_base;
};
typedef struct Poketudiant_factory Poketudiant_factory;

/*
 * @author : Nicolas
 * @date   : 01 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : create_poketudiant_factory
 * @arg    : ref_poke , pointer on hash table containing all base poketudiants, care
             responsability is not given to factory
 * @arg    : ref_att , pointer on hash table containing all base attack, care responsability
             is not given to factory
 * @desc   : This function is used to create a poketudiant factory that's gonna be use to
             generate poketudiants. Care two attributs in structures are just reference so
	     responsability is not given to created structure
 *
 * @return : pointer on poketudiant factory created;
 */
Poketudiant_factory* create_poketudiant_factory(Hash_table* ref_poke, Hash_table* ref_att);

/*
 * @author : Nicolas
 * @date   : 01 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : delete_poketudiant_factory
 * @arg    : factory , pointer on factory that we want to delete
 * @desc   : This function is used to delete a poketudiant factory and ensure no leak memory
             Note, references are not freed !
 *
 * @return : no return;
 */
void delete_poketudiant_factory(Poketudiant_factory* factory);

/*
 * @author : Nicolas
 * @date   : 01 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : generate_random_poketudiant
 * @arg    : factory , pointer on factory with which we want to generate poketudiant
 * @desc   : This function is used to generate a random poketudiant without restriction
 *
 * @return : pointer on poketudiant created;
 */
Poketudiant* generate_random_poketudiant(Poketudiant_factory* factory);

/*
 * @author : Nicolas
 * @date   : 01 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : generate_random_poketudiant_from_name
 * @arg    : factory , pointer on factory with which we want to generate poketudiant
 * @arg    : name , poketudiant name that we want to generate
 * @desc   : This function is used to generate a poketudiant from his variety name
 *
 * @return : pointer on poketudiant created;
 */
Poketudiant* generate_poketudiant_from_name(Poketudiant_factory* factory, char* name);

#endif
