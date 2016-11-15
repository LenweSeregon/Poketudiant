
typedef int** Weakness;

/* Il faudra voir à stocker le nombre de type quelque part ou à ajouter un last a l'enum Typepoke*/

Weakness* create_weakness();

/* type 1 est faible par rapport au type 2 */
void add_weakness(Weakness* weakness, Type_poke type1, Type_poke type2);

/* est-ce que type1 est faible par rapport au type2*/
int is_weak(Weakness* weakness, Type_poke type1, Type_poke type2);

void delete_weakness(Weakness* weakness);
