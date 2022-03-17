#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "utils.h"


short start(FILE* in) {  // function with main logic
	char** countries = NULL;  // ptr for array for storing unique countries
	int countries_count = 0;  // size of this array

	char** purposes = NULL;  // ptr for array for storing unique purposes
	int purposes_count = 0;

	skyscraper* objects = NULL;  // ptr for array for storing skyscrapers
	int objects_count = 0;

	char* mode = NULL;  // var for menu mode choosing
	size_t mode_size = 0;  // size of allocated memory to mode
	short error_code = 0;

	printf("Welcome to the program!\n");
	printf("Choose option from menu or any another character to exit: \n");
	printf("1. Add skyscraper;\n");
	printf("2. List skyscrapers;\n");

	while (getline(&mode, &mode_size, in)) {
		if (feof(in)) {  // if EOF received
			error_code = ERR_EOF;
			break;
		} else if (mode_size == 0) {  // if mode_size is empty, then malloc error
			error_code = ERR_MALLOC;
			break;
		} else if (strlen(mode) > 2) {  // if entered more than 1 character return ERR_BAD_INPUT
			error_code = ERR_BAD_INPUT;
			break;
		} else if (mode[0] == '1') {  // adding mode
			result_t* temp = add(objects, &objects_count, in);  // temp var for checking errors
			objects = (skyscraper*)temp->ptr;

			if (temp->code) {
				error_code = temp->code;
				free(temp);
				break;
			}

			free(temp);

			temp = add_str(objects[objects_count - 1].country, countries, &countries_count);
								// checking and adding country in array
			countries = (char**)temp->ptr;

			if (temp->code) {  // possible errors checking
				error_code = temp->code;
				free(temp);
				break;
			}

			free(temp);

			temp = add_str(objects[objects_count - 1].purpose, purposes, &purposes_count);
								// checking and adding country in array
			purposes = (char**)temp->ptr;

			if (temp->code) {
				error_code = temp->code;
				free(temp);
				break;
			}

			free(temp);
		} else if (mode[0] == '2') {  // list mode
			list(objects, objects_count, countries, countries_count, purposes, purposes_count);
		} else {  // another character received
			error_code = ERR_BAD_INPUT;
			break;
		}

		free(mode);
		mode_size = 0;

		printf("\nChoose option:\n");
		printf("1. Add skyscraper;\n");
		printf("2. List skyscrapers;\n");
	}

	free(mode);

	int i = 0;

	for (i = 0; i < objects_count; ++i) {
		free(objects[i].name);
		free(objects[i].country);
		free(objects[i].purpose);
	}

	for (i = 0; i < countries_count; ++i)
		free(countries[i]);

	for (i = 0; i < purposes_count; ++i)
		free(purposes[i]);

	free(objects);
	free(countries);
	free(purposes);

	return error_code;
}

result_t* add_str(const char* str, char** arr, int* size) {
		// function that adds str to arr, if str is not already in arr
	if (*size == 0)
		arr = (char**)malloc(sizeof(char*));

	if (!arr)  // check for possible malloc error
		return get_result(ERR_MALLOC, NULL);

	if (contains(str, arr, *size))
		// if str already in arr, exit from function
		return get_result(0, arr);

	char** check_arr = (char**)realloc(arr, sizeof(char*) * (*size + 1));
				// else, alloc new memory and copy str to it

	if (!check_arr)  // check for possible realloc error
		return get_result(ERR_MALLOC, arr);

	arr = check_arr;

	char* check_str = (char*)malloc(sizeof(char) * (strlen(str) + 1));

	if (!check_str)
		return get_result(ERR_MALLOC, arr);

	++(*size);

	arr[(*size) - 1] = check_str;
	snprintf(arr[(*size) - 1], strlen(str) + 1, "%s", str);

	return get_result(0, arr);
}

short contains(const char* const str, char** arr, const int size) {
			// function that checks availibility of str in arr
	if (size) {
		int i;

		for (i = 0; i < size; ++i) {
			if (strcmp(str, arr[i]) == 0)
				return 1;
		}
	}

	return 0;
}

