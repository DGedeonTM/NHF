#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structs.h"
#include "functions.h"

/*
  Description: The main function of the program, which presents a menu to the user for interacting with the recipe and ingredient system.
  Error Cases: None.
  Input arguments: None.
  Return type: int.
  Memory usage: Depends on the system's usage throughout the program. Freed at the end of the program.
  Big O notation: Depends on the operations performed, typically O(1) for each menu option.
 */
extern int main(void) {

    int i_choice = 0;
    char c_tmpRecipeName[51];
    char c_Recipe_Description[5001];
    char c_tmpDeleteName[51];
    char c_tmpIngredientName[51];
    char c_tmpUnit[11];
    double d_tmpAmount;
    int i_Differencial_Day;
    Date D_tmpDate;

    // Initialize the system
    Init();
    while (i_choice != 13){
        printf("\n>----------------------<\n");
        printf("  .-----.\n");
        printf("  `.   .' \n");
        printf("   |___|  \n");
        printf("   :o o:  \n");
        printf("  _`~^~'_ \n");
        printf("/    ^    \\  \n");

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

        // Take user input for the menu choice
        printf("Enter your choice: "); 
        if(scanf("%d", &i_choice) !=1 ){
            printf("Invalid choice. Program will exit.\n");
            break;
        }

        // Perform actions based on user's menu choice
        switch (i_choice) {
            case 1:
            printf("Recipes in the system:\n");
                ViewRecipes();
                break;

            case 2:
                printf("Please enter the name of Recipe:");
                scanf("%s", c_tmpRecipeName);
                if( strlen(c_tmpRecipeName) < 51){
                    printf("\nYou entered: \"%s\" \n",c_tmpRecipeName);
                }
                else{
                     printf("\nInput too long. Please enter up to 50 characters.\n");
                     break; 
                }
                printf("\nPlease enter the description of Recipe:");
               scanf("%s", c_Recipe_Description);
                if( strlen(c_Recipe_Description)>=5001){
                     printf("\nInput too long. Please enter up to 5000 characters.\n");
                     break;
                }

                AddRecipe(c_tmpRecipeName,c_Recipe_Description);
                break;

            case 3:
                printf("Please enter the name of Recipe what you want to delete:");
                scanf("%s",c_tmpDeleteName) ;
                if(strlen(c_tmpDeleteName) < 51){
                    printf("You entered: \"%s\" \n",c_tmpDeleteName);

                }
                else{
                     printf("Input too long. Please enter up to 50 characters.\n");
                     break;
                }
                DeleteRecipe(c_tmpDeleteName);
                break;
            case 4:
                ViewIngredients();
                break;

            case 5:
                printf("\nPlease enter the name of ingredient:");
                    scanf("%s",c_tmpIngredientName);
                if(strlen(c_tmpIngredientName) < 51){
                    printf("You entered: \"%s\" \n",c_tmpIngredientName);
                }
                else{
                     printf("Input too long. Please enter up to 50 characters.\n");
                     break;
                }
    
                printf("Please enter the unit of ingredient:");
                scanf("%s",c_tmpUnit);
                if(strlen(c_tmpUnit) < 11){
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
                scanf("%s",c_tmpIngredientName);
                
                if(strlen(c_tmpIngredientName) < 51){
                    printf("You entered: \"%s\" \n",c_tmpIngredientName);
                }
                else{
                     printf("Input too long. Please enter up to 50 characters.\n");
                     break;
                }
                
                if(!IsThereStorageItemExist(c_tmpIngredientName)){
                    printf("The choosen item: -%s- is not in the system. Please make sure you type correctly. \n Maybe you trying to enter an ingredient type which is not in sytem. Please make sure is the ingredient what you want to use, is exist. For this use \"4. View Ingredients\" function or add new ingredient to your system \n",c_tmpIngredientName);
                    break;
                }

                printf("\nPlease enter the amount of ingredient:");
                scanf("%lf",&d_tmpAmount);
                if( d_tmpAmount <= 0){
                    printf("The amount must be greater than 0");
                    break;
                }
                else {
                    
                }
                printf("Please enter the ingredient Expiration date. If the ingredient has not explicit Expiration day, then enter the most possible date, what you think will be expired.\n");

                printf("Expiraton date: \n");
                printf("Day:");
                scanf("%d",&D_tmpDate.i_day);
                if(D_tmpDate.i_day < 32 && D_tmpDate.i_day > 0){
                    printf("Month:");
                    scanf("%d",&D_tmpDate.i_month);
                    if(D_tmpDate.i_month < 13 && D_tmpDate.i_month > 0){
                        printf("Year:");
                        scanf("%d",&D_tmpDate.i_year);
                        printf("You entered the day (day:month:year): %d:%d:%d\n",D_tmpDate.i_day,D_tmpDate.i_month,D_tmpDate.i_year);
                        if(DateDifferencial(D_tmpDate) < 0){
                            printf("This ingredient already expired.\n");
                            break;
                        }
                        else{
                            AddStorage(c_tmpIngredientName,d_tmpAmount, &D_tmpDate);
                            printf("Storage was updated.\n");
                            break;
                        }                       
                    }
                    else{
                        printf("Month must be between 1 - 12\n");
                        break;
                    }
                
                }
                else{
                    printf("Date must be between 1 - 31\n");
                    break;
                }
                break;

            case 8:
                printf("\nSuggested recipes are the followings:\n");
                SuggesetRandomRecipe();
                break;

            case 9:
                printf("Please enter the name of ingredient:");
                scanf("%s",c_tmpIngredientName);
                if(strlen(c_tmpIngredientName) < 51 ){
                    printf("You entered: \"%s\" \n",c_tmpIngredientName);

                    if(!IsThereStorageItemExist(c_tmpIngredientName)){
                        printf("The choosen item: \"%s\" is not in the system. Please make sure you type correctly. \n Maybe you trying to enter an ingredient type which is not in sytem. Please make sure is the ingredient what you want to use, is exist. For this use -- 4. View Ingredients -- function or add new ingredient to your system \n " , c_tmpIngredientName);
                        break;
                    }
                    else{
                        printf("\nRecipes which are include the ingredient \"%s\" are the followings:\n",c_tmpIngredientName);
                        SuggestRecipeByIngredient(c_tmpIngredientName);
                        break;
                    }
                }
                else{
                     printf("Input too long. Please enter up to 50 characters.\n");
                     break;
                }                
                break;

            case 10:
                printf("\nPlease enter the date within which you want the expiry date to be:");
                scanf("%d",&i_Differencial_Day);
                printf("\nYou entered: \"%d\"\n",i_Differencial_Day);
                SuggestRecipeByExpiryDate(i_Differencial_Day);
                break;

            case 11:                 
                printf("Please enter your choosen Recipe name what you want to cook:");
                scanf("%s",c_tmpRecipeName);
                if(strlen(c_tmpRecipeName) < 51){
                    printf("\nYou entered: \"%s\"\n",c_tmpRecipeName);
                    if(!IsThereRecipeItemExist(c_tmpRecipeName)){
                        printf("The recipe \"%s\" is not in the system. Please make sure you write correctly or add that recipe to the system.\n",c_tmpRecipeName);
                    break;
                    }
                    else{
                        CookRecipe(c_tmpRecipeName);
                        printf("Recipe was cooked.\n");
                        break;
                    }
                }
                else{
                     printf("\nInput too long. Please enter up to 50 characters.\n");
                }                
                break;

            case 12:
                ViewLog();
                break;        

            case 13:
                printf("Exiting the program.\nGoodbye\n");
                break;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
      
    }
    
    // Free allocated memory and display memory debugging information
    FreeAll();
    return 0;
}