#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 *
 * @param s - The string whose length to check.
 * @return - Integer length of the string.
 */
int _strlen(const char *s)
{
    int i = 0;

    if (!s)
        return 0;

    while (*s++)
        i++;
    return i;
}

/**
 * _strcmp - Performs lexicographic comparison of two strings.
 *
 * @param s1 - The first string.
 * @param s2 - The second string.
 * @return - Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 */
int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }
    if (*s1 == *s2)
        return 0;
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if a string starts with a substring.
 *
 * @param haystack - String to search.
 * @param needle - The substring to find.
 * @return - Address of the next char of haystack if found, or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
    while (*needle)
    {
        if (*needle++ != *haystack++)
            return NULL;
    }
    return (char *)haystack;
}

/**
 * _strcat - Concatenates two strings.
 *
 * @param dest - The destination buffer.
 * @param src - The source buffer.
 * @return - Pointer to the destination buffer.
 */
char *_strcat(char *dest, const char *src)
{
    char *ret = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return ret;
}
