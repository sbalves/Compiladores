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



parameter_t * create_param(char * type);
parameters_t * find_params(ast_node * node);
table_t * create_table(char * id);
void funcdecl_analysis(ast_node * node);
void semantic_analysis(ast_node * node);

#endif //SEM_A