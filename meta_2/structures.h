#ifndef __AST_H
#define __AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct node
{
    char *value;
    char *type;
    struct node *first_child;
    struct node *sibling;
} node;

node *newNode(char *type, char *value);
void add_child(node *parent, node *child);
void add_sibling(node *child, node *new_sibling);
void print_ast(node *current_node, int n); // n é o número de pontos
void free_ast(node *head);

#endif // __AST_H