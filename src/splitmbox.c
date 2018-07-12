/**
 * @file splitmbox.c
 *
 * Split email mbox into seperate YYYYMM.mbox files based on date.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "alloc.h"
#include "mbox.h"
#include "split.h"

/**
 * Maximum number of messages in mbox.
 */
#define MAX_MESSAGES 500000

/**
 * Splits mbox (received on standard input) into seperate YYYYMM.mbox
 * files for each month.
 *
 * @return Error if unable to read mbox
 */
int main(void)
{
    char *mbox;
    char **messages;
    int n;   // number of messages

    mbox = malloc(ALLOCSIZE*sizeof(char));
    messages = (char **) malloc(MAX_MESSAGES*sizeof(char *));

    n = mbox_read(mbox, messages, MAX_MESSAGES);
    if (n == -1) {
        fprintf(stderr, "Input mbox too large\n");
        return EXIT_FAILURE;
    }

    write_by_month(messages, n);

    free(messages);
    free(mbox);
    return EXIT_SUCCESS;
}
