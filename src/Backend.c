#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"
#include "functions.h"
#include <time.h>

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

extern void CookRecipe(char c_Recipe_Name[],Recipe *R_Recipe, Storage *S_Storage, Connection *C_Connection, Logs *L_ptr){
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