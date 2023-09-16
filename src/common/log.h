#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Logs an error to stderr
void log_error(char*);

// Logs info to stdout
void log_info(char*);

// Logs a warning to stdout
void log_warning(char*);

#endif
