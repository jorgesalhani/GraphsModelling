#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// Data structure
// ==============

typedef struct node_ NODE;

struct node_ {
    bool visited;
    bool in_scc;
    ITEM* item;
    NODE* next;
    NODE* connection;
};

struct graph_ {
    int degree_node;
    int degree_edge;
    bool is_directed;
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

NODE* node_already_in_graph_(NODE* node_head, ITEM* item) {
    if (!node_exists_(node_head)) return NULL;
    if (item_get_key(node_head->item) == item_get_key(item)) return node_head;
    node_already_in_graph_(node_head->next, item);
}

NODE* node_detached_(NODE* node_head) {
    if (!node_exists_(node_head)) return NULL;
    if (!node_head->visited) return node_head;
    node_detached_(node_head->next);
}

NODE* node_already_connected_(NODE* node_from, ITEM* item) {
    if (!node_exists_(node_from)) return NULL;
    if (item_get_key(node_from->item) == item_get_key(item)) return node_from;
    node_already_connected_(node_from->connection, item);
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
    new_node->in_scc = false;

    if (graph_is_empty_(graph)) {
        graph->node = new_node;
    } else {
        NODE* previous_node = graph_get_previous_node_aux(graph->node, item_from);
        new_node->next = previous_node->next;
        previous_node->next = new_node;
    }

    return new_node;
}

NODE* graph_get_next_available_connection(NODE* node_from) {
    if (!node_exists_(node_from)) return NULL;
    if (item_is_available(node_from->item)) return node_from;
    graph_get_next_available_connection(node_from->connection);
}

bool graph_find_eulerian_path(GRAPH* graph, PATH* path, NODE* node_from, NODE* node_to) {
    if (graph->degree_edge + 1 == path_get_total_stack(path) && item_get_key(path_get_top(path)) == item_get_key(graph->node->item)) {
        return true;
    }

    if (!node_exists_(node_to) || path_get_total_stack(path) == graph->degree_edge + 1) return false;
    if (!node_exists_(node_to->connection) && !item_is_available(node_to->item)) return false;

    path_add(path, node_from->item);

    item_set_availability(node_to->item, false);

    NODE* node_with_double_edge = node_already_in_graph_(graph->node, node_to->item);
    NODE* node_double_edge = node_already_connected_(node_with_double_edge, node_from->item);
    item_set_availability(node_double_edge->item, false);

    NODE* next_available = graph_get_next_available_connection(node_with_double_edge->connection);
    if (!node_exists_(next_available)) {
        path_add(path, node_to->item);
        return false;
    }

    // if (item_is_available(node_with_double_edge->connection->item)) {
    //     graph_find_eulerian_path(graph, path, node_with_double_edge, node_with_double_edge->connection);
    // } else {
    graph_find_eulerian_path(graph, path, node_with_double_edge, next_available);

    if (graph->degree_edge + 1 == path_get_total_stack(path) && item_get_key(path_get_top(path)) == item_get_key(graph->node->item)) {
        return true;
    }
    // }

    // if (item_is_available(node_to->item)) {
    //     path_add(path, node_from->item);
    //     item_set_availability(node_to->item, false);
    //     NODE* node_double_edge = node_already_connected_(node_with_double_edge, node_from->item);
    //     item_set_availability(node_double_edge->item, false);
    //     graph_find_eulerian_path(graph, path, node_to, node_with_double_edge->connection);
    // } else {
    //     graph_find_eulerian_path(graph, path, node_from, node_to->connection);
    // }

    if (path_get_total_stack(path) < 2) return false;
    ITEM* item_to = path_unstack(path);
    ITEM* item_from = path_unstack(path);
    
    NODE* next_node_from = node_already_in_graph_(graph->node, item_from);
    NODE* next_node_to = node_already_connected_(next_node_from, item_to);

    item_set_availability(next_node_to->item, true);

    graph_find_eulerian_path(graph, path, next_node_from, next_node_to->connection);
}


// Main operations
// ===============

GRAPH* graph_create(int degree_node, int degree_edge, bool is_directed) {
    GRAPH* graph = (GRAPH*) malloc(sizeof(GRAPH));
    if (!graph_exists(graph)) return NULL;
    graph->node = NULL;
    graph->degree_node = degree_node;
    graph->degree_edge = degree_edge;
    graph->is_directed = is_directed;
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
    if (!graph->is_directed) graph_add_link(node_to, node_from->item);


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

int graph_get_node_degree(GRAPH* graph) {
    if (!graph_exists(graph)) return -1;
    return graph->degree_node;
}

int graph_get_edge_degree(GRAPH* graph) {
    if (!graph_exists(graph)) return -1;
    return graph->degree_edge;
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

    // graph_print(graph, false);

    bool path_found = graph_find_eulerian_path(graph, path, graph->node, graph->node->connection);

    if (path_found){
        printf("Sim\n");
        path_print(path, false);
    } else {
        printf("Não\n");
    }

    path_delete(&path);
}

bool update_visited_order(NODE* node, int* visited_order) {
    if (!node_exists_(node)) return false;
    int vist_ord = *visited_order;
    vist_ord++;
    *visited_order = vist_ord;
    item_set_visited_order(node->item, *visited_order);
    return true;
}

int scc_get_low_w(GRAPH* graph, NODE* base_node, NODE* connected, int low) {
    if (!graph_exists(graph) || !node_exists_(base_node) || !node_exists_(connected)) return low;
    NODE* node = node_already_in_graph_(graph->node, connected->item);
    if (low > item_get_visited_order(node->item) && !node->in_scc) {
        scc_get_low_w(graph, base_node, connected->connection, item_get_visited_order(node->item));
    } else {
        scc_get_low_w(graph, base_node, connected->connection, low);
    }
}

bool unstack_scc(GRAPH* graph, PATH* path, int low_w) {
    if (!graph_exists(graph) || !path_exists(path)) return false;
    if (path_is_empty(path)) return false;



    ITEM* item_top = path_get_top(path);
    NODE* node = node_already_in_graph_(graph->node, item_top);
    NODE* connect_available = graph_get_next_available_connection(node->connection);
    if (node_exists_(connect_available)) return false;

    item_top = path_unstack(path);
    int low_v = item_get_visited_order(item_top);
    int new_low_w = scc_get_low_w(graph, node, node->connection, low_v);
    if (low_w > new_low_w) low_v = new_low_w;
    else low_v = low_w;

    item_print(item_top);
    if (low_v == item_get_visited_order(item_top)) printf("---\n");
    node->in_scc = true;
    unstack_scc(graph, path, low_v);


}

bool graph_strong_connected_components(GRAPH* graph, PATH* path, NODE* node_from, NODE* node_to, int* visited_order) {
    if (!node_exists_(node_from) || !node_exists_(node_to)) return false;
    
    NODE* next_step = graph_get_next_available_connection(node_from->connection);
    if (!node_exists_(next_step)) {
        return false;
    }

    NODE* current_node_from = node_already_in_graph_(graph->node, node_from->item);
    
    NODE* next_node_from = node_already_in_graph_(graph->node, next_step->item);
    if (!node_exists_(next_node_from)) return false;

    item_set_availability(next_step->item, false);
    
    if (!next_node_from->visited) {
        path_add(path, next_node_from->item);
        update_visited_order(next_node_from, visited_order);
    }
    next_node_from->visited = true;
    
    graph_strong_connected_components(graph, path, next_node_from, next_node_from->connection, visited_order);    

    graph_strong_connected_components(graph, path, node_from, next_step, visited_order);

    if (path_get_total_stack(path) != graph->degree_node) {
        unstack_scc(graph, path, INFINITY);
        NODE* node_detached = node_detached_(graph->node);
        if (!node_exists_(node_detached)) return true;
        
        path_add(path, node_detached->item);
        update_visited_order(node_detached, visited_order);
        node_detached->visited = true;
        graph_strong_connected_components(graph, path, node_detached, next_step, visited_order);
    }
    
}

bool graph_print_strong_connected_components(GRAPH* graph) {
    if (!graph_exists(graph) || graph_is_empty_(graph)) return false;

    PATH* path = path_create();
    if (!path_exists(path)) return false;

    int visited_order = 0;

    path_add(path, graph->node->item);
    item_set_visited_order(graph->node->item, visited_order);
    graph->node->visited = true;
    
    bool sccs = graph_strong_connected_components(graph, path, graph->node, graph->node->connection, &visited_order);
    path_print(path, true);
    path_delete(&path);
    return true;
}