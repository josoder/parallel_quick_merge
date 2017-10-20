//
// Created by josoder on 08.09.17.
//
#include <stdlib.h>
#include "stack.h"

void stack_new_stack(stack *stack ,int elementSize, freeFunction freeFunction){
    stack->list = malloc(sizeof(list));
    list_new(stack->list, elementSize, freeFunction);
}

void stack_destroy_stack(stack *stack){
    list_destroy(stack->list);
    free(stack-> list);
}

void stack_push(stack *stack, void *element){
    list_add_head(stack->list, element);
}

void stack_pop(stack *stack, void *element){
    list_head(stack->list, element, true);
}

void stack_peek(stack *stack, void *element){
    list_head(stack->list, element, false);
}

int stack_size(stack *stack){
    return list_size(stack->list);
}