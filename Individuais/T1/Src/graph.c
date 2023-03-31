#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// Data structure
// ==============

typedef struct node_ NODE;

struct node_ {
    ITEM* item;
    NODE* next;
    NODE* connection;
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
    if (!node_exists_(node->next)) return node;
    if (item_get_key(node->next->item) >= item_get_key(item)) return node;

    return graph_get_previous_node_aux(node->next, item);
}

void graph_print_aux(NODE* node) {
    if (node_exists_(node)) {
        printf("%d -> ", item_get_key(node->item));
        graph_print_aux(node->next);
    }
}

void graph_delete_aux(NODE** node) {
    if (node != NULL && node_exists_(*node)) {
        graph_delete_aux(&((*node)->next));
        
        item_delete(&((*node)->item));
        free((*node));
        *node = NULL;
        node = NULL;
    }
}

bool node_already_in_graph_(NODE* node, ITEM* item) {
    if (!node_exists_(node)) return false;
    if (item_get_key(node->item) == item_get_key(item)) {
        printf("%d", item_get_key(node->item));
        printf(" Exists\n"); 
        return true;
    }
    node_already_in_graph_(node->next, item);
}

bool graph_add_link(NODE* node, ITEM* item_from, ITEM* item_to) {
    
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

bool graph_add_node(GRAPH* graph, ITEM* item_from, ITEM* item_to) {
    if (!graph_exists(graph) || !item_exists(item_from)) return false;

    if (node_already_in_graph_(graph->node, item_from)) {
        graph_add_link(graph->node, item_from, item_to);
        return true;
    }
    
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    if (!node_exists_(new_node)) return false;
    new_node->item = item_from;
    new_node->next = NULL;
    new_node->connection = NULL;

    if (graph_is_empty_(graph)) {
        graph->node = new_node;
    } else {
        NODE* previous_node = graph_get_previous_node_aux(graph->node, item_from);
        new_node->next = previous_node->next;
        previous_node->next = new_node;
    }

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
    printf("\n");
}
