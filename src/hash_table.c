#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "math_utils.h"
#include "container.h"
#include "linked_list.h"
#include "hash_table.h"

Hash_table* create_hash_table(unsigned int size)
{
  Hash_table* table = malloc(sizeof(Hash_table));
  table->size = size;
  table->array = calloc(table->size, sizeof(Linked_list*));
  return table;
}

void delete_hash_table(Hash_table* table)
{
  unsigned int i;
  for(i = 0; i < table->size; i++)
    {
      if(table->array[i] != NULL)
	{
	  delete_linked_list(table->array[i]);
	}
    }
  free(table->array);
  free(table);
}

void add_to_hash_table(Hash_table* table, void* element)
{
  int hash = table->hash_fct(element) % table->size;
  Linked_list* list = table->array[hash];

  if(list == NULL)
    {
      list = create_linked_list();
      list->print_fct = table->print_fct_linked_list;
      list->cmp_fct = table->cmp_fct_linked_list;
      list->free_fct = table->free_fct_linked_list;
      add_head_linked_list(list,element);
      table->array[hash] = list;
    }
  else
    {
      add_head_linked_list(list,element);
    }
}

void print_hash_table(const Hash_table* table)
{
  unsigned int i;
  for(i = 0; i < table->size; i++)
    {
      if(table->array[i] != NULL)
	{
	  print_linked_list(table->array[i]);
	  printf("#############\n");
	  printf("#############\n");
	}
    }
}

void set_cmp_fct_for_hash_table(Hash_table* table, int(*cmp)(void*,void*))
{
  unsigned int i;
  table->cmp_fct_linked_list = cmp;
  for(i = 0; i < table->size; i++)
    {
      if(table->array[i] != NULL)
	{
	  table->array[i]->cmp_fct = table->cmp_fct_linked_list;
	}
    }
}

void* get_element_in_hash_table(Hash_table* table, void* element)
{
  int hash = table->hash_fct(element) % table->size;
  Linked_list* list = table->array[hash];
  
  if(list != NULL)
    {     
      return get_element_in_linked_list(list,element);
    }
  else
    {
      return NULL;
    }
}


void* get_random_element_in_hash_table(Hash_table* table)
{
  int random_value;
  unsigned int i;
  void* to_return;
  Container* container = create_container(DYNAMIC,30,0);
  for(i = 0; i < table->size; i++)
    {
      if(table->array[i] != NULL)
	{
	  get_all_element_in_ll_into_container(table->array[i],container);
	}
    }
  if(container->current == 0) return NULL;
  else
    {
      random_value = random_int(0,container->current - 1);
      to_return = search_in_container_from_position(container,random_value);
      delete_container(container);
      return to_return;
    }
}


void* get_random_element_with_criteria_in_hash_table(Hash_table* table, void* criteria)
{
  int random_value;
  unsigned int i;
  void* to_return;
  Container* container = create_container(DYNAMIC,30,0);
  for(i = 0; i < table->size; i++)
    {
      if(table->array[i] != NULL)
	{
	  get_all_element_in_ll_into_container_criteria(table->array[i],container,criteria);
	}
    }

  if(container->current == 0) 
    {
      return NULL;
    }
  else
    {
      random_value = random_int(0,container->current - 1);
      to_return = search_in_container_from_position(container,random_value);
      delete_container(container);
      return to_return;
    }
}

