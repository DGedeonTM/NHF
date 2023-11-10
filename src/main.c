#include <stdio.h>
#include <stdlib.h>
#include "RecipeBook.h"

int main() {
    RecipeBook book;
    initializeRecipeBook(&book);

    int choice;
    while (1) {
        printf("\nRecipe Book Menu:\n");
        printf("1. Add Recipe\n");
        printf("2. Delete Recipe\n");
        printf("3. Add Ingredient\n");
        printf("4. Generate Recipe Suggestions (by ingredients)\n");
        printf("5. Generate Recipe Suggestions (by expiration date)\n");
        printf("6. Generate Recipe based on Logs\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecipe(&book);
                break;
            case 2:
                deleteRecipe(&book);
                break;
            case 3:
                addIngredient(&book);
                break;
            case 4:
                generateIngredientBasedSuggestions(&book);
                break;
            case 5:
                generateExpirationDateSuggestions(&book);
                break;
            case 6:
                generateRecipeFromLogs(&book);
                break;
            case 7:
                saveRecipeBookToFile(&book);
                freeRecipeBook(&book);
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    Ingredient I_start;  // Create a dummy start node
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
    }
    return 0;
}