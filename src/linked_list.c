#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "container.h"
#include "linked_list.h"


Linked_list_element* create_linked_list_element(void* element, Linked_list_element* next)
{
  Linked_list_element* list_element = malloc(sizeof(Linked_list_element));
  list_element->element = element;
  list_element->next = next;
  return list_element;
}

void delete_linked_list_element(Linked_list_element* list_element)
{
  free(list_element);
}

Linked_list* create_linked_list()
{
  Linked_list* list = malloc(sizeof(Linked_list));
  list->head = NULL;
  return list;
}

void delete_linked_list(Linked_list* list)
{
  Linked_list_element* cur = list->head;
  
  while(cur)
    {
      Linked_list_element* to_erase = cur;
      cur = cur->next;
      list->free_fct(to_erase->element);
      delete_linked_list_element(to_erase);
    }
  free(list);
}


void add_head_linked_list(Linked_list* list, void* element)
{
  Linked_list_element* new_list_element = create_linked_list_element(element,list->head);
  list->head = new_list_element;
}

void add_tail_linked_list(Linked_list* list, void* element)
{
  Linked_list_element* new_list_element = create_linked_list_element(element,NULL);
  Linked_list_element* cur = list->head;
  Linked_list_element* prev = NULL;

  while(cur)
    {
      prev = cur;
      cur = cur->next;
    }

  prev->next = new_list_element;
}


void remove_head(Linked_list* list)
{
  if(list->head != NULL)
    {
      Linked_list_element* to_erase = list->head;
      delete_linked_list_element(to_erase);

      list->head = list->head->next;
    }
}

void remove_tail(Linked_list* list)
{
  if(list->head != NULL)
    {
      Linked_list_element* cur = list->head;
      Linked_list_element* prev = NULL;
      Linked_list_element* to_erase;
      while(cur->next)
	{
	  prev = cur;
	  cur = cur->next;
	}

      if(cur == list->head)
	{
	  to_erase = list->head;
	  delete_linked_list_element(to_erase);
	  list->head = NULL;
	}
      else
	{
	  to_erase = cur;
	  prev->next = NULL;
	  delete_linked_list_element(to_erase);
	  
	}
    }
}

void remove_element(Linked_list* list, void* element)
{
  if(list->head != NULL)
    {
      Linked_list_element* cur = list->head;
      Linked_list_element* prev = NULL;
 
      while(cur)
	{
	  if(cur == list->head && list->cmp_fct(list->head->element,element))
	    {
	      remove_head(list);
	      break;
	    }
	  else if(list->cmp_fct(cur->element,element))
	    {
	      Linked_list_element* to_erase = cur;
	      prev->next = cur->next;
	      delete_linked_list_element(to_erase);
	      break;
	    }

	  prev = cur;
	  cur = cur->next;
	}      
    }
}

void remove_elements(Linked_list* list, void* element)
{
  if(list->head != NULL)
    {
      Linked_list_element* cur = list->head;
      Linked_list_element* prev = NULL;

      while(cur)
	{
	  if(cur == list->head && list->cmp_fct(list->head->element,element))
	    {
	      remove_head(list);
	      cur = list->head;
	    }
	  else if(list->cmp_fct(cur->element,element))
	    {
	      Linked_list_element* to_erase = cur;
	      prev->next = cur->next;
	      cur = cur->next;
	      delete_linked_list_element(to_erase);
	    }
	  else
	    {
	      prev = cur;
	      cur = cur->next;
	    }
	}
    }
}

void* get_element_in_linked_list(const Linked_list* list, void* element)
{
  Linked_list_element* cur = list->head;

  while(cur)
    {
      if(list->cmp_fct(cur->element,element) == 0)
	{
	  return cur->element;
	}
      cur = cur->next;
    }
  return NULL;
}

void get_all_element_in_ll_into_container(const Linked_list* list, Container* container)
{
  Linked_list_element* cur = list->head;
  while(cur)
    {
      add_to_container(container,cur->element);
      cur = cur->next;
    }
}

void get_all_element_in_ll_into_container_criteria(const Linked_list* list,
						   Container* container,
						   void* criteria)
{
  Linked_list_element* cur = list->head;
  while(cur)
    {
      if(list->cmp_fct(cur->element,criteria) == 0)
	{
	  add_to_container(container,cur->element);
	}
      cur = cur->next;
    }
}


void print_linked_list(const Linked_list* list)
{
  Linked_list_element* cur = list->head;
  
  while(cur)
    {
      list->print_fct(cur->element);
      printf("->");
      cur = cur->next;
    }
  printf("NULL\n");
}
