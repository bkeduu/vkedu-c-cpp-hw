#pragma once

#include "defaults.h"

short start(FILE*);

short add_str(const string str, string** arr, size_t* size);

short contains(const string str, string* arr, const size_t size);
void free_arr(string* arr, size_t);
void free_struct(skyscraper*);
