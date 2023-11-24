#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"

/*
  Description: Creates a new Ingredient list item and appends it to the end of the list.
  Error Cases: Exits the program if memory allocation fails.
  Input arguments: I_Ingredient - Pointer to the Ingredient structure to be added.
                   I_ptr - Pointer to the head of the Ingredient list.
  Return type: void
  Memory usage: Allocates memory for a new Ingredient structure.
  Big O notation: O(n), where n is the number of elements in the Ingredient list.
 */
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

/*
  Description: Deletes an Ingredient list item with a specified ingredient ID.
  Error Cases: None.
  Input arguments: I_Ingredient - Pointer to the head of the Ingredient list.
                   c_searchedID - Ingredient ID to search for and delete.
  Return type: void
  Memory usage: Frees memory for the deleted Ingredient structure.
  Big O notation: O(n), where n is the number of elements in the Ingredient list.
 */
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

/*
  Description: Lists the names of each Ingredient list item.
  Error Cases: None.
  Input arguments: I_Ingredient - Pointer to the head of the Ingredient list.
  Return type: void
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Ingredient list.
 */
extern void listIngredientsListItems(Ingredient *I_Ingredient){
    Ingredient *I_tmp_ptr = I_Ingredient;
    while(I_tmp_ptr != NULL){
        printf("%s\n", I_tmp_ptr->c_Ingredient_Name);
        I_tmp_ptr = I_tmp_ptr->I_next_Ingredient;
    }
}

/*
  Description: Frees the memory allocated for the entire Ingredient list.
  Error Cases: None.
  Input arguments: I_ptr - Pointer to the head of the Ingredient list.
  Return type: void
  Memory usage: Frees memory for all Ingredient structures in the list.
  Big O notation: O(n), where n is the number of elements in the Ingredient list.
 */
extern void freeIngredientsList(Ingredient *I_ptr){
    Ingredient* I_tmp_ptr = I_ptr;
    while (I_ptr != NULL) {
        I_tmp_ptr = I_ptr->I_next_Ingredient;
        free(I_ptr);
        I_ptr = I_tmp_ptr;
    }
}

/*
  Description: Retrieves an Ingredient list item with a specified ingredient ID.
  Error Cases: None.
  Input arguments: I_Ingredient - Pointer to the head of the Ingredient list.
                   c_searchedID - Ingredient ID to search for.
  Return type: Pointer to the found Ingredient structure or NULL if not found.
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Ingredient list.
 */
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

/*
  Description: Retrieves an Ingredient list item with a specified ingredient name.
  Error Cases: None.
  Input arguments: I_Ingredient - Pointer to the head of the Ingredient list.
                   c_searchedName - Ingredient name to search for.
  Return type: Pointer to the found Ingredient structure or NULL if not found.
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Ingredient list.
 */
extern Ingredient* getIngredientElementByName(Ingredient *I_Ingredient, char c_searchedName[]){
     Ingredient *I_tmp_ptr = I_Ingredient;
    while(I_tmp_ptr != NULL){
        if(strcmp(I_tmp_ptr->c_Ingredient_Name,c_searchedName)==0){
            return I_tmp_ptr;           
        }
        I_tmp_ptr = I_tmp_ptr->I_next_Ingredient;
    }
    return NULL;
}