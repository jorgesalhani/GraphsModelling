#include "item.h"
#include <stdlib.h>
#include <stdio.h>

// Data Structure
// ==============

struct item_ {
    int key;
    bool available;
};

// Main operations
// ===============

ITEM* item_create(int key) {
    ITEM* item = (ITEM*) malloc(sizeof(ITEM));
    if (!item_exists(item)) return NULL;
    item->key = key;
    item->available = true;
    return item;
}

int item_get_key(ITEM* item) {
    if (!item_exists(item)) return -1;
    return item->key;
}

bool item_is_available(ITEM* item) {
    if (!item_exists(item)) return false;
    return item->available;
}

bool item_delete(ITEM** item) {
    if (item != NULL && !item_exists(*item)) return false;
    free(*item);
    *item = NULL;
    item = NULL;
    return true;
}

bool item_exists(ITEM* item) {
    return item != NULL ? true : false;
}

void item_print(ITEM* item) {
    if (item_exists(item)) {
        printf("%d\n", item->key);
    }
}
