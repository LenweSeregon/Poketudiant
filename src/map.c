#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constantes.h"
#include "string_utils.h"
#include "map.h"

#define COLOR(param) printf("\033[%sm",param);

#define WILD '1'
#define ROAD '0'
#define NURSE 'n'
#define ENEMY 'e'

#define YELLOW_BACK COLOR("43");
#define BLUE_BACK COLOR("44");
#define GREEN_BACK COLOR("42");
#define RED_BACK COLOR("41");
#define WHITE_BACK COLOR("47");

#define YELLOW_TEXT COLOR("33");
#define BLUE_TEXT COLOR("34");
#define GREEN_TEXT COLOR("32");
#define RED_TEXT COLOR("31");
#define WHITE_TEXT COLOR("37");


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
  free(map->mapArray);
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
  for(j = 0; j < map->height; j++)
    {
      for(k = 0; k < map->width; k++)
	{
	  char elem = map->mapArray[j*map->width+k].type;
	  switch(elem)
	    {
	    case WILD:
	      GREEN_BACK;
	      GREEN_TEXT;
	      break;
	    case ROAD:
	      YELLOW_BACK;
	      YELLOW_TEXT;
	      break;
	    case NURSE:
	      BLUE_BACK;
	      BLUE_TEXT;
	      break;
	    case ENEMY:
	      RED_BACK;
	      RED_TEXT;
	      break;
	    default:
	      printf("Error\n");
	    }

	  if(j*map->width+k == map->position_trainer)
	    {
	      WHITE_TEXT;
	      printf("%c ",'X');
	    }
	  else
	    {
	      printf("%c ",elem);
	    }
	  COLOR("0");
	}
      printf("\n");
    }
}

void load_map(Map* map, const char* file_name)
{
  FILE* file;
  file = fopen(file_name,"r");
  if(file)
    {
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
		      tile.type = NURSE;
		      tile.tile.nurse.val = string_getter[0];
		    }
		  else if(string_splitter[0] == ENEMY)
		    {
		      
		      tile.type = ENEMY;
		      tile.tile.enemy.val = string_getter[0];
		      strcpy(tile.tile.enemy.name,&string_splitter[2]);
		    }
		  else
		    {
		      int value = atoi(string_splitter);
		      tile.type = WILD;
		      tile.tile.wild.level = value;
		      tile.tile.wild.val = value;
		    }
	      
		  string_splitter = strtok(NULL," ");
		}
	      map->mapArray[i++] = tile;
	    }
	}while(1);
      fclose(file);
    }
  else
    {
      printf("Error, impossible to open file\n");
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
