#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "graph.h"

int main(void) {
    ITEM* item = item_create(1);
    ITEM* item2 = item_create(13);
    
    GRAPH* graph = graph_create();
    graph_add_node(graph, item);
    graph_delete(&graph);
    
    item_print(item2);
    item_delete(&item2);

    return 0;
}