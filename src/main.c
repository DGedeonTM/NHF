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
    }
    return 0;
}