#ifndef __AST_H
#define __AST_H
/*  
    * Projeto de Compiladores 2021/2022
    * Meta 2
    * 2019218953 João Miguel Ferreira Castelo Branco Catré
    * 2019227240 Sofia Botelho Vieira Alves
    * 
    * , int *line, int *col
*/ 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct node
{
    int line;
    int col;
    char *value;
    char *type;
    struct node *first_child;
    struct node *sibling;
} node;

node *newNode(char *type, char *value, int line, int column);
void add_child(node *parent, node *child);
void add_sibling(node *child, node *new_sibling);
void print_ast(node *current_node, int n); // n é o número de pontos
void free_ast(node *head);

#endif // __AST_H