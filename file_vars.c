#include "shell.h"

/**
 * _strncpy - Copies up to n characters from the source string to destination.
 *
 * @param dest - Destination buffer.
 * @param src - Source string.
 * @param n - Maximum number of characters to copy.
 * @return - Pointer to destination buffer.
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < n; i++)
		dest[i] = '\0';
	return dest;
}

/**
 * _strncat - Appends up to n characters from the source string to destination.
 *
 * @param dest - Destination buffer.
 * @param src - Source string.
 * @param n - Maximum number of characters to append.
 * @return - Pointer to destination buffer.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return dest;
}

/**
 * _strndup - Duplicates up to n characters of a string.
 *
 * @param str - Source string.
 * @param n - Maximum number of characters to duplicate.
 * @return - Pointer to the duplicated string.
 */
char *_strndup(const char *str, size_t n)
{
	size_t len = _strlen(str);
	if (n < len)
		len = n;
	char *new_str = malloc(len + 1);
	if (new_str == NULL)
		return NULL;
	_strncpy(new_str, str, len);
	new_str[len] = '\0';
	return new_str;
}
