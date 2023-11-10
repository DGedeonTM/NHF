#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"

extern void createIngredientListItem(Ingredient * I_Ingredient, Ingredient *I_ptr) {
    while(I_ptr->I_next_Ingredient !=NULL){
        I_ptr = I_ptr->I_next_Ingredient;
    }

    Ingredient* I_tmpIngredient = (Ingredient*)malloc(sizeof(Ingredient));
    if (I_tmpIngredient == NULL) {
        perror("Failed to allocate memory for Ingredients");
        exit(1);  // Handle the error as needed
    }
    I_tmpIngredient-> I_next_Ingredient = NULL;
    strcpy(I_tmpIngredient->c_Ingredient_ID,I_Ingredient->c_Ingredient_ID);
    strcpy(I_tmpIngredient->c_Ingredient_Name,I_Ingredient->c_Ingredient_Name);
    strcpy(I_tmpIngredient->c_Unit,I_Ingredient->c_Unit);
    I_ptr->I_next_Ingredient = I_tmpIngredient;
    I_ptr = I_ptr->I_next_Ingredient;
}

extern void deleteIngredientListItem(Ingredient *I_Ingredient, char c_searchedID[]){
    Ingredient *I_tmp_ptr = I_Ingredient->I_next_Ingredient;
    Ingredient *I_behind_ptr = I_Ingredient;

    while(I_tmp_ptr != NULL){
        if(strcmp(I_tmp_ptr->c_Ingredient_ID,c_searchedID)==0){
            I_behind_ptr->I_next_Ingredient = I_tmp_ptr->I_next_Ingredient;
            free(I_tmp_ptr);
            break;
        }
        I_tmp_ptr = I_tmp_ptr->I_next_Ingredient;
        I_behind_ptr = I_behind_ptr->I_next_Ingredient;
    }
}

extern void listIngredientsListItems(Ingredient *I_Ingredient){
    Ingredient *I_tmp_ptr = I_Ingredient;
    while(I_tmp_ptr != NULL){
        printf("%s\n", I_tmp_ptr->c_Ingredient_Name);
        I_tmp_ptr = I_tmp_ptr->I_next_Ingredient;
    }
}

extern void freeIngredientsList(Ingredient *I_ptr){
    Ingredient* I_tmp_ptr = I_ptr;
    while (I_ptr != NULL) {
        I_tmp_ptr = I_ptr->I_next_Ingredient;
        free(I_ptr);
        I_ptr = I_tmp_ptr;
    }
}

extern Ingredient* getIngredientElementByID(Ingredient *I_Ingredient, char c_searchedID[]){
    Ingredient *I_tmp_ptr = I_Ingredient;
    while(I_tmp_ptr != NULL){
        if(strcmp(I_tmp_ptr->c_Ingredient_ID,c_searchedID)==0){
            return I_tmp_ptr;
        }
        I_tmp_ptr = I_tmp_ptr->I_next_Ingredient;
    }
    return NULL;
}