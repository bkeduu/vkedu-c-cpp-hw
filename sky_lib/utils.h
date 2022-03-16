#pragma once

#include <stdio.h>

#include "errors.h"

short start(FILE*);

result* add_str(const char* str, char** arr, int* size);

result* get_line(FILE*);
short contains(const char* const str, char** arr, const int size);
int to_int(const char* str);

