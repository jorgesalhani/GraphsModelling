#ifndef GRAPH_H
    #define GRAPH_H

    #include "item.h"
    #include "path.h"

    typedef struct graph_ GRAPH;

    GRAPH* graph_create();
    bool graph_exists(GRAPH* graph);
    bool graph_add_nodes(GRAPH* graph, int key_from, int key_to);
    bool graph_delete(GRAPH** graph);
    void graph_print(GRAPH* graph, bool with_availability);

    bool graph_is_eulerian(GRAPH* graph);

#endif