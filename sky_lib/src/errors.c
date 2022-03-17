#include <stdlib.h>

#include "errors.h"

result_t* get_result(int code, void* ptr) {  // function that returns result structure object
	result_t* res = (result_t*)malloc(sizeof(result_t));

	res->code = code;
	res->ptr = ptr;

	return res;
}
