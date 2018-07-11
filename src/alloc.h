/**
 * @file alloc.h
 *
 * Allocation function prototypes and definitions.
 */

#pragma once

/**
 * Buffer size.
 */
#define ALLOCSIZE 8589934592ULL  // 8 GBi

char *alloc(char *, int);
