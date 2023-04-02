#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "graph.h"

int main(void) {
    int v, a;
    int node_from, node_to;

    scanf("%d %d ", &v, &a);
    GRAPH* graph = graph_create();
    int i = 0;
    while (i < a) {
        scanf("%d %d ", &node_from, &node_to);
        graph_add_node(graph, node_from, node_to);
        i++;
    }

    // GRAPH* graph = graph_create();  
    // graph_add_node(graph, 0, 1);
    // graph_add_node(graph, 0, 3);
    // graph_add_node(graph, 1, 2);
    // graph_add_node(graph, 1, 3);
    // graph_add_node(graph, 1, 4);
    // graph_add_node(graph, 2, 3);
    // graph_add_node(graph, 3, 4);

    graph_print(graph);
    graph_delete(&graph);

    return 0;
}