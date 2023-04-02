#ifndef GRAPH_H
    #define GRAPH_H

    #include "item.h"

    typedef struct graph_ GRAPH;

    GRAPH* graph_create();
    bool graph_exists(GRAPH* graph);
    bool graph_add_node(GRAPH* graph, int key_from, int key_to);
    bool graph_delete(GRAPH** graph);
    void graph_print(GRAPH* graph);

#endif