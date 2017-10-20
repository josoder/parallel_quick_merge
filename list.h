//
// Created by josoder on 20.10.17.
//

#ifndef PARALLEL_MERGE_SORT_LIST_H
#define PARALLEL_MERGE_SORT_LIST_H

#include <stdbool.h>

// function to free malloc'd objects
typedef void (*freeFunction)(void *);

// iterate over the list
typedef void (*listIterator)(void *);

typedef struct _listNode {
    void *data;
    struct _listNode *next;
} listNode;

typedef struct {
    int logicalLength;
    int elementSize;
    listNode *head;
    listNode *tail;
    freeFunction freeFn;
} list;

void list_new(list *list, int elementSize, freeFunction freeFn);

void list_destroy(list *list);

void list_for_each(list *list ,listIterator listIterator);

void list_add_head(list *list, void *element);

void list_add_tail(list *list, void *element);

void list_head(list *list, void *element, bool rm);

void list_tail(list *list, void *element);

int list_size(list *list);

#endif //PARALLEL_MERGE_SORT_LIST_H
