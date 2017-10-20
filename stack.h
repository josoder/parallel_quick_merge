//
// Created by josoder on 20.10.17.
//

#ifndef PARALLEL_MERGE_SORT_STACK_H
#define PARALLEL_MERGE_SORT_STACK_H

#include "list.h"

typedef void (*freeFunction)(void *);

typedef struct stack {
    list *list;
} stack;

void stack_new_stack(stack *stack ,int elementSize, freeFunction freeFunction);

void stack_destroy_stack(stack *stack);

void stack_push(stack *stack, void *element);

void stack_pop(stack *stack, void *element);

void stack_peek(stack *stack, void *element);

int stack_size(stack *stack);

#endif //PARALLEL_MERGE_SORT_STACK_H
