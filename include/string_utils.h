#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

/*
 * @name   : remove_occurences
 * @arg    : string , string from which we want to remove character
 * @arg    : c , character that we want to remove
 * @desc   : This function is used to remove all occurence of c in string.
             the string is directly modify, there is no return
 *
 * @return : no return;
 */
void remove_occurences(char* string, char c);

/*
 * @name   : remove_first_occurence
 * @arg    : string , string from which we want to remove character
 * @arg    : c , character that we want to remove
 * @desc   : This function is used to remove first occurence of c in string.
             the string is directly modify, there is no return
 *
 * @return : no return;
 */
void remove_first_occurence(char* string, char c);

/*
 * @name   : remove_last_occurence
 * @arg    : string , string from which we want to remove character
 * @arg    : c , character that we want to remove
 * @desc   : This function is used to remove last occurence of c in string.
             the string is directly modify, there is no return
 *
 * @return : no return;
 */
void remove_last_occurence(char* string, char c);

void empty_buffer();

#endif
