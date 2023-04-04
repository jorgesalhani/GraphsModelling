#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "graph.h"
#include "path.h"

#define MAX_FILENAME 50
#define MAX_LENGTH_LINE_IN_FILE 20

FILE* open_file(char* filename) {
    FILE* file_graph = fopen(filename, "r");
    if (file_graph == NULL) {
        perror(filename);
        return NULL;
    }
    return file_graph;
}

int main(void) {
    int v, a;
    int node_from, node_to;

    char filename[MAX_FILENAME];
    scanf("%s", filename);

    FILE* file_open = open_file(filename);
    if (file_open == NULL) return -1;
    
    fscanf(file_open, "%d ", &v);
    fscanf(file_open, "%d ", &a);
    GRAPH* graph = graph_create(v, a);
    
    while (!feof(file_open)) {
        fscanf(file_open, "%d", &node_from);
        fscanf(file_open, "%d", &node_to);
        graph_add_nodes(graph, node_from, node_to);
    }

    fclose(file_open);

    graph_is_eulerian(graph);
    graph_delete(&graph);

    return 0;
}