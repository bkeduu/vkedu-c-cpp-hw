#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "utils.h"


result* add(skyscraper* arr, int* size, FILE* in) {  // function that scan parameters of new skyscraper
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
	result* input = NULL;  // temp structure object for scanning new parameters

	temp = (skyscraper*)malloc(sizeof(skyscraper));

	printf("Enter parameters of new skyscraper:\n");

	printf("Enter skyscraper\'s name: ");
	input = get_line(in);  // input line

	if (input->code) {  // if error given
		code = input->code;  // delete from heap all previously allocated memory and return error code

		free(input);
		free(temp);

		return get_result(code, arr);
	}

	temp->name = (char*)input->ptr;  // if error not given, store information in temp object
	free(input);

	printf("Enter skyscraper\'s country: ");
	input = get_line(in);  // scan next line

	if (input->code) {
		code = input->code;

		free(input);
		free(temp->name);
		free(temp);

		return get_result(code, arr);
	}

	temp->country = (char*)input->ptr;
	free(input);

	printf("Enter skyscraper\'s purpose: ");
	input = get_line(in);

	if (input->code) {
		code = input->code;

		free(input);
		free(temp->country);
		free(temp->name);
		free(temp);

		return get_result(code, arr);
	}

	temp->purpose = (char*)input->ptr;
	free(input);

	printf("Enter skyscraper\'s height: ");
	input = get_line(in);

	if (input->code) {
		code = input->code;

		free(input);
		free(temp->purpose);
		free(temp->country);
		free(temp->name);
		free(temp);

		return get_result(code, arr);
	}

	int height = to_int(input->ptr);
	free(input->ptr);
	free(input);

	if (height < 0) {
		free(temp->purpose);
		free(temp->country);
		free(temp->name);
		free(temp);

		return get_result(height, arr);
	}

	temp->height = height;

	printf("Enter skyscraper\'s spire height: ");
	input = get_line(in);

	if (input->code) {
		code = input->code;

		free(input);
		free(temp->purpose);
		free(temp->country);
		free(temp->name);
		free(temp);

		return get_result(code, arr);
	}

	int s_height = to_int(input->ptr);
	free(input->ptr);
	free(input);

	if (s_height < 0) {
		free(temp->purpose);
		free(temp->country);
		free(temp->name);
		free(temp);

		return get_result(s_height, arr);
	}

	temp->spire_height = s_height;

	printf("Enter skyscraper\'s floors count: ");
	input = get_line(in);

	if (input->code) {
		code = input->code;

		free(input);
		free(temp->purpose);
		free(temp->country);
		free(temp->name);
		free(temp);

		return get_result(code, arr);
	}

	int f_count = to_int(input->ptr);
	free(input->ptr);
	free(input);

	if (f_count < 0) {
		free(temp->purpose);
		free(temp->country);
		free(temp->name);
		free(temp);

		return get_result(f_count, arr);
	}

	temp->floors_count = f_count;

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
	// function that lists skyscrapers with groupping by country, and then by purpose
	// not optimal algorithm
	// algorithm iterating on countries array, and then choosing all objects with this country

	int i = 0, j = 0;

	if (!size) {
		printf("\nNothing to be listed.\n");
		return;
	}

	printf("\nListing skyscrapers by country:\n");

	for (i; i < ccount; ++i) {
		printf("\nCountry: %s\n\n", countries[i]);

		for (j = 0; j < size; ++j) {
			if (strcmp(arr[j].country, countries[i]) == 0) {
				printf("\tName: %s;\n", arr[j].name);
				printf("\tCountry: %s;\n", arr[j].country);
				printf("\tPurpose: %s;\n", arr[j].purpose);
				printf("\tHeight: %d;\n", arr[j].height);
				printf("\tSpire height: %d;\n", arr[j].spire_height);
				printf("\tFloors count: %d;\n\n", arr[j].floors_count);
			}
		}
	}

	i = j = 0;

	printf("\nListing skyscrapers by purpose:\n");

	for (i; i < pcount; ++i) {
		printf("\nPurpose: %s\n\n", purposes[i]);

		for (j = 0; j < size; ++j) {
			if (strcmp(arr[j].purpose, purposes[i]) == 0) {
				printf("\tName: %s;\n", arr[j].name);
				printf("\tCountry: %s;\n", arr[j].country);
				printf("\tPurpose: %s;\n", arr[j].purpose);
				printf("\tHeight: %d;\n", arr[j].height);
				printf("\tSpire height: %d;\n", arr[j].spire_height);
				printf("\tFloors count: %d;\n\n", arr[j].floors_count);
			}
		}
	}
}
