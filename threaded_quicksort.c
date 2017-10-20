//
// Created by josoder on 19.10.17.
//

#include "threaded_quicksort.h"

int cmpfunc(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

/**
 * Sort an array of integers in a thread with q-sort.
 * @param vargp
 * @return
 */
void *sortThread(void *vargp) {
    sort_struct *s = (sort_struct *) vargp;
    printf("thread:%d sorting.. \n", s->id);
    qsort(s->numbers, s->length, sizeof(int), cmpfunc);
    return NULL;
}

/**
 * Divide array into smaller segments and sort them in a sort_struct.
 * Sort the segments in parallel using quicksort.
 * @param numbers
 * @param size
 * @param nThreads
 * @param segments
 */
void divideAndConquer(int segSize, int nThreads, int numbers[nThreads][segSize], sort_struct* sortStructs[]) {
    pthread_t tmp;
    for (int i = 0; i < nThreads; i++) {
        pthread_create(&tmp, NULL, sortThread, (void *) sortStructs[i]);
    }

    pthread_join(tmp, NULL);

    printf("all segments are now sorted: \n");
}