**********************************************************
*                                                        *
*                   Projet Pokétudiants                  *
*                                                        *
*                        Langage C                       *
*                                                        *
*                    Guide développeur                   *
*                                                        *
**********************************************************

Option de compilation :

La compilation sera executer avec ces différents flags :

Wall , Wextra , ansi , pedantic , g

**********************************************************

Convention sur les fichiers:

Les fichiers suivent la même règle de notation des 
identifiants c’est à dire comme suit

nom_fichier.h

Chaque « .h » aura un ifndef comme suit

#ifndef __FILE_H__
#define __FILE_H__

/* CORPS FONCTION */

#endif

**********************************************************

Convention sur les includes :

Chaque fichier « .c » include de manière permanente les 
3 fichiers de base de la bibliothèque standard :
	- « stdio.h » , « stdlib.h » et « string.h »

Les includes de la bibliothèque standard sont séparés de 
ceux personnels comme suit :

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include «perso.h»
#include «perso2.h»

ATTENTION : On suit la règle de Mazure, pas d’include dans
les « .h » donc penser aussi aux règles pour le makefile

**********************************************************

Convention sur les defines : 

Tout les defines seront écris en majuscule et séparer
comme pour les identifiants avec un « _ »

#define PI 3.14
#define WIDTH_MAP 20
#define HEIGHT_MAP 20


**********************************************************

Convention sur les commentaires de fonctions :
Toutes les fonctions / structures doivent être commentées avec le 
	format suivant (en adaptant si fonction ou structure)

/**
 *
 * @author : Y
 * @date   : XX / XX / 2016
 * @state  : [No bug, possible bug, bug]
 * 
 * @name   : foo
 * @arg    : a1 , description argument 
 * @arg    : a2 , description argument
 * @desc   : description function
 *
 * @return : description return;
 */
int foo(int a1, int a2);

**********************************************************

Convention sur les identificateurs : 

Les identificateurs seront au format suivant :

identifiant_numero_1

**********************************************************

Convention sur les accolades :

Les accolades de bloc sont placées sur une ligne 
différente du début de bloc

for(;;)
{
    if(1)
    {
        return;
    }
}

**********************************************************

Convention sur les structures :

Le nom d’un structure commence par une majuscule et suit
le format habituel des identificateurs.
Le typedef est fait après la déclaration de la structure
sur la ligne en dessous

struct Struct_name
{
    int a;
    char* p;
};
typedef struct Struct_name Struct_name;

**********************************************************

Convention sur les énumerations :

Le nom d’une énumeration commence par une majuscule et suit
le format habituel des identificateurs
Le typedef est fait après la déclaration de la structure 
sur la ligne en dessous
Les constantes de l’énumération sont en majuscule

enum Enum_name
{
    VALUE1,
    VALUE2,
    VALUE3
};
typedef enum Enum_name Enum_name

**********************************************************