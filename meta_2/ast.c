/*
 * Projeto de Compiladores 2021/2022
 * 2019218953 João Miguel Ferreira Castelo Branco Catré
 * 2019227240 Sofia Botelho Vieira Alves
*/
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "structures_p.h"
#include "y.tab.h"

int alloc_types[] = {
    ID,
    INTLIT,
    REALLIT,
    STRLIT
};

token_t token(char *value, int type) {
    for (int i = 0; i < (sizeof(alloc_types) / sizeof(alloc_types[0])); ++i) {
        if (type == alloc_types[i]) {
            return (char *)strdup(value);
        }
    }
    return NULL;
}

ast_node_t *ast_node(char *id, token_t value) {
    ast_node_t *node = (ast_node_t *)malloc(sizeof(ast_node_t));
    assert(node != NULL);

    node->id = id;
    node->value = value;
    node->first_child = NULL;
    node->next_sibling = NULL;

    return node;
}

void add_children(ast_node_t *parent, int argc, ...) {
    va_list args;
    ast_node_t *child = NULL;
    va_start(args, argc);

    assert(parent != NULL);
    child = va_arg(args, ast_node_t *);

    parent->first_child = child;
    ast_node_t *current = parent->first_child;

    for (int i = 0; i < argc - 1; ++i) {
        child = va_arg(args, ast_node_t *);
        for (ast_node_t *c = child; c; c = c->next_sibling) {
            current->next_sibling = c;
            current = current->next_sibling;
        }
    }
    va_end(args);
}

void add_siblings(ast_node_t *node, int argc, ...) {
    va_list args;
    va_start(args, argc);
    ast_node_t *sibling;

    assert(node != NULL);
    ast_node_t *current = node;
    while (current->next_sibling != NULL) {
        current = current->next_sibling;
    }

    for (int i = 0; i < argc; ++i) {
        sibling = va_arg(args, ast_node_t *);
        if (!sibling)
            continue;
        current->next_sibling = sibling;
        current = current->next_sibling;
    }
    va_end(args);
}

void free_ast(ast_node_t *node) {
    if (node) {
        if (node->value)
            free(node->value);
        free_ast(node->first_child);
        free_ast(node->next_sibling);

        free(node);
    }
}

void print_node(char *id, char *value, int indent_level) {
    for (int i = 0; i < indent_level; ++i)
        printf("..");
    printf("%s", id);
    if (value) printf("(%s)", value);
    printf("\n");
}

void __print_ast(ast_node_t *node, int indent_level) {
    print_node(node->id, node->value, indent_level);
    if (node->first_child != NULL)
        __print_ast(node->first_child, indent_level + 1);
    if (node->next_sibling != NULL)
        __print_ast(node->next_sibling, indent_level);
}

/* //Alterar
void print_ast(ast_node_t *program) {
    if (!syntax_error)
        __print_ast(program, 0);
}*/

void add_typespec(ast_node_t *type, ast_node_t *give_me_type) {
    ast_node_t *new_type_node = NULL;
    for (ast_node_t *current = give_me_type; current; current = current->next_sibling) {
        new_type_node = ast_node(type->id, NULL);                
        new_type_node->next_sibling = current->first_child;       
        current->first_child = new_type_node;                     
    }
}

ast_node_t *statement_list(ast_node_t *stat_list) {
    ast_node_t *list = stat_list;
    if (list && list->next_sibling) {
        list = ast_node("StatList", NULL);
        list->first_child = stat_list;
    }
    return list;
}

ast_node_t *null_check(ast_node_t *node) {
    return node ? node : ast_node("Null", NULL);
}