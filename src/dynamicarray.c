#include "dynamicarray.h"


DynamicArray *dynarray_new(size_t item_size) {
    DynamicArray *dynarray = (DynamicArray*)malloc(sizeof(DynamicArray) * item_size * 16);
    dynarray->item_size = item_size;
    dynarray->capacity = 16;
    dynarray->total = 0;
    dynarray->items = malloc(dynarray->capacity * dynarray->item_size);
    return dynarray;
}

void dynarray_free(DynamicArray *dynarray) {
    free(dynarray->items);
    free(dynarray);
}

static void dynarray_resize(DynamicArray *dynarray, int capacity) {
    void *items = realloc(dynarray->items, dynarray->item_size * capacity);
    if (items) {
        dynarray->items = items;
        dynarray->capacity = capacity;
    }
}

void dynarray_push_back(DynamicArray *dynarray, void *item) {
    if (dynarray->capacity == dynarray->total) {
        dynarray_resize(dynarray, dynarray->capacity * 2);
    }
    void *target = (char*)dynarray->items + dynarray->item_size * dynarray->total;
    memcpy(target, item, dynarray->item_size);
    dynarray->total++;
}

void* dynarray_pop_back(DynamicArray *dynarray) {
    dynarray->total--;
    void *target = (char*)dynarray->items + dynarray->item_size * dynarray->total;
    return target;
}
