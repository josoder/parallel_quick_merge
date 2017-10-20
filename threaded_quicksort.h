//
// Created by josoder on 19.10.17.
//

#ifndef PARALLEL_MERGE_SORT_THREADED_QUICKSORT_H
#define PARALLEL_MERGE_SORT_THREADED_QUICKSORT_H

#include "common.h"


typedef struct sort_struct {
    int length;
    int *numbers;
    int id;
    int start;
    int end;
} sort_struct;


/**
 * Divide numbers into smaller segments and sort the segments in parallel
 */
void divideAndConquer(int segSize, int nThreads, int [nThreads][segSize], sort_struct* sortStructs[]);

int cmpfunc(const void *a, const void *b);

#endif //PARALLEL_MERGE_SORT_THREADED_QUICKSORT_H
