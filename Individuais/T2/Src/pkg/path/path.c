#include <stdio.h>
#include <stdlib.h>
#include "path.h"

// Data structure
// ==============

typedef struct layer_ LAYER;

struct layer_ {
    LAYER* down_layer;
    ITEM* item;
};

struct path_ {
    int total_layers;
    LAYER* top_layer;
};

// Util operations
// ===============

bool path_exists(PATH* path) {
    return path != NULL ? true : false;
}

bool layer_exists_(LAYER* layer) {
    return layer != NULL ? true : false;
}

bool path_is_empty(PATH* path) {
    return path->total_layers == 0 ? true : false;
}

void path_delete_aux(PATH* path) {
    ITEM* item = path_unstack(path);
    if (!item_exists(item)) return;

    path_delete_aux(path);
}

void print_path_aux(LAYER* layer, bool with_metadata) {
    if (!layer_exists_(layer) || !item_exists(layer->item)) return;
    print_path_aux(layer->down_layer, with_metadata);
    if (with_metadata) {
        printf("%d (%d) -- ", item_get_key(layer->item), item_get_visited_order(layer->item));
    } else {
        printf("%d ", item_get_key(layer->item));
    }
}

// Main operations
// ===============

PATH* path_create() {
    PATH* path = (PATH*) malloc(sizeof(PATH));
    if (!path_exists(path)) return NULL;
    path->total_layers = 0;
    path->top_layer = NULL;
    return path;
}

bool path_add(PATH* path, ITEM* item) {
    if (!path_exists(path) || !item_exists(item)) return false;
    
    LAYER* new_layer = (LAYER*) malloc(sizeof(LAYER));
    if (!layer_exists_(new_layer)) return false;

    new_layer->item = item;
    new_layer->down_layer = NULL;
    if (path_is_empty(path)) {
        path->top_layer = new_layer;
    } else {
        new_layer->down_layer = path->top_layer;
        path->top_layer = new_layer;
    }

    path->total_layers++;
    return true;
}

ITEM* path_get_top(PATH* path) {
    if (!path_exists(path) || path_is_empty(path)) return NULL;
    return path->top_layer->item;
}

int path_get_total_stack(PATH* path) {
    if (!path_exists(path)) return -1;
    return path->total_layers;
}

ITEM* path_unstack(PATH* path) {
    if (!path_exists(path) || path_is_empty(path)) return NULL;

    ITEM* item = path->top_layer->item;
    LAYER* layer_to_delete = path->top_layer;
    path->top_layer = path->top_layer->down_layer;

    free(layer_to_delete);
    layer_to_delete = NULL;

    path->total_layers--;
    return item;
}

bool path_delete(PATH** path) {
    if (path == NULL || !path_exists(*path)) return false;
    if (!path_is_empty(*path)) {
        path_delete_aux(*path);
    }

    free(*path);
    *path = NULL;
    path = NULL;
    return true;
}

void path_print(PATH* path, bool with_metadata) {
    if (!path_exists(path) || path_is_empty(path)) return;
    print_path_aux(path->top_layer, with_metadata);
    printf("\n");
}