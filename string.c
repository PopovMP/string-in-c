#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Returns 1 if strings are equal or 0 atherwise. */
char string_equal(const char* a, const char* b) {
    for (long i = 0;; ++i) {
        const char ca = a[i];
        const char cb = b[i];
        if (ca != cb) return 0;
        if (ca == '\0' && cb == '\0') return 1;
    }
}

/** Allocates a new string. */
char* string_alloc(const char* text) {
    const long len = (long) strlen(text);
    char* str = malloc(sizeof(char) * (len + 1));

    for (long i = 0; i <= len; ++i)
        str[i] = text[i];

    return str;
}

/** Allocates a string from a character. */
char* string_from_char(char ch) {
    char* str = malloc(sizeof(char) * 2);
    str[0] = ch;
    str[1] = '\0';

    return str;
}

/**
 * Checks if the string "text" starts with the string "search".
 * Returns 1 on success and 0 on failure.
 */
char string_starts_with(const char* text, const char* search) {
    for (long i = 0;; ++i) {
        const char ct = text[i];
        const char cs = search[i];
        if (cs == '\0') return 1;
        if (ct == '\0') return 0;
        if (ct !=  cs ) return 0;
    }
}

/**
 * Checks if the string "text" ends with the string "search".
 * Returns 1 on success and 0 on failure.
 */
char string_ends_with(const char* text, const char* search) {
    const long text_len   = (long) strlen(text);
    const long search_len = (long) strlen(search);

    if (text_len < search_len) return 0;

    for (long i = search_len - 1; i >= 0; --i)
        if (text[text_len - i - 1] != search[search_len - i - 1])
            return 0;

    return 1;
}

/** Gets the index of "search" within "text" or -1. */
long string_index_of(const char* text, const char* search) {
    const long len = (long) strlen(text);

    for (long i = 0; i < len; ++i)
        if (string_starts_with(text + i, search))
            return i;

    return -1;
}

/** Gets the last index of "search" within "text" or -1. */
long string_last_index_of(const char* text, const char* search) {
    const long text_len   = (long) strlen(text);
    const long search_len = (long) strlen(search);

    if (text_len < search_len)
        return -1;

    for (long i = text_len - search_len; i >= 0; --i)
        if (string_starts_with(text + i, search))
            return i;

    return -1;
}

/** Gets a substring of "text" from "start_index" to "end_index" exclusuvely. */
char* string_substring(const char* text, long start_index, long end_index) {
    const long text_len = strlen(text);

    if (end_index < start_index || start_index > text_len)
        return NULL;

    if (end_index > text_len)
        end_index = text_len;

    const long len = end_index - start_index;
    char* str = malloc(sizeof(char) * (len + 1));

    for (long i = 0; i < len; ++i)
        str[i] = text[start_index + i];

    str[len] = '\0';

    return str;
}

/** Trims white spaces from the start of "text" */
char* string_trim_start(const char* text) {
    const long len = (long) strlen(text);

    if (len == 0)
        return string_alloc("");

    long i = 0;

    char ch;
    while ((ch = text[i]) &&
           (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r'))
        ++i;

    if (i == len)
        return string_alloc("");

    return string_substring(text, i, len);
}

/** Trims white spaces from the end of "text" */
char* string_trim_end(const char* text) {
    const long len = (long) strlen(text);

    if (len == 0)
        return string_alloc("");

    long i = len - 1;

    while (i >= 0) {
        const char ch = text[i];
        if (ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r')
            break;
        --i;
    }

    if (i < 0)
        return string_alloc("");

    return string_substring(text, 0, i + 1);
}

/** Trims "text" ifrom the start and the end */
char* string_trim(const char* text) {
    char* trim_a = string_trim_start(text);
    char* trim_b = string_trim_end(trim_a);
    free(trim_a);

    return trim_b;
}

/**
 * Splits the "text" on "sep" into "arr".
 * Returns the count of parts.
 */
long string_split(char*** arr, const char* text, const char* sep) {
    const long sep_len  = (long) strlen(sep);
    const long text_len = (long) strlen(text);

    /* Split the characters */
    if (sep_len == 0) {
        *arr = malloc(sizeof(char*) * text_len);
        for (int i = 0; i < text_len; ++i)
            (*arr)[i] = string_from_char(text[i]);
        return text_len;
    }

    long to_index = string_index_of(text, sep);

    /* Sets an array with one string */
    if (to_index == -1) {
        *arr = malloc(sizeof(char*));
        (*arr)[0] = string_alloc(text);
        return 1;
    }

    long from_index   = 0;
    long arr_len      = 0;
    long arr_capacity = 1024;
    *arr = malloc(sizeof(char*) * arr_capacity);

    while (1) {
        /* Having separator at the end, add an empty string and return. */
        if (from_index == text_len) {
            (*arr)[arr_len] = string_alloc("");
            ++arr_len;
            *arr = realloc(*arr, sizeof(char*) * arr_len);
            return arr_len;
        }

        /* Search the next index from the current position. */
        to_index = string_index_of(text + from_index, sep);

        /* The separator is not found anymore. Add the last part and return. */
        if (to_index == -1) {
            (*arr)[arr_len] = string_substring(text, from_index, text_len);
            ++arr_len;
            *arr = realloc(*arr, sizeof(char*) * arr_len);
            return arr_len;
        }

        /* Correct "from_index" to start from the beggining of the "text". */
        to_index += from_index;

        /* Add a part */
        (*arr)[arr_len] = string_substring(text, from_index, to_index);
        ++arr_len;

        /* Expand the array if necessery. */
        if (arr_len == arr_capacity) {
            arr_capacity *= 2;
            *arr = realloc(*arr, sizeof(char*) * arr_capacity);
        }

        from_index = to_index + sep_len;
    }
}

