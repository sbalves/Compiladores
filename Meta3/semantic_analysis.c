#include "semantic_analysis.h"


void add_element(table_t * table, element_t * new_elem){

    if(table->list_elems == NULL){
       table->list_elems = new_elem;
       printf("element %s added to %s table ^^\n", new_elem->id, table->id);
    }
    else{
        element_t * current = table->list_elems;
        while(current->next_elem != NULL){ // is it like this?
            current = current->next_elem;
        }
        current->next_elem = new_elem;
        printf("element %s added to %s table ^^\n", new_elem->id, table->id);
    }
}

element_t * create_element(char * id, char * type, parameter_t * params_list){
    element_t * new_element = (element_t * )malloc(sizeof(element_t));

    strcpy(new_element->id, id);
    strcpy(new_element->type, type);
    new_element->list_params = params_list;
    new_element->is_parameter = 1;
    new_element->next_elem = NULL;
    
    return new_element;
}


parameter_t * create_param(ast_node * node){
    parameter_t * parameter = (parameter_t *)malloc(sizeof(parameter_t));
    
    //(node->first_child)->id) = (ParamDecl->Type->Id)
    strcpy(parameter->param_type, (node->first_child)->id); //? não sei se posso fazer assim, mas tecnicamente são dois chars
    parameter->next_param = NULL;

    return parameter;
}


/* ainda n sei fazer :s ver depois */ 
parameter_t * find_params(element_t * elem, parameter_t * param, ast_node * node, table_t * table){
    parameter_t * new_param = NULL;
    element_t * new_elem = NULL;

    if(node->sibling != NULL){
        //(((node->sibling)->first_child)->sibling)->id = (ParamDecl->Type->Id->(id do param))
        //((node->sibling)->first_child)->id) = (ParamDecl->Type->Id (tipo do param))

        // adiciona params à tabela
        new_elem = create_element((((node->sibling)->first_child)->sibling)->id,((node->sibling)->first_child)->id, NULL);
        add_element(table, new_elem);
        elem->next_elem = new_elem;

        //cria novos params e adiciona à lista de params
        new_param = create_param(node->sibling);
        param->next_param = new_param;
        find_params(new_elem, new_param, node->sibling, table);
    }
    return new_param; // faz sentido? a ideia é retornar a root.... acho?
}


table_t * add_table(table_t * root, char * table_id){
    table_t * table = NULL;

    if(root != NULL){
        table_t * current = root;
        while (current->next_table) {
            current = current->next_table;
        }
        table = create_table(table_id);
        current->next_table = table;
        printf("table %s added ^^\n", table_id);
    }
    return table;
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
    ast_node * return_type = (((node->first_child)->first_child)->sibling); //retirar o return type da função (header->id-> typespe). Vai ser importante para adicionar na tabela global
    element_t * first_param_elem;
    
    
    ast_node * params;
    char * return_type_table;

    //temos que tornar minusculo para depois anotar na árvore
    // verificar o que a função retorna e encontrar o nó FuncParams
    if(strcmp(return_type->id,"FuncParams")){
        strcpy(return_type_table, "none");
        params = return_type;
    }
    else{
        strcpy(return_type_table, return_type->id);
        params = return_type->sibling;
    }

    // criar tabela da função
    table_t * new_table = add_table(tables_root, table_id);
    
    //adicionar return à tabela
    element_t * return_element = create_element("return", return_type_table, NULL);
    add_element(new_table, return_element);


    parameter_t * params_list = NULL;

    // encontrar os parametros da função + adicionar à tabela da função
    if(params->first_child != NULL){ //seams fishy af :s ver!!
        params_list = create_param(params->first_child);
        first_param_elem = create_element((((params->first_child)->first_child)->sibling)->id,((params->first_child)->first_child)->id, NULL);
        return_element->next_elem = first_param_elem;

        add_element(tables_root,first_param_elem);
        params_list = find_params(first_param_elem, params_list, params->first_child, new_table);
    }
    
    // criar elemento correspondente à função
    element_t * new_element = create_element(table_id, return_type_table, params_list);

    // adicionar à tabela global
    add_element(tables_root, new_element);    


    /*
    
    verificar se já foi definida
    gerar erros caso já tenha sido definida

    */



}



void vardecl_analysis(ast_node * node){
    printf("to do\n");

}


void semantic_analysis(ast_node * node){
    int fisrt_table = 1;

    if(node->first_child != NULL && node->sibling != NULL){
        return;   
    }

    if(strcmp(node->id, "FuncDecl")){
        if(fisrt_table){ //faz sentido? 1 e depois 0 no else
            fisrt_table = 0;
            tables_root =create_table("Global");
        }
        else{
            funcdecl_analysis(node);
        }
    }
    
    if(strcmp(node->id, "VarDecl")){
        vardecl_analysis(node);
    }

    

}