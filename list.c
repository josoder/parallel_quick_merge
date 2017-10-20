//
// Created by josoder on 20.10.17.
//

#include "list.h"
#include "common.h"

/**
 * Create a new linked list
 * @param list
 * @param elementSize
 * @param freeFunction, Needed when storing strings
 */
void list_new(list *list, int elementSize, freeFunction freeFunction)
{
    assert(elementSize > 0);
    list->logicalLength = 0;
    list->elementSize = elementSize;
    list->head = list->tail = NULL;
    list->freeFn = freeFunction;
}

/**
 * Free memory
 * @param list
 */
void list_destroy(list *list)
{
    listNode *current;
    while(list->head != NULL) {
        current = list->head;
        list->head = current->next;

        if(list->freeFn){
            list->freeFn(current->data);
        }
        free(current->data);
        free(current);
    }
}

/**
 * Add element in front of the list, replacing head.
 * @param list
 * @param element
 */
void list_add_head(list *list, void *element){
    // allocate memory for the node & the element it self
    listNode *front = malloc(sizeof(listNode));
    front->data = malloc(list->elementSize);
    // copy the raw bytes sent in with element to front->data
    memcpy(front->data, element, list->elementSize);


    front->next = list->head;
    list->head = front;

    // if the list is empty, the tail and head pointers will point to the same node
    if(list->logicalLength==0){
        list->tail = list->head;
    }

    list->logicalLength++;
}

/**
 * Add element after the last element in the list, replacing the tail.
 * @param list
 * @return
 */
void list_add_tail(list *list, void *element) {
    listNode *back = malloc(sizeof(listNode));
    back->data = malloc(sizeof(list->elementSize));
    memcpy(back->data, element, list->elementSize);

    if(list->logicalLength==0) {
        list -> tail = list -> head = back;
    } else {
        list->tail->next = back;
        list->tail = back;
    }

    list->logicalLength++;
}

/**
 * Copy the content of the heads data into the space specified by *element and remove it if rm is true.
 * @param list
 * @param element
 * @param rm
 */
void list_head(list *list, void *element, bool rm){
    assert(list->head != NULL);

    listNode *node = list->head;
    memcpy(element, node->data, list->elementSize);
    if (rm){
        list->head = node->next;
        list->logicalLength--;

        free(node->data);
        free(node);
    }
}

/**
 * Copy content from the tail of the list to element.
 * @param list
 * @param element
 */
void list_tail(list *list, void *element){
    assert(list->tail != NULL);

    memcpy(element, list->tail->data, list->elementSize);
}

void list_for_each(list *list, listIterator listIterator){
    assert(listIterator != NULL);
    listNode *current = list->head;

    while (current!=NULL){
        listIterator(current->data);
        current = current->next;
    }
}

/**
 * Return size of the list
 * @param list
 * @return
 */
int list_size(list *list) {
    return list->logicalLength;
}