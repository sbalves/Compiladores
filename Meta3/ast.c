/*  
    * Projeto de Compiladores 2021/2022
    * Meta 3
    * 2019218953 João Miguel Ferreira Castelo Branco Catré
    * 2019227240 Sofia Botelho Vieira Alves
*/ 
#include "ast.h"

//extern bool is_arithmetic_operator;
//extern bool is_logical_operator;


ast_node *newNode(char *type, char *value, int expr)
{
    ast_node *new_node = (ast_node *)malloc(sizeof(ast_node));
    new_node->id = (char *)strdup(type); // type -> "FuncDecl", "Id", ...
    new_node->first_child = NULL;
    new_node->sibling = NULL;
    new_node->annotation.type= NULL;
    new_node->annotation.parameters = NULL;
    new_node->is_expr = expr;

    /*
    new_node->col = column;
    new_node->line = line;
    */
    if (value == NULL) // value -> "fatorial", "12", ...
    {
        new_node->value = NULL;
        return new_node;
    }
    new_node->value = (char *)strdup(value);
    return new_node;
}

void add_child(ast_node *parent, ast_node *child)
{
    if (parent != NULL && child != NULL)
        parent->first_child = child;
}

void add_sibling(ast_node *child, ast_node *new_sibling)
{
    if (child != NULL && new_sibling != NULL)
    {
        ast_node *current = child;
        while (current->sibling != NULL)
        {
            current = current->sibling;
        }
        current->sibling = new_sibling;
    }
}

/*
void verify_types(ast_node * node){
    if(strcmp((node->first_child)->annotation_type, "int") && strcmp(((node->first_child)->sibling)->annotation_type, "int")){
        printf(node);
    }
}
*/

/*
void print_annotation(ast_node *node){
    if(is_arithmetic_operator(node)){
        if(strcmp((node->first_child)->id, "Id") && strcmp(((node->first_child)->sibling)->id, "Id"))
            verify_types(node);
    }
}
*/



void print_ast(ast_node *current_node, int n) /*o parametro "n" serve para calcular o nível de identação*/
{
    if (current_node == NULL)
        return; // empty node

    if (current_node != NULL)
    {
        if (current_node->id)
        {
            if (strcmp(current_node->id, "NULL") != 0)
            {
                for (int i = 0; i < n; i++)
                {
                    printf("..");
                }
                printf("%s", current_node->id);
                if (current_node->value != NULL)
                {
                    printf("(%s)", current_node->value);
                } 
                /*if(annotation.type){
                    printf(" - %s", annotation.type);
                    if (annotation.parameters) {
                        print_parameter_list(annotation.parameters);
                    }
                }*/

                if(current_node->is_expr){
                    printf(" - %s", current_node->annotation.type);
                }

                printf("\n");

                if (current_node->first_child != NULL)
                {
                    if(strcmp((current_node->first_child)->id, "Expr"))

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

/*
if(current_node->annotation_type != NULL && num_anottation == 0){
    printf(" - ()");
}

if(current_node->annotation_type != NULL && num_anottation == 1){
    printf(" - %s", current_node->annotation_type);
}

if(current_node->annotation_type != NULL &&  num_anottation > 1){
    printf(" - (%s", current_node->annotation_type[0]);
    for(int i; i == num_anottation-1; i++){
        printf(", %s", current_node->annotation_type[i]); 
    }
    printf(", %s)", current_node->annotation_type[num_anotattion-1]);
}
*/

void free_ast(ast_node *current_node)
{
    if (current_node == NULL) return;

    if (!current_node->id)
    {
        free(current_node->id);
    }
 
     if (!current_node->value)
    {
        free(current_node->value);
    }

    free_ast(current_node->first_child);
    free_ast(current_node->sibling);
    free(current_node);
}