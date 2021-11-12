/**
 * Licenciatura em Engenharia Informática | Faculdade de Ciências e Tecnologia da Universidade de Coimbra
 * Projeto de Compiladores 2021/2022
 *
 * 2019218953 João Miguel Ferreira Castelo Branco Catré
 * 2019227240 Sofia Botelho Vieira Alves
 *   
*/

#ifndef __STRUCTURES_H
#define __STRUCTURES_H

#include <stdbool.h>

typedef struct token{
    char * value;
    int line_num, column_num;
} token_t;

//Nós da árvore de sintaxe abstrata
typedef struct ASTNode ast_node_t;
struct ASTNode {
    const char *id;
    token_t token;
    //annotation_t annotation;
    ast_node_t *first_child;
    ast_node_t *next_sibling;
};

#endif