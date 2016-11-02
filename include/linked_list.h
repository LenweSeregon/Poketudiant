#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

/*
 * @author : Nicolas
 * @date   : 27 / 10 / 2016
 * 
 * @name   : Linked_list_element
 * @desc   : This structure is a basic structure that can stock all type of data
             It's use in Linked_list as basic element
 */
struct Linked_list_element
{
  void* element;
  struct Linked_list_element* next;
};
typedef struct Linked_list_element Linked_list_element;

Linked_list_element* create_linked_list_element(void* element, Linked_list_element* next);
void delete_linked_list_element(Linked_list_element* list_element);


/*
 * @author : Nicolas
 * @date   : 27 / 10 / 2016
 * 
 * @name   : Linked_list
 * @desc   : This structure is a basic simple linked list use as a data structure.
             Basically, and at the moment, this linked list is to use manage collision in hash table
	     As Linked_list head is a Linked_list_element, this list can be use to stock every
	     type of data.
	     Care : print_fct and cmp_fct have to be initialize with logic contents according
	     to data to manage datas stocked in linked list
*/
struct Linked_list
{
  Linked_list_element* head;
  void (*print_fct)(void*);
  int (*cmp_fct)(void*,void*);
  void (*free_fct)(void*);
};
typedef struct Linked_list Linked_list;

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : create_linked_list
 * @desc   : This function allocate memory for a linked list, set head to NULL
             and return it as a pointer
 *
 * @return : Pointer on generated linked list element;
 */
Linked_list* create_linked_list();

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : delete_linked_list
 * @arg    : list , pointer on the linked list that we want to delete 
 * @desc   : This function ensure to delete a linked list totally without memory leak on it
             It call internally delete_linked_list_element for each node of our linked list
 *
 * @return : no return
 */
void delete_linked_list(Linked_list* list);

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : add_head_linked_list
 * @arg    : list , pointer on the linked list that we want to insert in
 * @arg    : element , void pointer that's gonna be store on a linked_list_element
 * @desc   : This function add in linked list the element at head position
 *
 * @return : no return;
 */
void add_head_linked_list(Linked_list* list, void* element);

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : add_tail_linked_list
 * @arg    : list , pointer on the linked list that we want to insert in
 * @arg    : element , void pointer that's gonna be store on a linked_list_element
 * @desc   : This function add in linked list the element at tail position
 *
 * @return : no return;
 */
void add_tail_linked_list(Linked_list* list, void* element);

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : remove_head
 * @arg    : list , pointer on linked list where we want to remove head 
 * @desc   : This function can be call to remove the head element of the linked list
             It ensure to remove properly the linked list element without memory leak
 *
 * @return : no return;
 */
void remove_head(Linked_list* list);

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : remove_head
 * @arg    : list , pointer on linked list where we want to remove tail 
 * @desc   : This function can be call to remove the tail element of the linked list
             It ensure to remove properly the linked list element without memory leak
 *
 * @return : no return;
 */
void remove_tail(Linked_list* list);

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : remove_element
 * @arg    : list , pointer on linked list where we want to remove element 
 * @arg    : element , element that's we want to remove
 * @desc   : This function can be call to remove an element at any position in linked list
             It only destroy the first element encounter and ensure to remove properly
	     the linked list element without memory leak
 *
 * @return : no return;
 */
void remove_element(Linked_list* list, void* element);

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : remove_elements
 * @arg    : list , pointer on linked list where we want to remove elements 
 * @arg    : element , element that's we want to remove
 * @desc   : This function can be call to remove an element at any position in linked list
             It destroy all element encounter and ensure to remove properly
	     the linked list elements without memory leak
 *
 * @return : no return;
 */
void remove_elements(Linked_list* list, void* element);

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : get_element_in_linked_list
 * @arg    : list , pointer on linked list where we want to get element 
 * @arg    : element , element identifier that's we are looking for
 * @desc   : This function can be call to get a pointer on an element. This function
             do not erase the element or something, it's only give a pointer on it but it
	     must keep control on the variable, if you want to get and remove it, call
	     remove_elements function after calling this one
 *
 * @return : pointer on element if find , else NULL;
 */
void* get_element_in_linked_list(const Linked_list* list, void* element);

/*
 * @author : Nicolas
 * @date   : 01 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : get_all_element_in_ll_into_container
 * @arg    : list , pointer on linked list where we want to get all element
 * @arg    : container , container where we want to insert reference on element
 * @desc   : This function is used to insert a pointer reference in container given in
             parameters for example during random generation
 *
 * @return : no return;
 */
void get_all_element_in_ll_into_container(const Linked_list* list, Container* container);

/*
 * @author : Nicolas
 * @date   : 01 / 11 / 2016
 * @state  : [No bug]
 * 
 * @name   : get_all_element_in_ll_into_container_criteria
 * @arg    : list , pointer on linked list where we want to get all element
 * @arg    : container , container where we want to insert reference on element
 * @arg    : criteria , the criteria for our insertion , take care he's according to 
             cmp_fct given to linked list
 * @desc   : This function is used to insert a pointer reference in container given in
             parameters for example during random generation but according to a criteria
 *
 * @return : no return;
 */
void get_all_element_in_ll_into_container_criteria(const Linked_list* list,
						   Container* container,
						   void* criteria);

/*
 * @author : Nicolas
 * @date   : 28 / 10 / 2016
 * @state  : [No bug]
 * 
 * @name   : print_linked_list
 * @arg    : list, pointer on linked list that's we want to display
 * @desc   : This function can be use to print linked list element using the fct 
             initiliaze in linked list structure
 *
 * @return : no return;
 */
void print_linked_list(const Linked_list* list);

#endif
