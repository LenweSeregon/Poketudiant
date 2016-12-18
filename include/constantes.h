#ifndef __CONSTANTE_H__
#define __CONSTANTE_H__

#include <math.h>
/* Math define function for calculation */
/*#define CAPTURE_CALC(hp_player,hp_ia) (2 * max((0.5-((float)(hp_player)/(hp_ia))),0))*/
#define CAPTURE_CALC(hp_current,hp_max) (2 * (max((0.5-((float)(hp_current)/(hp_max))),0)))
#define NEXT_LEVEL_CALC(level) ((int)floor(500 * ((float)(1+(level)) / 2)))


/* Trainer direction */
enum Direction
  {
    NORTH,
    WEST,
    EAST,
    SOUTH
  };
typedef enum Direction Direction;

/* General define for poketudiant management */
#define POSITION_START_TRAINER 0
#define MIN_LEVEL_POKETUDIANT 1
#define MAX_LEVEL_POKETUDIANT 10
#define MULTIPLIER_DMG_WEAK 2
#define XP_START_WILD_POKE 300 /* If wild poke is level 1, we must give him a bit xp */
#define MAX_POKETUDIANT_TEAM 3
#define MAX_POKETUDIANT_BY_TABLE 4
#define NB_TABLE_POKECAFETARIA 3
#define INIT_SIZE_HASH_TABLE 20
#define LEVEL_POKETUDIANT_CATCH_COMMAND 1 /* Catch command debbug can generate some capture,
					     constante represent level of capturated poketudiant */
#define XP_NEEDED_LEVEL_1 500

/* Evolve interaction */
#define CHANCE_EVOLVE_LEVEL_3 20.0
#define CHANCE_EVOLVE_LEVEL_4 37.5
#define MIN_RANGE_EVOLVE_POSSIBLE 3
#define MAX_RANGE_EVOLVE_POSSIBLE 5

/* Escape interaction 
   Less represent poketudiant's player has x level below 
   More represent poketudiant's player has x level above */
#define CHANCE_CAPTURE_2_LEVEL_LESS 25
#define CHANCE_CAPTURE_1_LEVEL_LESS 40
#define CHANCE_CAPTURE_0_LEVEL_DIFF 50
#define CHANCE_CAPTURE_1_LEVEL_MORE 75
#define CHANCE_CAPTURE_2_LEVEL_MORE 95

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


