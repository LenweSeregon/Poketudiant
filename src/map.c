#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constantes.h"
#include "string_utils.h"
#include "map.h"

#define COLOR(param) printf("\033[%sm",param);

#define WILD 1
#define ROAD 2

#define YELLOW_BACK COLOR("43");
#define BLUE_BACK COLOR("44");
#define GREEN_BACK COLOR("42");

#define YELLOW_TEXT COLOR("33");
#define BLUE_TEXT COLOR("34");
#define GREEN_TEXT COLOR("32");


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
	    default:
	      printf("Error\n");
	    }
	  printf("%c ",elem);
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

      print_map(map);
      
      fclose(file);
    }
  else
    {
      printf("Error, impossible to open file\n");
    }
}
	  
