#include "semantic_analysis.h"


parameter_t * create_param(char * type){
    parameter_t * parameter = (parameter_t *)malloc(sizeof(parameter_t));
    
    strcpy(parameter->type, type); //?
    parameter->next_param = NULL;

    return parameter;
}


parameter_t * iterate_params(){

    if(node->first_child != NULL){

        
    }
}

parameter_t * find_params(ast_node * node){
    parameter_t * list_params = NULL;

    if(node->first_child != NULL){
        list_params = create_param(node->first_child);
        
    }


}

table_t * add_table(table_t * root, char * table_id){
    if(root != NULL){
        table_t * current = root;
        while (current->next) {
            current = current->next;
        }
        table_t * table = create_table(table_id);
        current->next = table;
        return table;
    }
}

table_t * create_table(char * id){
    table_t * table = (table_t *)malloc(sizeof(table_t));

    table->id = id;
    table->list_elems = NULL;
    table->next_table = NULL;

    return table;
}


void funcdecl_analysis(ast_node * node){
    char * table_id = ((node->first_child)->first_child)->value; //retirar o nome da função (header->id-> valor, i.e. nome da função neste caso). Vai ser importante para adicionar na tabela global e para criar uma tabela com este nome
    ast_node * return_type = (((node->first_child)->first_child)->sibling) //retirar o return type da função (header->id-> typespe). Vai ser importante para adicionar na tabela global
    
    ast_node * params;
    char * return_type_table;

     //temos que tornar minusculo para depois anotar na árvore
    if(strcmp(return_type->id,"FuncParams")){
        strcpy(return_type_table, "none");
        params = return_type_table;
    }
    else{
        strcpy(return_type_table, return_type->id);
        params = return_type_table->sibling;
    }
    
    parameter_t * params_list;

    find_parans(params);
    
    /*
    
    verificar se já foi definida
    gerar erros caso já tenha sido definida

    */

    add_table(tables_root, table_id);


}

void semantic_analysis(ast_node * node){
    int fisrt_table = 1;

    if(node->child != NULL && node->sibling != NULL){
        return;   
    }

    if(strcmp(ast_node->id, "FuncDecl")){
        if(fisrt_table){
            fisrt_table = 0;
            tables_root =create_table("Global");
        }
        else{
            funcdecl_analysis(node);
        }
    }

}