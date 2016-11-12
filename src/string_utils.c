#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "string_utils.h"


void remove_occurences(char* string, char c)
{
  char *ptr_reader = string;
  char *ptr_writer = string;
    
  while (*ptr_reader)
    {
      *ptr_writer = *ptr_reader++;
      ptr_writer += (*ptr_writer != c);
    }
  *ptr_writer = '\0';
}

void remove_first_occurence(char* string, char c)
{
    
  char *ptr_reader = string;
  char *ptr_writer = string;
  int found = 0;
  while(*ptr_reader)
    {
      *ptr_writer = *ptr_reader++;
      if(!found && *ptr_writer == c)
        {
	  found = 1;
	  ptr_writer += 0;
        }
      else
        {
	  ptr_writer += 1;
        }
    }
  *ptr_writer = '\0';
}

void remove_last_occurence(char* string, char c)
{
  long position = strrchr(string, c) - string;
    
  char *ptr_reader = string;
  char *ptr_writer = string;
  int i = 0;
    
  while(*ptr_reader)
    {
      *ptr_writer = *ptr_reader++;
      if(i != position)
        {
	  ptr_writer += 1;
        }
      i++;
    }
  *ptr_writer = '\0';
}

void empty_buffer()
{
  int c = 0;
  while (c != '\n' && c != EOF)
    {
      c = getchar();
    }
}
