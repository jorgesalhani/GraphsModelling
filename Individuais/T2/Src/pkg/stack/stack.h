#ifndef STACK_H
  #define STACK_H

  #include <stdbool.h>
  #include <stdlib.h>
  #include "../item/item.h"

  typedef struct stack_ STACK;

  STACK* stack_create();
  bool stack_add(STACK* stack, ITEM* item);
  ITEM* stack_pop(STACK* stack);
  bool stack_remove(STACK* stack);
  bool stack_delete(STACK** stack);
  bool stack_is_empty(STACK* stack);
  bool stack_exists(STACK* stack);
  void stack_print(STACK* stack);
  

#endif