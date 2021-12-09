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


typedef struct node ast_node;
struct node
{
    int line;
    int col;
    char *value;
    char *id;
    char * annotation_type;

    ast_node *first_child;
    ast_node *sibling;
};

typedef struct parameters parameter_t;
struct parameters
{
    char * param_type;
    parameter_t * next_param;
};

typedef struct element element_t;
struct element
{
    int is_func;
    int is_parameter;
    char * id;
    char * type;
    element_t * next_elem;
    parameter_t * list_params;
};

typedef struct table table_t;
struct table
{
    char * id;
    element_t * list_elems;
    table_t * next_table;
};

//ast_node *newNode(char *type, char *value, int line, int column);

ast_node *newNode(char *type, char *value);
void add_child(ast_node *parent, ast_node *child);
void add_sibling(ast_node *child, ast_node *new_sibling);
void print_ast(ast_node *current_node, int n); // n é o número de pontos
void free_ast(ast_node *head);

#endif // __AST_H