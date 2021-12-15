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
#include "structures.h"
#include "symbol_table.h"
#include "auxiliar_functions.h"


ast_node * program_root;

extern table_t * current_table;
extern table_t * tables_root;
extern char * expressions_aux;

void anotate_arithmetic_operator(ast_node * node);
void anotate_logical_operator(ast_node * node);
void funcdecl_analysis(ast_node * node);
void vardecl_analysis(ast_node * node);
void semantic_analysis(ast_node * node);
int checknewvar(char * name);


#endif //SEM_A