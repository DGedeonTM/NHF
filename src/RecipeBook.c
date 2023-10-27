#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "RecipeBook.h"
#include "debugmalloc.h"

 RecipeBook* createRecipeListItem( RecipeBook * R_tmpRecipe){
    RecipeBook *R_recipe = (RecipeBook*)malloc(sizeof(RecipeBook));
        if (R_recipe == NULL){
            perror("The following error occurred");
           // return NULL;
        }
        R_recipe->i_Recipe_Id = R_tmpRecipe->i_Recipe_Id;
        strcpy(R_recipe->c_Recipe_Name,R_tmpRecipe->c_Recipe_Name);
        strcpy(R_recipe->c_description,R_tmpRecipe->c_description);
        return R_recipe;
}


extern void initializeRecipeBook(RecipeBook* R_start_ptr,Ingredients *I_first_ptr){

    FILE * F_file_Recipe_txt = fopen("recipes.txt", "r");
    if(F_file_Recipe_txt == NULL){
        perror("The following error occurred?");
    }
    Ingredients *I_ptr = NULL;
    Ingredients Ia_tmpIngredients[20];
    RecipeBook R_tmpRecipe;
    RecipeBook *R_ptr = R_start_ptr;
    char c_tmp_IngredientLine[550];
    int i_indexForIngredient =0;
    bool b_first_time_appariance=true;

    while (fscanf(F_file_Recipe_txt,"%d; %51[^;]; %550[^;]; %5000[^\n]",&R_tmpRecipe.i_Recipe_Id,
                                                       &R_tmpRecipe.c_Recipe_Name,
                                                       &c_tmp_IngredientLine,
                                                       &R_tmpRecipe.c_description) !=EOF){

        R_ptr->R_next = createRecipeListItem(&R_tmpRecipe);
        R_ptr = R_ptr->R_next;

        char* token = strtok(c_tmp_IngredientLine, ",");
        while (token != NULL && i_indexForIngredient < 20) {
            if (sscanf(token, "%lf %10[^ ] %50[^\n]",
                        &Ia_tmpIngredients[i_indexForIngredient].d_weight,
                        &Ia_tmpIngredients[i_indexForIngredient].c_unit,
                        &Ia_tmpIngredients[i_indexForIngredient].c_ingredients_name) == 3) {

        while (sscanf(strtok(c_tmp_IngredientLine,","),"%d %s %s",&Ia_tmpIngredients[i_indexForIngredient].d_weight,
                                                                  &Ia_tmpIngredients[i_indexForIngredient].c_unit,
                                                                  &Ia_tmpIngredients[i_indexForIngredient].c_ingredients_name)!= 0){

            R_ptr->Ia_ingredients_array[i_indexForIngredient].d_weight;
            i_indexForIngredient ++;
        }

        i_indexForIngredient=0;

        fgetc(F_file_Recipe_txt);
        }

        fclose(F_file_Recipe_txt);
        }
    }
}

extern int main(void){
    RecipeBook testBook;
    Ingredients ingred;
    testBook.i_Recipe_Id=-200;
    RecipeBook  *elso = &testBook;
    initializeRecipeBook(&testBook,&ingred);

    freeRecipeBook(elso->R_next);

    debugmalloc_dump();
    return 0;
}
