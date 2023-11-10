#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"


extern void createConnectionListItem(Connection * C_Connection, Connection * C_ptr){
    while(C_ptr->C_next_Connection != NULL){
        C_ptr = C_ptr->C_next_Connection;
    }
       
    Connection* C_tmpConnection = (Connection*)malloc(sizeof(Connection));
    if (C_tmpConnection == NULL) {
        perror("Failed to allocate memory for Ingredients");
        exit(1);  // Handle the error as needed
    }   
    C_tmpConnection->C_next_Connection = NULL;
    strcpy(C_tmpConnection->c_Recipe_ID,C_Connection->c_Recipe_ID);
    strcpy(C_tmpConnection->c_Ingredient_ID,C_Connection->c_Ingredient_ID);
    C_tmpConnection->d_Amount_For_Recipe = C_Connection->d_Amount_For_Recipe;
    C_ptr->C_next_Connection = C_tmpConnection;
    C_ptr = C_ptr->C_next_Connection;
}


extern int numbersOfSeachedConnectionItem(Connection *C_Connection, char c_searchedID[]){
    int i_n;
    Connection *C_tmp_ptr = C_Connection;
    while(C_tmp_ptr != NULL){
        if(strcmp(C_tmp_ptr->c_Recipe_ID,c_searchedID)==0){
            i_n++;
        }
        C_tmp_ptr = C_tmp_ptr->C_next_Connection ;
    }
    return i_n;
}

extern void deleteConnectionListItem(Connection *C_Connection, char c_searchedID[] ){
    Connection *C_tmp_ptr = C_Connection->C_next_Connection;
    Connection *C_behind_ptr = C_Connection;
    
    for(int i = 0; i< numbersOfSeachedConnectionItem(C_tmp_ptr,c_searchedID); i++){
        while(C_tmp_ptr != NULL){
        if(strcmp(C_tmp_ptr->c_Recipe_ID,c_searchedID)==0){
            C_behind_ptr->C_next_Connection = C_tmp_ptr->C_next_Connection;
            free(C_tmp_ptr);   
            break;         
        }        
        C_tmp_ptr = C_tmp_ptr->C_next_Connection;
        C_behind_ptr = C_behind_ptr->C_next_Connection;
        }
        C_tmp_ptr = C_Connection->C_next_Connection;
        C_behind_ptr = C_Connection;
    }
    
}

extern void listConnectionListItems(Connection *C_Connection){
    Connection *C_tmp_ptr = C_Connection;
    while(C_tmp_ptr != NULL){
        printf("%lf\n",C_tmp_ptr->d_Amount_For_Recipe);
        C_tmp_ptr = C_tmp_ptr->C_next_Connection ;
    }
}

extern void freeConnectionList(Connection *C_ptr){
    Connection* C_tmp_ptr = C_ptr;
    while (C_ptr != NULL) {
        C_tmp_ptr = C_ptr->C_next_Connection;
        free(C_ptr);
        C_ptr = C_tmp_ptr;
    }
}

extern Connection* getConnectionRecipeElementByID(Connection *C_Connection, char c_searchedID[] ){
    Connection *C_tmp_ptr = C_Connection;
    while(C_tmp_ptr != NULL){
        if(strcmp(C_tmp_ptr->c_Recipe_ID,c_searchedID)==0){
            return C_tmp_ptr;           
        }
        C_tmp_ptr = C_tmp_ptr->C_next_Connection;
    }
    return NULL;
}

extern Connection* getConnectionIngredientElementByID(Connection *C_Connection, char c_searchedID[] ){
    Connection *C_tmp_ptr = C_Connection;
    while(C_tmp_ptr != NULL){
        if(strcmp(C_tmp_ptr->c_Ingredient_ID,c_searchedID)==0){
            return C_tmp_ptr;           
        }
        C_tmp_ptr = C_tmp_ptr->C_next_Connection;
    }
    return NULL;
}