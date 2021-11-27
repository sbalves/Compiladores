/*  
    * Projeto de Compiladores 2021/2022
    * Meta 2
    * 2019218953 João Miguel Ferreira Castelo Branco Catré
    * 2019227240 Sofia Botelho Vieira Alves
*/ 
#include "structures.h"

node *newNode(char *type, char *value)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->type = (char *)strdup(type); // type -> "FuncDecl", "Id", ...
    new_node->first_child = NULL;
    new_node->sibling = NULL;

    if (value == NULL) // value -> "fatorial", "12", ...
    {
        new_node->value = NULL;
        return new_node;
    }
    new_node->value = (char *)strdup(value);
    return new_node;
}

void add_child(node *parent, node *child)
{
    if (parent != NULL && child != NULL)
        parent->first_child = child;
}

void add_sibling(node *child, node *new_sibling)
{
    if (child != NULL && new_sibling != NULL)
    {
        node *current = child;
        while (current->sibling != NULL)
        {
            current = current->sibling;
        }
        current->sibling = new_sibling;
    }
}


void print_ast(node *current_node, int n)
{
    if (current_node == NULL)
    {
        return; // empty node
    }

    if (current_node != NULL)
    {
        if (current_node->type != NULL)
        {
            if (strcmp(current_node->type, "NULL") != 0)
            {
                for (int i = 0; i < n; i++)
                {
                    printf("..");
                }

                if (current_node->value != NULL)
                {
                    printf("%s(%s)\n", current_node->type, current_node->value);
                }
                else
                {
                    printf("%s\n", current_node->type);
                }
                if (current_node->first_child != NULL)
                {
                    print_ast(current_node->first_child, n + 1);
                }
                if (current_node->sibling != NULL)
                {
                    print_ast(current_node->sibling, n);
                }
            }
            else
            {
                if (current_node->first_child != NULL)
                {
                    print_ast(current_node->first_child, n);
                }
                if (current_node->sibling != NULL)
                {
                    print_ast(current_node->sibling, n);
                }
            }
        }
    }
}


void free_ast(node *current_node)
{
    if (current_node)
    {
        if (current_node->first_child)
        {
            free_ast(current_node->first_child);
        }
        if (current_node->sibling)
        {
            free_ast(current_node->sibling);
        }
        free(current_node);
    }
}