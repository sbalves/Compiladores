#include "structures.h"
#include "symbol_table.h"


//ast_node *newNode(char *type, char *value, int line, int column);
ast_node * newNode(char *type, char *value);
void add_child(ast_node *parent, ast_node *child);
void add_sibling(ast_node *child, ast_node *new_sibling);
void print_ast(ast_node *current_node, int n); // n é o número de pontos
void print_ast1(ast_node *current_node, int n); // n é o número de pontos
void free_ast(ast_node *head);