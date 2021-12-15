#include "auxiliar_functions.h"

//const char expressions_aux[50][8] = {"Call", "Id", , , "Minus", "Plus", "IntLit", "RealLit"};

const char logical_operators[9][3] = {"Or", "And", "Lt", "Gt", "Eq", "Ne", "Le", "Ge", "Not"};
const char arithmentic_operators[5][3] = {"Add", "Mul", "Sub", "Div", "Mod"};

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