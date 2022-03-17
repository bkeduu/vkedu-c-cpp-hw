#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "utils.h"


result_t* add(skyscraper* arr, int* size, FILE* in) {  // function that scan parameters of new skyscraper
	    					    // and adds new structure object to arr

	if (*size == 0)
		arr = (skyscraper*)malloc(sizeof(skyscraper));

	if(!arr)
		return get_result(ERR_MALLOC, NULL);

	skyscraper* temp = (skyscraper*)realloc(arr, sizeof(skyscraper) * (*size + 1));

	if (!temp)
		return get_result(ERR_MALLOC, arr);

	arr = temp;

	short code = 0;  // var for storing error code
	char* input = NULL;  // temp structure object for scanning new parameters
	size_t input_size = 0;

	temp = (skyscraper*)malloc(sizeof(skyscraper));

	temp->name = NULL;
	temp->country = NULL;
	temp->purpose = NULL;

	printf("Enter parameters of new skyscraper:\n");

	printf("Enter skyscraper\'s name: ");
	getline(&input, &input_size, in);  // input line

	if (!input_size)
		code = ERR_MALLOC;

	if (feof(in)) {
		code = ERR_EOF;
	} else {
		input[strlen(input) - 1] = '\0';
		temp->name = input;  // if error not given, store information in temp object
		input = NULL;
		input_size = 0;
	}

	printf("Enter skyscraper\'s country: ");
	getline(&input, &input_size, in);  // scan next line

	if (!input_size)
		code = ERR_MALLOC;

	if (feof(in)) {
		code = ERR_EOF;
	} else {
		input[strlen(input) - 1] = '\0';
		temp->country = input;
		input = NULL;
		input_size = 0;
	}

	printf("Enter skyscraper\'s purpose: ");
	getline(&input, &input_size, in);

	if (!input_size)
		code = ERR_MALLOC;

	if (feof(in)) {
		code = ERR_EOF;
	} else {
		input[strlen(input) - 1] = '\0';
		temp->purpose = input;
		input = NULL;
		input_size = 0;
	}

	printf("Enter skyscraper\'s height: ");
	getline(&input, &input_size, in);

	if (!input_size)
		code = ERR_MALLOC;

	if (feof(in)) {
		code = ERR_EOF;
	} else {
		input[strlen(input) - 1] = '\0';
		int height = atoi(input);
		free(input);
		input = NULL;
		input_size = 0;

		if (height < 0)
			code = ERR_NEG_NUM;

		temp->height = height;
	}

	printf("Enter skyscraper\'s spire height: ");
	getline(&input, &input_size, in);

	if (!input_size)
		code = ERR_MALLOC;

	if (feof(in)) {
		code = ERR_EOF;
	} else {
		input[strlen(input) - 1] = '\0';
		int s_height = atoi(input);
		free(input);
		input = NULL;
		input_size = 0;

		if (s_height < 0)
			code = ERR_NEG_NUM;

		temp->spire_height = s_height;
	}

	printf("Enter skyscraper\'s floors count: ");
	getline(&input, &input_size, in);

	if (!input_size)
		code = ERR_MALLOC;

	if (feof(in)) {
		code = ERR_EOF;
	} else {
		input[strlen(input) - 1] = '\0';
		int f_count = atoi(input);
		free(input);
		input = NULL;
		input_size = 0;

		if (f_count < 0)
			code = ERR_NEG_NUM;

		temp->floors_count = f_count;
	}

	if (code) {  // if error code received, free all heap vars and exit
		free(temp->name);
		free(temp->country);
		free(temp->purpose);
		free(temp);
		free(input);

		return get_result(code, arr);
	}

	++(*size);  // if no errors, increase arr size

	arr[(*size) - 1].name = temp->name;  // and add information to new object
	arr[(*size) - 1].country = temp->country;
	arr[(*size) - 1].purpose = temp->purpose;
	arr[(*size) - 1].height = temp->height;
	arr[(*size) - 1].spire_height = temp->spire_height;
	arr[(*size) - 1].floors_count = temp->floors_count;

	free(temp);

	return get_result(0, arr);
}

void list(const skyscraper* arr, const int size, char** countries, const int ccount,
						char** purposes, const int pcount) {
	// function that lists skyscrapers with groupping by purpose, and then by country

	int i, j, k;

	if (!size) {
		printf("\nNothing to be listed.\n");
		return;
	}

	printf("\nListing skyscrapers:\n");

	for (i = 0; i < pcount; ++i) {
		printf("\nPurpose: %s\n\n", purposes[i]);

		for (j = 0; j < ccount; ++j) {
			for(k = 0; k < size; ++k)
			if (strcmp(arr[k].purpose, purposes[i]) == 0 && strcmp(arr[k].country, countries[j]) == 0) {
				printf("\tName: %s;\n", arr[k].name);
				printf("\tCountry: %s;\n", arr[k].country);
				printf("\tPurpose: %s;\n", arr[k].purpose);
				printf("\tHeight: %d;\n", arr[k].height);
				printf("\tSpire height: %d;\n", arr[k].spire_height);
				printf("\tFloors count: %d;\n\n", arr[k].floors_count);
			}
		}
	}
}
