#include "shell.h"

/**
 * Terminate the shell.
 *
 * @param shellInfo - Structure containing potential arguments.
 * @return Returns the exit status.
 * (0) if shellInfo->argv[0] is not "exit".
 */
int terminateShell(shell_info_t *shellInfo)
{
    int exitStatus;

    if (shellInfo->argv[1]) // If there is an exit argument
    {
        exitStatus = parseExitCode(shellInfo->argv[1]);
        if (exitStatus == -1)
        {
            shellInfo->status = 2;
            printErrorMessage(shellInfo, "Illegal number: ");
            printStringMessage(shellInfo->argv[1]);
            printCharacter('\n');
            return 1;
        }
        shellInfo->error_num = parseExitCode(shellInfo->argv[1]);
        return -2;
    }
    shellInfo->error_num = -1;
    return -2;
}

/**
 * Change the current working directory of the process.
 *
 * @param shellInfo - Structure containing potential arguments.
 * @return Always returns 0.
 */
int changeWorkingDirectory(shell_info_t *shellInfo)
{
    char *currentDir, *newDir, buffer[1024];
    int chdirResult;

    currentDir = getCurrentDirectory(buffer, 1024);
    if (!currentDir)
        printStringMessage("TODO: >>getcwd failure emsg here<<\n");

    if (!shellInfo->argv[1])
    {
        newDir = getEnvironmentVar(shellInfo, "HOME=");
        if (!newDir)
            chdirResult = /* TODO: What should this be? */
                changeDir((newDir = getEnvironmentVar(shellInfo, "PWD=")) ? newDir : "/");
        else
            chdirResult = changeDir(newDir);
    }
    else if (compareStrings(shellInfo->argv[1], "-") == 0)
    {
        if (!getEnvironmentVar(shellInfo, "OLDPWD="))
        {
            printStringMessage(currentDir);
            printCharacter('\n');
            return 1;
        }
        printStringMessage(getEnvironmentVar(shellInfo, "OLDPWD="));
        printCharacter('\n');
        chdirResult = /* TODO: What should this be? */
            changeDir((newDir = getEnvironmentVar(shellInfo, "OLDPWD=")) ? newDir : "/");
    }
    else
    {
        chdirResult = changeDir(shellInfo->argv[1]);
    }

    if (chdirResult == -1)
    {
        printErrorMessage(shellInfo, "can't cd to ");
        printStringMessage(shellInfo->argv[1]);
        printCharacter('\n');
    }
    else
    {
        setEnvironmentVar(shellInfo, "OLDPWD", getEnvironmentVar(shellInfo, "PWD="));
        setEnvironmentVar(shellInfo, "PWD", getCurrentDirectory(buffer, 1024));
    }

    return 0;
}

/**
 * Display help information (not yet implemented).
 *
 * @param shellInfo - Structure containing potential arguments.
 * @return Always returns 0.
 */
int showHelp(shell_info_t *shellInfo)
{
    char **argArray;

    argArray = shellInfo->argv;
    printStringMessage("Help call works. Function not yet implemented \n");
    if (0)
        printStringMessage(*argArray); // Temporary workaround for unused variable warning
    return 0;
}
