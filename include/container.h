#ifndef __CONTAINER_H__
#define __CONTAINER_H__

enum Container_type
  {
    DYNAMIC,
    STATIC
  };
typedef enum Container_type Container_type;

/*
 * @author : Nicolas
 * @date   : 27 / 10 / 2016
 * 
 * @name   : Container
 * @desc   : This structure is a basic array container that can stock all type of data
             It can be use have dynamic or static array according to type give to create_container
	     function. 
	     Care : display_element_fct and cmp_fct have to be initiliaze with logic content 
	     according to data stocked in Container
 */
struct Container
{ 
  Container_type type;
  void** list;
  unsigned int max;
  unsigned int current;

  int has_memory_element_responsability;

  void (*display_element_fct)(void *);
  int (*cmp_fct)(void*,void*);
  void (*delete_fct)(void*);
};
typedef struct Container Container;

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : create_container
 * @arg    : type , enum type to determine if we want static or dynamic collection
 * @arg    : initial_size , this initial size for dynamic collection or final size for static
 * @desc   : This function create dynamic container according to type given in argument
             and return this container as pointer
 *
 * @return : pointer on collection
 */
Container* create_container(Container_type type, unsigned int initial_size, int memory_element_owner);

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : delete_container
 * @arg    : container , pointer on container that's we want to delete
 * @desc   : This function is use to delete a container allocate dynamically and it ensure
             to erase all elements in container properly
 *
 * @return : no return;
 */
void delete_container(Container* container);


/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : add_to_container
 * @arg    : container , pointer on container where we want to add element 
 * @arg    : element , element that's we want to insert in container
 * @desc   : This function is use to add an element in container. If you're container
             is create as static, and if there's no more place, insertion is cancel 
 *
 * @return : no return;
 */
int add_to_container(Container* container, void* element);

/*
 * @author : Nicolas
 * @date   : 04 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : add_to_container_if_not_exist
 * @arg    : container , pointer on container where we want to add element 
 * @arg    : element , element that's we want to insert in container
 * @desc   : This function is use to add an element in container. If you're container
             is create as static, and if there's no more place, insertion is cancel.
	     Also, according to cmp function, if element already exist, insertion is cancel
 *
 * @return : no return;
 */
int add_to_container_if_not_exist(Container* container, void* element);

/*
 * @author : Nicolas
 * @date   : 04 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : empty_container
 * @arg    : container , pointer on container that's we want to empty 
 * @desc   : This function is use to empty the container ! It's also free element
             if container is responsable of memory
 *
 * @return : return the removed element;
 */
void empty_container(Container* container);

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : remove_to_container
 * @arg    : container , pointer on container where we want to remove element 
 * @arg    : element, element that's we want to insert in container
 * @desc   : This function is use to remove an element from our container. take care
             this function remove the pointer but doesn't free it !
 *
 * @return : return the removed element;
 */
void* remove_to_container(Container* container, void* element);


/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : search_in_container
 * @arg    : container , pointer on container where we are looking for element 
 * @arg    : element , element that's we are looking for
 * @desc   : This function is use to search an element into container according to 
             the cmp_fct provide in container structure
 *
 * @return : return pointer on the element but take care the memory responsability still 
             in container ! If element is not found return NULL;
 */
void* search_in_container(const Container* container, void* element);

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : search_in_container_from_position
 * @arg    : container , pointer on container where we are looking for element 
 * @arg    : pos , position in array that we are looking for element
 * @desc   : This function is use to search an element into container according to position require
 *
 * @return : return pointer on the element but take care the memory responsability still in 
             container ! If position is unvailable, return NULL
 */
void* search_in_container_from_position(const Container* container, unsigned int pos);

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : search_in_container
 * @arg    : container , pointer on container where we are looking for element 
 * @arg    : element , element that's we are looking for
 * @desc   : This function is use to search an element into container according to 
             the cmp_fct provide in container structure
 *
 * @return : return index of the element in the container ! If element is not found return -1;
 */
int search_position_in_container(const Container* container, void* element);

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : print_container
 * @arg    : container , const pointer on container that's we want to display 
 * @desc   : This function is use to print the entire container in console according to
             display_element_fct provide in the container structure
 *
 * @return : no return;
 */
void print_container(const Container* container);

#endif
