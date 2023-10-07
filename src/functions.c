#include <stdio.h>
#include <stdlib.h>

typedef struct Ingredients{
    int i_weight;
    char c_unit[11];
    char c_ingredients_name[51];
}Ingredients;



typedef struct Recepts {
    int i_receptID;
    char c_recept_name[51];
    char c_recept_allergenes_name[51];
    Ingredients I_ingredients[50];
    char c_preparation[3000];
    struct Recepts *R_next;
}Recepts;

