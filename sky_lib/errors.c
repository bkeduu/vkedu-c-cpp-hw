#include <stdlib.h>

#include "errors.h"

result* get_result(int code, void* ptr) {  // function that returns result structure object
	result* res = (result*)malloc(sizeof(result));

	res->code = code;
	res->ptr = ptr;

	return res;
}
