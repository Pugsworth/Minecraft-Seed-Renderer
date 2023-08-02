#pragma once

#include <stdlib.h>
#include <string.h>


typedef struct {
    void *items; // void pointer to the start of the array.
    int capacity; // how many items can be stored in the array.
    int total; // how many items are currently stored in the array.
    int item_size; // how big is each item in the array in bytes.
} DynamicArray;


/**
 * @brief Create a new Dynamic Array object
 *
 * @param item_size amount of bytes each item in the array will take up.
 * @return DynamicArray*
 */
DynamicArray *dynarray_new(size_t item_size);

/**
 * @brief Free the memory allocated for the Dynamic Array.
 *
 * @param dynarray Dynamic Array instance to free.
 */
void dynarray_free(DynamicArray *dynarray);

/**
 * @brief Push an item to the back of the Dynamic Array.
 *
 * @param dynarray
 * @param item void*
 */
void dynarray_push_back(DynamicArray *dynarray, void *item);

/**
 * @brief Pop an item from the back of the Dynamic Array.
 *
 * @param dynarray
 * @return void* item popped from the back of the array.
 */
void* dynarray_pop_back(DynamicArray *dynarray);