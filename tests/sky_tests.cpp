#include <gtest/gtest.h>
#include <string>
#include <iostream>

extern "C" {
#include "utils.h"
#include "struct.h"
}

TEST(test_start_eof, start_tests) {
	const char* start_eof = "";
	FILE* stream = fmemopen((void*)start_eof, strlen(start_eof), "r");
	EXPECT_EQ(ERR_EOF, start(stream));
	fclose(stream);
}

TEST(test_start_bad_char, start_tests) {
	const char* start_bad = "3\n";
	FILE* stream = fmemopen((void*)start_bad, strlen(start_bad), "r");
	EXPECT_EQ(ERR_BAD_INPUT, start(stream));
	fclose(stream);
}

TEST(test_start_string, start_tests) {
	const char* start_string = "many characters\n";
	FILE* stream = fmemopen((void*)start_string, strlen(start_string), "r");
	EXPECT_EQ(ERR_BAD_INPUT, start(stream));
	fclose(stream);
}

TEST(test_start_add, start_tests) {
	const char* add_test = "1\nFederation Tower\nRussia\nOffices\n462\n0\n95\n1\nFederation Tower\nRussia\nOffices\n462\n0\n95\n";
	FILE* stream = fmemopen((void*)add_test, strlen(add_test), "r");
	EXPECT_EQ(ERR_EOF, start(stream));
	fclose(stream);
}

TEST(test_start_list, start_tests) {
	const char* add_test = "2\n";
	FILE* stream = fmemopen((void*)add_test, strlen(add_test), "r");
	EXPECT_EQ(ERR_EOF, start(stream));
	fclose(stream);
}

TEST(test_add_1, add_tests) {
	const char* add_test = "Federation Tower";
	skyscraper* arr = NULL;
	size_t size = 0;
	char** countries = NULL;
	char** purposes = NULL;
	size_t ccount = 0;
	size_t pcount = 0;
	FILE* stream = fmemopen((void*)add_test, strlen(add_test), "r");

	EXPECT_EQ(ERR_EOF, add(&arr, &size, &countries, &ccount, &purposes, &pcount, stream));

	free(arr);
	fclose(stream);
}

TEST(test_add_2, add_tests) {
	const char* add_test = "Federation Tower\nRussia";
	skyscraper* arr = NULL;
	size_t size = 0;
	char** countries = NULL;
	char** purposes = NULL;
	size_t ccount = 0;
	size_t pcount = 0;
	FILE* stream = fmemopen((void*)add_test, strlen(add_test), "r");

	EXPECT_EQ(ERR_EOF, add(&arr, &size, &countries, &ccount, &purposes, &pcount, stream));

	free(arr);
	fclose(stream);
}

TEST(test_add_3, add_tests) {
	const char* add_test = "Federation Tower\nRussia\nOffices";
	skyscraper* arr = NULL;
	size_t size = 0;
	char** countries = NULL;
	char** purposes = NULL;
	size_t ccount = 0;
	size_t pcount = 0;
	FILE* stream = fmemopen((void*)add_test, strlen(add_test), "r");

	EXPECT_EQ(ERR_EOF, add(&arr, &size, &countries, &ccount, &purposes, &pcount, stream));

	free(arr);
	fclose(stream);
}

TEST(test_add_4, add_tests) {
	const char* add_test = "Federation Tower\nRussia\nOffices\n462";
	skyscraper* arr = NULL;
	size_t size = 0;
	char** countries = NULL;
	char** purposes = NULL;
	size_t ccount = 0;
	size_t pcount = 0;
	FILE* stream = fmemopen((void*)add_test, strlen(add_test), "r");

	EXPECT_EQ(ERR_EOF, add(&arr, &size, &countries, &ccount, &purposes, &pcount, stream));

	free(arr);
	fclose(stream);
}

TEST(test_add_5, add_tests) {
	const char* add_test = "Federation Tower\nRussia\nOffices\n462\n0";
	skyscraper* arr = NULL;
	size_t size = 0;
	char** countries = NULL;
	char** purposes = NULL;
	size_t ccount = 0;
	size_t pcount = 0;
	FILE* stream = fmemopen((void*)add_test, strlen(add_test), "r");

	EXPECT_EQ(ERR_EOF, add(&arr, &size, &countries, &ccount, &purposes, &pcount, stream));

	free(arr);
	fclose(stream);
}

