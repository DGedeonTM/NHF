#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "RecipeBook.h"
#include "debugmalloc.h"


static void createRecipeListItem( RecipeBook *R_ptr, RecipeBook const* R_tmpRecipe){
    RecipeBook *R_recipe = (RecipeBook*)malloc(sizeof(RecipeBook));
        if (R_recipe == NULL){
            perror("The following error occurred");
           // return NULL;
        }
        R_recipe->R_next = NULL;
        R_ptr->R_next =R_recipe;
        R_ptr = R_recipe;

        R_recipe->i_Recipe_Id = R_tmpRecipe->i_Recipe_Id;
        strcpy(R_recipe->c_Recipe_Name,R_tmpRecipe->c_Recipe_Name);
        strcpy(R_recipe->c_description,R_tmpRecipe->c_description);

}

static void createIngredientListItem(Ingredients *I_ptr,Ingredients const* Ia_tmpIngredients){
      Ingredients *I_tmpIngredient = (Ingredients*)malloc(sizeof(Ingredients));
        if (I_tmpIngredient == NULL){
            perror("The following error occurred");
            //return NULL;
        }
        I_tmpIngredient->I_next = NULL;
        I_ptr->I_next = I_tmpIngredient;
        I_ptr = I_tmpIngredient;

        I_tmpIngredient->d_weight = Ia_tmpIngredients->d_weight;
        strcpy(I_tmpIngredient->c_unit,Ia_tmpIngredients->c_unit);
        strcpy(I_tmpIngredient->c_ingredients_name, Ia_tmpIngredients->c_ingredients_name);
        Date D_null= {.i_day =0,
                      .i_month=0,
                      .i_year=0};
        I_tmpIngredient->D_expiration_date = D_null;
}


extern void initializeRecipeBook(RecipeBook* book){

    FILE * F_file_Recipe_txt = fopen("recipes.txt", "r");
    if(F_file_Recipe_txt == NULL){
        perror("The following error occurred?");
    }
    RecipeBook *R_ptr = book;
    Ingredients *I_ptr;
    RecipeBook R_tmpRecipe;
    Ingredients Ia_tmpIngredients[20];
    char c_tmp_IngredientLine[71];
    int i_indexForIngredient =0;
    while (fscanf(F_file_Recipe_txt,"%d; %[^,], %[^,];%s",&R_tmpRecipe.i_Recipe_Id,
                                                       &R_tmpRecipe.c_Recipe_Name,
                                                       &c_tmp_IngredientLine,
                                                       &R_tmpRecipe.c_description)!=EOF){
        i_indexForIngredient = 0;
    printf("hi %d\n",i_indexForIngredient);

        while (sscanf(strtok(c_tmp_IngredientLine,","),"%d %s %s",&Ia_tmpIngredients[i_indexForIngredient].d_weight,
                                                                  &Ia_tmpIngredients[i_indexForIngredient].c_unit,
                                                                  &Ia_tmpIngredients[i_indexForIngredient].c_ingredients_name)!= 0){
            i_indexForIngredient ++;
        }
        printf("%s",R_tmpRecipe.c_Recipe_Name);

        createRecipeListItem(R_ptr,&R_tmpRecipe);
        createIngredientListItem(I_ptr,&Ia_tmpIngredients[0]);
        R_ptr->I_ingredients = *I_ptr;

        for (int i = 1; i <= i_indexForIngredient; i++){
             createIngredientListItem(I_ptr,&Ia_tmpIngredients[i]);
        }
    }

    fclose(F_file_Recipe_txt);
}


static void freeRecipeBook(RecipeBook* R_ptr){
    RecipeBook * R_tmpNext = NULL;
   while(R_ptr->R_next !=NULL){
        R_tmpNext = R_ptr->R_next;
        freeIngredients(&R_ptr->I_ingredients);
        free(R_ptr);
    }
}

void freeIngredients(Ingredients * I_ptr){
    Ingredients *I_tmpNext = NULL;
    while(I_ptr!=NULL){
        I_tmpNext = I_ptr->I_next;
        free(I_ptr);
        I_ptr = I_tmpNext;
    }
}


int main(void){

    printf("hi\n");
    RecipeBook *testBook;
    initializeRecipeBook(testBook);

    while (testBook->R_next !=NULL){
        printf("%s\n",testBook->c_Recipe_Name);
    }

    freeRecipeBook(testBook);
    debugmalloc_dump();
}