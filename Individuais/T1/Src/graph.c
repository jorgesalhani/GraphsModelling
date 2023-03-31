#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// Data structure
// ==============

typedef struct node_ NODE;

struct node_ {
    ITEM* item;
    NODE* node;
};

struct graph_ {
    NODE* node;
};

// Util operations
// ===============

bool node_exists_(NODE* node) {
    return node != NULL ? true : false;
}

bool graph_is_empty_(GRAPH* graph) {
    if (graph_exists(graph) && !node_exists_(graph->node)) {
        return true;
    }
    return false;
}

NODE* graph_get_previous_node_aux(NODE* node, ITEM* item) {
    if (!node_exists_(node)) return node;
    if (item_get_key(node->item) >= item_get_key(item)) return node;

    return graph_get_previous_node_aux(node->node, item);
}

void graph_print_aux(NODE* node) {
    if (node_exists_(node)) {
        printf("%d -> ", item_get_key(node->item));
        graph_print_aux(node->node);
    }
}

void graph_delete_aux(NODE** node) {
    if (node != NULL && node_exists_(*node)) {
        graph_delete_aux(&((*node)->node));
        
        item_delete(&((*node)->item));
        free((*node));
        *node = NULL;
        node = NULL;
    }
}


// Main operations
// ===============

GRAPH* graph_create() {
    GRAPH* graph = (GRAPH*) malloc(sizeof(GRAPH));
    if (!graph_exists(graph)) return NULL;
    graph->node = NULL;
    return graph;
}

bool graph_exists(GRAPH* graph) {
    return graph != NULL ? true : false;
}

bool graph_add_node(GRAPH* graph, ITEM* item) {
    if (!graph_exists(graph) || !item_exists(item)) return false;
    
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    if (!node_exists_(new_node)) return false;
    new_node->item = item;
    new_node->node = NULL;

    if (graph_is_empty_(graph)) {
        graph->node = new_node;
    } else {
        NODE* previous_node = graph_get_previous_node_aux(graph->node, item);
        new_node->node = previous_node->node;
        previous_node->node = new_node;
    }

    return true;
}

bool graph_add_link(GRAPH* graph, ITEM* item_from, ITEM* item_to) {
    return true;
}

bool graph_delete(GRAPH** graph) {
    if (!graph_exists(*graph)) return false;
    if (graph_is_empty_(*graph)) {
        free((*graph)->node);
        (*graph)->node = NULL;
    } else {
        graph_delete_aux(&((*graph)->node));
    }

    free((*graph));
    *graph = NULL;
    graph = NULL;
    return true;
}

void graph_print(GRAPH* graph) {
    if (graph_exists(graph) && !graph_is_empty_(graph)) {
        graph_print_aux(graph->node);
    }
}
