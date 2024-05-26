#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

#include <stdlib.h>

Heap *heap_create() {
    Heap *pq = (Heap *)malloc(sizeof(Heap));
    pq->capacity = 10;
    pq->size = 0;
    pq->data = (void **)malloc(pq->capacity * sizeof(void *));
    pq->priorities = (int *)malloc(pq->capacity * sizeof(int));
    return pq;
}

void heap_push(Heap *pq, void *data, int priority) {
    if (pq->size + 1 > pq->capacity) {
        pq->capacity *= 2;
        pq->data = (void **)realloc(pq->data, pq->capacity * sizeof(void *));
        pq->priorities = (int *)realloc(pq->priorities, pq->capacity * sizeof(int));
    }

    int i = pq->size;
    pq->data[i] = data;
    pq->priorities[i] = priority;
    pq->size++;

    while (i > 0 && pq->priorities[i] < pq->priorities[(i - 1) / 2]) {
        void *temp_data = pq->data[i];
        pq->data[i] = pq->data[(i - 1) / 2];
        pq->data[(i - 1) / 2] = temp_data;

        int temp_priority = pq->priorities[i];
        pq->priorities[i] = pq->priorities[(i - 1) / 2];
        pq->priorities[(i - 1) / 2] = temp_priority;

        i = (i - 1) / 2;
    }
}

void *heap_top(Heap *pq) {
    if (pq->size == 0)
        return NULL;
    return pq->data[0];
}

void heap_pop(Heap *pq) {
    if (pq->size == 0)
        return;

    pq->size--;
    pq->data[0] = pq->data[pq->size];
    int priority = pq->priorities[pq->size];

    int i = 0;
    while (2 * i + 1 < pq->size) {
        int j = 2 * i + 1;
        if (j + 1 < pq->size && pq->priorities[j + 1] < pq->priorities[j])
            j++;

        if (priority > pq->priorities[j]) {
            void *temp_data = pq->data[i];
            pq->data[i] = pq->data[j];
            pq->data[j] = temp_data;

            int temp_priority = pq->priorities[i];
            pq->priorities[i] = pq->priorities[j];
            pq->priorities[j] = temp_priority;

            i = j;
        } else {
            break;
        }
    }
}

void heap_clean(Heap *pq) {
    free(pq->data);
    free(pq->priorities);
    free(pq);
}