#ifndef SEM_A
#define SEM_A
/*  
    * Projeto de Compiladores 2021/2022
    * Meta 3
    * 2019218953 João Miguel Ferreira Castelo Branco Catré
    * 2019227240 Sofia Botelho Vieira Alves
    * 
    * , int *line, int *col
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>



typedef struct parameters
{
    char * name;
    char * param_type;
    struct parameters *next;
} parameters;

typedef struct variables
{
    int is_parameter
    char * name;
    char * type;
    struct variables * next;
} variables;


#endif //SEM_A