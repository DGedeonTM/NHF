Basics of Programming 1
Date:
2023.11.12
Documentation 

Functions:

	- gen_uuid()
Description:
	The function creates a random UUID by selecting random hexadecimal digits and arranging them in the format specified for version 4 UUIDs. Version 4 UUIDs are generated purely based on random or pseudo-random numbers and are designed to be unique across all devices and applications.
Parameters: This function takes no parameters.
Return Type: 
char*: The gen_uuid function returns a pointer to a character array (string) representing the generated UUID.
Input: This function does not require any input parameters.
Memory/CPU Usage:
	Memory Usage: The function uses memory to store the generated UUID as a character array. The memory required is constant (36 bytes for the UUID and an additional byte for the null-terminating character).
CPU Usage: The CPU usage is low and depends on the number of random digit selections, which is typically 36 iterations through the random digit selection loop.
Big O Notation:
The time complexity of this function is O(1) because it performs a fixed number of iterations (36) to generate the UUID. The time required to generate the UUID is constant and does not depend on the size of data or the length of a list.

	- createRecipeListItem()
Description: This function is used to create a new recipe item and add it to the end of the linked list.
Parameters:
	Recipe * R_Recipe: A pointer to the new Recipe item to be created.
	Recipe * R_ptr: A pointer to the head of the recipe list.
Return Type: void
Input: The function takes a pointer to the new recipe item and a pointer to the list of recipes.
Memory/CPU Usage: The function uses memory for a new Recipe structure and increments the list's size. CPU usage is low.
Big O n: O(1) - The time complexity is constant since the function directly adds an item to the end of the list.

	-deleteRecipeListItem()
Description: This function allows the removal of a recipe item from the linked list based on a provided recipe ID.
Parameters:
	Recipe * R_Recipe: A pointer to the head of the recipe list.
	char c_searchedID[]: The ID of the recipe to be deleted.
Return Type: void
Input: The function takes a pointer to the list of recipes and the ID of the recipe to delete.
Memory/CPU Usage: The function deallocates memory for the removed item. Memory and CPU usage depend on the position of the item to be deleted. If the item is at the end of the list, it requires less memory and CPU usage.
Big O n: O(n) - The time complexity is linear as it may need to traverse the entire list in the worst case.

	-listRecipeListItems()
Description: This function prints the names of all recipes in the linked list.
Parameters:
	Recipe * R_Recipe: A pointer to the head of the recipe list.
Return Type: void
Input: The function takes a pointer to the list of recipes.
Memory/CPU Usage: The function reads data from memory and prints it to the console. It does not significantly affect memory or CPU usage.
Big O n: O(n) - The time complexity is linear as it traverses the entire list to print the names.

	-freeRecipesList()
Description: This function is used to free the memory occupied by the entire linked list of recipes.
Parameters:
	Recipe * R_Recipe: A pointer to the head of the recipe list.
Return Type: void
Input: The function takes a pointer to the list of recipes.
Memory/CPU Usage: The function deallocates memory for all items in the list. Memory and CPU usage depend on the list's size.
Big O n: O(n) - The time complexity is linear as it needs to traverse the entire list to free memory.

	-getRecipeElementByID()
Description: This function searches the linked list and returns a pointer to the recipe with a specific ID.
Parameters:
	Recipe * R_Recipe: A pointer to the head of the recipe list.
	char c_searchedID[]: The ID of the recipe to search for.
Return Type: Recipe*
Input: The function takes a pointer to the list of recipes and the ID to search for.
Memory/CPU Usage: The function searches for a specific item in memory. Memory and CPU usage depend on the item's position in the list.
Big O n: O(n) - The time complexity is linear as it may need to traverse the entire list in the worst case.

	-getRecipeElementByName()
Description: This function searches the linked list and returns a pointer to the recipe with a specific name.
Parameters:
	Recipe * R_Recipe: A pointer to the head of the recipe list.
	char c_searchedName[]: The name of the recipe to search for.
Return Type: Recipe*
Input: The function takes a pointer to the list of recipes and the name to search for.
Memory/CPU Usage: The function searches for a specific item in memory. Memory and CPU usage depend on the item's position in the list.
Big O n: O(n) - The time complexity is linear as it may need to traverse the entire list in the worst case.
