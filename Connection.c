#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"

/*
  Description: Creates a new Connection list item and appends it to the end of the list.
  Error Cases: Exits the program if memory allocation fails.
  Input arguments: C_Connection - Pointer to the Connection structure to be added.
                   C_ptr - Pointer to the head of the Connection list.
  Return type: void
  Memory usage: Allocates memory for a new Connection structure.
  Big O notation: O(n), where n is the number of elements in the Connection list.
 */
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

/*
  Description: Counts the number of Connection list items with a specified recipe ID.
  Error Cases: None.
  Input arguments: C_Connection - Pointer to the head of the Connection list.
                   c_searchedID - Recipe ID to search for.
  Return type: int - Number of Connection items with the specified recipe ID.
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Connection list.
 */
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

/*
  Description: Deletes Connection list items with a specified recipe ID.
  Error Cases: None.
  Input arguments: C_Connection - Pointer to the head of the Connection list.
                   c_searchedID - Recipe ID to search for and delete.
  Return type: void
  Memory usage: Frees memory for the deleted Connection structures.
  Big O notation: O(n^2), where n is the number of elements in the Connection list.
 */
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

/*
  Description: Lists the amounts for each Connection list item.
  Error Cases: None.
  Input arguments: C_Connection - Pointer to the head of the Connection list.
  Return type: void
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Connection list.
 */
extern void listConnectionListItems(Connection *C_Connection){
    Connection *C_tmp_ptr = C_Connection;
    while(C_tmp_ptr != NULL){
        printf("%lf\n",C_tmp_ptr->d_Amount_For_Recipe);
        C_tmp_ptr = C_tmp_ptr->C_next_Connection ;
    }
}

/*
  Description: Frees the memory allocated for the entire Connection list.
  Error Cases: None.
  Input arguments: C_ptr - Pointer to the head of the Connection list.
  Return type: void
  Memory usage: Frees memory for all Connection structures in the list.
  Big O notation: O(n), where n is the number of elements in the Connection list.
 */
extern void freeConnectionList(Connection *C_ptr){
    Connection* C_tmp_ptr = C_ptr;
    while (C_ptr != NULL) {
        C_tmp_ptr = C_ptr->C_next_Connection;
        free(C_ptr);
        C_ptr = C_tmp_ptr;
    }
}

/*
  Description: Retrieves a Connection list item with a specified recipe ID.
  Error Cases: None.
  Input arguments: C_Connection - Pointer to the head of the Connection list.
                   c_searchedID - Recipe ID to search for.
  Return type: Pointer to the found Connection structure or NULL if not found.
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Connection list.
 */
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

/*
  Description: Retrieves a Connection list item with a specified ingredient ID.
  Error Cases: None.
  Input arguments: C_Connection - Pointer to the head of the Connection list.
                   c_searchedID - Ingredient ID to search for.
  Return type: Pointer to the found Connection structure or NULL if not found.
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Connection list.
 */
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