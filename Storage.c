#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"
/*
  Description: Creates a new Storage list item and appends it to the end of the list.
  Error Cases: Exits the program if memory allocation fails.
  Input arguments: S_StoredItemInStorage - Pointer to the Storage structure to be added.
                   S_ptr - Pointer to the head of the Storage list.
  Return type: void
  Memory usage: Allocates memory for a new Storage structure.
  Big O notation: O(n), where n is the number of elements in the Storage list.
 */
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

/*
  Description: Deletes a Storage list item with a specified ingredient ID.
  Error Cases: None.
  Input arguments: S_Storage - Pointer to the head of the Storage list.
                   c_searchedID - Ingredient ID to search for and delete.
  Return type: void
  Memory usage: Frees memory for the deleted Storage structure.
  Big O notation: O(n), where n is the number of elements in the Storage list.
 */
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

/*
  Description: Lists the amount in storage for each Storage list item.
  Error Cases: None.
  Input arguments: S_Storage - Pointer to the head of the Storage list.
  Return type: void
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Storage list.
 */
extern void listStorageListItems(Storage *S_Storage){
    Storage *S_tmp_ptr = S_Storage;
    while(S_tmp_ptr != NULL){
        printf("%lf\n", S_tmp_ptr->d_Amount_In_Storage);
        S_tmp_ptr = S_tmp_ptr->S_next_Storage;
    }
}


/*
  Description: Frees the memory allocated for the entire Storage list.
  Error Cases: None.
  Input arguments: S_ptr - Pointer to the head of the Storage list.
  Return type: void
  Memory usage: Frees memory for all Storage structures in the list.
  Big O notation: O(n), where n is the number of elements in the Storage list.
 */
extern void freeStorageList(Storage *S_ptr){
    Storage* S_tmp_ptr = S_ptr;

    while (S_ptr != NULL) {
        S_tmp_ptr = S_ptr->S_next_Storage;
        free(S_ptr);
        S_ptr = S_tmp_ptr;
    }
}

/*
  Description: Retrieves a Storage list item with a specified ingredient ID.
  Error Cases: None.
  Input arguments: S_Storage - Pointer to the head of the Storage list.
                   c_searchedID - Ingredient ID to search for.
  Return type: Pointer to the found Storage structure or NULL if not found.
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Storage list.
 */
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
