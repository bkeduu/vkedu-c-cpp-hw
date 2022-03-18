#include <string.h>

#include "struct.h"
#include "utils.h"

short start(FILE* in) {  // function with main logic
	string* countries = NULL;  // ptr for array for storing unique countries
	size_t countries_count = 0;  // size of this array

	string* purposes = NULL;  // ptr for array for storing unique purposes
	size_t purposes_count = 0;

	skyscraper* objects = NULL;  // ptr for array for storing skyscrapers
	size_t objects_count = 0;

	string mode = NULL;  // var for menu mode choosing
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
		} else if (strlen(mode) > 2) {  // if entered more than 1 character, return ERR_BAD_INPUT
			error_code = ERR_BAD_INPUT;
			break;
		} else if (mode[0] == '1') {  // adding mode
			short temp = add(&objects, &objects_count, &countries, &countries_count,
							&purposes, &purposes_count, in);  // temp var for checking errors

			if (temp) {
				error_code = temp;
				break;
			}
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

	for (size_t i = 0; i < objects_count; ++i) {
		free_struct(&objects[i]);
	}

	free(objects);

	free_arr(countries, countries_count);
	free_arr(purposes, purposes_count);

	return error_code;
}

short add_str(const string str, string** arr, size_t* size) {
		// function that adds str to arr, if str is not already in arr

	if (str == NULL || arr == NULL || size == NULL) {
		return ERR_NULL;
	}

	if (*size == 0)
		*arr = (string*)malloc(sizeof(string));

	if (!*arr)  // check for possible malloc error
		return ERR_MALLOC;

	if (contains(str, *arr, *size))
		// if str already in arr, exit from function
		return 0;

	string check_str = (string)malloc(sizeof(char) * (strlen(str) + 1));

	if (!check_str)
		return ERR_MALLOC;

	string* check_arr = (string*)realloc(*arr, sizeof(string) * (*size + 1));

	if (!check_arr) {  // check for possible realloc error
		free(check_str);
		return ERR_MALLOC;
	}

	++(*size);

	check_arr[(*size) - 1] = check_str;
	snprintf(check_arr[(*size) - 1], strlen(str) + 1, "%s", str);

	*arr = check_arr;

	return 0;
}

short contains(const string str, string* arr, const size_t size) {
			// function that checks availibility of str in arr
	if (size) {
		for (size_t i = 0; i < size; ++i) {
			if (strcmp(str, arr[i]) == 0) {
				return 1;
			}
		}
	}

	return 0;
}

void free_arr(string* arr, size_t size) {  // function to free array
	for (size_t i = 0; i < size; ++i) {
		free(arr[i]);
	}

	free(arr);
}

void free_struct(skyscraper* obj) {  // function to free structure object
	free(obj->name);
	free(obj->country);
	free(obj->purpose);
}
