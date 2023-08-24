#include "shell.h"

/**
 * Display the current environment variables.
 *
 * @param shellInfo - Structure containing potential arguments.
 * @return Always returns 0.
 */
int showEnvironment(shell_info_t *shellInfo)
{
    printStringList(shellInfo->env);
    return 0;
}

/**
 * Get the value of an environment variable.
 *
 * @param shellInfo - Structure containing potential arguments.
 * @param name - The name of the environment variable.
 * @return Returns the value of the environment variable.
 */
char *getEnvVariable(shell_info_t *shellInfo, const char *name)
{
    list_t *node = shellInfo->env;
    char *value;

    while (node)
    {
        value = startsWith(node->str, name);
        if (value && *value)
            return value;
        node = node->next;
    }
    return NULL;
}

/**
 * Initialize a new environment variable or modify an existing one.
 *
 * @param shellInfo - Structure containing potential arguments.
 * @return Always returns 0.
 */
int setEnvVariable(shell_info_t *shellInfo)
{
    if (shellInfo->argc != 3)
    {
        printErrorMessage("Incorrect number of arguments\n");
        return 1;
    }
    if (updateEnvVariable(shellInfo, shellInfo->argv[1], shellInfo->argv[2]))
        return 0;
    return 1;
}

/**
 * Remove an environment variable.
 *
 * @param shellInfo - Structure containing potential arguments.
 * @return Always returns 0.
 */
int unsetEnvVariable(shell_info_t *shellInfo)
{
    int i;

    if (shellInfo->argc == 1)
    {
        printErrorMessage("Too few arguments.\n");
        return 1;
    }

    for (i = 1; i < shellInfo->argc; i++)
        removeEnvVariable(shellInfo, shellInfo->argv[i]);

    return 0;
}

/**
 * Populate the environment linked list.
 *
 * @param shellInfo - Structure containing potential arguments.
 * @return Always returns 0.
 */
int populateEnvList(shell_info_t *shellInfo)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        addNodeToEnd(&node, environ[i], 0);

    shellInfo->env = node;
    return 0;
}
