#include "structures.h"

extern table_t * tables_root;

table_t * add_table(table_t * root, char * table_id);
void add_element(table_t * table, element_t * new_elem);
element_t * create_element(char * id, char * type, parameter_t * params_list);
parameter_t * create_param(ast_node * node);
element_t * find_element(table_t * table, char * id);
void find_params(parameter_t * param, ast_node * node,  table_t * table);
element_t * find_table(table_t * table, char * function_name);
table_t * create_table(char * id);
char * lowercase(char * word);
void print_table_params(parameter_t * list);
void print_table_params(parameter_t * list);
void print_elements(element_t * elem);
void print_table_list(table_t * table);