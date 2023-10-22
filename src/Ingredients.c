#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ingredients.h"
#include "debugmalloc.h"

static Ingredients* createIngredientListItem(Ingredients * Ia_tmpIngredients) {
    Ingredients* I_tmpIngredient = (Ingredients*)malloc(sizeof(Ingredients));
    if (I_tmpIngredient == NULL) {
        perror("Failed to allocate memory for Ingredients");
        exit(1);  // Handle the error as needed
    }

    I_tmpIngredient->I_next = NULL;
    I_tmpIngredient->d_weight = Ia_tmpIngredients->d_weight;
    strcpy(I_tmpIngredient->c_unit, Ia_tmpIngredients->c_unit);
    strcpy(I_tmpIngredient->c_ingredients_name, Ia_tmpIngredients->c_ingredients_name);
    I_tmpIngredient->D_expiration_date = Ia_tmpIngredients->D_expiration_date;
    return I_tmpIngredient;
}

extern void InitIngredientList(Ingredients* I_start_ptr) {
    FILE* F_file_Ingredients_txt = fopen("Ingredients.txt", "r");
    if (F_file_Ingredients_txt == NULL) {
        perror("Failed to open Ingredients.txt");
        exit(1);
    }
    Ingredients I_tmpIngredients;
    Ingredients* I_ptr = I_start_ptr;

   while (fscanf(F_file_Ingredients_txt, "%lf ; %s ; %[^;] ; %d.%d.%d",
              &I_tmpIngredients.d_weight,
              &I_tmpIngredients.c_unit,
              &I_tmpIngredients.c_ingredients_name,
              &I_tmpIngredients.D_expiration_date.i_day,
              &I_tmpIngredients.D_expiration_date.i_month,
              &I_tmpIngredients.D_expiration_date.i_year) != EOF ) {

        I_ptr->I_next = createIngredientListItem(&I_tmpIngredients);
        I_ptr = I_ptr->I_next;
    }

    fclose(F_file_Ingredients_txt);
}

static void freeIngredientsList(Ingredients *I_ptr){
    while (I_ptr != NULL) {
        Ingredients* temp = I_ptr;
        I_ptr = I_ptr->I_next;
        free(temp);
    }
}
/*
int main() {
    Ingredients I_start;  // Create a dummy start node
    InitIngredientList(&I_start);

    // Print the linked list of Ingredients
    Ingredients* current = I_start.I_next;
    while (current != NULL) {
        printf("Weight: %g, Unit: %s, Name: %s, Expiration Date: %d.%d.%d\n",
               current->d_weight,
               current->c_unit,
               current->c_ingredients_name,
               current->D_expiration_date.i_day,
               current->D_expiration_date.i_month,
               current->D_expiration_date.i_year);

        current = current->I_next;
    }

    freeIngredientsList(I_start.I_next);

    debugmalloc_dump();
    return 0;
}*/