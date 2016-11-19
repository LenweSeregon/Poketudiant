#ifndef __EVOLVE_MODULE_H__
#define __EVOLVE_MODULE_H__

/*
 * @name   : Evolve_center
 * @desc   : This structure is only use to store a reference on poketudiant base in hash table
             indeed it's needed for evolution when our poketudiant is ready to evolve
 *
 */
struct Evolve_center
{
  Hash_table* ref_poke_base;
};
typedef struct Evolve_center Evolve_center;

/*
 * @name   : create_evolve_center
 * @arg    : ref_poke_base , ref on hash table containing poke base for evolution needed as
             attribut of evolve center
 * @desc   : This function is use to allocate an evolve center with a reference on hash table
 *
 * @return : return allocated evolve center as pointer
*/
Evolve_center* create_evolve_center(Hash_table* ref_poke_base);

/*
 * @name   : delete_evolve_center
 * @arg    : center , pointer on evovle center that we want to delete
 * @desc   : This function is use free a evolve center and ensure no memory leak. Take care
             this struct only own a reference on hash table with poketudiant base so it doesn't
	     free it.
 *
 * @return : no return
*/
void delete_evolve_center(Evolve_center* center);

/*
 * @name   : make_poketudiant_evolve
 * @arg    : center , pointer on evolve center use to make poketudiant evolve
 * @arg    : poke , poketudiant that how need to be evolve
 * @arg    : coeff_att , coefficient that's has been randomly generated representing attack
 * @arg    : coeff_def , coefficient that's has been randomly generated representing defense
 * @arg    : coeff_hp , coefficient that's has been randomly generated representing hp
 * @desc   : This function is use to make a poketudiant evolve according to his attribut
             named "evolution". It also check poketudiant level because he can't evolve only if
	     his level his <= 3 && >= 5
 *
 * @return : return 1 if poketudiant evolved, 0 otherwise
*/
int make_poketudiant_evolve(Evolve_center* center, 
			    Poketudiant* poke, 
			    double coeff_att,
			    double coeff_def,
			    double coeff_hp);

/*
 * @name   : make_poketudiant_upgrade
 * @arg    : center , pointer on evolve center use to make poketudiant upgrade
 * @arg    : poke , poketudiant that's have to upgrade
 * @desc   : This function is use to make poktetudiant level upgrade. It's ensure to upgrade
             mutlti time if poketudiant has too much experience. It's also call evolve function
	     if poketudiant has an evolution available
 *
 * @return : no return
*/
void make_poketudiant_upgrade(Evolve_center* center, Poketudiant* poke);


#endif
