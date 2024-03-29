#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constantes.h"
#include "string_utils.h"
#include "container.h"
#include "linked_list.h"
#include "hash_table.h"

#include "type_poke.h"
#include "attack.h"
#include "poketudiant.h"

#include "pokecafetaria.h"
#include "trainer.h"
#include "map.h"

#define COLOR(param) printf("\033[%sm",param);

#define WILD '1'
#define ROAD '0'
#define NURSE 'n'
#define ENEMY 'e'


#define LIGHT_GREEN_BACK printf("\x1B[48;5;%dm  ", 10);
#define GREEN_BACK printf("\x1B[48;5;%dm  ", 34);
#define DARK_GREEN_BACK printf("\x1B[48;5;%dm  ", 22);

#define MARRON_BACK printf("\x1B[48;5;%dm  ", 130);
#define RED_BACK printf("\x1B[48;5;%dm  ", 124);
#define TRAINER_BACK printf("\x1B[48;5;%dm  ", 6);
#define PURPLE_BACK printf("\x1B[48;5;%dm  ", 5);


Map* create_map()
{
  Map* map = malloc(sizeof(Map));
  map->width = -1;
  map->height = -1;
  map->mapArray = NULL;
  return map;
}

void delete_map(Map* map)
{
  if(map->mapArray != NULL)
    free(map->mapArray);
  if(map != NULL)
    free(map);
}

int get_action_associated(const Map* map)
{
  return map->buffer.type;
}

int get_level_wild_poketudiant(const Map* map)
{
  return map->buffer.tile.wild.level;
}

int get_first_nurse_from_bottom(const Map* map)
{
  int i;
  for(i = (map->width * map->height)-1 ; i >= 0 ; i--)
    {
      if(map->mapArray[i].type == NURSE)
	return i;
    }
  return -1;
}

const char* get_name_diploma_trainer(const Map* map)
{
  return map->buffer.tile.enemy.name;
}

void destroy_enemy_and_set_road(Map* map)
{
  Tile tile;
  tile.type = ROAD;
  tile.tile.road.val = 0;
  map->buffer = tile;
  map->mapArray[map->position_trainer] = tile;
}

void init_map_empty(Map* map)
{
  map->mapArray = malloc((map->width * map->height) * sizeof(Tile));
}

void print_map(const Map* map)
{
  int j,k;
  print_recap(map);
  for(j = 0; j < map->height; j++)
    {
      for(k = 0; k < map->width; k++)
	{
	  if(j*map->width+k == map->position_trainer) /* Trainer */
	    {
	      TRAINER_BACK
	    }
	  else
	    {
	      Tile tile = map->mapArray[j*map->width+k];
	      switch(tile.type)
		{
		case WILD:
		  if(tile.tile.wild.level >= 1 && tile.tile.wild.level <= 3)
		    {
		      LIGHT_GREEN_BACK
		    }
		  else if(tile.tile.wild.level >= 4 && tile.tile.wild.level <= 6)
		    {
		      GREEN_BACK
		    }
		  else
		    {
		      DARK_GREEN_BACK
		    }
		  break;
		case ROAD:
		  MARRON_BACK
		  break;
		case NURSE:
		  RED_BACK
		  break;
		case ENEMY:
		  PURPLE_BACK
		  break;
		default:
		  printf("Error\n");
		}
	    }
	 
	  COLOR("0");
	}
      printf("\n");
    }
}

void print_recap()
{
  MARRON_BACK COLOR("0"); printf(" = Road"); printf("\n"); 
  LIGHT_GREEN_BACK COLOR("0"); printf(" = Easy wild area"); printf("\n");
  GREEN_BACK COLOR("0"); printf(" = Medium wild area"); printf("\n");
  DARK_GREEN_BACK COLOR("0"); printf(" = Hard wild area"); printf("\n");
  RED_BACK COLOR("0"); printf(" = Nursery");  printf("\n");
  PURPLE_BACK COLOR("0"); printf(" = Diploma trainer"); printf("\n");
  TRAINER_BACK COLOR("0"); printf(" = Your trainer"); printf("\n");
  
}

int trainer_exist(Trainer*** diploma_list, int nb_trainer, char* nameT)
{
  int i;
  remove_occurences(nameT,'\n');
  remove_occurences(nameT,' ');
  remove_occurences(nameT,'\t');
  for(i = 0; i < nb_trainer; i++)
    {
      if(strcmp(((*diploma_list)[i])->name,nameT) == 0)
	{
	  return 1;
	}
    }
  return 0;
}

