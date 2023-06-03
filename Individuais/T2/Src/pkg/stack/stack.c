#include "stack.h"

typedef struct stack_element_ STACK_ELEMENT;

struct stack_element_ {
  ITEM* item;
  STACK_ELEMENT* next;
};

struct stack_ {
  int size;
  STACK_ELEMENT* top;
};

bool stack_element_exists(STACK_ELEMENT* next);
bool stack_delete_aux(STACK* stack);

bool ftn_print(STACK_ELEMENT* next) { item_print(next->item); }

bool stack_map_aux(STACK_ELEMENT* next, bool (*function)()) {
  if (!stack_element_exists(next)) return false;
  (*function)(next);
  stack_map_aux(next->next, function);
  return true;
}

bool stack_map(STACK* stack, bool (*function)()) {
  if (!stack_exists(stack) || stack_is_empty(stack)) return false;
  return stack_map_aux(stack->top, function);
}

void stack_print(STACK* stack) {
  stack_map(stack, ftn_print);
}


STACK* stack_create() {
  STACK* stack = (STACK*) malloc(sizeof(STACK));
  if (!stack_exists(stack)) return NULL;

  stack->size = 0;
  stack->top = NULL;
  return stack;
}

bool stack_add(STACK* stack, ITEM* item) {
  if (!stack_exists(stack) || !item_exists(item)) return false;

  STACK_ELEMENT* new_element = (STACK_ELEMENT*) malloc(sizeof(STACK_ELEMENT));
  if (!stack_element_exists(new_element)) return false;

  new_element->item = item;
  new_element->next = NULL;

  new_element->next = stack->top;
  stack->top = new_element;

  stack->size ++;
  return true;
}

bool stack_element_exists(STACK_ELEMENT* next) {
  return next != NULL ? true : false;
}

ITEM* stack_pop(STACK* stack) {
  if (!stack_exists(stack) || stack_is_empty(stack)) return NULL;
  ITEM* item = stack->top->item;
  STACK_ELEMENT* top = stack->top;
  stack->top = stack->top->next;
  free(top);
  top = NULL;

  stack->size --;
  return item;
}

bool stack_remove(STACK* stack) {
  if (!stack_exists(stack) || stack_is_empty(stack)) return false;
  ITEM* item = stack_pop(stack);
  item_delete(&item);

  return true;
}

bool stack_delete(STACK** stack) {
  if (stack == NULL || !stack_exists(*stack)) return false;
  stack_delete_aux(*stack);
  free(*stack);
  *stack = NULL;
  stack = NULL;
  return true;
}

bool stack_delete_aux(STACK* stack) {
  if (!stack_exists(stack) || stack_is_empty(stack)) return false;
  stack_remove(stack);
  return stack_delete_aux(stack);
}

bool stack_is_empty(STACK* stack) {
  if (!stack_exists(stack)) return true;
  if (stack->size == 0) return true;
  return false;
}

bool stack_exists(STACK* stack) {
  return stack != NULL ? true : false;
}
