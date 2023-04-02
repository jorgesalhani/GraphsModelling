#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "graph.h"
#include "path.h"

int main(void) {
    // int v, a;
    // int node_from, node_to;

    // scanf("%d %d ", &v, &a);
    // GRAPH* graph = graph_create();
    // int i = 0;
    // while (i < a) {
    //     scanf("%d %d ", &node_from, &node_to);
    //     graph_add_nodes(graph, node_from, node_to);
    //     i++;
    // }

    // // GRAPH* graph = graph_create();  
    // // graph_add_node(graph, 0, 1);
    // // graph_add_node(graph, 0, 3);
    // // graph_add_node(graph, 1, 2);
    // // graph_add_node(graph, 1, 3);
    // // graph_add_node(graph, 1, 4);
    // // graph_add_node(graph, 2, 3);
    // // graph_add_node(graph, 3, 4);

    // graph_print(graph);
    // graph_delete(&graph);

    PATH* path = path_create();
    ITEM* item1 = item_create(0);
    ITEM* item2 = item_create(2);
    ITEM* item3 = item_create(1);
    ITEM* item4 = item_create(10);

    path_add(path, item1);
    path_add(path, item2);
    path_add(path, item3);
    path_add(path, item4);

    ITEM* item = path_unstack(path);
    item_print(item);
    item_delete(&item);
    ITEM* item5 = item_create(3);
    path_add(path, item5);

    path_print(path);
    path_delete(&path);

    return 0;
}