#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "type_poke.h"
#include "weakness.h"

Weakness* create_weakness()
{
  int i,j;
  Weakness* weak = malloc(sizeof(Weakness));
  *weak = malloc(LAST*sizeof(int*));
  for(i=0;i<LAST;i++)
    {
      (*weak)[i] = malloc(LAST*sizeof(int));
      for(j=0;j<LAST;j++)
	{
          (*weak)[i][j]=0;
	}
    }
  return weak;
}

void add_weakness(Weakness* weakness, Type_poke type1, Type_poke type2)
{
  (*weakness)[type1][type2]=1;
}

int is_weak(Weakness* weakness, Type_poke type1, Type_poke type2)
{
  return (*weakness)[type1][type2];
}
 void delete_weakness(Weakness* weakness)
{
  int i;
  for(i=0;i<LAST;i++)
    {
      free((*weakness)[i]);
    }
  free(*weakness);
  free(weakness);
}

