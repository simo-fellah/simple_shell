#include "shell.h"

/**
 * Checks if a file is an executable command.
 *
 * @param info - The info struct (unused).
 * @param path - Path to the file.
 * @return - 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    (void)info; // Unused info parameter
    if (!path || stat(path, &st) != 0)
        return 0;

    return (st.st_mode & S_IFREG) ? 1 : 0;
}

/**
 * Duplicates characters from a given path string.
 *
 * @param pathstr - The PATH string.
 * @param start - Starting index.
 * @param stop - Stopping index.
 * @return - Pointer to a new buffer containing duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i, k = 0;

    for (i = start; i < stop && k < sizeof(buf) - 1; i++)
    {
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
    }
    buf[k] = '\0';
    return buf;
}

/**
 * Finds the full path of a command in the PATH string.
 *
 * @param info - The info struct (unused).
 * @param pathstr - The PATH string.
 * @param cmd - The command to find.
 * @return - Full path of the command if found, or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return NULL;

    if (_strlen(cmd) > 2 && starts_with(cmd, "./") && is_cmd(info, cmd))
    {
        return cmd;
    }

    while (pathstr[i] != '\0')
    {
        if (pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);
            if (*path == '\0')
                _strcpy(path, cmd);
            else
                _strcat(path, "/");
            _strcat(path, cmd);

            if (is_cmd(info, path))
                return path;

            curr_pos = i + 1;
        }
        i++;
    }

    path = dup_chars(pathstr, curr_pos, i);
    if (*path == '\0')
        _strcpy(path, cmd);
    else
        _strcat(path, "/");
    _strcat(path, cmd);

    if (is_cmd(info, path))
        return path;

    return NULL;
}
