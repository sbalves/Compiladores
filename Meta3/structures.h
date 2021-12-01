#ifndef __AST_H
#define __AST_H
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

extern table_t * tables_root;

typedef struct node
{
    int line;
    int col;
    char *value;
    char *id;
    ast_node *first_child;
    ast_node node *sibling;
} ast_node;

typedef struct parameters
{
    char * param_type;
    parameter_t * next_param;
} parameter_t;

typedef struct element
{
    int is_parameter
    char * id;
    char * type;
    element_t * next_elem;
    parameters * list_params;
} element_t;

typedef struct table
{
    char * id;
    element_t * list_elems;
    table_t * next_table;
} table_t;


node *newNode(char *type, char *value, int line, int column);
void add_child(node *parent, node *child);
void add_sibling(node *child, node *new_sibling);
void print_ast(node *current_node, int n); // n é o número de pontos
void free_ast(node *head);

#endif // __AST_H