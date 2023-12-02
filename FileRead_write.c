#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"
#include "functions.h"

/*
  Description: Reads ingredient data from the "ingredients.csv" file and creates an ingredient list.
  Error Cases: Exits the program if the file cannot be opened.
  Input arguments: I_ptr - Pointer to the Ingredient list.
  Return type: void
  Memory usage: Allocates memory for temporary Ingredient structures.
  Big O notation: O(n), where n is the number of ingredients in the file.
 */
extern void ReadIngredientFile(Ingredient *I_ptr) {
    FILE* F_file_Ingredients_csv = fopen("ingredients.csv", "r");
    if (F_file_Ingredients_csv == NULL) {
        perror("Failed to open ingredients.csv");
        exit(1);
    }
    Ingredient I_tmpIngredient;
   while(fscanf(F_file_Ingredients_csv, "%[^,],%[^,],%[^\n]\n",
              I_tmpIngredient.c_Ingredient_ID ,
              I_tmpIngredient.c_Ingredient_Name,
              I_tmpIngredient.c_Unit) != EOF ){
        createIngredientListItem(&I_tmpIngredient,I_ptr);
    }
    fclose(F_file_Ingredients_csv);
}

/*
  Description: Reads recipe data from the "recipes.csv" file and creates a recipe list.
  Error Cases: Exits the program if the file cannot be opened.
  Input arguments: R_ptr - Pointer to the Recipe list.
  Return type: void
  Memory usage: Allocates memory for temporary Recipe structures.
  Big O notation: O(n), where n is the number of recipes in the file.
 */
extern void ReadRecipeFile(Recipe *R_ptr) {
    FILE* F_file_Recipe_csv = fopen("recipes.csv", "r");
    if (F_file_Recipe_csv == NULL) {
        perror("Failed to open recipes.csv");
        exit(1);
    }
    Recipe R_tmpRecipe;
   while(fscanf(F_file_Recipe_csv, "%[^,],%[^,],%[^\n]\n",
              R_tmpRecipe.c_Recipe_ID,
              R_tmpRecipe.c_Recipe_Name,
              R_tmpRecipe.c_Recipe_Description) != EOF ){
        createRecipeListItem(&R_tmpRecipe,R_ptr);   
    }
    fclose(F_file_Recipe_csv);
}

/*
  Description: Reads storage data from the "storage.csv" file and creates a storage list.
  Error Cases: Exits the program if the file cannot be opened.
  Input arguments: S_ptr - Pointer to the Storage list.
  Return type: void
  Memory usage: Allocates memory for temporary Recipe structures.
  Big O notation: O(n), where n is the number of storage in the file.
 */
extern void ReadStorageFile(Storage *S_ptr) {
    FILE* F_file_Storage_csv = fopen("storage.csv", "r");
    if (F_file_Storage_csv == NULL) {
        perror("Failed to open storage.csv");
        exit(1);
    }
    Storage S_tmpStorage;
   while(fscanf(F_file_Storage_csv, "%[^,],%lf,%d,%d,%d\n",
              S_tmpStorage.c_Ingredient_ID,
              &S_tmpStorage.d_Amount_In_Storage,
              &S_tmpStorage.D_Expiration_date.i_day,
              &S_tmpStorage.D_Expiration_date.i_month,
              &S_tmpStorage.D_Expiration_date.i_year) != EOF ){
        createStorageListItem(&S_tmpStorage,S_ptr);
    }
    fclose(F_file_Storage_csv);
}

/*
  Description: Reads log data from the "logs.csv" file and creates a log list.
  Error Cases: Exits the program if the file cannot be opened.
  Input arguments: L_ptr - Pointer to the Logs list.
  Return type: void
  Memory usage: Allocates memory for temporary Logs structures.
  Big O notation: O(n), where n is the number of logs in the file.
 */
