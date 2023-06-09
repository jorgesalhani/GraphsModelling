#include "item.h"
#include <stdlib.h>
#include <stdio.h>

// Data Structure
// ==============

struct item_ {
    int key;
    bool available;
    int visited_order;
};

// Main operations
// ===============

ITEM* item_create(int key) {
    ITEM* item = (ITEM*) malloc(sizeof(ITEM));
    if (!item_exists(item)) return NULL;
    item->key = key;
    item->available = true;
    item->visited_order = INFINITY;
    return item;
}

int item_get_visited_order(ITEM* item) {
    if (!item_exists(item)) return INFINITY;
    return item->visited_order;
}

int item_get_key(ITEM* item) {
    if (!item_exists(item)) return -1;
    return item->key;
}

bool item_is_available(ITEM* item) {
    if (!item_exists(item)) return false;
    return item->available;
}

void item_set_availability(ITEM* item, bool availability) {
    if (!item_exists(item)) return;
    item->available = availability;
}

void item_set_visited_order(ITEM* item, int visited_order) {
    if (!item_exists(item)) return;
    item->visited_order = visited_order;
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
