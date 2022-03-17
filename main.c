#include <stdio.h>

#include "utils.h"

int main(void) {
	switch (start(stdin)) {  // calling start function and checking returned error code
		case ERR_BAD_INPUT:
			printf("\nBad character(s) received, exiting...\n");
			break;
		case ERR_MALLOC:
			printf("\nMemory allocation error, exiting...\n");
			break;
		case ERR_NEG_NUM:
			printf("\nSkyscraper\'s characteristics should be positive numbers, exiting...\n");
			break;
		case ERR_EOF:
			printf("EOF received, exiting...\n");
			break;
		default:
			break;
	}

	return 0;
}
