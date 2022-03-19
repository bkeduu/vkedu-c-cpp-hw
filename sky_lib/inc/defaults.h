#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef char* string;

typedef struct skyscraper {  // description of skyscraper structure
	string name;
	string country;
	string purpose;
	int floors_count;
	int height;
	int spire_height;
} skyscraper;

typedef enum errors_t {  // description of enum with error codes
	ERR_BAD_INPUT = -1,
	ERR_MALLOC = -2,
	ERR_NEG_NUM = -3,
	ERR_EOF = -4,
	ERR_NULL = -5
} errors;