int load_map(Map* map, const char* file_name, int nb_diploma_trainer, Trainer*** diploma_list)
{
  FILE* file;
  file = fopen(file_name,"r");
  if(file)
    {
      int nurse_detected = 0;
      int valid = 1;
      int nb_trainer = 0;
      int i = 0;
      char string_getter[MAX_STRING_FILE_SIZE] = "";
      char* string_splitter;
      /* Get Width */
      fgets(string_getter,MAX_STRING_FILE_SIZE,file);
      remove_occurences(string_getter,' ');
      remove_occurences(string_getter,'\n');
      remove_occurences(string_getter,'\t');
      map->width = atoi(string_getter);
      /* Get height */
      fgets(string_getter,MAX_STRING_FILE_SIZE,file);
      remove_occurences(string_getter,' ');
      remove_occurences(string_getter,'\n');
      remove_occurences(string_getter,'\t');
      map->height = atoi(string_getter);
      /* Map */
      init_map_empty(map);

      do
	{
	  fgets(string_getter,MAX_STRING_FILE_SIZE,file);
	  
	  /* End of file */
	  if( feof(file) )
	    {
	      break ;
	    }

	  /* Split */
	  string_splitter = strtok(string_getter," ");
	  while(string_splitter != NULL)
	    {
	      Tile tile;
	      if( (strcmp(string_splitter," ") != 0) && (strcmp(string_splitter,"\n") != 0) )
		{
		  if(string_splitter[0] == ROAD)
		    {
		      tile.type = ROAD;
		      tile.tile.road.val = string_getter[0];
		    }
		  else if(string_splitter[0] == NURSE)
		    {
		      nurse_detected = 1;
		      tile.type = NURSE;
		      tile.tile.nurse.val = string_getter[0];
		    }
		  else if(string_splitter[0] == ENEMY)
		    {
		      nb_trainer++;
		      tile.type = ENEMY;
		      tile.tile.enemy.val = string_getter[0];
		      strcpy(tile.tile.enemy.name,&string_splitter[2]);
		      if(!trainer_exist(diploma_list,nb_diploma_trainer,tile.tile.enemy.name))
			{
			  printf("connard\n");
			  valid = 0;
			}
		    }
		  else
		    {
		      int value = atoi(string_splitter);
		      if(value < 1 || value > 10)
			{
			  valid = 0;
			  tile.type = WILD;
			  tile.tile.wild.level = 0;
			  tile.tile.wild.val = 0;
			}
		      else
			{
			  tile.type = WILD;
			  tile.tile.wild.level = value;
			  tile.tile.wild.val = value;
			}
		    }
	      
		  string_splitter = strtok(NULL," ");
		}
	      if(i >= map->width * map->height)
		{
		  valid = 0;
		}
	      else
		{
		  map->mapArray[i++] = tile;
		}
	    }
	}while(1);
      fclose(file);

      if((i != (map->width * map->height)) || (nb_trainer != nb_diploma_trainer) || !nurse_detected)
	{
	  valid = 0;
	}
      return valid;
    }
  else
    {
      printf("Error, impossible to open file\n");
      return 0;
    }
}
	  
void set_position_trainer_start(Map* map, int i)
{
  map->position_trainer = i;
  map->buffer = map->mapArray[i];
}

void move_trainer(Map* map, Direction dir)
{
    switch(dir)
    {
    case NORTH:
      map->mapArray[map->position_trainer] = map->buffer;
      map->buffer = map->mapArray[map->position_trainer-map->width];
      map->position_trainer -= map->width;
      break;
    case SOUTH:
      map->mapArray[map->position_trainer] = map->buffer;
      map->buffer = map->mapArray[map->position_trainer+map->width];
      map->position_trainer += map->width;
      break;
    case EAST:
      map->mapArray[map->position_trainer] = map->buffer;
      map->buffer = map->mapArray[map->position_trainer+1];
      map->position_trainer += 1;
      break;
    case WEST:
      map->mapArray[map->position_trainer] = map->buffer;
      map->buffer = map->mapArray[map->position_trainer-1];
      map->position_trainer -= 1;
      break;
    default:
      printf("Error\n");
      break;
    }
}

int trainer_can_move(Map* map, Direction dir)
{
  int posNext;
  int canMove = 1;
  switch(dir)
    {
    case NORTH:
      posNext = map->position_trainer - map->width;
      canMove = (posNext >= 0);
      break;
    case SOUTH:
      posNext = map->position_trainer + map->width;
      canMove = (posNext <= ((map->width*map->height)-1));
      break;
    case EAST:
      posNext = map->position_trainer + 1;
      canMove = !((posNext % map->width) == 0);
      break;
    case WEST:
      canMove = !((map->position_trainer % map->width) == 0);
      break;
    default:
      printf("Error\n");
      break;
    }
  return canMove;
}
