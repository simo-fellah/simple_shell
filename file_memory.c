#include "shell.h"

/**
 * Frees a pointer and sets its address to NULL.
 *
 * @param ptr - Address of the pointer to be freed.
 * @return - 1 if freed successfully, otherwise 0.
 */
int bfree(void **ptr)
{
    if (ptr && *ptr)
    {
        freeMemory(*ptr);
        *ptr = NULL;
        return 1;
    }
    return 0;
}
