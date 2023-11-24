#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "structs.h"
#include "functions.h"

/*
  Description: Creates a new Logs list item and appends it to the end of the list.
  Error Cases: Exits the program if memory allocation fails.
  Input arguments: L_Log - Pointer to the Logs structure to be added.
                   L_ptr - Pointer to the head of the Logs list.
  Return type: void
  Memory usage: Allocates memory for a new Logs structure.
  Big O notation: O(n), where n is the number of elements in the Logs list.
 */
extern void createLogsListItem(Logs * L_Log, Logs *L_ptr){
    while(L_ptr->L_next_Logs != NULL){
        L_ptr =L_ptr->L_next_Logs;
    }

    Logs* L_tmpLog = (Logs*)malloc(sizeof(Logs));
    if (L_tmpLog == NULL) {
        perror("Failed to allocate memory for Ingredients");
        exit(1);  // Handle the error as needed
    }
    L_tmpLog->L_next_Logs = NULL;
    strcpy(L_tmpLog->c_ID,L_Log->c_ID);
    strcpy(L_tmpLog->c_Operation_Description,L_Log->c_Operation_Description);
    L_tmpLog->D_Date_Of_The_Log.i_day = L_Log->D_Date_Of_The_Log.i_day;
    L_tmpLog->D_Date_Of_The_Log.i_month = L_Log->D_Date_Of_The_Log.i_month;
    L_tmpLog->D_Date_Of_The_Log.i_year = L_Log->D_Date_Of_The_Log.i_year;

    L_ptr->L_next_Logs = L_tmpLog;
    L_ptr = L_ptr->L_next_Logs;
}

/*
  Description: Deletes a Logs list item with a specified log ID.
  Error Cases: None.
  Input arguments: L_Log - Pointer to the head of the Logs list.
                   c_searchedID - Log ID to search for and delete.
  Return type: void
  Memory usage: Frees memory for the deleted Logs structure.
  Big O notation: O(n), where n is the number of elements in the Logs list.
 */
extern void deleteLogListItem(Logs *L_Log, char c_searchedID[] ){
    Logs *L_tmp_ptr = L_Log->L_next_Logs;
    Logs *L_behind_ptr = L_Log;

    while(L_tmp_ptr != NULL){
        if(strcmp(L_tmp_ptr->c_ID,c_searchedID)==0){
            L_behind_ptr->L_next_Logs = L_tmp_ptr->L_next_Logs;
            free(L_tmp_ptr);
            break;
        }
        L_tmp_ptr = L_tmp_ptr->L_next_Logs;
        L_behind_ptr = L_behind_ptr->L_next_Logs;
    }
}

/*
  Description: Lists the operation descriptions for each Logs list item.
  Error Cases: None.
  Input arguments: L_Log - Pointer to the head of the Logs list.
  Return type: void
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Logs list.
 */
extern void listLogsListItems(Logs *L_Log){
    Logs *L_tmp_ptr = L_Log;
    while(L_tmp_ptr != NULL){
        printf("%s\n",L_tmp_ptr->c_Operation_Description);
        L_tmp_ptr = L_tmp_ptr->L_next_Logs;
    }
}

/*
  Description: Frees the memory allocated for the entire Logs list.
  Error Cases: None.
  Input arguments: L_ptr - Pointer to the head of the Logs list.
  Return type: void
  Memory usage: Frees memory for all Logs structures in the list.
  Big O notation: O(n), where n is the number of elements in the Logs list.
 */
extern void freeLogsList(Logs *L_ptr){
     Logs *L_tmp_ptr = L_ptr;
    while(L_ptr != NULL){
        L_tmp_ptr = L_ptr->L_next_Logs;
        free(L_ptr);
        L_ptr = L_tmp_ptr;
    }
}

/*
  Description: Retrieves a Logs list item with a specified log ID.
  Error Cases: None.
  Input arguments: L_Log - Pointer to the head of the Logs list.
                   c_searchedID - Log ID to search for.
  Return type: Pointer to the found Logs structure or NULL if not found.
  Memory usage: No dynamic memory allocation.
  Big O notation: O(n), where n is the number of elements in the Logs list.
 */
extern Logs* getLogElementByID(Logs *L_Log, char c_searchedID[] ){
    Logs *L_tmp_ptr = L_Log;
    while(L_tmp_ptr != NULL){
        if(strcmp(L_tmp_ptr->c_ID,c_searchedID)==0){
            return L_tmp_ptr;           
        }
        L_tmp_ptr = L_tmp_ptr->L_next_Logs;
    }
    return NULL;
}
