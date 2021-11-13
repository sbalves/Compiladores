#include <stdbool.h>

#ifndef __AST_H
#define __AST_H

typedef char *token_t;

typedef struct ASTNode ast_node_t;
struct ASTNode {
    char *id;
    token_t value;
    ast_node_t *first_child;
    ast_node_t *next_sibling;
};

// Error Flags
extern bool syntax_error;

token_t token(char *value, int type);
ast_node_t *ast_node(char *id, token_t token);
void add_children(ast_node_t *parent, int argc, ...);
void add_siblings(ast_node_t *parent, int argc, ...);
void free_ast(ast_node_t *head);
void print_ast(ast_node_t *root);
void add_typespec(ast_node_t *type, ast_node_t *give_me_type);
ast_node_t *statement_list(ast_node_t *stat_list);
ast_node_t *null_check();

#endif // __AST_H