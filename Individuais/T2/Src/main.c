#include <stdio.h>
#include <stdlib.h>
#include "pkg/item/item.h"
#include "pkg/graph/graph.h"
#include "pkg/path/path.h"

int main(void) {
    int v, a;
    int node_from, node_to;
    
    scanf("%d ", &v);
    scanf("%d ", &a);
    GRAPH* graph = graph_create(v, a, true);
    
    int line_i = 0;
    while (line_i < a) {
        scanf("%d", &node_from);
        scanf("%d", &node_to);
        graph_add_nodes(graph, node_from, node_to);
        line_i++;
    }

    graph_print(graph, true);
    graph_print_strong_connected_components(graph);
    graph_delete(&graph);

    return 0;
}