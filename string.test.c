#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string.h"

#define TESTS 61

void ok(long a, const char* message) {
    static int test_index = 0;
    printf("%s %d - %s\n", (a ? "ok" : "not ok"), ++test_index, message);
}

void not_ok(long a, const char* message) {
    ok(!a, message);
}

/**
 * Asserts strings equal.
 * Frees actual.
 */
void equal_str(char* actual, const char* expected, const char* message) {
    if (strcmp(actual, expected) == 0) {
        ok(1, message);
        free(actual);
        return;
    }

    ok(0, message);
    printf("  ---\n");
    printf("  message: \"%s\"\n",  message );
    printf("  actual: \"%s\"\n",   actual  );
    printf("  expected: \"%s\"\n", expected);
    printf("  ...\n");
    free(actual);
}

void equal_long(long actual, long expected, const char* message) {
    if (actual == expected) {
        ok(1, message);
        return;
    }

    ok(0, message);

    printf("  ---\n");
    printf("  message: \"%s\"\n",  message );
    printf("  actual: %ld\n",   actual  );
    printf("  expected: %ld\n", expected);
    printf("  ...\n");
}

void eq(int a, int b, char* message) {
    ok(a == b, message);
}

int main(void) {
    printf("1..%d\n", TESTS);

    ok(    string_equal("",    ""   ), "Empty strings are equal");
    ok(    string_equal("foo", "foo"), "Equal strings");
    not_ok(string_equal("foo", "bar"), "Not equal strings");
    not_ok(string_equal("foo", "fo" ), "Not equal length");

    equal_str(string_alloc(""   ), "",    "Allocate an empty string");
    equal_str(string_alloc("foo"), "foo", "Allocate a non-empty string");

    ok(    string_starts_with("foo bar", "foo"), "String starts with");
    ok(    string_starts_with("foo",     "foo"), "When the string is equal to the search, it starts with the search");
    ok(    string_starts_with("foo",     ""   ), "A strign starts with an empty string");
    not_ok(string_starts_with("foo bar", "bar"), "String does not start with");

    ok(    string_ends_with("foo bar", "bar"), "String ends with");
    ok(    string_ends_with("foo",     "foo"), "When the string is equal to the search, it ends with the search");
    ok(    string_ends_with("foo",     ""   ), "A strign ends with an empty string");
    not_ok(string_ends_with("foo bar", "foo"), "String does not end with");

    equal_long(string_index_of("foo bar", "foo"),  0, "Index of 0 match");
    equal_long(string_index_of("foo bar", "bar"),  4, "Index of 4 match");
    equal_long(string_index_of("foo bar", "baz"), -1, "Index of not-found is -1");

    equal_long(string_last_index_of("foo bar",     "foo"),  0, "Last index of 0 match");
    equal_long(string_last_index_of("foo foo bar", "foo"),  4, "Last index of 4 match");
    equal_long(string_last_index_of("foo bar",     "baz"), -1, "Last index of not-found is -1");

    equal_str(string_alloc(""   ), "",    "Allocates an empty string");
    equal_str(string_alloc("foo"), "foo", "Allocates a string");

    equal_str(string_substring("foo bar baz", 0, 3), "foo", "Gets a substring from the beginning");
    equal_str(string_substring("foo bar baz", 4, 7), "bar", "Gets a substring");
    equal_str(string_substring("foo bar baz", 0, 0), "",    "Gets an empty substring");
    equal_str(string_substring("foo bar baz", 0, 1), "f",   "Gets an one-char substring");
    equal_str(string_substring("foo",         0, 9), "foo", "Gets all when last index is greater than the text length");

    equal_str(string_trim_start("foo"         ), "foo", "Gets the complete string when no white spaces");
    equal_str(string_trim_start("\t  foo"     ), "foo", "Removes white spaces from the start and gets the string");
    equal_str(string_trim_start("   \t\r\n   "), "",    "Removes all white spaces and gets an empty string");

    equal_str(string_trim_end("foo"         ), "foo", "Gets the complete string when no white spaces");
    equal_str(string_trim_end("foo \t\n"    ), "foo", "Removes white spaces fromthe end and gets the string");
    equal_str(string_trim_end("   \t\r\n   "), "",    "Removes all white spaces and gets an empty string");

    equal_str(string_trim("foo"          ), "foo", "Gets the complete string when no white spaces");
    equal_str(string_trim("\t\t foo \t\n"), "foo", "Trims both ends");
    equal_str(string_trim("   \t\r\n    "), "",    "Removes all white spaces and gets an empty string");


    char** arr1 = NULL;
    long len1 = string_split(&arr1, "abc", "");
    equal_long(len1, 3, "Splitis to characters and gets the correct length");
    equal_str(arr1[0], "a", "The first character matches");
    equal_str(arr1[1], "b", "The second character matches");
    equal_str(arr1[2], "c", "The third character matches");
    free(arr1);

    char** arr2 = NULL;
    long len2 = string_split(&arr2, "foo", ";");
    equal_long(len2, 1, "When no splitter, gets a string array of one string");
    equal_str(arr2[0], "foo", "The first split string matches");
    free(arr2);

    char** arr3 = NULL;
    long len3 = string_split(&arr3, "foo bar baz", " ");
    equal_long(len3, 3, "Splits to 3 parts by spaces");
    equal_str(arr3[0], "foo", "foo matches");
    equal_str(arr3[1], "bar", "bar matches");
    equal_str(arr3[2], "baz", "baz matches");
    free(arr3);

    char** arr4 = NULL;
    long len4 = string_split(&arr4, ";foo", ";");
    equal_long(len4, 2, "Having a splitter at the beginning, it has the correct length");
    equal_str(arr4[0], "",    "The first string is empty");
    equal_str(arr4[1], "foo", "The second string matches");
    free(arr4);

    char** arr5 = NULL;
    long len5 = string_split(&arr5, "foo;", ";");
    equal_long(len5, 2, "Having a splitter at the end, it has the correct length");
    equal_str(arr5[0], "foo", "The first string matches");
    equal_str(arr5[1], "",    "The second string is empty");
    free(arr5);

    char** arr6 = NULL;
    long len6 = string_split(&arr6, ";foo;", ";");
    equal_long(len6, 3, "Having splitters in both ends, length match");
    equal_str(arr6[0], "",    "Have an empty string in the beginning");
    equal_str(arr6[1], "foo", "Middle string match");
    equal_str(arr6[2], "",    "Have an empty strign at the end");
    free(arr6);

    char** arr7 = NULL;
    long len7 = string_split(&arr7, ";", ";");
    equal_long(len7, 2, "Having only a splitter, it splits to two parts");
    equal_str(arr7[0], "", "The first string is empty");
    equal_str(arr7[1], "", "The second string is empty");
    free(arr7);

    char** arr8 = NULL;
    long len8 = string_split(&arr8, "", ";");
    equal_long(len8, 1, "Given an empty string, it gets one part");
    equal_str(arr8[0], "", "It is an empty string");
    free(arr8);

    return EXIT_SUCCESS;
}

