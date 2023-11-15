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
   // C_dumyConnectionStart.C_next_Connection = NULL;
    Logs L_dumyLogsStart;

    Recipe R_tmp_Recipe;
    Ingredient I_tmp_Ingredient;
    Storage S_tmp_Storage;
    Connection C_tmp_Connection;
    Logs L_tmp_Log;


extern void Init(void){
    ReadRecipeFile(&R_dumyRecipeStart);
    ReadIngredientFile(&I_dumyIngredientStart);
    ReadStorageFile(&S_dumyStorageStart);
    ReadConnectionFile();
    ReadLogsFile(&L_dumyLogsStart);
}

extern char* gen_uuid() {
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

static void getDate(Date *D_tmp_Date){
    time_t currentTime;
    time(&currentTime);
    struct tm* localTime = localtime(&currentTime);    
    D_tmp_Date->i_day = localTime->tm_mday;
    D_tmp_Date->i_month = localTime->tm_mon +1;
    D_tmp_Date->i_year = localTime->tm_year + 1900;
}

static void strcpyDate(Date D_from, Date D_to){
    D_to.i_day = D_from.i_day;
    D_to.i_month = D_from.i_month;
    D_to.i_year = D_from.i_year;
}

extern void ViewRecipes(void){
    if(R_dumyRecipeStart.R_next_Recipe == NULL){
        printf("\nThere are no available Recipes in the system\n");
    }
    else{
        listRecipeListItems(R_dumyRecipeStart.R_next_Recipe);
    }
}

extern void AddRecipe(char c_Recipe_Name[], char c_Recipe_Description[]){
    strcpy(R_tmp_Recipe.c_Recipe_ID, gen_uuid());
    strcpy(R_tmp_Recipe.c_Recipe_Name, c_Recipe_Name);
    strcpy(R_tmp_Recipe.c_Recipe_Description, c_Recipe_Description); 
    createRecipeListItem(&R_tmp_Recipe,&R_dumyRecipeStart);

    strcpy(L_tmp_Log.c_ID,R_tmp_Recipe.c_Recipe_ID);
    strcpy(L_tmp_Log.c_Operation_Description,"A");
    getDate(&L_tmp_Log.D_Date_Of_The_Log);
    createLogsListItem(&L_tmp_Log,L_dumyLogsStart.L_next_Logs);
    WriteRecipeToFile(&R_tmp_Recipe);
    WriteLogsToFile(&L_tmp_Log);
}

extern void DeleteRecipe(char c_Recipe_Name[]){
    R_tmp_Recipe = getRecipeElementByName(R_dumyRecipeStart.R_next_Recipe,c_Recipe_Name);
    if(R_tmp_Recipe == NULL){
        printf("\nRecipe does not extist\n");
    }
    else{
        strcpy(L_tmp_Log.c_ID,R_tmp_Recipe.c_Recipe_ID);
        strcpy(L_tmp_Log.c_Operation_Description,"D");
        getDate(&L_tmp_Log.D_Date_Of_The_Log);
        deleteRecipeListItem(&R_dumyRecipeStart.R_next_Recipe,R_tmp_Recipe->c_Recipe_ID);
        createLogsListItem(&L_tmp_Log,L_dumyLogsStart.L_next_Logs);
        WriteLogsToFile(&L_tmp_Log);
    }
}

extern ViewIngredients(void){
    if(I_dumyIngredientStart.c_Ingredient_ID == NULL){
        printf("\nThere are no available Ingredients in the system\n");
    }
    else{
        listIngredientsListItems(I_dumyIngredientStart.I_next_Ingredient);
    }
}

extern void AddIngredient(char c_Ingredient_Name[], char c_Ingredient_Unit[]){
    strcpy(I_tmp_Ingredient.c_Ingredient_ID,gen_uuid());
    strcpy(I_tmp_Ingredient.c_Ingredient_Name, c_Ingredient_Name);
    strcpy(I_tmp_Ingredient.c_Unit,c_Ingredient_Unit);
    createIngredientListItem(&I_tmp_Ingredient , &I_dumyIngredientStart);

    strcpy(L_tmp_Log.c_ID,I_tmp_Ingredient.c_Ingredient_ID);
    strcpy(L_tmp_Log.c_Operation_Description,"A");
    getDate(&L_tmp_Log.D_Date_Of_The_Log);
    createLogsListItem(&L_tmp_Log,L_dumyLogsStart.L_next_Logs);
    WriteIngredientToFile(&I_tmp_Ingredient);
    WriteLogsToFile(&L_tmp_Log);

}

extern void ViewStorage(void){
    if(S_dumyStorageStart.S_next_Storage == NULL){
        printf("\nThere are no available Storage items in the system\n");
    }
    else{
        listStorageListItems(S_dumyStorageStart.S_next_Storage);
    }
}

extern void AddStorage(char c_Storage_Name[], double amount, Date Exp_Date){
    Storage *S_tmpCompareStorage = getStorageElementByID(S_dumyStorageStart.S_next_Storage, getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient ,c_Storage_Name)->c_Ingredient_ID);
     strcpy(S_tmp_Storage.c_Ingredient_ID,S_tmpCompareStorage->c_Ingredient_ID);
        S_tmp_Storage.d_Amount_In_Storage = amount;
    strcpyDate(Exp_Date,S_tmp_Storage.D_Expiration_date);
        strcpy(L_tmp_Log.c_ID,S_tmpCompareStorage->c_Ingredient_ID);
        strcpy(L_tmp_Log.c_Operation_Description,"A");
        getDate(&L_tmp_Log.D_Date_Of_The_Log);

    if(S_tmpCompareStorage != NULL && S_tmpCompareStorage->D_Expiration_date.i_day == Exp_Date.i_day &&
                                    S_tmpCompareStorage->D_Expiration_date.i_month == Exp_Date.i_month &&
                                    S_tmpCompareStorage->D_Expiration_date.i_year == Exp_Date.i_year){
        S_tmpCompareStorage->d_Amount_In_Storage += amount;
        ReplaceLineInStorageFile(&S_tmpCompareStorage);
    }
    else{
        createStorageListItem(&S_tmp_Storage ,&S_dumyStorageStart);
        createLogsListItem(&L_tmp_Log,L_dumyLogsStart.L_next_Logs);
        WriteStorageToFile(&S_tmp_Storage);
        WriteLogsToFile(&L_tmp_Log);
    }
}
extern bool IsThereStorageItemExist(char c_Ingredient_Name[]){
    if(getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient ,c_Ingredient_Name)!=NULL){
        return true;
    }
    else{
        return false;
    }
}

