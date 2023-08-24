#include "shell.h"

/**
 * Copy a portion of a source string to a destination string.
 *
 * @param destination - The destination string to copy to.
 * @param source - The source string.
 * @param num - The number of characters to copy.
 * @return The resulting concatenated string.
 */
char *copySubstring(char *destination, char *source, int num)
{
    int i, j;
    char *result = destination;

    i = 0;
    while (source[i] != '\0' && i < num - 1)
    {
        destination[i] = source[i];
        i++;
    }
    
    if (i < num)
    {
        j = i;
        while (j < num)
        {
            destination[j] = '\0';
            j++;
        }
    }
    
    return result;
}

/**
 * Concatenate a portion of a source string to a destination string.
 *
 * @param destination - The destination string.
 * @param source - The source string to be concatenated.
 * @param num - The maximum number of bytes to be used.
 * @return The concatenated string.
 */
char *concatenateSubstring(char *destination, char *source, int num)
{
    int i, j;
    char *result = destination;

    i = 0;
    while (destination[i] != '\0')
        i++;

    j = 0;
    while (source[j] != '\0' && j < num)
    {
        destination[i] = source[j];
        i++;
        j++;
    }

    if (j < num)
        destination[i] = '\0';

    return result;
}

/**
 * Locate a character in a given string.
 *
 * @param string - The string to be searched.
 * @param character - The character to find.
 * @return A pointer to the memory area containing the character, or NULL if not found.
 */
char *findCharacter(char *string, char character)
{
    do {
        if (*string == character)
            return string;
    } while (*string++ != '\0');

    return NULL;
}
