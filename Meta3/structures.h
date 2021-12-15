#ifndef __STRUCTURES_H
#define __STRUCTURES_H
/*  
    * Projeto de Compiladores 2021/2022
    * Meta 3
    * 2019218953 João Miguel Ferreira Castelo Branco Catré
    * 2019227240 Sofia Botelho Vieira Alves
    * 
*/ 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

typedef const char *type_t;

typedef struct parameters parameter_t;
struct parameters
{
    char * param_type;
    parameter_t * next_param;
};

typedef struct annotation annotation_t;
struct annotation {
    type_t type;
    parameter_t *parameters;
};

typedef struct node ast_node;
struct node
{
    int line;
    int col;

    char *value;
    char *id;

    annotation_t annotation;
    ast_node *first_child;
    ast_node *sibling;
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



#endif // __STRUCTURES_H