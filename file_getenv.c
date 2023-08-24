#include "shell.h"

/**
 * Retrieve the copy of the environment as a string array.
 *
 * @param info - Parameter struct.
 * @return String array copy of the environment.
 */
char **getEnvironment(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = convertListToStrings(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * Remove an environment variable.
 *
 * @param info - Parameter struct.
 * @param var - The string env var property.
 * @return 1 on delete, 0 otherwise.
 */
int unsetEnvironmentVariable(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return 0;

    while (node)
    {
        p = startsWith(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = deleteNodeAtIndex(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return info->env_changed;
}

/**
 * Initialize a new environment variable or modify an existing one.
 *
 * @param info - Parameter struct.
 * @param var - The string env var property.
 * @param value - The string env var value.
 * @return Always 0.
 */
int setEnvironmentVariable(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return 0;

    buf = malloc(strlen(var) + strlen(value) + 2);
    if (!buf)
        return 1;
    copyString(buf, var);
    concatenateString(buf, "=");
    concatenateString(buf, value);
    node = info->env;
    while (node)
    {
        p = startsWith(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return 0;
        }
        node = node->next;
    }
    addNodeEnd(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return 0;
}
