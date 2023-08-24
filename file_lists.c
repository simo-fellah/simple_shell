#include "shell.h"

/**
 * Get the history file.
 *
 * @param info - Parameter struct.
 * @return - Allocated string containing history file.
 */
char *getHistoryFile(info_t *info)
{
    char *buf, *dir;

    dir = getenvVariable(info, "HOME=");

    if (!dir)
        return (NULL);

    buf = allocateMemory(sizeof(char) * (stringLength(dir) + stringLength(HIST_FILE) + 2));

    if (!buf)
        return (NULL);

    buf[0] = 0;
    copyString(buf, dir);
    appendString(buf, "/");
    appendString(buf, HIST_FILE);

    return (buf);
}

/**
 * Write history to a file.
 *
 * @param info - Parameter struct.
 * @return - 1 on success, else -1.
 */
int writeHistory(info_t *info)
{
    ssize_t fd;
    char *filename = getHistoryFile(info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    freeMemory(filename);

    if (fd == -1)
        return (-1);

    for (node = info->history; node; node = node->next)
    {
        writeStringToFile(node->str, fd);
        writeToFile("\n", fd);
    }

    writeToFile(BUF_FLUSH, fd);
    close(fd);

    return (1);
}

/**
 * Read history from a file.
 *
 * @param info - Parameter struct.
 * @return - Histcount on success, 0 otherwise.
 */
int readHistory(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = getHistoryFile(info);

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

    buf = allocateMemory(sizeof(char) * (fsize + 1));

    if (!buf)
        return (0);

    rdlen = readFromFile(fd, buf, fsize);
    buf[fsize] = 0;

    if (rdlen <= 0)
        return (freeMemory(buf), 0);

    close(fd);

    for (i = 0; i < fsize; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = 0;
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
 * Build history list by adding an entry to a history linked list.
 *
 * @param info - Parameter struct.
 * @param buf - Buffer.
 * @param linecount - The history line count (histcount).
 * @return - Always 0.
 */
int buildHistoryList(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    addNodeEnd(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return (0);
}

/**
 * Renumber the history linked list after changes.
 *
 * @param info - Parameter struct.
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
