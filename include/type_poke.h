#ifndef __TYPE_POKE_H__
#define __TYPE_POKE_H__

#define NB_TYPE_POKE 4

enum Type_poke
  {
    LAZY, 
    NOISY,
    MOTIVATED,
    TEACHER
  };
typedef enum Type_poke Type_poke;

/*
 * @name   : string_from_enum_type_poke
 * @arg    : type , enum type that we want to convert as string
 * @desc   : This function is used to get a string format from enum format for poke type
 *
 * @return : char* that represent relation from enum;
 */
char* string_from_enum_type_poke(Type_poke type);

/*
 * @name   : enum_from_string_type_poke
 * @desc   : This function is used to get a enum format from a string format for poke type
 *
 * @return : enum type that represent translation from string;
 */
Type_poke enum_from_string_type_poke(const char* string);
#endif
