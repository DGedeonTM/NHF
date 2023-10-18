#ifndef RECIPE_BOOK_H
#define RECIPE_BOOK_H

typedef struct RecipeBook{
    int i_Recept_Id;
    int i_Ingredients_Id;
    char c_description[5001];
}RecipeBook;


void initializeRecipeBook(RecipeBook* book);
void addRecipe(RecipeBook* book);
void deleteRecipe(RecipeBook* book);
void addIngredient(RecipeBook* book);
void generateIngredientBasedSuggestions(const RecipeBook* book);
void generateExpirationDateSuggestions(const RecipeBook* book);
void generateRecipeFromLogs(const RecipeBook* book);
void saveRecipeBookToFile(const RecipeBook* book);
void freeRecipeBook(RecipeBook* book);

#endif