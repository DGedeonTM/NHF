#ifndef FUNCTIONS_H
#define FUNCTIONS_H
/*
extern void InitIngredientList(Ingredient* I_start_ptr);
extern void InitRecipesList(Recipe* R_start_ptr);
extern void InitStorageList(Storage* S_start_ptr);

extern Connection* addNewConnection(char R_Recipe_ID[], char I_Ingredients_ID[], double Amount);
extern void InitConnectionList(Connection* C_start_ptr);






extern void freeIngredientsList(Ingredient *I_ptr);
extern void freeRecipesList(Recipe *R_ptr);
extern void freeStorageList(Storage *S_ptr);
extern void freeConnectionList(Connection *C_ptr);

*/

extern void freeRecipesList(Recipe *R_ptr);
extern void listRecipeListItems(Recipe *R_Recipe);
extern void deleteRecipeListItem(Recipe *R_Recipe, char c_searchedID[] );
extern void createRecipeListItem(Recipe * R_Recipe, Recipe * R_ptr) ;
extern Recipe* getRecipeElementByID(Recipe *R_Recipe, char c_searchedID[] );
extern Recipe* getRecipeElementByName(Recipe *R_Recipe, char c_searchedName[]);

extern void createIngredientListItem(Ingredient * I_Ingredient, Ingredient *I_ptr);
extern void deleteIngredientListItem(Ingredient *I_Ingredient, char c_searchedID[]);
extern void listIngredientsListItems(Ingredient *I_Ingredient);
extern void freeIngredientsList(Ingredient *I_ptr);
extern Ingredient* getIngredientElementByID(Ingredient *I_Ingredient, char c_searchedID[]);
extern Ingredient* getIngredientElementByName(Ingredient *I_Ingredient, char c_searchedName[]);


extern void createStorageListItem(Storage * S_StoredItemInStorage, Storage *S_ptr);
extern void deleteStorageListItem(Storage *S_Storage, char c_searchedID[]);
extern void listStorageListItems(Storage *S_Storage);
extern void freeStorageList(Storage *S_ptr);
extern Storage* getStorageElementByID(Storage *S_Storage, char c_searchedID[]);


extern void createConnectionListItem(Connection * C_Connection, Connection * C_ptr);
extern void deleteConnectionListItem(Connection *C_Connection, char c_searchedID[] );
extern void listConnectionListItems(Connection *C_Connection);
extern void freeConnectionList(Connection *C_ptr);
extern Connection* getConnectionRecipeElementByID(Connection *C_Connection, char c_searchedID[] );
extern Connection* getConnectionIngredientElementByID(Connection *C_Connection, char c_searchedID[] );


extern void createLogsListItem(Logs * L_Log, Logs *L_ptr);
extern void deleteLogListItem(Logs *L_Log, char c_searchedID[] );
extern void listLogsListItems(Logs *L_Log);
extern void freeLogsList(Logs *L_ptr);
extern Logs* getLogElementByID(Logs *L_Log, char c_searchedID[] );


extern char* gen_uuid(void);
extern int numbersOfSeachedConnectionItem(Connection *C_Connection, char c_searchedID[]);
extern bool IsThereStorageItemExist(char c_Ingredient_Name[]);
extern bool IsThereRecipeItemExist(char c_Recipe_Name[]);

extern char* gen_uuid();

extern void ViewRecipes(void);
extern void AddRecipe(char c_Recipe_Name[], char c_Recipe_Description[]);
extern void DeleteRecipe(char c_Recipe_Name[]);
extern ViewIngredients(void);
extern void AddIngredient(char c_Inredient_Name[], char c_Ingredient_Unit);
extern void ViewStorage();
extern void AddStorage(char c_Storage_Name[], double amount, Date Exp_Date);
extern void CookRecipe(char c_Recipe_Name[]);
extern void ViewLogs(void);
extern void Init(void);
extern void AddConnection(char c_Recipe_Name[],char c_Ingredient_Name[],double d_amount);


extern void SuggestRecipeByIngredient(char c_Ingredient_Name[]);
        
extern void ReadIngredientFile(Ingredient *I_ptr);
extern void ReadRecipeFile(Recipe *R_ptr);
extern void ReadStorageFile(Storage *S_ptr);
extern void ReadConnectionFile(Connection* C_ptr);
extern void ReadLogsFile(Logs *L_ptr);


extern void WriteRecipeToFile(Recipe *R_Recipe);
extern void WriteIngredientToFile(Ingredient *I_Ingredient);
extern void WriteStorageToFile(Storage *S_Storage);
extern void WriteConnenctionToFile(Connection *C_Connection);
extern void WriteLogsToFile(Logs *L_Log);


#endif