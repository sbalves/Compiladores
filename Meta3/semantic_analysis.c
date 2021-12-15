#include "semantic_analysis.h"

table_t * current_table = NULL;

void anotate_statement_token(ast_node * node){
    if(node){
        if(strcmp((node->first_child)->annotation.type, "bool")){
            printf("Erro\n");
            /*
                desenvolver - a condição tem que ser sempre bool
            */
        }
    }
}

void anotate_unary_operator(ast_node * node){
    if(!strcmp((node->first_child)->annotation.type, "int") && !strcmp(((node->first_child)->sibling)->annotation.type, "int")){
        node->annotation.type = strdup("int");
    }
    else if(!strcmp((node->first_child)->annotation.type, "float32") && !strcmp(((node->first_child)->sibling)->annotation.type, "float32")){
        node->annotation.type = strdup("float32");
    }
    /*
        Ver erros
    */
}

void anotate_relational_operator(ast_node * node){
    
    /*
        Ver erros
    */

    node->annotation.type = strdup("bool");


}

void anotate_logical_operator(ast_node * node){
    /*
        Ver erros
    */
    node->annotation.type = strdup("bool");
}

void anotate_arithmetic_operator(ast_node * node){
    if(!strcmp((node->first_child)->annotation.type, "int") && !strcmp(((node->first_child)->sibling)->annotation.type, "int")){
        node->annotation.type = strdup("int");
    }
    else if(!strcmp((node->first_child)->annotation.type, "float32") && !strcmp(((node->first_child)->sibling)->annotation.type, "float32")){
        node->annotation.type = strdup("float32");
    }

    /*
        Verificar erros:
        se for MOD - ver se ambos são inteiros (mod é sobre inteiros)
        ADD - podemos somar strings penso...not sure tho, confirmar com o andré
    */

}

void annotate_id(ast_node * node){
    element_t * element = find_element(tables_root,node->value);
    /* 
        verificar se existe ou não. se não existir -> ERRO (n está definido)
    */
    
    node->annotation.type = strdup(lowercase(element->type));

}


void funcdecl_analysis(ast_node * node){
    //retirar o nome da função (header->id-> valor, i.e. nome da função neste caso). Vai ser importante para adicionar na tabela global e para criar uma tabela com este nome
    ast_node * return_type = (((node->first_child)->first_child)->sibling); //retirar o return type da função (header->id-> typespe). Vai ser importante para adicionar na tabela global
    element_t * first_param_elem; // criar elemento associado à função para adicionar à tabela global

    ast_node * params;
    char * return_type_table;
    //temos que tornar minusculo para depois anotar na árvore
    // verificar o que a função retorna e encontrar o nó FuncParams

    if(!strcmp(return_type->id,"FuncParams")){
        return_type_table= strdup("none");
        params = return_type;
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
    if(params->first_child != NULL){ //seems fishy af :s ver!!
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


void vardecl_analysis(ast_node * node){
    element_t * new_elem = create_element(((node->first_child)->sibling)->value, ((node->first_child)->id), NULL);

    /* 
    verificar se já foi declarado dentro do mesmo scope
    */

   if(!new_elem){
       return;
   }

    node->annotation.type = strdup(lowercase((node->first_child)->id)); 

    add_element(current_table, new_elem);
}



void semantic_analysis(ast_node * node){


    if(node != NULL){
        printf("Node id: %s\n", node->id);
        //printf("Node id: %s\n", (node->first_child)->id);


        if(!strcmp(node->id, "Program")){
            program_root = node;
            current_table = tables_root = create_table("Global");
            semantic_analysis(node->first_child);
        }

        if(!strcmp(node->id, "FuncDecl")){
            funcdecl_analysis(node);
        }

        if(!strcmp(node->id, "FuncBody")){
            semantic_analysis(node->first_child);
        }

        if(!strcmp(node->id, "VarDecl")){
            vardecl_analysis(node);
        }

        /*
        if(!strcmp(node->id, "Assign")){
            printf("Assignnnnn\n");
            semantic_analysis(node->first_child);
            anotate_arithmetic_operator(node);
        }*/



        if(is_arithmetic_operator(node->id)){
            printf("its an arith %s\n", node->id);
            semantic_analysis(node->first_child);
            anotate_arithmetic_operator(node);
        }

        if(is_logical_operator(node->id)){
            printf("its an logical %s\n", node->id);
            semantic_analysis(node->first_child);
            anotate_logical_operator(node);
        }

        if(is_realtional_operator(node->id)){
            printf("its an relational %s\n", node->id);
            semantic_analysis(node->first_child);
            anotate_relational_operator(node);
        }

        if(is_unary_operator(node->id)){
            printf("its an unary %s\n", node->id);
            semantic_analysis(node->first_child);
            anotate_unary_operator(node);
        }

        if(is_statement_token(node->id)){
            printf("its an statement_token %s\n", node->id);
            semantic_analysis(node->first_child);
            anotate_statement_token(node);
        }

        if(!strcmp(node->id, "IntLit")){
            printf("its an intlit %s\n", node->id);
            node->annotation.type = strdup("int"); 
        } 

        if(!strcmp(node->id, "RealLit")){
            printf("its an realit %s\n", node->id);
            node->annotation.type = strdup("float32"); 
        }   

        if(!strcmp(node->id, "Id")){
            printf("its an id %s\n", node->id);
            annotate_id(node); 
        }   

        if(node->sibling != NULL)
            semantic_analysis(node->sibling);
    }
    printf("is null\n");
}
