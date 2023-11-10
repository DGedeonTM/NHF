#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Date{
    int i_year;
    int i_month;
    int i_day;
}Date;

typedef struct Recipe{
    char c_Recipe_ID[37];
    char c_Recipe_Name[51];
    char c_Recipe_Description[5001];
    struct Recipe * R_next_Recipe;
}Recipe;

typedef struct Ingredient{
    char c_Ingredient_ID[37];
    char c_Ingredient_Name[51];
    char c_Unit[11];
    struct Ingredient * I_next_Ingredient;
}Ingredient;

typedef struct Storage{
    char c_Ingredient_ID[37];
    double d_Amount_In_Storage;
    Date D_Expiration_date;
    struct Storage * S_next_Storage;
}Storage;

typedef struct Connection{
    char c_Recipe_ID[37];
    char c_Ingredient_ID[37];
    double d_Amount_For_Recipe;
    struct Connection * C_next_Connection;
}Connection;

typedef struct Logs{
    Date D_Date_Of_The_Log;
    char c_ID[37];
    char c_Operation_Description[2];
    struct Logs * L_next_Logs;
}Logs;


#endif