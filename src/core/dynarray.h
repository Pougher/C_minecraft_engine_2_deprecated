#ifndef DYN_ARRAY
#define DYN_ARRAY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/types.h"

// the number of times the reserve queue can be used for memory allocation
// before it has to be refreshed
#define RESERVE_QUEUE_REFRESH 20

typedef struct {
    // the length or number of elements currently within the data structure
    size_t length;

    // the maximum capacity that the data structure can hold
    size_t cap;

    // the size of each element in the array
    size_t elem_size;

    // the reserved deletion queue
    size_t *reserve_queue;

    // the length of the reserved deletion queue
    size_t reserve_queue_size;

    // the array of pointers to data that can be allocated on the top of the
    // vector
    void *data;

    // the number of times the reserve queue has been used to fill in values
    // marked for deletion in the array
    i32 reserve_queue_uses;
} DynArray;

// Creates a new generic dynamic array. The capacity and the length are
// initialized to zero
DynArray *dynarray_new(size_t);

// Pushes an element to the end of the array. If the length of the array plus
// the new element is greater than the capacity of the array, the capacity
// is doubled and the data is reallocated.
void dynarray_push(DynArray*, void*);

// Deletes the top value from the array
void dynarray_pop(DynArray*);

// Frees all memory allocated to the dynamic array, also frees the dynamic
// array object itself
void dynarray_free(DynArray*);

// Deletes an index in a dynamic array
void dynarray_delete(DynArray*, size_t);

// Reserves a location in the dynamic array for deletion the next time an
// element is added to the array
void dynarray_reserve_delete(DynArray*, size_t);

// Returns a pointer to the top value on the array
void *dynarray_top(DynArray*);

// Performs arithmetic on the internal array in order to get pointer to an
// element in the array.
void *dynarray_get(DynArray*, size_t);

#endif
