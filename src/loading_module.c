#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "string_utils.h"
#include "container.h"
#include "linked_list.h"
#include "hash_table.h"
#include "type_poke.h"
#include "attack.h"
#include "poketudiant.h"
#include "loading_module.h"

#define MAX_STRING_FILE_SIZE 300
#define MAX_STRING_ATTRIBUTS_POKETUDIANT 60

void load_base_poketudiant(Hash_table* table_poke, const char* file_name)
{
  FILE* file;
  file = fopen(file_name,"r");
  if(file)
    {
      char string_getter[MAX_STRING_FILE_SIZE] = "";
      while(fgets(string_getter,MAX_STRING_FILE_SIZE,file) != NULL)
	{
	  remove_occurences(string_getter,' ');
	  remove_occurences(string_getter,'\n');
	  remove_occurences(string_getter,'\t');
	  if(strcmp(string_getter,"{") == 0) /* Detect new poketudiant flag */ 
	    {
	      Poketudiant* poke = NULL;
	      Type_poke type; 
	      char variety[MAX_STRING_ATTRIBUTS_POKETUDIANT];
	      char evolution[MAX_STRING_ATTRIBUTS_POKETUDIANT];
	      int capturable;
	      unsigned int attack;
	      unsigned int defense;
	      unsigned int hp;
	      
	      int end_objet = 0;
	      while(!end_objet)
		{
		  fgets(string_getter,MAX_STRING_FILE_SIZE,file);
		  remove_occurences(string_getter,' ');
		  remove_occurences(string_getter,'\n');
		  remove_occurences(string_getter,'\t');
		  
		  if(string_getter[0] == '#'){} /* Commentary */
		  else if(string_getter[0] == '}'){end_objet = 1;} /* End objet */
		  else
		    {
		      long eq_position;
		      char id[MAX_STRING_ATTRIBUTS_POKETUDIANT] = {0};
		      char val[MAX_STRING_ATTRIBUTS_POKETUDIANT] = {0};
		      
		      eq_position = strchr(string_getter,'=') - string_getter;
		      strncpy(id,string_getter,eq_position);
		      strcpy(val,strchr(string_getter,'=') + sizeof(char));
		      		      
		      if(strcmp(id,"name") == 0)
			{
			  strcpy(variety,val);
			}
		      else if(strcmp(id,"type") == 0)
			{
			  type = enum_from_string_type_poke(val);
			}
		      else if(strcmp(id,"capturable") == 0)
			{
			  capturable = atoi(val);
			}
		      else if(strcmp(id,"evolution") == 0)
			{
			  strcpy(evolution,val);
			}
		      else if(strcmp(id,"attack") == 0)
			{
			  attack = atoi(val);
			}
		      else if(strcmp(id,"defense") == 0)
			{
			  defense = atoi(val);
			}
		      else if(strcmp(id,"pv_max") == 0)
			{
			  hp = atoi(val);
			}
		      else
			{
			  printf("Unkown value in pokemon loading from file!\n");
			}
		    }
		}
	      
	      poke = create_poketudiant(type,variety,
					NULL,NULL,
					attack,defense,hp,
					capturable,evolution);
	      
	      add_to_hash_table(table_poke,poke);
	    }
	}
      fclose(file);
    }
  else
    {
      printf("Error, impossible to open file\n");
    }
}

void load_base_attack(Hash_table* table_attack, const char* file_name)
{
  FILE* file;
  file = fopen(file_name,"r");
  if(file)
    {
      char string_getter[MAX_STRING_FILE_SIZE] = "";
      while(fgets(string_getter,MAX_STRING_FILE_SIZE,file) != NULL)
	{
	  remove_occurences(string_getter,' ');
	  remove_occurences(string_getter,'\n');
	  remove_occurences(string_getter,'\t');
	  if(strcmp(string_getter,"{") == 0) /* Detect new poketudiant flag */ 
	    {
	      Attack* attack = NULL;
	      char name[MAX_STRING_ATTRIBUTS_POKETUDIANT];
	      Type_poke type;
	      unsigned int pow;
	      
	      int end_objet = 0;
	      while(!end_objet)
		{
		  fgets(string_getter,MAX_STRING_FILE_SIZE,file);
		  remove_occurences(string_getter,' ');
		  remove_occurences(string_getter,'\n');
		  remove_occurences(string_getter,'\t');
		  
		  if(string_getter[0] == '#'){} /* Commentary */
		  else if(string_getter[0] == '}'){end_objet = 1;} /* End objet */
		  else
		    {
		      long eq_position;
		      char id[MAX_STRING_ATTRIBUTS_POKETUDIANT] = {0};
		      char val[MAX_STRING_ATTRIBUTS_POKETUDIANT] = {0};
		      
		      eq_position = strchr(string_getter,'=') - string_getter;
		      strncpy(id,string_getter,eq_position);
		      strcpy(val,strchr(string_getter,'=') + sizeof(char));
		      		      
		      if(strcmp(id,"name") == 0)
			{
			  strcpy(name,val);
			}
		      else if(strcmp(id,"type") == 0)
			{
			  type = enum_from_string_type_poke(val);
			}
		      else if(strcmp(id,"pow") == 0)
			{
			  pow = atoi(val);
			}
		      else
			{
			  printf("Unkown value in pokemon loading from file!\n");
			}
		    }
		}
	      
	      attack = create_attack(name,type,pow);
	      add_to_hash_table(table_attack,attack);
	    }
	}
      fclose(file);
    }
  else
    {
      printf("Error, impossible to open file\n");
    }
}
