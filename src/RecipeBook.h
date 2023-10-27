#ifndef RECIPE_BOOK_H
#define RECIPE_BOOK_H
#include "Ingredients.h"

typedef struct RecipeBook{
    int i_Recipe_Id;
    char c_Recipe_Name[51];
    Ingredients Ia_ingredients_array[20];
    char c_description[5001];
    struct RecipeBook *R_next;
}RecipeBook;

extern void initializeRecipeBook(RecipeBook* R_ptr,Ingredients *I_first_ptr);
  //RecipeBook* createRecipeListItem( RecipeBook *R_ptr, RecipeBook * R_tmpRecipe);

 //void createIngredientListItem(Ingredients *I_ptr, Ingredients *I_Ingredients);

void freeRecipeBook(RecipeBook* R_ptr);
void freeIngredients(Ingredients * I_ptr);


void addRecipe(RecipeBook* book);
void deleteRecipe(RecipeBook* book);
void addIngredient(RecipeBook* book);
void generateIngredientBasedSuggestions(const RecipeBook* book);
void generateExpirationDateSuggestions(const RecipeBook* book);
void generateRecipeFromLogs(const RecipeBook* book);
void saveRecipeBookToFile(const RecipeBook* book);

#endif