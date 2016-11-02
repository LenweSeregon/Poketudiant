#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "container.h"

Container* create_container(Container_type type, unsigned int initial_size, int memory_element_owner)
{
  Container* container = malloc(sizeof(Container));
  container->type = type;
  container->max = initial_size;
  container->current = 0;
  container->list = malloc(container->max * sizeof(void*));
  container->has_memory_element_responsability = memory_element_owner;
  
  return container;
}

void delete_container(Container* container)
{
  if(container->has_memory_element_responsability)
    {
      unsigned int i;
      for(i = 0 ; i < container->current ; i++)
	{
	  free(container->list[i]);
	}
    }
  free(container->list);
  free(container);
}

void add_to_container(Container* container, void* element)
{
  if(container->type == STATIC && container->current == container->max)
    {
      return;
    }

  if(container->current == container->max)
    {
      container->max *= 2;
      container->list = realloc(container->list, container->max * sizeof(void*));
      add_to_container(container,element);
    }
  else
    {
      container->list[container->current] = element;
      container->current++;
    }
}

void remove_to_container(Container* container, void* element)
{
  int getter;
  if((getter = search_position_in_container(container,element)) != -1)
    {
      void* tmp = container->list[getter];
      container->list[getter] = container->list[container->current - 1];
      container->list[container->current - 1] = tmp;

      free(container->list[container->current - 1]);
      container->current--;
    }
}

void print_container(const Container* container)
{
  unsigned int i;
  for(i = 0; i < container->current; i++)
    {
      printf("Element number %d = ",i);
      container->display_element_fct(container->list[i]);
    }
}

void* search_in_container(const Container* container, void* element)
{
  unsigned int i;
  for(i = 0; i < container->current; i++)
    {
      if(container->cmp_fct(container->list[i],element))
	{
	  return container->list[i];
	}
    }
  return NULL;
}

void* search_in_container_from_position(const Container* container, unsigned int pos)
{
  if(pos >= container->current)
    {
      return NULL;
    }
  else
    {
      return container->list[pos];
    }
}


int search_position_in_container(const Container* container, void* element)
{
  unsigned int i;
  for(i = 0; i < container->current; i++)
    {
      if(container->cmp_fct(container->list[i],element))
	{
	  return i;
	}
    }
  return -1;
}
