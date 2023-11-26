#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"
#include "functions.h"
#include <time.h>

    Recipe R_dumyRecipeStart;
    Ingredient I_dumyIngredientStart;
    Storage S_dumyStorageStart;
    Connection C_dumyConnectionStart;
    Logs L_dumyLogsStart;

    Recipe R_tmp_Recipe;
    Ingredient I_tmp_Ingredienet;
    Storage S_tmp_Storage;
    Connection C_tmp_Connection;
    Logs L_tmp_Log;
    Date D_tmp_Date;

/*
  Description: Initializes the system by setting up the random seed, reading recipe, ingredient, storage, connection, and logs files.
  Error Cases: None.
  Input arguments: None.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(N), where N is the size of the data being read from files.
 */
extern void Init(void){
    srand((unsigned int)time(NULL));
    ReadRecipeFile(&R_dumyRecipeStart);
    ReadIngredientFile(&I_dumyIngredientStart);
    AutoDeleteStorageItem();
    ReadStorageFile(&S_dumyStorageStart);
    ReadConnectionFile(&C_dumyConnectionStart);
    ReadLogsFile(&L_dumyLogsStart);
}

/*
  Description: Generates a random UUID.
  Error Cases: None.
  Input arguments: None.
  Return type: char* (pointer to a static buffer containing the UUID).
  Memory usage: Uses a static buffer.
  Big O notation: O(1).
 */
