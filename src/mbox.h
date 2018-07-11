/**
 * @file mbox.h
 *
 * Email mbox function declarations and definitions.
 */

#pragma once

int mbox_envsender(const char *, char *, int);
int mbox_header(const char *, char *, int);
int mbox_time(const char *, struct tm *);
int mbox_read(char *, char **, unsigned long);
