#include <stdio.h>
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

	result* mode = NULL;  // var for menu mode choosing
	short error_code = 0;
	char* mode_str = NULL;  // menu mode in str type

	printf("Welcome to the program!\n");
	printf("Choose option from menu or any another character to exit: \n");
	printf("1. Add skyscraper;\n");
	printf("2. List skyscrapers;\n");

	while ((mode = get_line(in))) {
		mode_str = (char*)mode->ptr;

		if (mode->code == ERR_MALLOC || mode->code == ERR_EOF) {  // checking for errors in mode choosing
			error_code = mode->code;
			break;
		} else if (strlen((char*)mode_str) > 1) {  // if entered more than 1 character return ERR_BAD_INPUT
			error_code = ERR_BAD_INPUT;
			break;
		} else if (mode_str[0] == '1') {  // adding mode
			result* temp = add(objects, &objects_count, in);  // temp var for checking errors
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
		} else if (mode_str[0] == '2') {  // list mode
			list(objects, objects_count, countries, countries_count, purposes, purposes_count);
		} else {  // another character received
			error_code = ERR_BAD_INPUT;
			break;
		}

		free(mode_str);
		free(mode);

		printf("\nChoose option:\n");
		printf("1. Add skyscraper;\n");
		printf("2. List skyscrapers;\n");
	}

	free(mode_str);  // deleting all heap variables
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

result* add_str(const char* str, char** arr, int* size) {
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
	snprintf(arr[(*size) - 1], strlen(str) + 1, str);

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

result* get_line(FILE* in) {  // function that input str from in
	char* result_str = NULL;
	char* check = NULL;

	result_str = (char*)malloc(sizeof(char));

	if (!result_str)
		return get_result(ERR_MALLOC, NULL);

	int size = 1;  // real strlen
	int buff_size = 1;  // size of allocated buffer

	char input = '\0';

	while ((input = getc(in))) {
		if (input != '\n' && input != EOF) {
			result_str[size++ - 1] = input;

			if (size >= buff_size) {  // if count of scanned characters grater than buffer size
				buff_size *= 2;  // multiply buffer size
				check = (char*)realloc(result_str, sizeof(char) * buff_size);  // and realloc memory

				if (!check) {
					free(result_str);
					return get_result(ERR_MALLOC, NULL);
				}

				result_str = check;
			}
		} else if (input == EOF) {  // if EOF (Ctrl+D) received, delete str from heap and return ERR_EOF
			result_str[size - 1] = '\0';
			free(result_str);

			return get_result(ERR_EOF, NULL);
		} else {  // if newline character recieved, exit from cycle
			break;
		}
	}

	check = (char*)realloc(result_str, sizeof(char) * (size + 1));  // allocate memory for '\0'-symbol

	if (!check) {
		free(result_str);
		return get_result(ERR_MALLOC, NULL);
	}

	result_str = check;

	result_str[size - 1] = '\0';

	return get_result(0, result_str);
}

int to_int(const char* str) {  // function that converts str to integer value
	int i;
	int out = 0;  // result var

	for (i = 0; i < strlen(str); ++i) {
		if (str[i] >= '0' && str[i] <= '9') {
			out += (int)(str[i] - '0');
			out *= 10;
		} else if (str[i] == '-') {  // if negative number presented
			return ERR_NEG_NUM;
		} else {  // if non-digits given in input
			return ERR_BAD_INPUT;
		}
	}

	return out /= 10;  // divide by 10 because of last cycle iteration
}
