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



extern void Init(void){
    srand((unsigned int)time(NULL));
    ReadRecipeFile(&R_dumyRecipeStart);
    ReadIngredientFile(&I_dumyIngredientStart);
    ReadStorageFile(&S_dumyStorageStart);
    ReadConnectionFile(&C_dumyConnectionStart);
    ReadLogsFile(&L_dumyLogsStart);
}

extern char* gen_uuid(void) {
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

static int DateDifferencial(Date D_date){
    Date D_Today; 
    getDate(&D_Today);
    return ((D_date.i_year-D_Today.i_year)*365) + ((D_date.i_month - D_Today.i_month) *30 ) + (D_date.i_day - D_Today.i_day);
}

extern void ViewRecipes(void){
    listRecipeListItems(R_dumyRecipeStart.R_next_Recipe);
}

extern void AddRecipe(char c_Recipe_Name[], char c_Recipe_Description[]){
   
   char c_falseIngredient[4];

    strcpy(R_tmp_Recipe.c_Recipe_ID, gen_uuid());
    strcpy(R_tmp_Recipe.c_Recipe_Name, c_Recipe_Name);
    strcpy(R_tmp_Recipe.c_Recipe_Description, c_Recipe_Description); 
    createRecipeListItem(&R_tmp_Recipe,R_dumyRecipeStart.R_next_Recipe);
    WriteRecipeToFile(&R_tmp_Recipe);

    char c_tmpIngredientName[51];
    char c_tmpUnit[11];  
    int i_NumberOfIngredient=0;
    printf("\nPlease write the number of how many ingredient need to make this recipe:");
    scanf("%d",&i_NumberOfIngredient);
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
                     break;
                }
    
                printf("Please enter the unit of ingredient:");
                scanf("%s",c_tmpUnit);
                if(strlen(c_tmpUnit) < 11){
                    printf("You entered: \"%s\" \n",c_tmpUnit);
                }
                else{
                     printf("Input too long. Please enter up to 10 characters.\n");
                     break;
                }        
                AddIngredient(c_tmpIngredientName,c_tmpUnit);
                
            }
            else if (strcmp("no",c_falseIngredient)==0 || strcmp("n",c_falseIngredient)==0){
                break;
            }
            else{
                printf("Command not found.\n");
                break;
            }
            
        }

        printf("\nThe amount of the ingredient \"%s\":",I_tmp_Ingredienet.c_Ingredient_Name);
        scanf("%lf",&C_tmp_Connection.d_Amount_For_Recipe);

        strcpy(C_tmp_Connection.c_Ingredient_ID, getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient, I_tmp_Ingredienet.c_Ingredient_Name)->c_Ingredient_ID);
        strcpy(C_tmp_Connection.c_Recipe_ID,R_tmp_Recipe.c_Recipe_ID);
        createConnectionListItem( &C_tmp_Connection ,C_dumyConnectionStart.C_next_Connection);
        WriteConnenctionToFile(&C_tmp_Connection);
    }


    getDate(&L_tmp_Log.D_Date_Of_The_Log);
    strcpy(L_tmp_Log.c_ID,R_tmp_Recipe.c_Recipe_ID);
    strcpy(L_tmp_Log.c_Operation_Description,"A");
    WriteLogsToFile(&L_tmp_Log);
    printf("Recipe list was updated\n");

}

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
    }
}

extern void ViewIngredients(void){
    if(I_dumyIngredientStart.c_Ingredient_ID == NULL){
        printf("\nThere are no available Ingredients in the system\n");
    }
    else{
        listIngredientsListItems(I_dumyIngredientStart.I_next_Ingredient);
    }
}

extern void AddIngredient(char c_Inredient_Name[], char c_Ingredient_Unit[]){
    strcpy(I_tmp_Ingredienet.c_Ingredient_ID,gen_uuid());
    strcpy(I_tmp_Ingredienet.c_Ingredient_Name, c_Inredient_Name);
    strcpy(I_tmp_Ingredienet.c_Unit,c_Ingredient_Unit);
    createIngredientListItem(&I_tmp_Ingredienet , I_dumyIngredientStart.I_next_Ingredient);
    WriteIngredientToFile(&I_tmp_Ingredienet);

    getDate(&L_tmp_Log.D_Date_Of_The_Log);
    strcpy(L_tmp_Log.c_ID, getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient,c_Inredient_Name)->c_Ingredient_ID);
    strcpy(L_tmp_Log.c_Operation_Description,"A");
    WriteLogsToFile(&L_tmp_Log);
}

extern void ViewStorage(){
    listStorageListItems(S_dumyStorageStart.S_next_Storage);
}

