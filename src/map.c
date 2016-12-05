#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constantes.h"
#include "string_utils.h"
#include "map.h"

#define COLOR(param) printf("\033[%sm",param);

#define WILD 1
#define ROAD 2
#define NURSE 3
#define ENEMY 4

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

void init_map_empty(Map* map)
{
  map->mapArray = malloc((map->width * map->height) * sizeof(char));
}

void print_map(const Map* map)
{
  int j,k;
  for(j = 0; j < map->width; j++)
    {
      for(k = 0; k  < map->height; k++)
	{
	  char elem = map->mapArray[j*map->width+k];
	  int check = elem - '0';
	  switch(check)
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
      char char_getter;
      char string_getter[MAX_STRING_FILE_SIZE] = "";
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
	  char_getter = fgetc(file);
	  if( feof(file) )
	    {
	      break ;
	    }
	  if((char_getter != ' ') && (char_getter != '\n'))
	    {
	      map->mapArray[i++] = char_getter;
	    }
	}while(1);
      fclose(file);
    }
  else
    {
      printf("Error, impossible to open file\n");
    }
}
	  
void set_position_trainer(Map* map, int i)
{
  map->position_trainer = i;
}

int get_position_trainer(Map* map)
{
  return map->position_trainer;
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

  if(!canMove)
    {
      printf("You can't move !\n");
    }
  else
    {
      printf("You can move !\n");
    }
  return canMove;
}
