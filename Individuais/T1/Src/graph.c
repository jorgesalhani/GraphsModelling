#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// Data structure
// ==============

typedef struct node_ NODE;

struct node_ {
    bool visited;
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

NODE* graph_get_previous_connection_aux(NODE* node, ITEM* item) {
    if (!node_exists_(node->connection)) return node;
    if (item_get_key(node->connection->item) >= item_get_key(item)) return node;

    return graph_get_previous_connection_aux(node->connection, item);
}

void print_connections(NODE* node, bool with_availability) {
    if (node_exists_(node)) {
        if (with_availability) {
            char available = item_is_available(node->item) ? 'a' : 'u';
            printf("{%d:%c},", item_get_key(node->item), available);
        } else {
            printf("%d,", item_get_key(node->item));
        }
        print_connections(node->connection, with_availability);
    }
}

void graph_print_aux(NODE* node, bool with_availability) {
    if (node_exists_(node)) {
        if (with_availability) {
            char visited = node->visited ? 'y' : 'n';
            printf("{%d:%c}: [", item_get_key(node->item), visited);
        } else {
            printf("%d: [", item_get_key(node->item));
        }
        
        print_connections(node->connection, with_availability);
        printf("]\n");
        graph_print_aux(node->next, with_availability);
    }
}

void graph_delete_connections_aux(NODE** node) {
    if (node != NULL && node_exists_(*node)) {
        graph_delete_connections_aux(&((*node)->connection));
        if (item_exists((*node)->item)) item_delete(&((*node)->item));
        free((*node));
        *node = NULL;
        node = NULL;
    }
}

void graph_delete_nodes_aux(NODE** node) {
    if (node != NULL && node_exists_(*node)) {
        graph_delete_nodes_aux(&((*node)->next));
        if (item_exists((*node)->item)) item_delete(&((*node)->item));
    }
    graph_delete_connections_aux(node);
}

NODE* node_already_in_graph_(NODE* node, ITEM* item) {
    if (!node_exists_(node)) return NULL;
    if (item_get_key(node->item) == item_get_key(item)) return node;
    node_already_in_graph_(node->next, item);
}

NODE* node_already_connected_(NODE* node, ITEM* item) {
    if (!node_exists_(node)) return NULL;
    if (item_get_key(node->item) == item_get_key(item)) return node;
    node_already_connected_(node->connection, item);
}

bool graph_add_link(NODE* node_from, ITEM* item_to) {
    NODE* node_to = node_already_connected_(node_from, item_to);
    if (!node_exists_(node_from) || node_exists_(node_to)) return false;

    ITEM* new_item = item_create(item_get_key(item_to));
    if (!item_exists(new_item)) return false;
    
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    if (!node_exists_(new_node)) return false;
    new_node->item = new_item;
    new_node->next = NULL;
    new_node->connection = NULL;

    NODE* previous_node = graph_get_previous_connection_aux(node_from, item_to);
    new_node->connection = previous_node->connection;
    previous_node->connection = new_node;

    return true;
}

NODE* graph_add_node_aux(GRAPH* graph, ITEM* item_from) {
    NODE* node_in_graph = node_already_in_graph_(graph->node, item_from);

    if (node_exists_(node_in_graph)) return node_in_graph;
    
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    if (!node_exists_(new_node)) return NULL;
    new_node->item = item_from;
    new_node->next = NULL;
    new_node->connection = NULL;
    new_node->visited = false;

    if (graph_is_empty_(graph)) {
        graph->node = new_node;
    } else {
        NODE* previous_node = graph_get_previous_node_aux(graph->node, item_from);
        new_node->next = previous_node->next;
        previous_node->next = new_node;
    }

    return new_node;
}

NODE* graph_move_to_next_connection(NODE* node) {
    if (!node_exists_(node) || !node_exists_(node->connection)) return NULL;

    return node->connection;
}

bool graph_find_eulerian_path(PATH* path, NODE* node) {
    NODE* node_to = graph_move_to_next_connection(node);
    item_set_availability(node_to->item, false);

    // if (item_get_key(node_to->item) == item_get_key(path_get_top(path))) 
    
    node->visited = true;
    return true;
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

bool graph_add_nodes(GRAPH* graph, int key_from, int key_to) {
    if (!graph_exists(graph)) return false;

    ITEM* item_from = item_create(key_from);
    ITEM* item_to = item_create(key_to);
    
    NODE* node_from = node_already_in_graph_(graph->node, item_from);
    if (node_exists_(node_from)) {
        item_delete(&item_from);
    } else {
        node_from = graph_add_node_aux(graph, item_from);
    }

    NODE* node_to = node_already_in_graph_(graph->node, item_to);
    if (node_exists_(node_to)) {
        item_delete(&item_to);
    } else {
        node_to = graph_add_node_aux(graph, item_to);
    }

    graph_add_link(node_from, node_to->item);
    graph_add_link(node_to, node_from->item);

    return true;
}

bool graph_delete(GRAPH** graph) {
    if (!graph_exists(*graph)) return false;
    if (graph_is_empty_(*graph)) {
        free((*graph)->node);
        (*graph)->node = NULL;
    } else {
        graph_delete_nodes_aux(&((*graph)->node));
    }

    free((*graph));
    *graph = NULL;
    graph = NULL;
    return true;
}

void graph_print(GRAPH* graph, bool with_availability) {
    if (graph_exists(graph) && !graph_is_empty_(graph)) {
        graph_print_aux(graph->node, with_availability);
    }
    printf("\n");
}

bool graph_is_eulerian(GRAPH* graph) {
    if (!graph_exists(graph) || graph_is_empty_(graph)) return false;

    PATH* path = path_create();
    if (!path_exists(path)) return false;

    path_add(path, graph->node->item);
    graph->node->visited = true;
    bool path_found = graph_find_eulerian_path(path, graph->node);

    path_print(path);

    path_delete(&path);
}
