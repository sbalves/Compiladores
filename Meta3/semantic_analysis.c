#include "semantic_analysis.h"

table_t * current_table = NULL;

void annotate_parseargs(ast_node * node){
    //printf("annotating parseargs\n");
    if(!strcmp((node->first_child)->annotation.type, "int") && !strcmp(((node->first_child)->sibling)->annotation.type, "int")){
        node->annotation.type = strdup("int");
    }
    /*
        ver erros quais n sei
    */
   // printf("parseargs annoted\n");
}

void annotate_call(ast_node * node){
    //printf("annotating call\n");
    element_t * elem = find_element(current_table->list_elems, (node->first_child)->value);

    if(!elem){
        //printf("ver na global\n");
        elem = find_element(tables_root->list_elems, (node->first_child)->value);

    }

    if(strcmp((elem->type), "none"))
        node->annotation.type = strdup(lowercase(elem->type));
    //printf("call annoted\n");
}

void annotate_return(ast_node * node){
    /*
    if(node->first_child)
        verificar se tem o mesmo tipo
    
    verificar se a func é void
    */
}

void anotate_statement_token(ast_node * node){
    //printf("annotating statement_token\n");
    //if((node->first_child)) printf("has a child\n");
    if((node->first_child)->annotation.type){
        if(strcmp((node->first_child)->annotation.type, "bool")){
            printf("Erro\n");
            /*
                desenvolver - a condição tem que ser sempre bool
            */
        }
    }
    //printf("tatement_token annoted\n");
}

void anotate_unary_operator(ast_node * node){
    //printf("annotating unary_operator\n");

    if(!strcmp(node->id, "Plus") || !strcmp(node->id, "Minus")){
        if(!strcmp((node->first_child)->annotation.type, "int")){
            node->annotation.type = strdup("int");
        }
        else if(!strcmp((node->first_child)->annotation.type, "float32")){
            node->annotation.type = strdup("float32");
        }
    } 

      /*
        Ver erros
    */
    //printf("unary_operator annoted\n");
}

void anotate_relational_operator(ast_node * node){
    //printf("annotating relational_operator\n");
    
    /*
        Ver erros
    */

    node->annotation.type = strdup("bool");
    //printf("relational_operator annotated\n");

}

void anotate_logical_operator(ast_node * node){
   //printf("annotating logical_operator \n");
    /*
        Ver erros
    */
    node->annotation.type = strdup("bool");
    //printf("logical_operator annotated\n");
}

void anotate_arithmetic_operator(ast_node * node){
    //printf("annotating arithmetic_operator \n");
    //if((node->first_child)->annotation.type) printf("tem %s anot\n", (node->first_child)->id);
    //if((node->first_child)->sibling->annotation.type == NULL) printf("%s n tem anot\n", (node->first_child)->sibling->id);

    if(!strcmp(node->id, "Add") && !strcmp(node->id, "Sub")){
        if(!strcmp((node->first_child)->annotation.type, "undef") || !strcmp(((node->first_child)->sibling)->annotation.type, "undef") ||
        !strcmp((node->first_child)->annotation.type, "none") || !strcmp(((node->first_child)->sibling)->annotation.type, "none") ){
            node->annotation.type = strdup("undef");
        }
    }

    if(!strcmp(node->id, "Add") && !strcmp(node->id, "Sub")){
        if(!strcmp((node->first_child)->annotation.type, "undef") || !strcmp(((node->first_child)->sibling)->annotation.type, "undef")){
            node->annotation.type = strdup("undef");
        }
    }
    node->annotation.type = strdup((node->first_child)->annotation.type);
    

    /*
        Verificar erros:
        se for MOD - ver se ambos são inteiros (mod é sobre inteiros)
        ADD - podemos somar strings penso...not sure tho, confirmar com o andré
    */
    //printf("arithmetic_operator annotated\n");
}

