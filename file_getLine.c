#include "shell.h"

/**
 * Buffer chained commands for processing.
 *
 * @param info - Parameter struct.
 * @param buf - Address of the buffer.
 * @param len - Address of the length variable.
 * @return Bytes read.
 */
ssize_t bufferChainedCommands(info_t *info, char **buf, size_t *len)
{
    ssize_t bytesRead = 0;
    size_t len_p = 0;

    if (!*len) // If nothing left in the buffer, fill it
    {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, handleSIGINT);
#if USE_GETLINE
        bytesRead = getline(buf, &len_p, stdin);
#else
        bytesRead = getLine(info, buf, &len_p);
#endif
        if (bytesRead > 0)
        {
            if ((*buf)[bytesRead - 1] == '\n')
            {
                (*buf)[bytesRead - 1] = '\0'; // Remove trailing newline
                bytesRead--;
            }
            info->linecount_flag = 1;
            removeComments(*buf);
            buildHistoryList(info, *buf, info->histcount++);
            *len = bytesRead;
            info->cmd_buf = buf;
        }
    }
    return bytesRead;
}

/**
 * Get user input and process command chains.
 *
 * @param info - Parameter struct.
 * @return Bytes read.
 */
ssize_t getUserInput(info_t *info)
{
    static char *buf; // The ';' command chain buffer
    static size_t i, j, len;
    ssize_t bytesRead = 0;
    char **buf_p = &(info->arg), *p;

    putchar(BUF_FLUSH);
    bytesRead = bufferChainedCommands(info, &buf, &len);
    if (bytesRead == -1) // EOF
        return -1;

    if (len) // We have commands left in the chain buffer
    {
        j = i;
        p = buf + i;

        checkCommandChain(info, buf, &j, i, len);
        while (j < len)
        {
            if (isCommandChain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1;
        if (i >= len)
        {
            i = len = 0;
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p;
        return strlen(p);
    }

    *buf_p = buf;
    return bytesRead;
}

/**
 * Read from a buffer.
 *
 * @param info - Parameter struct.
 * @param buf - Buffer.
 * @param i - Size.
 * @return Bytes read.
 */
ssize_t readBuffer(info_t *info, char *buf, size_t *i)
{
    ssize_t bytesRead = 0;

    if (*i)
        return 0;
    
    bytesRead = read(info->readfd, buf, READ_BUF_SIZE);
    if (bytesRead >= 0)
        *i = bytesRead;
    
    return bytesRead;
}

/**
 * Get the next line of input from STDIN.
 *
 * @param info - Parameter struct.
 * @param ptr - Address of pointer to buffer, preallocated or NULL.
 * @param length - Size of preallocated ptr buffer if not NULL.
 * @return Size of the input.
 */
int getLine(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t bytesRead = 0, inputSize = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        inputSize = *length;

    if (i == len)
        i = len = 0;

    bytesRead = readBuffer(info, buf, &len);
    if (bytesRead == -1 || (bytesRead == 0 && len == 0))
        return -1;

    c = findCharacter(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;

    new_p = reallocateBuffer(p, inputSize, k);
    if (!new_p)
        return (p ? (free(p), -1) : -1);

    if (inputSize)
        concatenateSubstring(new_p, buf + i, k - i);
    else
        copySubstring(new_p, buf + i, k - i + 1);

    inputSize += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = inputSize;
    
    *ptr = p;
    return inputSize;
}

/**
 * Handle SIGINT (Ctrl+C) signal.
 *
 * @param signalNumber - The signal number.
 * @return Void.
 */
void handleSIGINT(__attribute__((unused))int signalNumber)
{
    puts("\n$ ");
    putchar(BUF_FLUSH);
}
