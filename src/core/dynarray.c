#include "dynarray.h"

DynArray *dynarray_new(size_t elem_size) {
    DynArray *new_arr = malloc(sizeof(DynArray));

    new_arr->length = 0;
    new_arr->cap = 1;
    new_arr->elem_size = elem_size;
    new_arr->data = NULL;

    new_arr->reserve_queue = NULL;
    new_arr->reserve_queue_size = 0;
    new_arr->reserve_queue_uses = 0;

    return new_arr;
}

void dynarray_push(DynArray *arr, void *data) {
    if (arr->reserve_queue_size > 0) {
        arr->reserve_queue_size--;
        char* ptr = (char*)arr->data
            + arr->reserve_queue[arr->reserve_queue_size] * arr->elem_size;
        memcpy(ptr, data, arr->elem_size);

        arr->reserve_queue_uses++;

        // only here to prevent the reserve_queue from growing out of control
        // and consuming too much memory
        if (arr->reserve_queue_uses == RESERVE_QUEUE_REFRESH + 1) {
            arr->reserve_queue = realloc(arr->reserve_queue,
                sizeof(size_t) * arr->reserve_queue_size);
            arr->reserve_queue_uses = 0;
            printf("DYNARRAY: Reallocated reserve_queue to size %zu\n",
                sizeof(size_t) * arr->reserve_queue_size);
        }
        return;
    }

    if (arr->length + 1 == arr->cap) {
        arr->cap *= 2;
        arr->data = realloc(arr->data, arr->cap * arr->elem_size);
    }
    memcpy(
        (char*)arr->data + (arr->length * arr->elem_size),
        data,
        arr->elem_size);

    arr->length++;
}

void dynarray_push_index(DynArray *arr, void *data, size_t *idx) {
    if (arr->reserve_queue_size > 0) {
        arr->reserve_queue_size--;
        char* ptr = (char*)arr->data
            + arr->reserve_queue[arr->reserve_queue_size] * arr->elem_size;
        memcpy(ptr, data, arr->elem_size);

        *idx = arr->reserve_queue[arr->reserve_queue_size];

        arr->reserve_queue_uses++;

        // only here to prevent the reserve_queue from growing out of control
        // and consuming too much memory
        if (arr->reserve_queue_uses == RESERVE_QUEUE_REFRESH + 1) {
            arr->reserve_queue = realloc(arr->reserve_queue,
                sizeof(size_t) * arr->reserve_queue_size);
            arr->reserve_queue_uses = 0;
            printf("DYNARRAY: Reallocated reserve_queue to size %zu\n",
                sizeof(size_t) * arr->reserve_queue_size);
        }
        return;
    }

    if (arr->length + 1 == arr->cap) {
        arr->cap *= 2;
        arr->data = realloc(arr->data, arr->cap * arr->elem_size);
    }
    memcpy(
        (char*)arr->data + (arr->length * arr->elem_size),
        data,
        arr->elem_size);

    *idx = arr->length;

    arr->length++;
}

void dynarray_pop(DynArray *arr) {
    arr->length--;
}

void dynarray_free(DynArray *arr) {
    free(arr->data);
    free(arr->reserve_queue);
    free(arr);
}

void dynarray_delete(DynArray *arr, size_t index) {
    if (index == arr->length - 1) {
        arr->length--;
        return;
    }

    // base address for the element after the index to be deleted
    char *ptr_after = (char*)arr->data + ((index + 1) * arr->elem_size);
    char *ptr = (char*)arr->data + index * arr->elem_size;

    memcpy(ptr, ptr_after, (arr->length - index) * arr->elem_size);

    arr->length--;
}

void dynarray_reserve_delete(DynArray *arr, size_t index) {
    // doesn't actually delete anything, just marks the position in the
    // dynamic array as being overwriteable, such that the next element that is
    // added overwrites the location
    arr->reserve_queue_size++;
    arr->reserve_queue =
        realloc(arr->reserve_queue, sizeof(size_t) * arr->reserve_queue_size);
    arr->reserve_queue[arr->reserve_queue_size - 1] = index;
}

void *dynarray_top(DynArray *arr) {
    void* index = (char*)arr->data + ((arr->length - 1) * arr->elem_size);
    return index;
}

void *dynarray_get(DynArray *arr, size_t index) {
    void* idx = (char*)arr->data + (index * arr->elem_size);
    return idx;
}
