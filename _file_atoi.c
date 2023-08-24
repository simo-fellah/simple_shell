#include "shell.h"
/**
 * Checks if the shell is currently operating in interactive mode.
 *
 * @param addrInfo - Structure containing address information.
 * @return Returns 1 if the shell is in interactive mode, 0 otherwise.
 */
int isInteractiveMode(addr_info_t *addrInfo)
{
    return (isatty(STDIN_FILENO) && addrInfo->fileDesc <= 2);
}

/**
 * Checks if a character is a delimiter.
 *
 * @param character - The character to be checked.
 * @param delimiter - The delimiter string.
 * @return Returns 1 if the character is a delimiter, 0 otherwise.
 */
int isDelimiter(char character, char *delimiter)
{
    while (*delimiter)
    {
        if (*delimiter++ == character)
            return (1);
    }
    return (0);
}

/**
 * Checks if a character is an alphabetic character.
 *
 * @param character - The character to be checked.
 * @return Returns 1 if the character is an alphabetic character, 0 otherwise.
 */
int isAlphabetic(int character)
{
    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 * Converts a string to an integer.
 *
 * @param inputString - The string to be converted.
 * @return Returns 0 if there are no numbers in the string, otherwise the converted number.
 */
int convertStringToInt(char *inputString)
{
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0; inputString[i] != '\0' && flag != 2; i++)
    {
        if (inputString[i] == '-')
            sign *= -1;

        if (inputString[i] >= '0' && inputString[i] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (inputString[i] - '0');
        }
        else if (flag == 1)
            flag = 2;
    }

    if (sign == -1)
        output = -result;
    else
        output = result;

    return (output);
}
