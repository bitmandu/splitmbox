/**
 * @file split.c
 *
 * Mailbox splitting functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mbox.h"

/**
 * Compare two messages by delivery date.
 *
 * @param x Message 1
 * @param y Message 2
 *
 * @return -1: if x is older than y
 *          0: if x and y have the same delivery date
 *          1: if x is newer than y
 */
int compare(const void *x, const void *y)
{
    struct tm xtm, ytm;
    time_t tx, ty;

    mbox_time(*(char **)x, &xtm);
    mbox_time(*(char **)y, &ytm);

    tx = mktime(&xtm);
    ty = mktime(&ytm);

    return (tx < ty) ? -1 : ((tx == ty) ? 0 : 1);
}

/**
 * Write messages to file(s) by month.
 *
 * @param messages Array of messages
 * @param n Number of messages
 *
 * @return Error if unable to open output file(s)
 */
int write_by_month(char *messages[], long n)
{
    int month, open_month = 0;
    char filename[12];
    struct tm time;
    FILE *out = NULL;

    qsort(messages, n, sizeof(char *), compare);

    for (long i = 0; i < n; i++) {
        mbox_time(messages[i], &time);
        month = time.tm_mon;

        // open new output file for the next month
        if (month != open_month) {
            if (out != NULL) {
                fclose(out);
            }

            strftime(filename, 12, "%Y%m.mbox", &time);
            if ((out = fopen(filename, "w")) == NULL) {
                fprintf(stderr, "Unable to open outfile %s\n", filename);
                return 1;
            }

            open_month = month;
        }

        fprintf(out, "%s\n", messages[i]);
    }

    fclose(out);
    return 0;
}
