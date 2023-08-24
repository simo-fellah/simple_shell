#include "shell.h"

/**
 * Convert a string to an integer, handling errors.
 *
 * @param str - The string to be converted.
 * @return Returns the converted number, or -1 on error.
 */
int safeAtoi(char *str)
{
    int i = 0;
    unsigned long int result = 0;

    if (*str == '+')
        str++;  /* TODO: Investigate why this affects return value */

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            result *= 10;
            result += (str[i] - '0');
            if (result > INT_MAX)
                return -1;
        }
        else
            return -1;
    }

    return result;
}

/**
 * Print an error message with relevant information.
 *
 * @param info - The parameter and return info struct.
 * @param errorString - String containing the specified error type.
 * @return Nothing.
 */
void printErrorInfo(info_t *info, char *errorString)
{
    printToStderrStream(info->fname);
    printToStderrStream(": ");
    printDec(info->line_count, STDERR_FILENO);
    printToStderrStream(": ");
    printToStderrStream(info->argv[0]);
    printToStderrStream(": ");
    printToStderrStream(errorString);
}

/**
 * Print a decimal (integer) number to a given file descriptor.
 *
 * @param num - The number to be printed.
 * @param fd - The file descriptor to write to.
 * @return The number of characters printed.
 */
int printDecimal(int num, int fd)
{
    int (*writeChar)(char) = writeCharacterToFd;
    int i, count = 0;
    unsigned int absValue, current;

    if (fd == STDERR_FILENO)
        writeChar = writeCharacterToStderrStream;

    if (num < 0)
    {
        absValue = -num;
        writeChar('-');
        count++;
    }
    else
    {
        absValue = num;
    }

    current = absValue;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absValue / i)
        {
            writeChar('0' + current / i);
            count++;
        }
        current %= i;
    }

    writeChar('0' + current);
    count++;

    return count;
}

/**
 * Convert a number to a string representation in a given base.
 *
 * @param num - The number.
 * @param base - The base for conversion.
 * @param flags - Flags for formatting.
 * @return The string representation of the number.
 */
char *convertToBaseString(long int num, int base, int flags)
{
    static char *digitArray;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }

    digitArray = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = digitArray[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;

    return ptr;
}

/**
 * Remove comments from a string by replacing the first instance of '#' with '\0'.
 *
 * @param buffer - Address of the string to modify.
 * @return Nothing.
 */
void removeComment(char *buffer)
{
    int i;

    for (i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
        {
            buffer[i] = '\0';
            break;
        }
    }
}
