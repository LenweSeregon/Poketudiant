#ifndef __CONSTANTE_H__
#define __CONSTANTE_H__


#define MIN_LEVEL_POKETUDIANT 1
#define MAX_LEVEL_POKETUDIANT 10
#define MULTIPLIER_DMG_WEAK 2
#define XP_START_WILD_POKE 300
#define MAX_POKETUDIANT_TEAM 3
#define MAX_POKETUDIANT_BY_TABLE 4
#define NB_TABLE_POKECAFETARIA 3
#define INIT_SIZE_HASH_TABLE 20

/* Evolve interaction */
#define CHANCE_EVOLVE_LEVEL_3 20.0
#define CHANCE_EVOLVE_LEVEL_4 37.5
#define MIN_RANGE_EVOLVE_POSSIBLE 3
#define MAX_RANGE_EVOLVE_POSSIBLE 5

/* User interaction */ 
#define MAX_SIZE_USER_COMMAND 100
#define BASE_USER 10 /* Integer parameter given by user are in base 10 */
#define COMMAND_SEPARATOR " "

/* File interaction */
#define MAX_STRING_FILE_SIZE 300
#define MAX_STRING_ATTRIBUTS_POKETUDIANT 60

/* Some element use a random number for simulate chance 
   Those values are between 0.9 and 1.1 
*/
#define MIN_RANGE_RANDOM_GAME 0.9
#define MAX_RANGE_RANDOM_GAME 1.1

#endif


