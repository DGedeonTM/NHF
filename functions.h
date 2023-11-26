#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Functions in Recipes.c -------------------------------------------------------------
extern void createRecipeListItem(Recipe * R_Recipe, Recipe * R_ptr) ;
extern void deleteRecipeListItem(Recipe *R_Recipe, char c_searchedID[] );
extern void listRecipeListItems(Recipe *R_Recipe);
extern void freeRecipesList(Recipe *R_ptr);
extern Recipe* getRecipeElementByID(Recipe *R_Recipe, char c_searchedID[]);
extern Recipe* getRecipeElementByName(Recipe *R_Recipe, char c_searchedName[]);
//-------------------------------------------------------------------------------------

// Functions in Ingredients.c ----------------------------------------------------------
extern void createIngredientListItem(Ingredient * I_Ingredient, Ingredient *I_ptr);
extern void deleteIngredientListItem(Ingredient *I_Ingredient, char c_searchedID[]);
extern void listIngredientsListItems(Ingredient *I_Ingredient);
extern void freeIngredientsList(Ingredient *I_ptr);
extern Ingredient* getIngredientElementByID(Ingredient *I_Ingredient, char c_searchedID[]);
extern Ingredient* getIngredientElementByName(Ingredient *I_Ingredient, char c_searchedName[]);
//-------------------------------------------------------------------------------------

// Functions in Storage.c -------------------------------------------------------------
extern void createStorageListItem(Storage * S_StoredItemInStorage, Storage *S_ptr);
extern void deleteStorageListItem(Storage *S_Storage, char c_searchedID[]);
extern void listStorageListItems(Storage *S_Storage);
extern void freeStorageList(Storage *S_ptr);
extern Storage* getStorageElementByID(Storage *S_Storage, char c_searchedID[]);
//-------------------------------------------------------------------------------------


// Functions in Connection.c -----------------------------------------------------------
extern void createConnectionListItem(Connection * C_Connection, Connection * C_ptr);
extern int numbersOfSeachedConnectionItem(Connection *C_Connection, char c_searchedID[]);
extern void deleteConnectionListItem(Connection *C_Connection, char c_searchedID[] );
extern void listConnectionListItems(Connection *C_Connection);
extern void freeConnectionList(Connection *C_ptr);
extern Connection* getConnectionRecipeElementByID(Connection *C_Connection, char c_searchedID[] );
extern Connection* getConnectionIngredientElementByID(Connection *C_Connection, char c_searchedID[] );
//-------------------------------------------------------------------------------------

// Functions in Logs.c ----------------------------------------------------------------
extern void createLogsListItem(Logs * L_Log, Logs *L_ptr);
extern void deleteLogListItem(Logs *L_Log, char c_searchedID[] );
extern void listLogsListItems(Logs *L_Log);
extern void freeLogsList(Logs *L_ptr);
extern Logs* getLogElementByID(Logs *L_Log, char c_searchedID[] );
//-------------------------------------------------------------------------------------

// Functions in Backend.c -------------------------------------------------------------
extern void Init(void);
extern char* Generate_uuid(void);
extern int DateDifferencial(Date D_date);
extern void ViewRecipes(void);
extern void AddRecipe(char c_Recipe_Name[], char c_Recipe_Description[]);
extern void DeleteRecipe(char c_Recipe_Name[]);
extern void ViewIngredients(void);
extern void AddIngredient(char c_Inredient_Name[], char c_Ingredient_Unit[]);
extern void ViewStorage(void);
extern void AddConnection(char c_Recipe_Name[],char c_Ingredient_Name[],double d_amount);
extern void AddStorage(char c_Storage_Name[], double amount, Date *Exp_Date);
extern bool IsThereStorageItemExist(char c_Ingredient_Name[]);
extern bool IsThereRecipeItemExist(char c_Recipe_Name[]);
extern void CookRecipe(char c_Recipe_Name[]);
extern void SuggestRecipeByIngredient(char c_Ingredient_Name[]);
extern void SuggesetRandomRecipe(void);
extern void SuggestRecipeByExpiryDate(int i_Differencial_Day);
extern void ViewLog(void);
extern void FreeAll(void);
//-------------------------------------------------------------------------------------


// Functions in FileRead_write.c -------------------------------------------------------
extern void ReadIngredientFile(Ingredient *I_ptr);
extern void ReadRecipeFile(Recipe *R_ptr);
extern void ReadStorageFile(Storage *S_ptr);
extern void ReadLogsFile(Logs *L_ptr);
extern void ReadConnectionFile(Connection* C_ptr);

extern void DeleteLineFromRecipeFile(Recipe *R_tmp_Recipe);
extern void UpdateStorageFile(char c_Storage_To_Update[], double d_amount);
extern void AutoDeleteStorageItem(void);

extern void WriteRecipeToFile(Recipe *R_Recipe);
extern void WriteIngredientToFile(Ingredient *I_Ingredient);
extern void WriteStorageToFile(Storage *S_Storage);
extern void WriteConnenctionToFile(Connection *C_Connection);
extern void WriteLogsToFile(Logs *L_Log);
//-------------------------------------------------------------------------------------

#endif