extern void ReadLogsFile(Logs *L_ptr) {
    FILE* F_file_Logs_csv = fopen("logs.csv", "r");
    if (F_file_Logs_csv == NULL) {
        perror("Failed to open logs.csv");
        exit(1);
    }
    Logs L_tmp_Log;
   while(fscanf(F_file_Logs_csv, "%d,%d,%d,%[^,],%c\n",
              &L_tmp_Log.D_Date_Of_The_Log.i_day,
              &L_tmp_Log.D_Date_Of_The_Log.i_month,
              &L_tmp_Log.D_Date_Of_The_Log.i_year,
              L_tmp_Log.c_ID,
              L_tmp_Log.c_Operation_Description) != EOF ){
        createLogsListItem(&L_tmp_Log,L_ptr);
    }
    fclose(F_file_Logs_csv);
}
/*
  Description: Reads connection data from the "connection.csv" file and creates a connection list.
  Error Cases: Exits the program if the file cannot be opened.
  Input arguments: C_ptr - Pointer to the Connection list.
  Return type: void
  Memory usage: Allocates memory for temporary Connection structures.
  Big O notation: O(n), where n is the number of connections in the file.
 */
extern void ReadConnectionFile(Connection *C_ptr) {
    FILE* F_file_Connection_csv = fopen("connection.csv", "r");
    if (F_file_Connection_csv == NULL) {
        perror("Failed to open logs.csv");
        exit(1);
    }
    Connection C_tmp_Connection;

   while(fscanf(F_file_Connection_csv, "%[^,],%[^,],%lf\n",
            C_tmp_Connection.c_Recipe_ID,
            C_tmp_Connection.c_Ingredient_ID,
            &C_tmp_Connection.d_Amount_For_Recipe) != EOF ){
        createConnectionListItem(&C_tmp_Connection,C_ptr);
    }
    fclose(F_file_Connection_csv);
}

/*
  Description: Writes recipe data to the "recipes.csv" file.
  Error Cases: Exits the program if the file cannot be opened.
  Input arguments: R_Recipe - Pointer to the Recipe structure to be written.
  Return type: void
  Memory usage: No dynamic memory allocation.
  Big O notation: O(1)
 */
extern void WriteRecipeToFile(Recipe *R_Recipe){
    FILE* F_file_Recipe_csv = fopen("recipes.csv", "a");
    if (F_file_Recipe_csv == NULL) {
        perror("Failed to open recipes.csv");
        exit(1);
    }
    fprintf(F_file_Recipe_csv,"%s,%s,%s\n",R_Recipe->c_Recipe_ID,R_Recipe->c_Recipe_Name,R_Recipe->c_Recipe_Description);
    fclose(F_file_Recipe_csv);
}

/*
  Description: Writes ingredient data to the "ingredients.csv" file.
  Error Cases: Exits the program if the file cannot be opened.
  Input arguments: I_Ingredient - Pointer to the Ingredient structure to be written.
  Return type: void
  Memory usage: No dynamic memory allocation.
  Big O notation: O(1)
 */
extern void WriteIngredientToFile(Ingredient *I_Ingredient){
    FILE* F_file_Ingredient_csv = fopen("ingredients.csv", "a");
    if (F_file_Ingredient_csv == NULL) {
        perror("Failed to open ingredients.csv");
        exit(1);
    }
    fprintf(F_file_Ingredient_csv,"%s,%s,%s\n",I_Ingredient->c_Ingredient_ID,I_Ingredient->c_Ingredient_Name,I_Ingredient->c_Unit);
    fclose(F_file_Ingredient_csv);
}

/*
  Description: Writes storage data to the "storage.csv" file.
  Error Cases: Exits the program if the file cannot be opened.
  Input arguments: S_Storage - Pointer to the Storage structure to be written.
  Return type: void
  Memory usage: No dynamic memory allocation.
  Big O notation: O(1)
 */
