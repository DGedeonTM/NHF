#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structs.h"
#include "functions.h"

extern int main(void) {

    int i_choice = 0;
    char c_tmpRecipeName[51];
    char c_Recipe_Description[5001];
    char c_tmpDeleteName[51];
    char c_tmpIngredientName[51];
    char c_tmpUnit[11];
    char c_tmpStorageName[51];
    double d_tmpAmount;
    Date D_tmpDate;
    int i_Ingredients;


    Init();
    while (i_choice != 13){
        printf("\n>----------------------<\n");
        printf("\nMenu Options:\n");
        printf("1. View Recipes\n");
        printf("2. Add Recipe\n");
        printf("3. Delete Recipe\n");
        printf("4. View Ingredients\n");
        printf("5. Add Ingredient\n");
        printf("6. View Storage\n");
        printf("7. Add to Storage\n");
        printf("8. Suggest Random Recipe\n");
        printf("9. Suggest Recipe by Ingredients\n");
        printf("10. Suggest Recipe by Expiry Date\n");
        printf("11. Select and cook recipe\n");
        printf("12. Logs\n");
        printf("13. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &i_choice);
        printf("\n");

        switch(i_choice){
            case 1:
                printf("\nRecipe List:\n");
                ViewRecipes();
                break;
            case 2:
                printf("Please enter the name of Recipe:");
                scanf("%s",&c_tmpRecipeName);
                if(strlen(c_tmpRecipeName) < 51){
                    printf("\nYou entered: \"%s\" \n",c_tmpRecipeName);
                }
                else{
                     printf("\nInput too long. Please enter up to 50 characters.\n");
                     break; 
                }

                printf("\nPlease enter the description of Recipe:");
                scanf("%s",&c_Recipe_Description);
                if(strlen(c_Recipe_Description)>=5001){
                     printf("\nInput too long. Please enter up to 5000 characters.\n");
                     break;
                }
                
                AddRecipe(c_tmpRecipeName,c_Recipe_Description);

                printf("\nHow many ingredients needed to make the recipe? :");
                scanf("%d",&i_Ingredients);

                for(int i = 0; i < i_Ingredients; i++){
                    printf("\nPlease write the ingredient name:");
                    scanf("%s",&c_tmpIngredientName);
                    if(strlen(c_tmpRecipeName) >= 51 ){
                     printf("\nInput too long. Please enter up to 50 characters.\n");
                     break;
                    }       
                    if(!IsThereStorageItemExist(c_tmpIngredientName)){
                        printf("\nThe choosen item: \"%s\" is not in the system. Please make sure you type correctly. \n Maybe you trying to enter an ingredient type which is not in sytem. Please make sure is the ingredient what you want to use, is exist. For this use -- 4. View Ingredients -- function or add new ingredient to your system \n " , c_tmpStorageName);
                        break;
                    }
                    printf("\nPlease write the amout of the ingredient:");
                    scanf("%lf",&d_tmpAmount);
                    if(d_tmpAmount <= 0 ){
                        printf("\nThe amount must be greater than 0\n");
                        break;
                    }
                    AddConnection(c_tmpRecipeName,c_tmpIngredientName,d_tmpAmount);

                } 

                printf("Recipe list was updated\n");
                break;

            case 3:
                printf("Please enter the name of Recipe what you want to delete:");
                if(scanf("%s",&c_tmpDeleteName) == 1 && strlen(c_tmpDeleteName) < 51){
                    printf("You entered: \"%s\" \n",c_tmpDeleteName);
                }
                else{
                     printf("Input too long. Please enter up to 50 characters.\n");
                     break;
                }
                DeleteRecipe(c_tmpDeleteName);
                break;
            case 4:
                printf("\nIngredient list:\n");
                ViewIngredients();
                break;
            case 5:
                printf("Please enter the name of ingredient:");
                if(scanf("%s",&c_tmpIngredientName) == 1 && strlen(c_tmpIngredientName) < 51 ){
                    printf("You entered: \"%s\" \n",c_tmpIngredientName);
                }
                else{
                     printf("Input too long. Please enter up to 50 characters.\n");
                     break;
                }
    
                printf("Please enter the unit of ingredient:");
                if(scanf("%s",&c_tmpUnit) == 1 && strlen(c_tmpUnit) < 11){
                    printf("You entered: \"%s\" \n",c_tmpUnit);
                }
                else{
                     printf("Input too long. Please enter up to 10 characters.\n");
                     break;
                }
        
                AddIngredient(c_tmpIngredientName,c_tmpUnit);
                printf("Ingredient list was updated\n");
                break;
            case 6:
                ViewStorage();
                break;
            case 7:
                printf("Please enter the name of ingredient:");
                if(scanf("%s",&c_tmpStorageName) == 1 && strlen(c_tmpStorageName) < 51){
                    printf("You entered: \"%s\" \n",c_tmpStorageName);
                }
                else{
                     printf("Input too long. Please enter up to 50 characters.\n");
                     break;
                }
                
                if(!IsThereStorageItemExist(c_tmpStorageName)){
                    printf("The choosen item: \"%s\" is not in the system. Please make sure you type correctly. \n Maybe you trying to enter an ingredient type which is not in sytem. Please make sure is the ingredient what you want to use, is exist. For this use -- 4. View Ingredients -- function or add new ingredient to your system \n " , c_tmpStorageName);
                    break;
                }

                printf("\nPlease enter the amount of ingredient:");
                if(scanf("%lf",&d_tmpAmount)==1 && d_tmpAmount >0){}
                else {
                    printf("The amount must be greater than 0");
                    break;
                }
                printf("Please enter the ingredient Expiration date in day:month:year format. If the ingredient has not explicit Expiration day, then enter the most possible date, what you think will be expired.\n");

                printf("Expiraton date: ");
                if(scanf("%d:%d:%d",&D_tmpDate.i_day,&D_tmpDate.i_month,&D_tmpDate.i_year)!=3){
                    printf("Please write the expiration date in day:month:year format\n");
                    break;
                }               
                AddStorage(c_tmpStorageName,d_tmpAmount,D_tmpDate);
                printf("Storage was updated.\n");
                break;
            case 8:

                break;
            case 9:
                printf("Please enter the name of ingredient:");
                scanf("%s",&c_tmpIngredientName);
                if(strlen(c_tmpIngredientName) < 51 ){
                    printf("You entered: \"%s\" \n",c_tmpIngredientName);
                }
                else{
                     printf("Input too long. Please enter up to 50 characters.\n");
                     break;
                }
                if(!IsThereStorageItemExist(c_tmpIngredientName)){
                    printf("The choosen item: \"%s\" is not in the system. Please make sure you type correctly. \n Maybe you trying to enter an ingredient type which is not in sytem. Please make sure is the ingredient what you want to use, is exist. For this use -- 4. View Ingredients -- function or add new ingredient to your system \n " , c_tmpStorageName);
                    break;
                }
                else{
                    printf("\nRecipes which are include the ingredient \"%s\" are the followings:\n",c_tmpIngredientName);
                    SuggestRecipeByIngredient(c_tmpIngredientName);
                }
                break;
            case 10:

                break;
            case 11: 
                
                printf("Please enter your choosen Recipe name what you want to cook:");
                int result = scanf("%s",&c_tmpRecipeName);
                if( result == 1 && strlen(c_tmpRecipeName) < 51){
                    printf("\nYou entered: \"%s\"\n",c_tmpRecipeName);
                }
                else{
                     printf("\nInput too long. Please enter up to 50 characters.\n");
                }
                if(!IsThereRecipeItemExist(c_tmpRecipeName)){
                    printf("The recipe \"%s\" is not in the system. Please make sure you write correctly or add that recipe to the system.\n",c_tmpRecipeName);
                    break;
                }
                else{
                    CookRecipe(c_tmpRecipeName);
                    printf("Recipe was cooked.\n");
                }
                break;
            case 12:
                ViewLogs();
                break;            
            case 13:
                printf("Exiting the program.\n Goodbye\n");
                break;            
            default:
                printf("Invalid choice. Please try again.\n");

        
    
        }
    }
    FreeAll();
    return 0;
}
