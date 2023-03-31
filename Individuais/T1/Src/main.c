#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "graph.h"

int main(void) {
    ITEM* item1 = item_create(1);
    ITEM* item2 = item_create(13);
    ITEM* item3 = item_create(5);
    ITEM* item4 = item_create(3);
    ITEM* item5 = item_create(20);
    ITEM* item6 = item_create(16);
    
    GRAPH* graph = graph_create();
    graph_add_node(graph, item1);
    graph_add_node(graph, item2);
    graph_add_node(graph, item3);
    graph_add_node(graph, item4);
    graph_add_node(graph, item5);
    graph_add_node(graph, item6);

    graph_print(graph);

    graph_delete(&graph);

    return 0;
}