extern char* Generate_uuid(void) {
    char v[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    static char buf[37] = {0};
    for(int i = 0; i < 36; ++i) {
        buf[i] = v[rand()%16];
    }
    buf[8] = '-';
    buf[13] = '-';
    buf[18] = '-';
    buf[23] = '-';
    buf[36] = '\0';
    return buf;
}

/*
  Description: Gets the current date.
  Error Cases: None.
  Input arguments: D_tmp_Date - a pointer to the Date structure to store the current date.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(1).
 */
static void getDate(Date *D_tmp_Date){
    time_t currentTime;
    time(&currentTime);
    struct tm* localTime = localtime(&currentTime);    
    D_tmp_Date->i_day = localTime->tm_mday;
    D_tmp_Date->i_month = localTime->tm_mon +1;
    D_tmp_Date->i_year = localTime->tm_year + 1900;
}

/*
  Description: Copies the values of a source date to a destination date.
  Error Cases: None.
  Input arguments: D_from - pointer to the source Date structure, D_to - pointer to the destination Date structure.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(1).
 */
static void strcpyDate(Date *D_from, Date *D_to){
    D_to->i_day = D_from->i_day;
    D_to->i_month = D_from->i_month;
    D_to->i_year = D_from->i_year;
}

/*
  Description: Calculates the difference in days between the given date and the current date.
  Error Cases: None.
  Input arguments: D_date - Date structure representing the target date.
  Return type: int - the difference in days.
  Memory usage: No additional memory is allocated.
  Big O notation: O(1).
 */
extern int DateDifferencial(Date D_date){
    Date D_Today; 
    getDate(&D_Today);
    return ((D_date.i_year-D_Today.i_year)*365) + ((D_date.i_month - D_Today.i_month) *30 ) + (D_date.i_day - D_Today.i_day);
}

/*
  Description: Displays the list of recipes.
  Error Cases: None.
  Input arguments: None.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(N), where N is the number of recipes.
 */
extern void ViewRecipes(void){
    listRecipeListItems(R_dumyRecipeStart.R_next_Recipe);
}

/*
  Description: Adds a new recipe with specified name and description, along with required ingredients.
  Error Cases: Handles memory allocation errors during ingredient input.
  Input arguments:  c_Recipe_Name - name of the recipe, 
                    c_Recipe_Description - description of the recipe.
  Return type: void.
  Memory usage: Allocates memory for temporary connection array.
  Big O notation: O(N), where N is the number of ingredients for the recipe.
 */
extern void AddRecipe(char c_Recipe_Name[], char c_Recipe_Description[]){
   char c_falseIngredient[4];
    strcpy(R_tmp_Recipe.c_Recipe_ID, Generate_uuid());
    strcpy(R_tmp_Recipe.c_Recipe_Name, c_Recipe_Name);
    strcpy(R_tmp_Recipe.c_Recipe_Description, c_Recipe_Description); 
   
    char c_tmpIngredientName[51];
    char c_tmpUnit[11];  
    int i_NumberOfIngredient=0;
    printf("\nPlease write the number of how many ingredient need to make this recipe:");
    scanf("%d",&i_NumberOfIngredient);
    printf("hiu\n");
    Connection *Ca_tmp_ConnectionArray = (Connection*)malloc(i_NumberOfIngredient * sizeof(Connection));
    if(Ca_tmp_ConnectionArray == NULL){
        perror("Failed to allocate memory for temp. Connection");
        exit(1); 
    }

    for(int i = 0; i<i_NumberOfIngredient; i++){
        printf("\n%d. ingredient:",i+1);
        scanf("%s",I_tmp_Ingredienet.c_Ingredient_Name);
        if(!IsThereStorageItemExist(I_tmp_Ingredienet.c_Ingredient_Name)){
            printf("This ingredient \"%s\" does not exsist. Do you want to add to the system? yes / no:",I_tmp_Ingredienet.c_Ingredient_Name);
            scanf("%s",c_falseIngredient);

            if(strcmp("yes",c_falseIngredient)==0 || strcmp("y",c_falseIngredient)==0){
                printf("\nPlease enter the name of ingredient:");
                    scanf("%s",c_tmpIngredientName);
                if(strlen(c_tmpIngredientName) < 51){
                    printf("You entered: \"%s\" \n",c_tmpIngredientName);
                }
                else{
                     printf("Input too long. Please enter up to 50 characters.\n");
                     free(Ca_tmp_ConnectionArray);
                     break;
                }
    
                printf("Please enter the unit of ingredient:");
                scanf("%s",c_tmpUnit);
                if(strlen(c_tmpUnit) < 11){
                    printf("You entered: \"%s\" \n",c_tmpUnit);
                }
                else{
                     printf("Input too long. Please enter up to 10 characters.\n");
                     free(Ca_tmp_ConnectionArray);
                     break;
                }        
                AddIngredient(c_tmpIngredientName,c_tmpUnit);
                
            }
            else if (strcmp("no",c_falseIngredient)==0 || strcmp("n",c_falseIngredient)==0){
                free(Ca_tmp_ConnectionArray);
                break;
            }
            else{
                printf("Command not found.\n");
                free(Ca_tmp_ConnectionArray);
                break;
            }
            
        }

        printf("\nThe amount of the ingredient \"%s\":",I_tmp_Ingredienet.c_Ingredient_Name);
        scanf("%lf",&C_tmp_Connection.d_Amount_For_Recipe);
        strcpy(C_tmp_Connection.c_Ingredient_ID, getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient, I_tmp_Ingredienet.c_Ingredient_Name)->c_Ingredient_ID);
        strcpy(C_tmp_Connection.c_Recipe_ID,R_tmp_Recipe.c_Recipe_ID);
        Ca_tmp_ConnectionArray[i] = C_tmp_Connection;
    }

    createRecipeListItem(&R_tmp_Recipe,R_dumyRecipeStart.R_next_Recipe);
    WriteRecipeToFile(&R_tmp_Recipe);

    for(int i = 0; i < i_NumberOfIngredient; i++){
        createConnectionListItem( &Ca_tmp_ConnectionArray[i] ,C_dumyConnectionStart.C_next_Connection);
        WriteConnenctionToFile(&Ca_tmp_ConnectionArray[i]);
    }
    

    getDate(&L_tmp_Log.D_Date_Of_The_Log);
    strcpy(L_tmp_Log.c_ID,R_tmp_Recipe.c_Recipe_ID);
    strcpy(L_tmp_Log.c_Operation_Description,"A");
    WriteLogsToFile(&L_tmp_Log);
    printf("Recipe list was updated\n");
    free(Ca_tmp_ConnectionArray);

}


/*
  Description: Deletes a recipe with the specified name.
  Error Cases: None.
  Input arguments: c_Recipe_Name - name of the recipe to be deleted.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(N), where N is the number of recipes.
 */
extern void DeleteRecipe(char c_Recipe_Name[]){
    Recipe * R_tmp_ptr_Recipe = getRecipeElementByName(R_dumyRecipeStart.R_next_Recipe,c_Recipe_Name);
    if(R_tmp_ptr_Recipe == NULL){
        printf("\nRecipe does not extist\n");
    }
    else{
        strcpy(L_tmp_Log.c_ID,R_tmp_ptr_Recipe->c_Recipe_ID);
        strcpy(L_tmp_Log.c_Operation_Description,"D");
        getDate(&L_tmp_Log.D_Date_Of_The_Log);
        DeleteLineFromRecipeFile(R_tmp_ptr_Recipe);
        deleteRecipeListItem(&R_dumyRecipeStart,R_tmp_ptr_Recipe->c_Recipe_ID);
        createLogsListItem(&L_tmp_Log,L_dumyLogsStart.L_next_Logs);
        WriteLogsToFile(&L_tmp_Log);
        printf("Recipe list was deleted\n");
    }
}