extern void AddConnection(char c_Recipe_Name[], char c_Ingredient_Name[],double d_amount){
    strcpy(C_tmp_Connection.c_Recipe_ID,getRecipeElementByName(R_dumyRecipeStart.R_next_Recipe,c_Recipe_Name)->c_Recipe_ID);
    strcpy(C_tmp_Connection.c_Ingredient_ID,getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient,c_Ingredient_Name)->c_Ingredient_ID);
    C_tmp_Connection.d_Amount_For_Recipe = d_amount;
    createConnectionListItem(&C_tmp_Connection,C_dumyConnectionStart.C_next_Connection);
    WriteConnenctionToFile(&C_tmp_Connection);
}

extern void AddStorage(char c_Storage_Name[], double amount, Date Exp_Date){
    strcpy(S_tmp_Storage.c_Ingredient_ID,getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient ,c_Storage_Name)->c_Ingredient_ID);
    S_tmp_Storage.d_Amount_In_Storage = amount;
    strcpyDate(Exp_Date,S_tmp_Storage.D_Expiration_date);
    createStorageListItem(&S_tmp_Storage,S_dumyStorageStart.S_next_Storage);
    WriteStorageToFile(&S_tmp_Storage);

    getDate(&L_tmp_Log.D_Date_Of_The_Log);
    strcpy(L_tmp_Log.c_ID, getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient,c_Storage_Name)->c_Ingredient_ID);
    strcpy(L_tmp_Log.c_Operation_Description,"A");
    WriteLogsToFile(&L_tmp_Log);
    
}

extern bool IsThereStorageItemExist(char c_Ingredient_Name[]){
    if(getIngredientElementByName(I_dumyIngredientStart.I_next_Ingredient,c_Ingredient_Name)!=NULL){
        return true;
    }
    else{
        return false;
    }
}

extern bool IsThereRecipeItemExist(char c_Recipe_Name[]){
    if(getRecipeElementByName(R_dumyRecipeStart.R_next_Recipe,c_Recipe_Name)!=NULL){
        return true;
    }
    else{
        return false;
    }
}

static bool IsThisExpired(Storage *S_Storage, int i_Acceptable_DiffDay){
    if(DateDifferencial(S_Storage->D_Expiration_date) >= i_Acceptable_DiffDay){
        return true;
    }
    else{
        return false;
    }  
}

static void RestoreStorageItemsAmount(char c_Recipe_Name[], Connection* C_end_ptr, Connection *C_Connection_ptr){
    while(strcmp(C_Connection_ptr->c_Recipe_ID,C_end_ptr->c_Recipe_ID)==0 && C_Connection_ptr != NULL){
        if(strcmp(C_Connection_ptr->c_Recipe_ID,getRecipeElementByName(R_dumyRecipeStart.R_next_Recipe,c_Recipe_Name)->c_Recipe_ID)==0){
            getStorageElementByID(S_dumyStorageStart.S_next_Storage, C_Connection_ptr->c_Ingredient_ID)->d_Amount_In_Storage += C_Connection_ptr->d_Amount_For_Recipe;          
        }
        C_Connection_ptr = C_Connection_ptr->C_next_Connection; 
    }
}

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

extern void CookRecipe(char c_Recipe_Name[]){
    SelectAndCookRecipe(c_Recipe_Name, C_dumyConnectionStart.C_next_Connection,
                                        L_dumyLogsStart.L_next_Logs);
}


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

extern void SuggestRecipeByExpiryDate(void){
    Storage* S_Storage_ptr = S_dumyStorageStart.S_next_Storage;
    int i_ExpDiffDate;

    while(S_Storage_ptr != NULL){              
        i_ExpDiffDate = DateDifferencial(S_Storage_ptr->D_Expiration_date);
        if(i_ExpDiffDate < 3 && i_ExpDiffDate >0 && S_Storage_ptr->d_Amount_In_Storage >= getConnectionIngredientElementByID(C_dumyConnectionStart.C_next_Connection, S_Storage_ptr->c_Ingredient_ID)->d_Amount_For_Recipe ){
           printf("%s\n",getRecipeElementByID(R_dumyRecipeStart.R_next_Recipe, getConnectionIngredientElementByID(C_dumyConnectionStart.C_next_Connection,S_Storage_ptr->c_Ingredient_ID)->c_Recipe_ID)->c_Recipe_Name); 
        }
        S_Storage_ptr = S_Storage_ptr->S_next_Storage;
    }
}

extern void ViewLog(void){
    listLogsListItems(L_dumyLogsStart.L_next_Logs);
}


extern void FreeAll(void){
    freeRecipesList(R_dumyRecipeStart.R_next_Recipe);
    freeIngredientsList(I_dumyIngredientStart.I_next_Ingredient);
    freeConnectionList(C_dumyConnectionStart.C_next_Connection);
    freeStorageList(S_dumyStorageStart.S_next_Storage);
    freeLogsList(L_dumyLogsStart.L_next_Logs);
    debugmalloc_dump();
}