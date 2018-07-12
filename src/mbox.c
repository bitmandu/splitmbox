/**
 * @file mbox.c
 *
 * Email mbox utilities.
 */

#define _POSIX_C_SOURCE 200809L  // for getline()
#define _XOPEN_SOURCE            // for strptime()

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "alloc.h"
#include "mbox.h"

/**
 * Message sender envelope.
 *
 * @param message Message
 * @param[out] envsender Sender envelope (null terminated)
 * @param n Length of envsender
 *
 * @return Error if envelope is greater than n characters
 */
int mbox_envsender(const char *message, char *envsender, int n)
{
    char c;

    for (int i = 0; i < n; i++) {
        c = *(message + 5 + i);  // +5 skips "From "

        *(envsender + i) = c;
        if (c == ' ') {
            *(envsender + i) = '\0';
            return 0;
        }
    }

    envsender[n-1] = '\0';
    return 1;
}

/**
 * Header (first line) of mbox message.
 *
 * @param message Message
 * @param[out] header Header (null terminated)
 * @param n Length of header
 *
 * @return Error if header is not valid
 */
int mbox_header(const char *message, char *header, int n)
{
    char c;

    for (int i = 0; i < n; i++) {
        c = *(message + i);
        if (c == '\r' || c == '\n') {
            *(header + i) = '\0';
            return strncmp(header, "From ", 5);
        }

        *(header + i) = c;
    }

    header[n-1] = '\0';
    return 1;
}

/**
 * Message delivery time.
 *
 * @param message Message
 * @param[out] time Delivery time
 *
 * @return Error if unable to match header time format
 */
int mbox_time(const char *message, struct tm *time)
{
    const char *datestr = NULL;
    const int n = 128;      // number of characters to parse
    bool foundit = false;

    // figure out where the date string starts
    for (int i = 5; i < n; i++) {
        if (*(message + i) == ' ') {
            // foundit becomes true after the sender envelope, and is
            // reassigned true until the first non-whitespace character
            foundit = true;
            continue;
        } else if (foundit) {
            datestr = message + i;
            break;
        }
    }

    // try different datetime formats until one works
    char *format[2] = {
        "%a %b %d %H:%M:%S %z %Y",  // option 1: used by Google
        "%a %b %d %H:%M:%S %Y"};    // option 2: mbox standard format

    for (int i = 0; i < 2; i++) {
        if (strptime(datestr, format[i], time) != NULL) {
            time->tm_isdst = -1;  // tell mktime() to check for DST
            return 0;
        }
    }

    perror(__func__);
    return 1;
}

/**
 * Read mbox from standard input.
 *
 * @param[out] mbox Pointer to allocated character buffer
 * @param[out] messages Array of pointers to each message
 * @param n Length of messages array
 *
 * @return Number of messages or -1 if there is insufficient memory
 */
int mbox_read(char *mbox, char *messages[], unsigned long n)
{
    char *p;     // pointer to next available mememory address in mbox
    size_t len;  // line length

    // these settings tell getline() to use malloc() to allocate *line
    char *line = NULL;
    size_t size = 0;

    unsigned long i = 0;
    while ((len = getline(&line, &size, stdin))) {
        if (len == -1) {
            free(line);

            // terminate the last message in mbox
            p = alloc(mbox, 1);
            *p = '\0';

            return i;
        }

        p = alloc(mbox, len);
        if (p == NULL || i == n) {
            return -1;
        }

        strcpy(p, line);

        // check if this line is the beginning of a message
        if (strncmp(line, "From ", 5) == 0) {
            messages[i] = p;

            // terminate the previous message
            if (i > 0) {
                *(p-1) = '\0';
            }

            i++;
        }
    }

    return -1;
}
