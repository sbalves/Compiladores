#ifndef __AST_H
#define __AST_H

#include <stdbool.h>
typedef char *token_t;

typedef struct ASTNode ast_node_t;
    struct ASTNode {
        char *id;
        token_t value;
};

token_t token(char *value, int type);
ast_node_t *ast_node(char *id, token_t token);
#endif // __AST_H