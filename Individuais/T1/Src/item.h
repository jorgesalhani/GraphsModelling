#ifndef ITEM_H
    #define ITEM_H

    #include <stdbool.h>

    typedef struct item_ ITEM;

    ITEM* item_create(int key);
    int item_get_key(ITEM* item);
    bool item_exists(ITEM* item);
    void item_set_availability(ITEM* item, bool availability);
    bool item_is_available(ITEM* item);
    bool item_delete(ITEM** item);
    void item_print(ITEM* item);

#endif