#include "shell.h"

/**
 * Get the history file path.
 *
 * @param info - Structure containing potential arguments.
 * @return - Allocated string containing the history file path.
 */
char *getHistoryFilePath(info_t *info)
{
    char *buf, *dir;

    dir = _getenv(info, "HOME=");
    if (!dir)
        return (NULL);
    buf = allocateMemory(_strlen(dir) + _strlen(HIST_FILE) + 2);
    if (!buf)
        return (NULL);
    buf[0] = '\0';
    _strcpy(buf, dir);
    _strcat(buf, "/");
    _strcat(buf, HIST_FILE);
    return (buf);
}

/**
 * Write history entries to a file.
 *
 * @param info - The parameter struct.
 * @return - 1 on success, -1 on failure.
 */
int writeHistoryToFile(info_t *info)
{
    ssize_t fd;
    char *filename = getHistoryFilePath(info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    freeMemory(filename);
    if (fd == -1)
        return (-1);

    for (node = info->history; node; node = node->next)
    {
        _putsToFile(node->str, fd);
        _putcharToFile('\n', fd);
    }

    _putcharToFile(BUF_FLUSH, fd);
    close(fd);
    return (1);
}

/**
 * Read history entries from a file.
 *
 * @param info - The parameter struct.
 * @return - histcount on success, 0 otherwise.
 */
int readHistoryFromFile(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = getHistoryFilePath(info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    freeMemory(filename);
    if (fd == -1)
        return (0);

    if (!fstat(fd, &st))
        fsize = st.st_size;

    if (fsize < 2)
        return (0);

    buf = allocateMemory(fsize + 1);
    if (!buf)
        return (0);

    rdlen = read(fd, buf, fsize);
    buf[fsize] = '\0';

    if (rdlen <= 0)
        return (freeMemory(buf), 0);

    close(fd);

    for (i = 0; i < fsize; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            buildHistoryList(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != i)
        buildHistoryList(info, buf + last, linecount++);

    freeMemory(buf);
    info->histcount = linecount;

    while (info->histcount-- >= HIST_MAX)
        deleteNodeAtIndex(&(info->history), 0);

    renumberHistory(info);
    return (info->histcount);
}

/**
 * Add an entry to the history linked list.
 *
 * @param info - Structure containing potential arguments.
 * @param buf - The buffer to add.
 * @param linecount - The history line count.
 * @return - Always 0.
 */
int buildHistoryList(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    addNodeToEnd(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return (0);
}

/**
 * Renumber the history linked list after changes.
 *
 * @param info - Structure containing potential arguments.
 * @return - The new histcount.
 */
int renumberHistory(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return (info->histcount = i);
}
