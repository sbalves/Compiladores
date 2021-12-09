#include "semantic_analysis.h"

table_t * current_table = NULL;

void add_element(table_t * table, element_t * new_elem){

    if(table->list_elems == NULL){
       table->list_elems = new_elem;
        //printf("element %s (%s) added to %s table^^\n", new_elem->id, new_elem->type, table->id);
    }
    else{
        element_t * current = table->list_elems;
        while(current->next_elem != NULL){ // is it like this?
            current = current->next_elem;
        }
        current->next_elem = new_elem;
        //printf("element %s (%s) added to %s table^^\n", new_elem->id, new_elem->type, table->id);

    }
}

element_t * create_element(char * id, char * type, parameter_t * params_list){
    element_t * new_element = (element_t * )malloc(sizeof(element_t));

    new_element->id = strdup(id);
    new_element->type = strdup(type);
    new_element->list_params = params_list;
    new_element->is_func = 0;
    new_element->is_parameter = 0;
    new_element->next_elem = NULL;
    
    return new_element;
}


parameter_t * create_param(ast_node * node){
    parameter_t * parameter = (parameter_t *)malloc(sizeof(parameter_t));
    
    //(node->first_child)->id) = (ParamDecl->Type->Id)
    parameter->param_type = strdup((node->first_child)->id); //? não sei se posso fazer assim, mas tecnicamente são dois chars
    parameter->next_param = NULL;

    return parameter;
}


/* ainda n sei fazer :s ver depois */ 

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


table_t * add_table(table_t * root, char * table_id){
    table_t * table = NULL;
    //printf("Entrei na add_table\n");

    //printf("hello! %p\n", table_id);

    if(root != NULL){
        table_t * current = root;
        while (current->next_table) {
            current = current->next_table;
        }

        table = create_table(table_id);
        //printf("nice\n");
        current->next_table = table;
        //printf("nice\n");
        //printf("table %s added ^^\n", table_id);
        //printf("nice\n");

    }
    return table;
}


table_t * create_table(char * id){
    //printf("Entrei na create_table\n");
    //printf("Criei a tabela %s\n", id);


    table_t * table = (table_t *)malloc(sizeof(table_t));

    table->id = strdup(id);

    table->list_elems = NULL;
    table->next_table = NULL;

    return table;
}


void funcdecl_analysis(ast_node * node){
    //printf("Entrei na funcdecl_analysis\n");
    //char * table_id = strdup(((node->first_child)->first_child)->value); //retirar o nome da função (header->id-> valor, i.e. nome da função neste caso). Vai ser importante para adicionar na tabela global e para criar uma tabela com este nome
    ast_node * return_type = (((node->first_child)->first_child)->sibling); //retirar o return type da função (header->id-> typespe). Vai ser importante para adicionar na tabela global
    element_t * first_param_elem; // criar elemento associado à função para adicionar à tabela global

    //printf("hello1! %p\n", table_id);
    //printf("hello2! %s\n", table_id);
    //printf("helloo\n");

    ast_node * params;
    char * return_type_table;
    //temos que tornar minusculo para depois anotar na árvore
    // verificar o que a função retorna e encontrar o nó FuncParams
        //printf("helloo6\n");

    if(!strcmp(return_type->id,"FuncParams")){
        return_type_table= strdup("none");
        //printf("helloo2\n");
        params = return_type;
        //printf("helloo3\n");

    }
    else{
        return_type_table= strdup(return_type->id);

        params = return_type->sibling;
    }

    // criar tabela da função 
    table_t * new_table = add_table(tables_root, ((node->first_child)->first_child)->value);
    
    //printf("helloo5\n");
    
    //adicionar return à tabela
    element_t * return_element = create_element("return", return_type_table, NULL);
    add_element(new_table, return_element);


    parameter_t * params_list = NULL;

    // encontrar os parametros da função + adicionar à tabela da função
    if(params->first_child != NULL){ //seams fishy af :s ver!!
        params_list = create_param(params->first_child);
        first_param_elem = create_element((((params->first_child)->first_child)->sibling)->value,((params->first_child)->first_child)->id, NULL);
        first_param_elem->is_parameter = 1;

        add_element(new_table,first_param_elem);
        find_params(params_list, params->first_child, new_table);
    }
    
    // criar elemento correspondente à função
    element_t * new_element = create_element(((node->first_child)->first_child)->value, return_type_table, params_list);
    //especificar que é uma função
    new_element->is_func = 1;
    // adicionar à tabela global
    add_element(tables_root, new_element);    
    //ataulizar o ponteiro da tabela atual, uma vez que agora estamos dentro da função
    current_table = new_table;
    //analisa o funcbody
    semantic_analysis((node->first_child)->sibling);
    //quando termina à analise do funcbody, significa que saiu da função, voltando ao estado global
    current_table = tables_root;


    /*
    verificar se já foi definida
    gerar erros caso já tenha sido definida
    */

}


//O erro está aqui.
void vardecl_analysis(ast_node * node){
    //printf("entrei na vardecl_analysis\n");
    element_t * new_elem = create_element(((node->first_child)->sibling)->value, ((node->first_child)->id), NULL);

    /* 
    verificar se já foi declarado dentro do mesmo scope
    */

    add_element(current_table, new_elem);

    //semantic_analysis(node->sibling); //Era aqui!
}

element_t * find_table(table_t * table, char * function_name){
    element_t * element_func = NULL;

    //printf("entrei na find_table_type com o id %s e estou na tabela %s\n", function_name, table->id);
    for(element_t * current = table->list_elems; current; current = current->next_elem){
        //printf("%s-%s\n", current->id, function_name);
        if(!strcmp(current->id, function_name)){
            element_func = current;
        }
        //printf("%s\n", current->id);
    } 
    //printf("hello3\n");
    //return "erro"; //ver depois :S
    /*

    VERIFICAR ERRO: quando o elemento procurado n se encotra na tabela global !!!!

    */
    return element_func;
}

// rever nome do parametro
char * lowercase(char * word){
    if(!strcmp(word,"Int"))
        return "int";
    else if(!strcmp(word,"Float32"))
        return "float32";
    else if(!strcmp(word,"String"))
        return "string";
    else if(!strcmp(word,"Bool"))
        return "bool";
    /*
    else if(!strcmp(word,"none"))
        return "";
    */
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
}

void print_params(element_t * elem){
    //parameter_t * list = elem->list_params;
    if(elem){
        if(elem->list_params){
            printf("(");
            //printf("fist p %s", lowercase((elem->list_params)->param_type));
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
            print_params(find_table(tables_root, current->id));
            printf(" Symbol Table =====\n");
            print_elements(current->list_elems);
            printf("\n");
        }
        
}

void semantic_analysis(ast_node * node){

    if(node != NULL){
        //printf("node %s\n", node->id);
        if(!strcmp(node->id, "Program")){
            //printf("Entrei no if 176\n");
            current_table = tables_root = create_table("Global");
            semantic_analysis(node->first_child);
        }

        if(!strcmp(node->id, "FuncDecl")){
            //printf("Estou no FuncDecl\n");
            funcdecl_analysis(node);
        }
        else if(!strcmp(node->id, "FuncBody")){
        //printf("Estou no body\n");
        semantic_analysis(node->first_child);
        }

        else if(!strcmp(node->id, "VarDecl")){
            //printf("Estou no VarDecl\n");
            vardecl_analysis(node);
        }
        
        //semantic_analysis(node->first_child);
        semantic_analysis(node->sibling);

    }

    //printf("O nó é null\n");


}