/*
  Description: Displays the list of ingredients.
  Error Cases: None.
  Input arguments: None.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(N), where N is the number of ingredients.
 */
extern void ViewIngredients(void){
    if(I_dumyIngredientStart.c_Ingredient_ID == NULL){
        printf("\nThere are no available Ingredients in the system\n");
    }
    else{
        listIngredientsListItems(I_dumyIngredientStart.I_next_Ingredient);
    }
}

/*
  Description: Adds a new ingredient with specified name and unit.
  Error Cases: Handles memory allocation errors.
  Input arguments:  c_Inredient_Name - name of the ingredient, 
                    c_Ingredient_Unit - unit of the ingredient.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(1).
 */
extern void AddIngredient(char c_Inredient_Name[], char c_Ingredient_Unit[]){
    strcpy(I_tmp_Ingredienet.c_Ingredient_ID,Generate_uuid());
    strcpy(I_tmp_Ingredienet.c_Ingredient_Name, c_Inredient_Name);
    strcpy(I_tmp_Ingredienet.c_Unit,c_Ingredient_Unit);
    createIngredientListItem(&I_tmp_Ingredienet , I_dumyIngredientStart.I_next_Ingredient);
    WriteIngredientToFile(&I_tmp_Ingredienet);

    getDate(&L_tmp_Log.D_Date_Of_The_Log);
    strcpy(L_tmp_Log.c_ID, getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient,c_Inredient_Name)->c_Ingredient_ID);
    strcpy(L_tmp_Log.c_Operation_Description,"A");
    WriteLogsToFile(&L_tmp_Log);
}

/*
  Description: Displays the list of storage items.
  Error Cases: None.
  Input arguments: None.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(N), where N is the number of storage items.
 */
extern void ViewStorage(void){
    listStorageListItems(S_dumyStorageStart.S_next_Storage);
}

/*
  Description: Adds a new connection between a recipe and an ingredient with a specified amount.
  Error Cases: None.
  Input arguments:  c_Recipe_Name - name of the recipe, 
                    c_Ingredient_Name - name of the ingredient, 
                    d_amount - amount required for the recipe.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(1).
 */
extern void AddConnection(char c_Recipe_Name[], char c_Ingredient_Name[],double d_amount){
    strcpy(C_tmp_Connection.c_Recipe_ID,getRecipeElementByName(R_dumyRecipeStart.R_next_Recipe,c_Recipe_Name)->c_Recipe_ID);
    strcpy(C_tmp_Connection.c_Ingredient_ID,getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient,c_Ingredient_Name)->c_Ingredient_ID);
    C_tmp_Connection.d_Amount_For_Recipe = d_amount;
    createConnectionListItem(&C_tmp_Connection,C_dumyConnectionStart.C_next_Connection);
    WriteConnenctionToFile(&C_tmp_Connection);
}


/*
  Description: Adds a new storage item with a specified name, amount, and expiration date.
  Error Cases: None.
  Input arguments:  c_Storage_Name - name of the storage item, 
                    amount - amount in storage, 
                    Exp_Date - pointer to the expiration date.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(1).
 */
extern void AddStorage(char c_Storage_Name[], double amount, Date *Exp_Date){
    strcpy(S_tmp_Storage.c_Ingredient_ID,getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient ,c_Storage_Name)->c_Ingredient_ID);
    S_tmp_Storage.d_Amount_In_Storage = amount;
    strcpyDate(Exp_Date,&S_tmp_Storage.D_Expiration_date);
    createStorageListItem(&S_tmp_Storage,S_dumyStorageStart.S_next_Storage);
    WriteStorageToFile(&S_tmp_Storage);
    
    getDate(&L_tmp_Log.D_Date_Of_The_Log);
    strcpy(L_tmp_Log.c_ID, getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient,c_Storage_Name)->c_Ingredient_ID);
    strcpy(L_tmp_Log.c_Operation_Description,"A");
    WriteLogsToFile(&L_tmp_Log);
}

/*
  Description: Checks if a storage item with the given ingredient name exists.
  Error Cases: None.
  Input arguments: c_Ingredient_Name - name of the ingredient.
  Return type: bool - true if the storage item exists, false otherwise.
  Memory usage: No additional memory is allocated.
  Big O notation: O(N), where N is the number of storage items.
 */
extern bool IsThereStorageItemExist(char c_Ingredient_Name[]){
    if(getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient,c_Ingredient_Name)!=NULL){
        return true;
    }
    else{
        return false;
    }
}

