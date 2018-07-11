/**
 * @file alloc.c
 *
 * Allocate a character buffer.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc.h"

/**
 * Pointer to next free position in buffer.
 */
static char *allocptr = NULL;

/**
 * Allocate n more characters of memory.
 *
 * @param buffer Character buffer
 * @param n Number of characters
 *
 * @return Pointer to available memory address or NULL
 */
char *alloc(char *buffer, int n)
{
    // first call only:
    if (allocptr == NULL) {
        allocptr = buffer;
    }

    if (buffer + ALLOCSIZE - allocptr >= n) {
        allocptr += n;
    } else {
        fprintf(stderr, "Out of memory: Increase ALLOCSIZE in alloc.h\n");
        return NULL;
    }

    return allocptr - n;
}