extern void CookRecipe(char c_Recipe_Name[]){
    SelectAndCookRecipe(c_Recipe_Name,  R_dumyRecipeStart.R_next_Recipe,
                                        S_dumyStorageStart.S_next_Storage,
                                        C_dumyConnectionStart.C_next_Connection,
                                        L_dumyLogsStart.L_next_Logs);
}

extern void SelectAndCookRecipe(char c_Recipe_Name[],Recipe *R_Recipe, Storage *S_Storage, Connection *C_Connection, Logs *L_ptr){
    Recipe *R_tmp_Recipe = getRecipeElementByName(R_Recipe,c_Recipe_Name);
    if(R_tmp_Recipe == NULL){
        printf("Searched \"%s\" is not found\n",c_Recipe_Name);
         
    }
    else{

    for(int i =0; i < numbersOfSeachedConnectionItem(C_Connection, R_tmp_Recipe->c_Recipe_ID);i++){
        getStorageElementByID(S_Storage,getConnectionRecipeElementByID(C_Connection,R_tmp_Recipe->c_Recipe_ID)->c_Ingredient_ID)->d_Amount_In_Storage -= C_Connection->d_Amount_For_Recipe;
    }
    Logs L_tmp_Log;
    getDate(&L_tmp_Log.D_Date_Of_The_Log);
    strcpy(L_tmp_Log.c_ID,R_tmp_Recipe->c_Recipe_ID);
    strcpy(L_tmp_Log.c_Operation_Description,"C");    
    createLogsListItem(&L_tmp_Log,L_ptr);
    WriteLogsToFile(&L_tmp_Log);
    }

}

extern void SuggestRndRecipe(Storage *S_Storage_ptr){
    while(S_Storage_ptr != NULL && S_Storage_ptr->d_Amount_In_Storage > 0){
        if(rand()%2 == 0){
            printf("Boop");
            //printf("%s\n",getConnectionRecipeElementByID(getConnectionIngredientElementByID(C_dumyConnectionStart.C_next_Connection,S_Storage_ptr->c_Ingredient_ID).c_Recipe_ID).c_Recipe_Name);
        }
        S_Storage_ptr = S_Storage_ptr->S_next_Storage;
    }
}

extern void ViewLogs(void){
    if(L_dumyLogsStart.L_next_Logs == NULL){
        printf("\nThere are no available Logs in the system\n");
    }
    else{
        listLogsListItems(L_dumyLogsStart.L_next_Logs);
    }
}

extern void FreeAll(void){
    freeRecipesList(R_dumyRecipeStart.R_next_Recipe);
    freeIngredientsList(I_dumyIngredientStart.I_next_Ingredient);
    freeStorageList(S_dumyStorageStart.S_next_Storage);
    freeConnectionList(C_dumyConnectionStart.C_next_Connection);
    freeLogsList(L_dumyLogsStart.L_next_Logs);
    debugmalloc_dump();
}