/*
  Description: Checks if a recipe with the given name exists.
  Error Cases: None.
  Input arguments: c_Recipe_Name - name of the recipe.
  Return type: bool - true if the recipe exists, false otherwise.
  Memory usage: No additional memory is allocated.
  Big O notation: O(N), where N is the number of recipes.
 */
extern bool IsThereRecipeItemExist(char c_Recipe_Name[]){
    if(getRecipeElementByName(R_dumyRecipeStart.R_next_Recipe,c_Recipe_Name)!=NULL){
        return true;
    }
    else{
        return false;
    }
}

/*
  Description: Restores the amounts of storage items used by a recipe in case of insufficient quantity.
  Error Cases: None.
  Input arguments:  c_Recipe_Name - name of the recipe, 
                    C_end_ptr - end pointer of the connection list, 
                    C_Connection_ptr - pointer to the connection list.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(N), where N is the number of connections.
 */
static void RestoreStorageItemsAmount(char c_Recipe_Name[], Connection* C_end_ptr, Connection *C_Connection_ptr){
    while(strcmp(C_Connection_ptr->c_Recipe_ID,C_end_ptr->c_Recipe_ID)==0 && C_Connection_ptr != NULL){
        if(strcmp(C_Connection_ptr->c_Recipe_ID,getRecipeElementByName(R_dumyRecipeStart.R_next_Recipe,c_Recipe_Name)->c_Recipe_ID)==0){
            getStorageElementByID(S_dumyStorageStart.S_next_Storage, C_Connection_ptr->c_Ingredient_ID)->d_Amount_In_Storage += C_Connection_ptr->d_Amount_For_Recipe;          
        }
        C_Connection_ptr = C_Connection_ptr->C_next_Connection; 
    }
}

/*
  Description: Selects and cooks a recipe by updating storage quantities and creating a log entry.
  Error Cases: Handles insufficient quantity of ingredients.
  Input arguments: c_Recipe_Name - name of the recipe, 
                   C_Connection_ptr - pointer to the connection list, 
                   L_ptr - pointer to the logs list.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(N), where N is the number of connections.
 */
static void SelectAndCookRecipe(char c_Recipe_Name[], Connection *C_Connection_ptr, Logs *L_ptr){
   
    strcpy(R_tmp_Recipe.c_Recipe_ID,getRecipeElementByName(R_dumyRecipeStart.R_next_Recipe,c_Recipe_Name)->c_Recipe_ID);

    while(C_Connection_ptr != NULL ){
        if(strcmp(C_Connection_ptr->c_Recipe_ID,getRecipeElementByName(R_dumyRecipeStart.R_next_Recipe,c_Recipe_Name)->c_Recipe_ID)==0){
           S_tmp_Storage.d_Amount_In_Storage = getStorageElementByID(S_dumyStorageStart.S_next_Storage, C_Connection_ptr->c_Ingredient_ID)->d_Amount_In_Storage;
           if(S_tmp_Storage.d_Amount_In_Storage >= C_Connection_ptr->d_Amount_For_Recipe){
            getStorageElementByID(S_dumyStorageStart.S_next_Storage, C_Connection_ptr->c_Ingredient_ID)->d_Amount_In_Storage -= C_Connection_ptr->d_Amount_For_Recipe;
            UpdateStorageFile(getStorageElementByID(S_dumyStorageStart.S_next_Storage,C_Connection_ptr->c_Ingredient_ID)->c_Ingredient_ID,C_Connection_ptr->d_Amount_For_Recipe);
           }
           else{
            printf("You have not enought amount from \"%s\" to make this recipe.\n",getIngredientElementByID(I_dumyIngredientStart.I_next_Ingredient,C_Connection_ptr->c_Ingredient_ID)->c_Ingredient_Name);
            RestoreStorageItemsAmount(c_Recipe_Name, C_Connection_ptr, C_dumyConnectionStart.C_next_Connection);
           }
        }
        C_Connection_ptr = C_Connection_ptr->C_next_Connection; 
    }
   
    Logs L_tmp_Log;
    getDate(&L_tmp_Log.D_Date_Of_The_Log);
    strcpy(L_tmp_Log.c_ID,R_tmp_Recipe.c_Recipe_ID);
    strcpy(L_tmp_Log.c_Operation_Description,"C");    
    createLogsListItem(&L_tmp_Log,L_ptr);
    WriteLogsToFile(&L_tmp_Log);
 }

