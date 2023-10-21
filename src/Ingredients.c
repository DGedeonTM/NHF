#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ingredients.h"

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

void InitIngredientList(Ingredients *I_start_ptr){
    FILE *F_file_Ingredients_txt = fopen("Ingredients.txt","r");
    if(F_file_Ingredients_txt==NULL){
        perror("The following error occurred?");
    }
    Ingredients I_tmpIngredients;
    Ingredients *I_ptr = I_start_ptr;

    while(fscanf(F_file_Ingredients_txt,"%lf %[^ ] %[^%d] %d.%d.%d",&I_tmpIngredients.d_weight,
                                                                &I_tmpIngredients.c_unit,
                                                                &I_tmpIngredients.c_ingredients_name,
                                                                &I_tmpIngredients.D_expiration_date.i_day,
                                                                &I_tmpIngredients.D_expiration_date.i_month,
                                                                &I_tmpIngredients.D_expiration_date.i_year)!= EOF){

        printf("hiii %g\n",I_tmpIngredients.d_weight);
        createIngredientListItem(I_ptr,&I_tmpIngredients);
    }


    I_ptr = I_start_ptr;
    for (int i = 0; i < 34; i++){
        printf("%d",I_ptr->d_weight);
    }


    fclose(F_file_Ingredients_txt);

}

int main(){
    Ingredients I_tmpIngredients;
 InitIngredientList(&I_tmpIngredients);


}