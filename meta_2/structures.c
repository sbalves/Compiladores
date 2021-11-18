#include "structures.h"
#include "y.tab.h"

int token_type[] = {
    INTLIT,
    REALLIT,
    STRLIT,
    ID,
};

token_t token(char *value, int type) {
    for (int i = 0; i < (sizeof(token_type) / sizeof(token_type[0])); ++i) {
        if (type == token_type[i]) {
            return (char *)strdup(value);
        }
    }
    return NULL;
}

ast *ast_node(char *id, token_t value) {
    ast *node = (ast *)malloc(sizeof(ast));
    assert(node != NULL);

    node->id = id;
    node->value = value;
    node->first_child = NULL;
    node->next_sibling = NULL;

    return node;
}