/*
  Description: Cooks a recipe by calling the necessary functions.
  Error Cases: Handles insufficient quantity of ingredients.
  Input arguments: c_Recipe_Name - name of the recipe.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(N), where N is the number of connections.
 */
extern void CookRecipe(char c_Recipe_Name[]){
    SelectAndCookRecipe(c_Recipe_Name, C_dumyConnectionStart.C_next_Connection,
                                        L_dumyLogsStart.L_next_Logs);
}

/*
  Description: Suggests recipes that can be made using a specific ingredient.
  Error Cases: None.
  Input arguments: c_Ingredient_Name - name of the ingredient.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(N), where N is the number of connections.
 */
extern void SuggestRecipeByIngredient(char c_Ingredient_Name[]){
    Connection* C_Connection_ptr = C_dumyConnectionStart.C_next_Connection;
    while(C_Connection_ptr != NULL){              
       if(strcmp(C_Connection_ptr->c_Ingredient_ID, getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient,c_Ingredient_Name)->c_Ingredient_ID)==0
            && getStorageElementByID(S_dumyStorageStart.S_next_Storage,C_Connection_ptr->c_Ingredient_ID)->d_Amount_In_Storage >= C_Connection_ptr->d_Amount_For_Recipe){
            printf("%s\n", getRecipeElementByID(R_dumyRecipeStart.R_next_Recipe, C_Connection_ptr->c_Recipe_ID)->c_Recipe_Name);
        }                
        C_Connection_ptr = C_Connection_ptr->C_next_Connection;
    }
}

/*
c
 */
extern void SuggesetRandomRecipe(void){
    Connection* C_Connection_ptr = C_dumyConnectionStart.C_next_Connection;
    while(C_Connection_ptr != NULL){              
       if(rand()%2 == 0
            && getStorageElementByID(S_dumyStorageStart.S_next_Storage,C_Connection_ptr->c_Ingredient_ID)->d_Amount_In_Storage >= C_Connection_ptr->d_Amount_For_Recipe){
            printf("%s\n", getRecipeElementByID(R_dumyRecipeStart.R_next_Recipe, C_Connection_ptr->c_Recipe_ID)->c_Recipe_Name);
        }         
        C_Connection_ptr = C_Connection_ptr->C_next_Connection;
    }
}

/*
  Description: Suggests recipes with ingredients about to expire within a specified number of days.
  Error Cases: None.
  Input arguments: i_Differencial_Day - the number of days within which the ingredients will expire.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(N), where N is the number of storage items.
 */
extern void SuggestRecipeByExpiryDate(int i_Differencial_Day){
    Storage* S_Storage_ptr = S_dumyStorageStart.S_next_Storage;
    int i_ExpDiffDate;

    while(S_Storage_ptr != NULL){              
        i_ExpDiffDate = DateDifferencial(S_Storage_ptr->D_Expiration_date);
        if(i_ExpDiffDate <= i_Differencial_Day && i_ExpDiffDate >=0 && S_Storage_ptr->d_Amount_In_Storage >= getConnectionIngredientElementByID(C_dumyConnectionStart.C_next_Connection, S_Storage_ptr->c_Ingredient_ID)->d_Amount_For_Recipe ){           
           printf("%s\n",getRecipeElementByID(R_dumyRecipeStart.R_next_Recipe, getConnectionIngredientElementByID(C_dumyConnectionStart.C_next_Connection,S_Storage_ptr->c_Ingredient_ID)->c_Recipe_ID)->c_Recipe_Name); 
        }        
        S_Storage_ptr = S_Storage_ptr->S_next_Storage;
    }
}

/*
  Description: Displays the list of logs.
  Error Cases: None.
  Input arguments: None.
  Return type: void.
  Memory usage: No additional memory is allocated.
  Big O notation: O(N), where N is the number of logs.
 */
extern void ViewLog(void){
    listLogsListItems(L_dumyLogsStart.L_next_Logs);
}

/*
  Description: Frees the memory allocated for all lists.
  Error Cases: None.
  Input arguments: None.
  Return type: void.
  Memory usage: Frees the memory allocated for recipes, ingredients, connections, storage, and logs.
  Big O notation: O(N), where N is the total number of elements in all lists.
 */
extern void FreeAll(void){
    freeRecipesList(R_dumyRecipeStart.R_next_Recipe);
    freeIngredientsList(I_dumyIngredientStart.I_next_Ingredient);
    freeConnectionList(C_dumyConnectionStart.C_next_Connection);
    freeStorageList(S_dumyStorageStart.S_next_Storage);
    freeLogsList(L_dumyLogsStart.L_next_Logs);
    debugmalloc_dump();
}