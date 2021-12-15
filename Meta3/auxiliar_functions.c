#include "auxiliar_functions.h"

//const char expressions_aux[50][8] = {"Call", "Id", , , "Minus", "Plus", "IntLit", "RealLit"};

const char * statement_token[] = {"For", "If"};
const char * unary_operator[] = {"Minus", "Plus", "Not"};
const char * realtional_operator[] = {"Lt", "Gt", "Eq", "Ne", "Le", "Ge"};
const char * logical_operators[] = {"Or", "And"};
const char * arithmentic_operators[] = {"Add", "Mul", "Sub", "Div", "Mod", "Assign"};

bool is_statement_token(char * id){
    for(int i = 0; i < sizeof(statement_token)/sizeof(statement_token[0]); i++){
        if(!strcmp(id,statement_token[i]))
            return true;
    }
    return false;
}

bool is_unary_operator(char * id){
    for(int i = 0; i < sizeof(unary_operator)/sizeof(unary_operator[0]); i++){
        if(!strcmp(id,unary_operator[i]))
            return true;
    }
    return false;
}

bool is_realtional_operator(char * id){
    for(int i = 0; i < sizeof(realtional_operator)/sizeof(realtional_operator[0]); i++){
        if(!strcmp(id,realtional_operator[i]))
            return true;
    }
    return false;
}

bool is_arithmetic_operator(char * id){
    for(int i = 0; i < sizeof(arithmentic_operators)/sizeof(arithmentic_operators[0]); i++){
        if(!strcmp(id,arithmentic_operators[i]))
            return true;
    }
    return false;
}

bool is_logical_operator(char * id){
    for(int i = 0; i < sizeof(logical_operators)/sizeof(logical_operators[0]); i++){
        if(!strcmp(id,logical_operators[i]))
            return true;
    }
    return false;
}