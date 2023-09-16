#include "dynarray.h"

DynArray *dynarray_new(size_t elem_size) {
    DynArray *new_arr = malloc(sizeof(DynArray));

    new_arr->length = 0;
    new_arr->cap = 1;
    new_arr->elem_size = elem_size;
    new_arr->data = NULL;

    return new_arr;
}

void dynarray_push(DynArray *arr, void *data) {
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

void dynarray_pop(DynArray *arr) {
    arr->length--;
}

void dynarray_free(DynArray *arr) {
    free(arr->data);
    free(arr);
}

void *dynarray_top(DynArray *arr) {
    void* index = (char*)arr->data + ((arr->length - 1) * arr->elem_size);
    return index;
}

void *dynarray_get(DynArray *arr, size_t index) {
    void* idx = (char*)arr->data + (index * arr->elem_size);
    return idx;
}
