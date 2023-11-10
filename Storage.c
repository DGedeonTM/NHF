#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"

extern void createStorageListItem(Storage * S_StoredItemInStorage, Storage *S_ptr) {
    while (S_ptr->S_next_Storage != NULL){
        S_ptr = S_ptr->S_next_Storage;
    }    

    Storage* S_tmp_StoredItemInStorage = (Storage*)malloc(sizeof(Storage));
    if (S_tmp_StoredItemInStorage == NULL) {
        perror("Failed to allocate memory for Ingredients");
        exit(1);  // Handle the error as needed
    }
    S_tmp_StoredItemInStorage->S_next_Storage = NULL;
    strcpy(S_tmp_StoredItemInStorage->c_Ingredient_ID,S_StoredItemInStorage->c_Ingredient_ID);
    S_tmp_StoredItemInStorage->d_Amount_In_Storage = S_StoredItemInStorage->d_Amount_In_Storage;
    S_tmp_StoredItemInStorage->D_Expiration_date.i_day = S_StoredItemInStorage->D_Expiration_date.i_day;
    S_tmp_StoredItemInStorage->D_Expiration_date.i_month = S_StoredItemInStorage->D_Expiration_date.i_month;
    S_tmp_StoredItemInStorage->D_Expiration_date.i_year = S_StoredItemInStorage->D_Expiration_date.i_year;

    S_ptr->S_next_Storage = S_tmp_StoredItemInStorage;
    S_ptr = S_ptr->S_next_Storage;
    
}

extern void deleteStorageListItem(Storage *S_Storage, char c_searchedID[]){
    Storage *S_tmp_ptr = S_Storage->S_next_Storage;
    Storage *S_behind_ptr = S_Storage;

    while(S_tmp_ptr !=NULL){
        if(strcmp(S_tmp_ptr->c_Ingredient_ID,c_searchedID)==0){
            S_behind_ptr->S_next_Storage = S_tmp_ptr->S_next_Storage;
            free(S_tmp_ptr);
            break;
        }
        S_tmp_ptr = S_tmp_ptr->S_next_Storage;
        S_behind_ptr = S_behind_ptr->S_next_Storage;
    }
}

extern void listStorageListItems(Storage *S_Storage){
    Storage *S_tmp_ptr = S_Storage;
    while(S_tmp_ptr != NULL){
        printf("%lf\n", S_tmp_ptr->d_Amount_In_Storage);
        S_tmp_ptr = S_tmp_ptr->S_next_Storage;
    }
}

extern void freeStorageList(Storage *S_ptr){
    Storage* S_tmp_ptr = S_ptr;

    while (S_ptr != NULL) {
        S_tmp_ptr = S_ptr->S_next_Storage;
        free(S_ptr);
        S_ptr = S_tmp_ptr;
    }
}

extern Storage* getStorageElementByID(Storage *S_Storage, char c_searchedID[]){
    Storage *S_tmp_ptr = S_Storage;
    while(S_tmp_ptr !=NULL){
        if(strcmp(S_tmp_ptr->c_Ingredient_ID,c_searchedID)==0){
            return S_tmp_ptr;
        }
        S_tmp_ptr = S_tmp_ptr->S_next_Storage;
    }
    return NULL;
}
