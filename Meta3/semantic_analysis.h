#ifndef SEM_A
#define SEM_A
/*  
    * Projeto de Compiladores 2021/2022
    * Meta 3
    * 2019218953 João Miguel Ferreira Castelo Branco Catré
    * 2019227240 Sofia Botelho Vieira Alves
    * 
    * , int *line, int *col
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "structures.h"


extern table_t * tables_root;

table_t * add_table(table_t * root, char * table_id);
void add_element(table_t * table, element_t * new_elem);
element_t * create_element(char * id, char * type, parameter_t * params_list);
parameter_t * create_param(ast_node * node);
parameter_t * find_params(element_t * elem, parameter_t * param, ast_node * node, table_t * table);
table_t * create_table(char * id);
void funcdecl_analysis(ast_node * node);
void vardecl_analysis(ast_node * node);
void semantic_analysis(ast_node * node);

#endif //SEM_A