#pragma once

typedef enum errors { ERR_BAD_INPUT = -1, ERR_MALLOC = -2, ERR_NEG_NUM = -3, ERR_EOF = -4 } errors;
							// description of enum with error codes

typedef struct result {  // result structure, that used as a return result in many functions
	short code;
	void* ptr;
} result;

result* get_result(int code, void* ptr);
