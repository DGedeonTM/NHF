#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "functions.h"

extern int main(void) {

    int i_choice;
    while (1) {
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

        switch (i_choice) {
            case 1:
                ViewRecipes();
                break;
            case 2:
                char c_tmpChoosenName[51];
                char c_tmpDescription[5001];
                printf("Please enter the name of Recipe:");
                if(scanf("%50s",&c_tmpChoosenName) == 1){
                    printf("You entered: \"%s\" \n",c_tmpChoosenName);
                }
                else{
                     printf("Input too long. Please enter up to 50 characters.\n");
                     break;
                }
    
                printf("Please enter the description of Recipe:");
                if(scanf("%5000s",&c_tmpDescription) == 1){}
                else{
                     printf("Input too long. Please enter up to 5000 characters.\n");
                     break;
                }
                AddRecipe(c_tmpChoosenName,c_tmpDescription);
                break;
            case 3:
                DeleteRecipe();
                break;
            case 4:
                ViewIngredients();
                break;
            case 5:
                char c_tmpChoosenName[51];
                char c_tmpUnit[11];
                printf("Please enter the name of ingredient:");
                if(scanf("%50s",&c_tmpChoosenName) == 1){
                    printf("You entered: \"%s\" \n",c_tmpChoosenName);
                }
                else{
                     printf("Input too long. Please enter up to 50 characters.\n");
                     break;
                }
    
                printf("Please enter the unit of ingredient:");
                if(scanf("%10s",&c_tmpUnit) == 1){
                    printf("You entered: \"%s\" \n",c_tmpUnit);
                }
                else{
                     printf("Input too long. Please enter up to 10 characters.\n");
                     break;
                }
        
                AddIngredient(c_tmpChoosenName,c_tmpUnit);
                printf("Ingredient list was updated\n")
                break;
            case 6:
                ViewStorage();
                break;
            case 7:
                char c_tmpChoosenName[51];
                double d_tmpAmount;
                printf("Please enter the name of ingredient:");
                if(scanf("%50s",&c_tmpChoosenName) == 1){
                    printf("You entered: \"%s\" \n",c_tmpChoosenName);
                }
                else{
                     printf("Input too long. Please enter up to 50 characters.\n");
                     break;
                }
                
                if(!IsThereStorageItemExist(c_tmpChoosenName)){
                    printf("The choosen item: \"%s\" is not in the system. Please make sure you type correctly. \n Maybe you trying to enter an ingredient type which is not in sytem.
                      Please make sure is the ingredient what you want to use, is exist. For this use \"4. View Ingredients\" function or add new ingredient to your system \n",c_tmpChoosenName);
                    break;
                }

                printf("\nPlease enter the amount of ingredient:");
                if(scanf("%lf",&d_tmpAmount)==1 && d_tmpAmount >0){}
                else {
                    printf("The amount must be greater than 0");
                    break;
                }
                printf("Please enter the ingredient Expiration date in day:month:year format. If the ingredient has not explicit Expiration day, then enter the most possible date, what you think will be expired.\n");
                Date D_tmpDate;

                printf("Expiraton date: ");
                if(scanf("%d:%d:%d",&D_tmpDate.i_day,&D_tmpDate.i_month,&D_tmpDate.i_year)!=1){
                    printf("Please write the expiration date in day:month:year format\n");
                    break;
                }               
                AddStorage(c_tmpChoosenName,d_tmpAmount,D_tmpDate);
                printf("Storage was updated.\n")
                break;
            case 8:

                break;
            case 9:

                break;
            case 10:

                break;
            case 11:
                char c_tmpChoosen[51];
                printf("Please enter your choosen Recipe name what you want to cook:");
                if(scanf("%50s",&c_tmpChoosen) == 1){
                    printf("You entered: \"%s\"",c_tmpChoosen);
                }
                else{
                     printf("Input too long. Please enter up to 50 characters.\n");
                }
                SelectAndCookRecipe();
                printf("Recipe was cooked.\n");
                break;
            case 12:
                ViewLogs();
                break;            
            case 13:
                printf("Exiting the program.\n Goodbye\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    return 0;
    }
}