void annotate_id(ast_node * node){
    //printf("annotating id %s\n",node->value);
    element_t * element = find_element(current_table->list_elems,node->value);

    if(!element){
        element = find_element(tables_root->list_elems, node->value);

        /* 
            verificar se existe ou não. se não existir -> ERRO (n está definido)
        */
    }
    
    node->annotation.type = strdup(lowercase(element->type));
    node->annotation.parameters = element->list_params;
    //printf("id annotated\n");
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

    table_t * table = find_table(tables_root->list_elems, ((node->first_child)->first_child)->value);
    if(table){
        //printf("Line %s, col %d: Symbol %s already defined", (node->first_child)->line, (node->first_child)->col, (node->first_child)->value);
        //free_elem()
        return;
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
    element_t * elem = find_element(current_table, (node->first_child)->value);
    if(elem){
        //printf("Line %s, col %d: Symbol %s already defined", (node->first_child)->line, (node->first_child)->col, (node->first_child)->value);
        //free_elem()
        return;
    }

   if(!new_elem){
       return;
   }

    add_element(current_table, new_elem);
}



void semantic_analysis(ast_node * node){


    if(node != NULL){
        //printf("Node id: %s\n", node->id);
        //printf("Node id: %s\n", (node->first_child)->id);


        if(!strcmp(node->id, "Program")){
            program_root = node;
            current_table = tables_root = create_table("Global");
            semantic_analysis(node->first_child);
        }

        if(!strcmp(node->id, "FuncDecl")){
        //printf("in a funcdecl: %s\n", node->value);
            //if(node->sibling) printf("Irmão: %s\n", node->sibling->id);
            funcdecl_analysis(node);
        }

        if(!strcmp(node->id, "FuncBody")){
            semantic_analysis(node->first_child);
        }

        if(!strcmp(node->id, "Block")){
            semantic_analysis(node->first_child);
        }

        if(!strcmp(node->id, "Print")){
            semantic_analysis(node->first_child);
        }

        if(!strcmp(node->id, "Return")){
            semantic_analysis(node->first_child);
            annotate_return(node);
        }

        if(!strcmp(node->id, "Call")){
            //printf("its a call\n");
            semantic_analysis(node->first_child);
            annotate_call(node);
        }

        if(!strcmp(node->id, "VarDecl")){
            vardecl_analysis(node);
        }

        if(!strcmp(node->id, "ParseArgs")){
            semantic_analysis(node->first_child);
            annotate_parseargs(node);
        }
      
        if(is_arithmetic_operator(node->id)){
            //printf("its an arith %s\n", node->id);
            semantic_analysis(node->first_child);
            anotate_arithmetic_operator(node);
        }

        if(is_logical_operator(node->id)){
            //printf("its an logical %s\n", node->id);
            semantic_analysis(node->first_child);
            anotate_logical_operator(node);
        }

        if(is_realtional_operator(node->id)){
            //printf("its an relational %s\n", node->id);
            semantic_analysis(node->first_child);
            anotate_relational_operator(node);
        }

        if(is_unary_operator(node->id)){
            //printf("its an unary %s\n", node->id);
            semantic_analysis(node->first_child);
            anotate_unary_operator(node);
        }

        if(is_statement_token(node->id)){
            //printf("its an statement_token %s\n", node->id);
            semantic_analysis(node->first_child);
            anotate_statement_token(node);
        }

        if(!strcmp(node->id, "IntLit")){
            //printf("its an intlit %s\n", node->id);
            node->annotation.type = strdup("int"); 
        } 

        if(!strcmp(node->id, "RealLit")){
            //printf("its an realit %s\n", node->id);
            node->annotation.type = strdup("float32"); 
        }   

        if(!strcmp(node->id, "Id")){
            //printf("its an id %s\n", node->id);
            annotate_id(node); 
        }   

        if(node->sibling != NULL)
            semantic_analysis(node->sibling);
    }
    //printf("is null\n");
}
