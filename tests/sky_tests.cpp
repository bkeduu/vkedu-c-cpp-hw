#include <gtest/gtest.h>
#include <string>
#include <iostream>

extern "C" {
#include "utils.h"
#include "struct.h"
}

TEST(test_1, to_int_tests) {
	EXPECT_EQ(1, to_int("1"));
}

TEST(test_negative_num, to_int_tests) {
	EXPECT_EQ(ERR_NEG_NUM, to_int("-1"));
}

TEST(test_bad_input, to_int_tests) {
	EXPECT_EQ(ERR_BAD_INPUT, to_int("a"));
}

TEST(test_empty_str, to_int_tests) {
	EXPECT_EQ(0, to_int(""));
}

TEST(test_normal_str, get_line_tests) {
	FILE* file = fopen("../tests/get_line_normal.txt", "r");
	result* normal = get_line(file);
	EXPECT_STREQ("normal test string with spaces", (char*)normal->ptr);
	free(normal->ptr);
	free(normal);
	fclose(file);
}

TEST(test_eof, get_line_tests) {
	FILE* file = fopen("../tests/get_line_eof.txt", "r");
	result* eof = get_line(file);
	EXPECT_EQ(ERR_EOF, eof->code);
	free(eof->ptr);
	free(eof);
	fclose(file);
}

TEST(test_two_lines, get_line_tests) {
	FILE* file = fopen("../tests/get_line_multiline.txt", "r");
	result* line1 = (result*)get_line(file);
	result* line2 = (result*)get_line(file);
	EXPECT_STREQ("line1", (char*)line1->ptr);
	EXPECT_STREQ("line2", (char*)line2->ptr);
	free(line1->ptr);
	free(line2->ptr);
	free(line1);
	free(line2);
	fclose(file);
}

TEST(test_result_struct, get_result_tests) {
	char* some_ptr = (char*)malloc(sizeof(char));
	result* res = get_result(1, some_ptr);
	EXPECT_EQ(1, res->code);
	EXPECT_EQ(some_ptr, res->ptr);
	free(some_ptr);
	free(res);
}

TEST(test_start_eof, start_tests) {
	FILE* file = fopen("../tests/start_eof.txt", "r");
	EXPECT_EQ(ERR_EOF, start(file));
	fclose(file);
}

TEST(test_start_bad_char, start_tests) {
	FILE* file = fopen("../tests/start_bad_char.txt", "r");
	EXPECT_EQ(ERR_BAD_INPUT, start(file));
	fclose(file);
}

TEST(test_start_string, start_tests) {
	FILE* file = fopen("../tests/start_string.txt", "r");
	EXPECT_EQ(ERR_BAD_INPUT, start(file));
	fclose(file);
}

TEST(test_add, add_tests) {
	FILE* file = fopen("../tests/add.txt", "r");
	EXPECT_EQ(ERR_BAD_INPUT, start(file));
	fclose(file);
}

TEST(test_list_empty, list_tests) {
	FILE* file = fopen("../tests/list_empty.txt", "r");
	EXPECT_EQ(ERR_BAD_INPUT, start(file));
	fclose(file);
}

TEST(test_list_filled, list_tests) {
	FILE* file = fopen("../tests/list_filled.txt", "r");
	EXPECT_EQ(ERR_BAD_INPUT, start(file));
	fclose(file);
}

TEST(test_contains, contains_tests) {
	FILE* file = fopen("../tests/contains.txt", "r");
	EXPECT_EQ(ERR_BAD_INPUT, start(file));
	fclose(file);
}
