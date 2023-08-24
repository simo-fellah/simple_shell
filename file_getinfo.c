#include "shell.h"

/**
 * Get the array of environment strings.
 *
 * @param info - Structure containing potential arguments.
 * @return - Pointer to the array of environment strings.
 */
char **getEnvironmentStrings(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = listToStringArray(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * Remove an environment variable.
 *
 * @param info - Structure containing potential arguments.
 * @param var - The string environment variable property.
 * @return - 1 if deleted, 0 otherwise.
 */
int unsetEnvironmentVariable(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

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
    return (info->env_changed);
}

/**
 * Initialize a new environment variable or modify an existing one.
 *
 * @param info - Structure containing potential arguments.
 * @param var - The string environment variable property.
 * @param value - The string environment variable value.
 * @return - Always 0.
 */
int setEnvironmentVariable(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return (0);

    buf = allocateMemory(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return (1);
    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->env;
    while (node)
    {
        p = startsWith(node->str, var);
        if (p && *p == '=')
        {
            freeMemory(node->str);
            node->str = buf;
            info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    addNodeToEnd(&(info->env), buf, 0);
    freeMemory(buf);
    info->env_changed = 1;
    return (0);
}
