#include "shell.h"

/**
 * Print a string to the standard error stream.
 *
 * @param str - The string to be printed.
 * @return Nothing.
 */
void printToStderrStream(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        writeCharacterToStderrStream(str[i]);
        i++;
    }
}

/**
 * Write a character to the standard error stream.
 *
 * @param c - The character to be written.
 * @return On success, returns 1.
 * On error, returns -1, and errno is set appropriately.
 */
int writeCharacterToStderrStream(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == FLUSH_BUF || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != FLUSH_BUF)
        buf[i++] = c;

    return 1;
}

/**
 * Write a character to a given file descriptor.
 *
 * @param c - The character to be written.
 * @param fd - The file descriptor to write to.
 * @return On success, returns 1.
 * On error, returns -1, and errno is set appropriately.
 */
int writeCharacterToFileDescriptor(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == FLUSH_BUF || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != FLUSH_BUF)
        buf[i++] = c;

    return 1;
}

/**
 * Print a string to a given file descriptor.
 *
 * @param str - The string to be printed.
 * @param fd - The file descriptor to write to.
 * @return The number of characters written.
 */
int printStringToFileDescriptor(char *str, int fd)
{
    int i = 0;

    if (!str)
        return 0;

    while (*str)
    {
        i += writeCharacterToFileDescriptor(*str++, fd);
    }

    return i;
}
