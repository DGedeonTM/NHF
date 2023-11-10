#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"

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

extern void listRecipeListItems(Recipe *R_Recipe){
    Recipe *R_tmp_ptr = R_Recipe;
    while(R_tmp_ptr != NULL){
        printf("%s\n",R_tmp_ptr->c_Recipe_Name);
        R_tmp_ptr = R_tmp_ptr->R_next_Recipe ;
    }
}

extern void freeRecipesList(Recipe *R_ptr){
     Recipe *R_tmp_ptr = R_ptr;
    while(R_ptr != NULL){
        R_tmp_ptr = R_ptr->R_next_Recipe;
        free(R_ptr);
        R_ptr = R_tmp_ptr;
    }
}


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

extern Recipe* getRecipeElementByName(Recipe *R_Recipe, char c_searchedName[]){
     Recipe *R_tmp_ptr = R_Recipe;
    printf("%s",c_searchedName);

    while(R_tmp_ptr != NULL){
        if(strcmp(R_tmp_ptr->c_Recipe_Name,c_searchedName)==0){
            return R_tmp_ptr;           
        }
        R_tmp_ptr = R_tmp_ptr->R_next_Recipe;
    }
    return NULL;
}