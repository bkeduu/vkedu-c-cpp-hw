#include <string.h>

#include "struct.h"
#include "utils.h"


short add(skyscraper** arr, size_t* size, string** countries, size_t* ccount,
				string** purposes, size_t* pcount, FILE* in) {  // function that scan parameters of new skyscraper
	    													  // and adds new structure object to arr
	if (arr == NULL || size == NULL || countries == NULL || ccount == NULL ||
		purposes == NULL || pcount == NULL) {
		return ERR_NULL;
	}

	if (!(*arr)) {
		*arr = (skyscraper*)malloc(sizeof(skyscraper));
	}

	if (!(*arr)) {
		return ERR_MALLOC;
	}

	skyscraper new_obj;
	short code = input_struct(&new_obj, in);  // var for storing error code

	if (code) {
		return code;
	}

	short check = add_str(new_obj.country, countries, ccount);

	if (check) {
		free_struct(&new_obj);

		return check;
	}

	check = add_str(new_obj.purpose, purposes, pcount);

	if (check) {
		free_struct(&new_obj);

		return check;
	}

	skyscraper* tmp_arr = (skyscraper*)realloc(*arr, sizeof(skyscraper) * (*size + 1));

	if (!tmp_arr) {
		free_struct(&new_obj);

		return ERR_MALLOC;
	}

	++(*size);  // if no errors, increase arr size

	tmp_arr[(*size) - 1] = new_obj;  // and add information to new object

	*arr = tmp_arr;

	return 0;
}

void list(const skyscraper* arr, const size_t size, string* countries, const size_t ccount,
						string* purposes, const size_t pcount) {
	// function that lists skyscrapers with groupping by purpose, and then by country

	if (arr == NULL || countries == NULL || purposes == NULL) {
		return;
	}


	if (!size) {
		printf("\nNothing to list.\n");
		return;
	}

	printf("\nListing skyscrapers:\n");

	for (size_t i = 0; i < pcount; ++i) {
		printf("\nPurpose: %s\n\n", purposes[i]);

		for (size_t j = 0; j < ccount; ++j) {
			for(size_t k = 0; k < size; ++k) {
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
}

short input_struct(skyscraper* res, FILE* in) {  // function with input new structure object
	short code = 0;  // var for storing error code
	string input = NULL;
	size_t input_size = 0;

	if (!res) {
		return ERR_NULL;
	}

	res->name = NULL;
	res->country = NULL;
	res->purpose = NULL;

	printf("Enter parameters of new skyscraper:\n");

	printf("Enter skyscraper\'s name: ");
	getline(&input, &input_size, in);  // input line

	if (!input_size) {
		code = ERR_MALLOC;
	}

	if (feof(in)) {
		code = ERR_EOF;
	} else {
		input[strlen(input) - 1] = '\0';
		res->name = input;  // if error not given, store information in temp object
		input = NULL;
		input_size = 0;
	}

	if (!code) {
		printf("Enter skyscraper\'s country: ");
		getline(&input, &input_size, in);  // scan next line

		if (!input_size) {
			code = ERR_MALLOC;
		}

		if (feof(in)) {
			code = ERR_EOF;
		} else {
			input[strlen(input) - 1] = '\0';
			res->country = input;
			input = NULL;
			input_size = 0;
		}
	}

	if (!code) {
		printf("Enter skyscraper\'s purpose: ");
		getline(&input, &input_size, in);

		if (!input_size) {
			code = ERR_MALLOC;
		}

		if (feof(in)) {
			code = ERR_EOF;
		} else {
			input[strlen(input) - 1] = '\0';
			res->purpose = input;
			input = NULL;
			input_size = 0;
		}
	}

	if (!code) {
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

			res->height = height;
		}
	}

	if (!code) {
		printf("Enter skyscraper\'s spire height: ");
		getline(&input, &input_size, in);

		if (!input_size) {
			code = ERR_MALLOC;
		}

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

			res->spire_height = s_height;
		}
	}

	if (!code) {
		printf("Enter skyscraper\'s floors count: ");
		getline(&input, &input_size, in);

		if (!input_size) {
			code = ERR_MALLOC;
		}

		if (feof(in)) {
			code = ERR_EOF;
		} else {
			input[strlen(input) - 1] = '\0';
			int f_count = atoi(input);
			free(input);
			input = NULL;
			input_size = 0;

			if (f_count < 0) {
				code = ERR_NEG_NUM;
			}

			res->floors_count = f_count;
		}
	}

	if (code) {  // if error code received, free all heap vars and exit
		free_struct(res);
		free(input);

		return code;
	}

	return 0;
}
