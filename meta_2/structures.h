#ifndef __AST_H
#define __AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include <stdarg.h> //used to add children/siblings nodes
#include <stdbool.h>


typedef char *token_t;

typedef struct ASTNode ast;
    struct ASTNode {
        char *id;
        token_t value;
        ast *first_child;
        ast *next_sibling;
};

token_t token(char *value, int type);
ast *ast_node(char *id, token_t token);
#endif // __AST_H