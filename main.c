#include "common.h"
#include "threaded_quicksort.h"

/**
 * Put some random integers into the array
 * @param array
 * @param size
 */
void populateRandom(int *array, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = (rand() % 1000);
    }
}


void mergeHelper(sort_struct *s1, sort_struct *s2 , int resSize, int res[resSize]) {
    int length = resSize;
    int j = 0;
    int k = 0;
    int i = 0;

    // cases:
    // seg1 is exhausted,
    // seg2 is exhausted
    while (i < length) {
        if (j >= s1->length) {
            while (i < length) {
                res[i++] = s2->numbers[k++];
            }
            break;
        }
        else if (k >= s2->length) {
            while (i < length) {
                res[i++] = s2->numbers[j++];
            }
            break;
        }

        if (s1->numbers[j] < s2->numbers[k]) {
            res[i++] = s1->numbers[j];

            j++;
        }
        else {
            res[i++] = s2->numbers[k];
            k++;
        }
    }
}


int main() {
    int nThreads = 2;
    int nNrs = 100;
    int segmentSize = nNrs / nThreads;

    int numbers[nNrs];
    populateRandom(numbers, nNrs);
    //sort_struct *segments[nThreads];

    // divide into segments

    sort_struct* sortStruct[2];

    for(int i = 0; i<nThreads; i++){
        sortStruct[i] = (sort_struct*) malloc(sizeof(sort_struct*));
        sortStruct[i]->numbers = (int *) malloc((nNrs/2) * sizeof(int));
        sortStruct[i]->id = i+1;
        sortStruct[i]->length = segmentSize;
    }

    int offset = 0;
    for(int i = 0; i<2; i++){
        for(int j=0; j<nNrs/2; j++) {
            sortStruct[i]->numbers[j] = numbers[j+offset];
        }
        offset = nNrs/2;
    }

    divideAndConquer(50, 2, numbers, sortStruct);

    int res[nNrs];

    mergeHelper(sortStruct[0], sortStruct[1], nNrs, res);

    for(int i=0; i<nNrs; i++){
        printf("%d ,", res[i]);
        if(i%9==0&&i!=0){
            puts("");
        }
    }

    return 0;
}