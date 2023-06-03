#ifndef ITEM_H
  #define ITEM_H

  #include <stdbool.h>
  #include <stdlib.h>
  #include <stdio.h>

  typedef struct item_ ITEM;

  ITEM* item_create(int key);
  bool item_delete(ITEM** item);
  bool item_exists(ITEM* item);
  void item_print(ITEM* item);

#endif