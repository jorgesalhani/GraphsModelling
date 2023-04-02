#ifndef PATH_H
    #define PATH_H

    #include "item.h"
    #include "graph.h"

    typedef struct path_ PATH;

    PATH* path_create();
    bool path_add(PATH* path, ITEM* item);
    ITEM* path_unstack(PATH* path);
    bool path_delete(PATH** path);
    void path_print(PATH* path);

#endif