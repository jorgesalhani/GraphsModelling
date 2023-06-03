#include <stdio.h>
#include <stdlib.h>
#include "pkg/graph/graph.h"
#include "pkg/item/item.h"
#include "pkg/stack/stack.h"

int main() {
  ITEM* item0 = item_create(0);
  ITEM* item1 = item_create(1);
  ITEM* item2 = item_create(2);
  ITEM* item3 = item_create(3);

  STACK* stack = stack_create();
  stack_add(stack, item0);
  stack_add(stack, item2);
  stack_add(stack, item3);
  stack_add(stack, item1);

  stack_print(stack);

  stack_delete(&stack);

  return 0;
}