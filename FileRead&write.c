#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"

extern void ReadIngredientFile() {
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

           
    }
    fclose(F_file_Ingredients_csv);
}

extern void ReadRecipeFile() {
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
           
    }
    fclose(F_file_Recipe_csv);
}

extern void ReadStorageFile() {
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
    }
    fclose(F_file_Storage_csv);
}

extern void ReadLogsFile() {
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
    }
    fclose(F_file_Logs_csv);
}

extern void ReadConnectionFile() {
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
    }
    fclose(F_file_Connection_csv);
}



extern void WriteRecipeToFile(Recipe *R_Recipe){
    FILE* F_file_Recipe_csv = fopen("recipes.csv", "a");
    if (F_file_Recipe_csv == NULL) {
        perror("Failed to open recipes.csv");
        exit(1);
    }
    fprintf(F_file_Recipe_csv,"%s,%s,%s\n",R_Recipe->c_Recipe_ID,R_Recipe->c_Recipe_Name,R_Recipe->c_Recipe_Description);
    fclose(F_file_Recipe_csv);
}

extern void WriteIngredientToFile(Ingredient *I_Ingredient){
    FILE* F_file_Ingredient_csv = fopen("ingredients.csv", "a");
    if (F_file_Ingredient_csv == NULL) {
        perror("Failed to open ingredients.csv");
        exit(1);
    }
    fprintf(F_file_Ingredient_csv,"%s,%s,%s\n",I_Ingredient->c_Ingredient_ID,I_Ingredient->c_Ingredient_Name,I_Ingredient->c_Unit);
    fclose(F_file_Ingredient_csv);
}

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

extern void WriteConnenctionToFile(Connection *C_Connection){
    FILE* F_file_Connection_csv = fopen("connection.csv", "a");
    if (F_file_Connection_csv == NULL) {
        perror("Failed to open connection.csv");
        exit(1);
    }
    fprintf(F_file_Connection_csv,"%s,%s,%lf\n",C_Connection->c_Recipe_ID,C_Connection->c_Ingredient_ID,C_Connection->d_Amount_For_Recipe);
    fclose(F_file_Connection_csv);
}

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