TEST(test_add_6, add_tests) {
	const char* add_test = "Federation Tower\nRussia\nOffices\n462\n0\n95";
	skyscraper* arr = NULL;
	size_t size = 0;
	char** countries = NULL;
	char** purposes = NULL;
	size_t ccount = 0;
	size_t pcount = 0;
	FILE* stream = fmemopen((void*)add_test, strlen(add_test), "r");

	EXPECT_EQ(ERR_EOF, add(&arr, &size, &countries, &ccount, &purposes, &pcount, stream));

	free(arr);
	fclose(stream);
}

TEST(test_add_7, add_tests) {
	const char* add_test = "Federation Tower\nRussia\nOffices\n-1\n0\n95\n";
	skyscraper* arr = NULL;
	size_t size = 0;
	char** countries = NULL;
	char** purposes = NULL;
	size_t ccount = 0;
	size_t pcount = 0;
	FILE* stream = fmemopen((void*)add_test, strlen(add_test), "r");

	EXPECT_EQ(ERR_NEG_NUM, add(&arr, &size, &countries, &ccount, &purposes, &pcount, stream));

	free(arr);
	fclose(stream);
}

TEST(test_add_8, add_tests) {
	const char* add_test = "Federation Tower\nRussia\nOffices\n462\n-1\n95\n";
	skyscraper* arr = NULL;
	size_t size = 0;
	char** countries = NULL;
	char** purposes = NULL;
	size_t ccount = 0;
	size_t pcount = 0;
	FILE* stream = fmemopen((void*)add_test, strlen(add_test), "r");

	EXPECT_EQ(ERR_NEG_NUM, add(&arr, &size, &countries, &ccount, &purposes, &pcount, stream));

	free(arr);
	fclose(stream);
}

TEST(test_add_9, add_tests) {
	const char* add_test = "Federation Tower\nRussia\nOffices\n462\n0\n-1\n";
	skyscraper* arr = NULL;
	size_t size = 0;
	char** countries = NULL;
	char** purposes = NULL;
	size_t ccount = 0;
	size_t pcount = 0;
	FILE* stream = fmemopen((void*)add_test, strlen(add_test), "r");

	EXPECT_EQ(ERR_NEG_NUM, add(&arr, &size, &countries, &ccount, &purposes, &pcount, stream));

	free(arr);
	fclose(stream);
}

TEST(test_add_null, add_tests) {
	EXPECT_EQ(ERR_NULL, add(NULL, NULL, NULL, NULL, NULL, NULL, NULL));
}

TEST(test_list_filled, list_tests) {
	const char* add_test = "Federation Tower\nRussia\nOffices\n462\n0\n95\n";
	skyscraper* arr = NULL;
	size_t size = 0;
	char** countries = NULL;
	char** purposes = NULL;
	size_t ccount = 0;
	size_t pcount = 0;
	FILE* stream = fmemopen((void*)add_test, strlen(add_test), "r");
	add(&arr, &size, &countries, &ccount, &purposes, &pcount, stream);

	list(arr, size, countries, ccount, purposes, pcount);

	free(countries[0]);
	free(purposes[0]);
	free(countries);
	free(purposes);
	free(arr[0].name);
	free(arr[0].country);
	free(arr[0].purpose);
	free(arr);
	fclose(stream);
}

TEST(test_list_empty, list_tests) {
	list(NULL, 0, NULL, 0, NULL, 0);
}

TEST(test_contains, contains_tests) {

	char** arr = NULL;
	const char* str = "test str";
	
	EXPECT_EQ(0, contains((char*)str, arr, 0));

	arr = (char**)malloc(sizeof(char*));
	if (!arr)
		exit(-1);

	arr[0] = (char*)malloc(sizeof("test str"));
	if (!arr[0])
		exit(-1);

	strcpy(arr[0], str);

	EXPECT_EQ(1, contains((char*)str, arr, 1));

	free(arr[0]);
	free(arr);
}
