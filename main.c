#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

/**
 * Data past into the sorting workers
 */
typedef struct sort_struct {
    size_t size;
    int *numbers;
    int start;
    int id;
} sort_struct;

int cmpfunc(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

/**
 * Sort an array of numbers in a thread.
 * @param vargp
 * @return
 */
void *sortThread(void *vargp) {
    sort_struct *s = (sort_struct *) vargp;
    printf("thread:%d sorting.. \n", s->id);
    qsort(s->numbers + (s->start), s->size, sizeof(int), cmpfunc);
    return NULL;
}

void populateRandom(int *array, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = (rand() % 100);
    }
}

/**
 * Divide the data into smaller segments and sort every part in its own thread.
 * @param buff
 * @param size
 */
void divide(int *numbers, int size, int nThreads) {
    sort_struct *sortStructs[nThreads];
    pthread_t threadIds[nThreads];

    int segSize = size / nThreads;

    for (int i = 0; i < nThreads; i++) {
        sortStructs[i] = (sort_struct *) malloc(sizeof(sort_struct));
        sortStructs[i]->start = i * (segSize);
        sortStructs[i]->size = segSize;
        sortStructs[i]->numbers = numbers;
        sortStructs[i]->id = i+1;
    }

    pthread_t tmp;
    for (int i = 0; i < nThreads; i++) {
        pthread_create(&tmp, NULL, sortThread, (void *) sortStructs[i]);
    }

    pthread_join(tmp, NULL);

    printf("all segments are now sorted: \n");

    for (int i = 0; i < nThreads; i++) {
        for (int j = 0; j < segSize; j++) {
            printf("%d, ", numbers[j+(i*segSize)]);
        }
        printf("\n");
    }

}

int main() {
    int numbers[100];
    populateRandom(numbers, 100);
    divide(numbers, 100, 10);


    //pthread_join(tid, NULL);

    //for(int i=0; i<s->size; i++){
    //    printf("%d, ", numbers[i]);
    //}

    return 0;
}