#ifndef __GENERIC_CONTROL_FUNCTION_H__
#define __GENERIC_CONTROL_FUNCTION_H__


int hash_poketudiant_fct_from_string(void* element);
int hash_poketudiant_fct_from_poketudiant(void* element);
void print_poketudiant_fct(void* element);
void delete_poketudiant_fct(void* element);
int cmp_poketudiant_fct_via_type(void* a,void* b);
int cmp_poketudiant_fct_via_variety(void* a, void* b);
int cmp_poketudiant_fct_via_id(void* a, void* b);
int cmp_poketudiant_fct_via_capturable(void* a, void* b);
int cmp_poketudiant_fct_via_type_refuse(void* a,void* b);

int hash_attack_fct(void* element);
void print_attack_fct(void* element);
void delete_attack_fct(void* element);
int cmp_attack_fct_via_type(void*a, void*b);
int cmp_attack_fct_via_type_and_no_teacher(void* a, void*b);
int cmp_attack_fct_via_type_refuse(void*a, void*b);
int cmp_attack_fct_via_type_refuse_and_no_teacher(void* a, void* b);

#endif
