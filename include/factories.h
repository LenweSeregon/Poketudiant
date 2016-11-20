#ifndef __FACTORIES_H__
#define __FACTORIES_H__


/*
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
 * @name   : delete_poketudiant_factory
 * @arg    : factory , pointer on factory that we want to delete
 * @desc   : This function is used to delete a poketudiant factory and ensure no leak memory
             Note, references are not freed !
 *
 * @return : no return;
 */
void delete_poketudiant_factory(Poketudiant_factory* factory);

/*
 * @name   : generate_poketudiant
 * @arg    : factory , pointer on factory with witch we want to generate poketudiant
 * @arg    : base_poke , the base poketudiant for generation, this base has specific value
             according to function that call the function. For example, this base poketudiant
	     cannot be a teacher base if function is call from generate_without_teacher
 * @arg    : level , level that we want our generated poketudiant to have
 * @desc   : This function is use to properly generate poketudiant from his base. It ensure to 
             give him the right level with multiplication in caracteristics
 *
 * @return : pointer on poketudiant generated, NULL if error in generator
 */
Poketudiant* generate_poketudiant(Poketudiant_factory* factory, Poketudiant* base_poke, int level);

/*
 * @name   : generate_random_poketudiant
 * @arg    : factory , pointer on factory with which we want to generate poketudiant
 * @arg    : level , level that we want our generated poketudiant to have
 * @desc   : This function is used to generate a random poketudiant at level specify in parameters
 *
 * @return : pointer on poketudiant created;
 */
Poketudiant* generate_random_poketudiant(Poketudiant_factory* factory,int level);


/*
 * @name   : generate_random_poketudiant
 * @arg    : factory , pointer on factory with which we want to generate poketudiant
 * @arg    : level , level that we want our generated poketudiant to have
 * @desc   : This function is used to generate a random poketudiant at level specify in parameters
             and without teacher poketudiant
 *
 * @return : pointer on poketudiant created;
 */
Poketudiant* generate_random_poketudiant_without_teacher(Poketudiant_factory* factory, int level);


/*
 * @name   : generate_random_capturable_poketudiant
 * @arg    : factory , pointer on factory with which we want to generate poketudiant
 * @arg    : level , level that we want our poketudiant to get
 * @desc   : This function is used to generate a random capturable poketudiant at level 
             specify in parameter
 *
 * @return : pointer on poketudiant created;
 */
Poketudiant* generate_random_capturable_poketudiant(Poketudiant_factory* factory, int level);

/*
 * @name   : generate_random_poketudiant_from_name
 * @arg    : factory , pointer on factory with which we want to generate poketudiant
 * @arg    : name , poketudiant name that we want to generate
 * @arg    : level , level that we want our generated poketudiant to get
 * @desc   : This function is used to generate a poketudiant from his variety name at level 
             specify in parameter
 *
 * @return : pointer on poketudiant created;
 */
Poketudiant* generate_poketudiant_from_name(Poketudiant_factory* factory,char* name,int level);

/*
 * @name   : generate_random_trainer
 * @arg    : factory , pointer on factory with which we want to generate trainer
 * @arg    : level , level that we want our trainer's poketudiant to get
 * @desc   : This function is used to generate a trainer with 3 poketudiant with right level
             according to parameter
 *
 * @return : pointer on trainer created;
 */
Trainer* generate_random_trainer(Poketudiant_factory* factory, int level);

#endif
