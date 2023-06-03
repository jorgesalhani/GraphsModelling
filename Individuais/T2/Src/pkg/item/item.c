#include "item.h"

struct item_ {
  int key;
};

ITEM* item_create(int key) {
  ITEM* item = (ITEM*) malloc(sizeof(ITEM));
  if (!item_exists(item)) return NULL;

  item->key = key;
  return item;
}

bool item_delete(ITEM** item) {
  if (item == NULL || !item_exists(*item)) return false;
  free(*item);
  *item = NULL;
  item = NULL;
  return true;
}

bool item_exists(ITEM* item) {
  return item == NULL ? false : true;
}

void item_print(ITEM* item) {
  if (!item_exists(item)) return;
  printf("%d\n", item->key);
}