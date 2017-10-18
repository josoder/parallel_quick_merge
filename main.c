#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

/**
 * Data past into the sorting workers
 */
typedef struct sort_struct {
    int size;
    int *numbers;
} sort_struct;

int cmpfunc (const void * a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Sort an array of numbers in a thread.
 * @param vargp
 * @return
 */
void *sortThread(void *vargp){
    sort_struct* s = (sort_struct*) vargp;
    printf("sorting..");
    qsort(s->numbers, s->size, sizeof(int), cmpfunc);
    return NULL;
}

void populateRandom(int *array, int size){
    srand(time(NULL));
    for(int i=0; i<size; i++){
        array[i] = (rand() % 100);
    }
}

/**
 * Divide the data into smaller part
 * @param buff
 * @param size
 */
void divide(int* numbers, int size, int nThreads){
    sort_struct* sortStructs[nThreads];
    pthread_t threadIds[nThreads];

    for(int i=0; i<nThreads; i++){
        sortStructs[i] = (sort_struct*) malloc(sizeof(sort_struct));
    }

    for(int i=0; i<nThreads; i++){
        sortStructs[i]->numbers = malloc((size/nThreads) * (sizeof(int)));
        memcpy(sortStructs[i]->numbers, (numbers)+(i*size/nThreads), size/nThreads*(sizeof(int)));
    }

    for(int i=0; i<nThreads; i++){
        int *num = sortStructs[i]->numbers;
        for(int i=0; i<(size/nThreads); i++){
            printf("%d, ", num[i]);
        }
        printf("\n");
    }

}

int main() {
    int numbers[100];
    populateRandom(numbers, 100);
    divide(numbers, 100, 2);


    //pthread_join(tid, NULL);

    //for(int i=0; i<s->size; i++){
    //    printf("%d, ", numbers[i]);
    //}

    return 0;
}