extern void WriteStorageToFile(Storage *S_Storage){
    FILE* F_file_Storage_csv = fopen("storage.csv", "a");
    if (F_file_Storage_csv == NULL) {
        perror("Failed to open storage.csv");
        exit(1);
    }
    fprintf(F_file_Storage_csv,"%s,%lf,%d,%d,%d\n", S_Storage->c_Ingredient_ID,
                                                    S_Storage->d_Amount_In_Storage,
                                                    S_Storage->D_Expiration_date.i_day,
                                                    S_Storage->D_Expiration_date.i_month,
                                                    S_Storage->D_Expiration_date.i_year);
    fclose(F_file_Storage_csv);
}

/*
  Description: Writes connection data to the "connection.csv" file.
  Error Cases: Exits the program if the file cannot be opened.
  Input arguments: C_Connection - Pointer to the Connection structure to be written.
  Return type: void
  Memory usage: No dynamic memory allocation.
  Big O notation: O(1)
 */
extern void WriteConnenctionToFile(Connection *C_Connection){
    FILE* F_file_Connection_csv = fopen("connection.csv", "a");
    if (F_file_Connection_csv == NULL) {
        perror("Failed to open connection.csv");
        exit(1);
    }
    fprintf(F_file_Connection_csv,"%s,%s,%lf\n",C_Connection->c_Recipe_ID,C_Connection->c_Ingredient_ID,C_Connection->d_Amount_For_Recipe);
    fclose(F_file_Connection_csv);
}

/*
  Description: Writes log data to the "logs.csv" file.
  Error Cases: Exits the program if the file cannot be opened.
  Input arguments: L_Log - Pointer to the Logs structure to be written.
  Return type: void
  Memory usage: No dynamic memory allocation.
  Big O notation: O(1)
 */
extern void WriteLogsToFile(Logs *L_Log){
    FILE* F_file_Logs_csv = fopen("logs.csv", "a");
    if (F_file_Logs_csv == NULL) {
        perror("Failed to open logs.csv");
        exit(1);
    }
    fprintf(F_file_Logs_csv,"%d,%d,%d,%s,%s\n", L_Log->D_Date_Of_The_Log.i_day,
                                                L_Log->D_Date_Of_The_Log.i_month,
                                                L_Log->D_Date_Of_The_Log.i_year,
                                                L_Log->c_ID,
                                                L_Log->c_Operation_Description);
    fclose(F_file_Logs_csv);
}

/*
  Description: Deletes a specified recipe line from the "recipes.csv" file.
  Error Cases: Exits the program if the file cannot be opened.
  Input arguments: R_delete_Recipe - Pointer to the Recipe structure to be deleted.
  Return type: void
  Memory usage: Allocates memory for temporary Recipe structures.
  Big O notation: O(n), where n is the number of recipes in the file.
 */
