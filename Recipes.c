#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"

/*
  Description: Creates a new Recipe list item and appends it to the end of the list.
  Error Cases: Exits the program if memory allocation fails.
  Input arguments: R_Recipe - Pointer to the Recipe structure to be added.
                   R_ptr - Pointer to the head of the Recipe list.
  Return type: void
  Memory usage: Allocates memory for a new Recipe structure.
  Big O notation: O(n), where n is the number of elements in the Recipe list.
 */
extern void createRecipeListItem(Recipe * R_Recipe, Recipe * R_ptr) {
    while(R_ptr->R_next_Recipe != NULL){
       R_ptr = R_ptr->R_next_Recipe;
    }

    Recipe* R_tmpRecipe = (Recipe*)malloc(sizeof(Recipe));
    if (R_tmpRecipe == NULL) {
        perror("Failed to allocate memory for Recipes");
        exit(1);  // Handle the error as needed
    }
    R_tmpRecipe->R_next_Recipe = NULL;
    strcpy(R_tmpRecipe->c_Recipe_ID,R_Recipe->c_Recipe_ID);
    strcpy(R_tmpRecipe->c_Recipe_Name,R_Recipe->c_Recipe_Name);
    strcpy(R_tmpRecipe->c_Recipe_Description,R_Recipe->c_Recipe_Description);
    R_ptr->R_next_Recipe = R_tmpRecipe;
    R_ptr = R_ptr->R_next_Recipe;
}

/*
  Description: Deletes a Recipe list item with a specified recipe ID.
  Error Cases: None.
  Input arguments: R_Recipe - Pointer to the head of the Recipe list.
                   c_searchedID - Recipe ID to search for and delete.
  Return type: void
  Memory usage: Frees memory for the deleted Recipe structure.
  Big O notation: O(n), where n is the number of elements in the Recipe list.
 */
extern void deleteRecipeListItem(Recipe *R_Recipe, char c_searchedID[] ){
    Recipe *R_tmp_ptr = R_Recipe->R_next_Recipe;
    Recipe *R_behind_ptr = R_Recipe;

    while(R_tmp_ptr != NULL){
        if(strcmp(R_tmp_ptr->c_Recipe_ID,c_searchedID)==0){
            R_behind_ptr->R_next_Recipe = R_tmp_ptr->R_next_Recipe;
            free(R_tmp_ptr);
            break;
        }
        R_tmp_ptr = R_tmp_ptr->R_next_Recipe;
        R_behind_ptr = R_behind_ptr->R_next_Recipe;
    }
}

/*
  Description: Lists the names of each Recipe list item.
  Error Cases: None.
  Input arguments: R_Recipe - Pointer to the head of the Recipe list.
  Return type: void
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Recipe list.
 */
extern void listRecipeListItems(Recipe *R_Recipe){
    Recipe *R_tmp_ptr = R_Recipe;
    while(R_tmp_ptr != NULL){
        printf("%s\n",R_tmp_ptr->c_Recipe_Name);
        R_tmp_ptr = R_tmp_ptr->R_next_Recipe ;
    }
}

/*
  Description: Frees the memory allocated for the entire Recipe list.
  Error Cases: None.
  Input arguments: R_ptr - Pointer to the head of the Recipe list.
  Return type: void
  Memory usage: Frees memory for all Recipe structures in the list.
  Big O notation: O(n), where n is the number of elements in the Recipe list.
 */
extern void freeRecipesList(Recipe *R_ptr){
     Recipe *R_tmp_ptr = R_ptr;
    while(R_ptr != NULL){
        R_tmp_ptr = R_ptr->R_next_Recipe;
        free(R_ptr);
        R_ptr = R_tmp_ptr;
    }
}

/*
  Description: Retrieves a Recipe list item with a specified recipe ID.
  Error Cases: None.
  Input arguments: R_Recipe - Pointer to the head of the Recipe list.
                   c_searchedID - Recipe ID to search for.
  Return type: Pointer to the found Recipe structure or NULL if not found.
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Recipe list.
 */
extern Recipe* getRecipeElementByID(Recipe *R_Recipe, char c_searchedID[] ){
    Recipe *R_tmp_ptr = R_Recipe;
    while(R_tmp_ptr != NULL){
        if(strcmp(R_tmp_ptr->c_Recipe_ID,c_searchedID)==0){
            return R_tmp_ptr;           
        }
        R_tmp_ptr = R_tmp_ptr->R_next_Recipe;
    }
    return NULL;
}

/*
  Description: Retrieves a Recipe list item with a specified recipe name.
  Error Cases: None.
  Input arguments: R_Recipe - Pointer to the head of the Recipe list.
                   c_searchedName - Recipe name to search for.
  Return type: Pointer to the found Recipe structure or NULL if not found.
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Recipe list.
 */
extern Recipe* getRecipeElementByName(Recipe *R_Recipe, char c_searchedName[]){
     Recipe *R_tmp_ptr = R_Recipe;

    while(R_tmp_ptr != NULL){
        if(strcmp(R_tmp_ptr->c_Recipe_Name,c_searchedName)==0){
            return R_tmp_ptr;           
        }
        R_tmp_ptr = R_tmp_ptr->R_next_Recipe;
    }
    return NULL;
}