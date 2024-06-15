# string helper functions in c

## API

```c
/** Allocates a new string. */
char* string_alloc(const char* text);

/** Allocates a string from a character. */
char* string_from_char(char ch);

/** Returns 1 if strings are equal or 0 atherwise. */
char string_equal(const char* a, const char* b);

/**
 * Checks if the string "text" starts with the string "search".
 * Returns 1 on success and 0 on failure.
 */
char string_starts_with(const char* text, const char* search);

/**
 * Checks if the string "text" ends with the string "search".
 * Returns 1 on success and 0 on failure.
 */
char string_ends_with(const char* text, const char* search);

/** Gets the index of "search" within "text" or -1. */
long string_index_of(const char* text, const char* search);

/** Gets the last index of "search" within "text" or -1. */
long string_last_index_of(const char* text, const char* search);

/** Gets a substring of "text" from "start_index" to "end_index" exclusuvely. */
char* string_substring(const char* text, long start_index, long end_index);

/** Trims white spaces from the start of "text" */
char* string_trim_start(const char* text);

/** Trims white spaces from the end of "text" */
char* string_trim_end(const char* text);

/** Trims "text" ifrom the start and the end */
char* string_trim(const char* text);

/**
 * Splits the "text" on "sep" into "arr".
 * Returns the count of parts.
 */
long string_split(char*** arr, const char* text, const char* sep);
```
