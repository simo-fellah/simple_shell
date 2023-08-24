#include "shell.h"

/**
 * Fills memory with a constant byte.
 *
 * @param s - Pointer to the memory area.
 * @param b - The byte to fill *s with.
 * @param n - The number of bytes to be filled.
 * @return - A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
        s[i] = b;
    return s;
}

/**
 * Frees a string of strings.
 *
 * @param pp - String of strings to be freed.
 */
void ffree(char **pp)
{
    char **a = pp;

    if (!pp)
        return;
    while (*pp)
    {
        free(*pp);
        pp++;
    }
    free(a);
}

/**
 * Reallocates a block of memory.
 *
 * @param ptr - Pointer to the previous malloc'ated block.
 * @param old_size - Byte size of the previous block.
 * @param new_size - Byte size of the new block.
 * @return - Pointer to the reallocated block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;

    if (!ptr)
        return malloc(new_size);
    if (!new_size)
    {
        free(ptr);
        return NULL;
    }
    if (new_size == old_size)
        return ptr;

    p = malloc(new_size);
    if (!p)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
        p[old_size] = ((char *)ptr)[old_size];
    free(ptr);
    return p;
}