extern void DeleteLineFromRecipeFile(Recipe *R_delete_Recipe){
    FILE *F_file_originalFile = fopen("recipes.csv", "r");
    FILE *F_file_tempFile = fopen("temp.csv", "a");

    if (F_file_originalFile == NULL || F_file_tempFile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Recipe R_tmpRecipe;

     while(fscanf(F_file_originalFile, "%[^,],%[^,],%[^\n]\n",
              R_tmpRecipe.c_Recipe_ID,
              R_tmpRecipe.c_Recipe_Name,
              R_tmpRecipe.c_Recipe_Description) != EOF ){
   
        if(strcmp(R_tmpRecipe.c_Recipe_ID, R_delete_Recipe->c_Recipe_ID) != 0){
            fprintf(F_file_tempFile,"%s,%s,%s\n",R_tmpRecipe.c_Recipe_ID,R_tmpRecipe.c_Recipe_Name,R_tmpRecipe.c_Recipe_Description);
        }        
    }

    fclose(F_file_originalFile);
    fclose(F_file_tempFile);

    remove("recipes.csv");
    rename("temp.csv","recipes.csv");
    
}

/*
  Description: Update a specified storage line from the "storage.csv" file.
  Error Cases: Exits the program if the file cannot be opened.
  Input arguments:  c_Storage_To_Update - Name of the Storage structure to be updated.
                    d_amount - Amount of the storage item, what need to update it.
  Return type: void
  Memory usage: Allocates memory for temporary Storage structures.
  Big O notation: O(n), where n is the number of storages in the file.
 */
extern void UpdateStorageFile(char c_Storage_To_Update[], double d_amount){
        FILE *F_file_originalFile = fopen("storage.csv", "r");
    FILE *F_file_tempFile = fopen("temp.csv", "a");

    if (F_file_originalFile == NULL || F_file_tempFile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

     Storage S_tmpStorage;

   while(fscanf(F_file_originalFile, "%[^,],%lf,%d,%d,%d\n",
              S_tmpStorage.c_Ingredient_ID,
              &S_tmpStorage.d_Amount_In_Storage,
              &S_tmpStorage.D_Expiration_date.i_day,
              &S_tmpStorage.D_Expiration_date.i_month,
              &S_tmpStorage.D_Expiration_date.i_year) != EOF ){
   
        if(strcmp(S_tmpStorage.c_Ingredient_ID ,c_Storage_To_Update) != 0){
            fprintf(F_file_tempFile,"%s,%lf,%d,%d,%d\n",S_tmpStorage.c_Ingredient_ID,
                                                        S_tmpStorage.d_Amount_In_Storage,
                                                        S_tmpStorage.D_Expiration_date.i_day,
                                                        S_tmpStorage.D_Expiration_date.i_month,
                                                        S_tmpStorage.D_Expiration_date.i_year);
        }
        else{
            fprintf(F_file_tempFile,"%s,%lf,%d,%d,%d\n",S_tmpStorage.c_Ingredient_ID,
                                                        S_tmpStorage.d_Amount_In_Storage - d_amount,
                                                        S_tmpStorage.D_Expiration_date.i_day,
                                                        S_tmpStorage.D_Expiration_date.i_month,
                                                        S_tmpStorage.D_Expiration_date.i_year);

        }
    }

    fclose(F_file_originalFile);
    fclose(F_file_tempFile);

    // Replace the original file with the temporary file
    remove("storage.csv");
    rename("temp.csv","storage.csv");
}

/*
  Description: Delete outdated storage element(s) from the "storage.csv" file.
  Error Cases: Exits the program if the file cannot be opened.
  Input arguments: void
  Return type: void
  Memory usage: Allocates memory for temporary Storage structures.
  Big O notation: O(n), where n is the number of storages in the file.
 */
extern void AutoDeleteStorageItem(void){
            FILE *F_file_originalFile = fopen("storage.csv", "r");
    FILE *F_file_tempFile = fopen("temp.csv", "a");

    if (F_file_originalFile == NULL || F_file_tempFile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

     Storage S_tmpStorage;

   while(fscanf(F_file_originalFile, "%[^,],%lf,%d,%d,%d\n",
              S_tmpStorage.c_Ingredient_ID,
              &S_tmpStorage.d_Amount_In_Storage,
              &S_tmpStorage.D_Expiration_date.i_day,
              &S_tmpStorage.D_Expiration_date.i_month,
              &S_tmpStorage.D_Expiration_date.i_year) != EOF ){
   
        if(DateDifferencial(S_tmpStorage.D_Expiration_date) >= 0 ){
            fprintf(F_file_tempFile,"%s,%lf,%d,%d,%d\n",S_tmpStorage.c_Ingredient_ID,
                                                        S_tmpStorage.d_Amount_In_Storage,
                                                        S_tmpStorage.D_Expiration_date.i_day,
                                                        S_tmpStorage.D_Expiration_date.i_month,
                                                        S_tmpStorage.D_Expiration_date.i_year);
        }
        else{
            continue;
        }
    }

    fclose(F_file_originalFile);
    fclose(F_file_tempFile);

    // Replace the original file with the temporary file
    remove("storage.csv");
    rename("temp.csv","storage.csv");
}