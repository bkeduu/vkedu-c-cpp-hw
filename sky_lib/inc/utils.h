#pragma once

#include <stdio.h>

#include "errors.h"

short start(FILE*);

result_t* add_str(const char* str, char** arr, int* size);

result_t* get_line(FILE*);
short contains(const char* const str, char** arr, const int size);
