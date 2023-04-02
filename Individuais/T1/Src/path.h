#ifndef PATH_H
    #define PATH_H

    #include "item.h"
    #include "graph.h"

    typedef struct path_ PATH;

    PATH* path_create();
    bool path_add(PATH* path, ITEM* item);
    ITEM* path_get_top(PATH* path);
    int path_get_total_stack(PATH* path);
    bool path_exists(PATH* path);
    bool path_is_empty(PATH* path);
    ITEM* path_unstack(PATH* path);
    bool path_delete(PATH** path);
    void path_print(PATH* path);

#endif