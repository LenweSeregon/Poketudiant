#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "type_poke.h"

char* string_from_enum_type_poke(Type_poke type)
{
  switch(type)
    {
    case LAZY:
      return "Lazy";
      break;
    case NOISY:
      return "Noisy";
      break;
    case MOTIVATED:
      return "Motivated";
      break;
    case TEACHER:
      return "Teacher";
      break;
    default:
      return "Undefined";
      break;
    }
}

Type_poke enum_from_string_type_poke(const char* string)
{
  if(strcmp(string,"LAZY") == 0)
    {
      return LAZY;
    }
  else if(strcmp(string,"NOISY") == 0)
    {
      return NOISY;
    }
  else if(strcmp(string,"MOTIVATED") == 0)
    {
      return MOTIVATED;
    }
  else if(strcmp(string,"TEACHER") == 0)
    {
      return TEACHER;
    }
  else 
    {
      printf("Error, there is no enum translation from this string\n");
      return -1;
    }
}
