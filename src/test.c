#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"
#include "functions.h"



extern int main(void){

    Recipe R_dumyRecipeStart;
    Ingredient I_dumyIngredientStart;
    Storage S_dumyStorageStart;
    Connection C_dumyConnectionStart;
    C_dumyConnectionStart.C_next_Connection = NULL;
    Logs L_dumyLogsStart;

    Recipe R ;
    strcpy(R.c_Recipe_ID, gen_uuid());
    strcpy(R.c_Recipe_Name, "fav kaja");
    strcpy(R.c_Recipe_Description, gen_uuid()); 
    createRecipeListItem( &R ,&R_dumyRecipeStart);    
    strcpy(R.c_Recipe_ID, gen_uuid());
    strcpy(R.c_Recipe_Name, "UwU");
    strcpy(R.c_Recipe_Description, gen_uuid());
    createRecipeListItem( &R ,&R_dumyRecipeStart);
    listRecipeListItems(R_dumyRecipeStart.R_next_Recipe);
    //printf("search food: %s\n",getRecipeElementByID(R_dumyRecipeStart.R_next_Recipe,R.c_Recipe_ID)->c_Recipe_Name);
   // deleteRecipeListItem(&R_dumyRecipeStart,R.c_Recipe_ID);
    listRecipeListItems(R_dumyRecipeStart.R_next_Recipe);
   // freeRecipesList(R_dumyRecipeStart.R_next_Recipe);

    Ingredient I;
    strcpy(I.c_Ingredient_ID,gen_uuid());
    strcpy(I.c_Ingredient_Name, "vuti");
    strcpy(I.c_Unit,"boop");
    createIngredientListItem(&I , &I_dumyIngredientStart);
    strcpy(I.c_Ingredient_ID,gen_uuid());
    strcpy(I.c_Ingredient_Name, "nyami");
    strcpy(I.c_Unit,"nyaw");
    createIngredientListItem(&I , &I_dumyIngredientStart);
    listIngredientsListItems(I_dumyIngredientStart.I_next_Ingredient);
    printf("Searched ingredient: %s\n",getIngredientElementByID(I_dumyIngredientStart.I_next_Ingredient,I.c_Ingredient_ID)->c_Ingredient_Name);
    //deleteIngredientListItem(&I_dumyIngredientStart,I.c_Ingredient_ID);
    listIngredientsListItems(I_dumyIngredientStart.I_next_Ingredient);
    //freeIngredientsList(I_dumyIngredientStart.I_next_Ingredient);

printf("----------------------\n");
    Storage S;
    strcpy(S.c_Ingredient_ID,I.c_Ingredient_ID);
    S.d_Amount_In_Storage = 42;
   createStorageListItem(&S,&S_dumyStorageStart);

   listStorageListItems(S_dumyStorageStart.S_next_Storage);
   printf("amount in storage: %lf\n",getStorageElementByID(S_dumyStorageStart.S_next_Storage,S.c_Ingredient_ID)->d_Amount_In_Storage);
  // deleteStorageListItem(&S_dumyStorageStart,S.c_Ingredient_ID);
   listStorageListItems(S_dumyStorageStart.S_next_Storage);
   //freeStorageList(S_dumyStorageStart.S_next_Storage);

    Logs L;
    L.D_Date_Of_The_Log.i_day = 3;
    L.D_Date_Of_The_Log.i_month = 11;
    L.D_Date_Of_The_Log.i_year = 2023;
    strcpy(L.c_ID, gen_uuid());
    strcpy(L.c_Operation_Description,"C");

    createLogsListItem(&L,&L_dumyLogsStart);

    L.D_Date_Of_The_Log.i_day = 4;
    L.D_Date_Of_The_Log.i_month = 11;
    L.D_Date_Of_The_Log.i_year = 2023;
    strcpy(L.c_ID, gen_uuid());
    strcpy(L.c_Operation_Description,"A");

    createLogsListItem(&L,&L_dumyLogsStart);

    listLogsListItems(L_dumyLogsStart.L_next_Logs);
    //printf("Action: %s\n",getLogElementByID(L_dumyLogsStart.L_next_Logs,L.c_ID)->c_Operation_Description);
    //deleteLogListItem(&L_dumyLogsStart,L.c_ID);
    listLogsListItems(L_dumyLogsStart.L_next_Logs);
   // freeLogsList(L_dumyLogsStart.L_next_Logs);

    Connection C;
    strcpy(C.c_Recipe_ID, gen_uuid());
    strcpy(C.c_Ingredient_ID, gen_uuid());
    C.d_Amount_For_Recipe = 21;
    createConnectionListItem(&C, &C_dumyConnectionStart);
    strcpy(C.c_Ingredient_ID, gen_uuid());
    C.d_Amount_For_Recipe = 2;
    createConnectionListItem(&C,&C_dumyConnectionStart);
    strcpy(C.c_Recipe_ID, gen_uuid());
    strcpy(C.c_Ingredient_ID, gen_uuid());
    C.d_Amount_For_Recipe = 76;
    createConnectionListItem(&C,&C_dumyConnectionStart);
    strcpy(C.c_Ingredient_ID, gen_uuid());
    C.d_Amount_For_Recipe = 88;   
    createConnectionListItem(&C,&C_dumyConnectionStart);
    listConnectionListItems(C_dumyConnectionStart.C_next_Connection);
    printf("----------------------------------\n");
    //deleteConnectionListItem(&C_dumyConnectionStart,C.c_Recipe_ID);
   // listConnectionListItems(C_dumyConnectionStart.C_next_Connection);
 //   freeConnectionList(C_dumyConnectionStart.C_next_Connection);


  // ReadIngredientFile();
   //ReadRecipeFile();
   //ReadStorageFile();

    printf("search food: %s\n",getRecipeElementByName(R_dumyRecipeStart.R_next_Recipe,"UwU")->c_Recipe_Name);


    CookRecipe("UwU",R_dumyRecipeStart.R_next_Recipe,
                     S_dumyStorageStart.S_next_Storage,
                     &C_dumyConnectionStart,
                     &L_dumyLogsStart);



    freeConnectionList(C_dumyConnectionStart.C_next_Connection);
    freeRecipesList(R_dumyRecipeStart.R_next_Recipe);
    freeLogsList(L_dumyLogsStart.L_next_Logs);
    freeStorageList(S_dumyStorageStart.S_next_Storage);
    freeIngredientsList(I_dumyIngredientStart.I_next_Ingredient);



    debugmalloc_dump();

    return 0;
}