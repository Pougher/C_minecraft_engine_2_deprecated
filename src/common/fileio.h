#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

// Reads a file into a character buffer. This is allocated on the heap and
// therefore must be freed after you are finished using it. Returns NULL if the
// file cannot be read, so therefore it is advised that you check for null
// pointers after calling this function.
char *read_file(char*);

// Writes a character buffer to a file. If the file already exists, then in is
// overwritten with the data supplied to the function
void write_file(char*, char*, size_t);

#endif
