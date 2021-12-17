#include "symbol_table.h"


element_t * find_element(element_t * elem_root, char * id){
    for(element_t * current_elem = elem_root; current_elem; current_elem = current_elem->next_elem){
        if(!strcmp(current_elem->id, id))
            return current_elem;
    }

    return NULL;
}


table_t * find_table(table_t * table, char * function_name){
    for(table_t * current = table; current; current = current->next_table){
        if(!strcmp(current->id, function_name)){
            return current;
        }
    } 
    //return "erro"; //ver depois :S
    /*
    VERIFICAR ERRO: quando o elemento procurado n se encotra na tabela global !!!!
    */
    return NULL;
}

void find_params(parameter_t * param, ast_node * node, table_t * table){

    parameter_t * new_param = NULL;
    element_t * new_elem = NULL;

    if(node->sibling != NULL){
        //(((node->sibling)->first_child)->sibling)->id = (ParamDecl->Type->Id->(id do param))
        //((node->sibling)->first_child)->id) = (ParamDecl->Type->Id (tipo do param))

        // adiciona params à tabela

        new_elem = create_element((((node->sibling)->first_child)->sibling)->value,((node->sibling)->first_child)->id, NULL);
        new_elem->is_parameter = 1;
        add_element(table, new_elem);


        //cria novos params e adiciona à lista de params
        new_param = create_param(node->sibling);
        param->next_param = new_param;

        find_params(new_param, node->sibling, table);
    }
    //return new_param; // faz sentido? a ideia é retornar a root.... acho?
}


void add_element(table_t * table, element_t * new_elem){

    if(table->list_elems == NULL){
       table->list_elems = new_elem;
    }
    else{
        element_t * current = table->list_elems;
        while(current->next_elem != NULL){ // is it like this?
            current = current->next_elem;
        }
        current->next_elem = new_elem;

    }
}

/*
//ast_level serve para comparar variáveis globais com locais (se for repetida, dá erro)
//aux_level serve para se as variáveis estão na mesma função (caso esteja repetida, dá erro)
int checknewvar(char * name, int ast_level, int aux_level){
    while(){

    }
}*/

element_t * create_element(char * id, char * type, parameter_t * params_list){
    element_t * new_element = (element_t * )malloc(sizeof(element_t));

    new_element->id = strdup(id);
    new_element->type = strdup(type);
    new_element->list_params = params_list;
    new_element->is_func = 0;
    new_element->is_parameter = 0;
    new_element->next_elem = NULL;
    
    //if(checknewvar(new_element->id)){
        return new_element;
    //}

    //return NULL;
}

parameter_t * create_param(ast_node * node){
    parameter_t * parameter = (parameter_t *)malloc(sizeof(parameter_t));
    
    //(node->first_child)->id) = (ParamDecl->Type->Id)
    parameter->param_type = strdup((node->first_child)->id);
    parameter->next_param = NULL;

    return parameter;
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
    }
    return table;
}


table_t * create_table(char * id){
    table_t * table = (table_t *)malloc(sizeof(table_t));

    table->id = strdup(id);

    table->list_elems = NULL;
    table->next_table = NULL;

    return table;
}



//============================== Printar Tabela ==============================//

char * lowercase(char * word){
    if(!strcmp(word,"Int"))
        return "int";
    else if(!strcmp(word,"Float32"))
        return "float32";
    else if(!strcmp(word,"String"))
        return "string";
    else if(!strcmp(word,"Bool"))
        return "bool";
    return word;
}

void print_table_params(parameter_t * list){
    
    printf("(");
    for(parameter_t * current = list; current; current = current->next_param){
        printf("%s", lowercase(current->param_type));
        if(current->next_param)
            printf(",");
    }
    printf(")");

    //printf("()");
}

void print_params(element_t * elem){
    if(elem){
        if(elem->list_params){
            printf("(");
            for (parameter_t * current = elem->list_params; current; current = current->next_param) {
                printf("%s", lowercase(current->param_type));
                if(current->next_param) printf(",");
            }
            printf(")");
        }   
        else{
            if(elem->is_func) printf("()");}
    }
}

void print_second(element_t * elem){
    print_params(elem);
    printf("\t");
    printf("%s", lowercase(elem->type));
}

void print_elements(element_t * elem){
    for(element_t * current = elem; current; current = current->next_elem){
        printf("%s\t", current->id);
        print_second(current);
        if(current->is_parameter) printf("\tparam");
        if(current->next_elem) printf("\n");
    }
}

void print_table_list(table_t * table){
        printf("===== %s Symbol Table =====\n", table->id);
        print_elements(table->list_elems);
        printf("\n");
        
        for(table_t * current = table->next_table; current; current = current->next_table){
            printf("\n===== Function %s", current->id);
            print_params(find_element(tables_root->list_elems, current->id));
            printf(" Symbol Table =====\n");
            print_elements(current->list_elems);
            printf("\n");
        }
        
}
