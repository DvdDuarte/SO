#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

int dupQueue (QUEUE *q) {
    int r = 0;
    int *t = malloc (2 * q -> size * sizeof(int));
    if (t == NULL) 
        r = 1;
    else {
        for(int i = 0; i < q -> size; i++) 
            t[i] = q -> valores[i];
        free(q -> valores);
        q -> valores = t;
        q -> size *= 2;
    }
    return r;
}

void initQueue (QUEUE *q, int size) {
    q -> inicio = 0;
    q -> fim = 0;
    q -> size = size;
    q -> valores = malloc (q -> size * sizeof(int));
}

int isEmptyQ (QUEUE *q) {
    return (q -> fim == 0);
}

int enqueue (QUEUE *q, int x) {
    int r = 0;
    int pos;
    if (q -> fim == q -> size) 
        r = dupQueue(q);
    if (r == 0) {
        pos = (q -> inicio) + (q -> fim) % q -> size;
        q -> valores[pos] = x;
        q -> fim++;
    }
    return r;
}

int dequeue (QUEUE *q, int *x) {
    if (!isEmptyQ(q)) {
        *x = q -> valores[q -> inicio];
        q -> inicio = (q -> inicio + 1) % q -> size;
        return 0;
    }
    else return 1;
}

int front (QUEUE *q, int *x) {
    if (!isEmptyQ(q)) {
        *x = q -> valores[q -> inicio];
        return 0;
    }
    else return 1;
}

int end (QUEUE *q, int *x) {
    if (!isEmptyQ(q)) {
        *x = q -> valores[q -> fim - 1];
        return 0;
    }
    else return 1;
}

void list (QUEUE *q) {
    printf("Lista: ");
    if (!isEmptyQ(q)) {
        for (int i = q -> inicio; i < q -> fim; i++)
            printf("%d ", q -> valores[i]);
        printf("\n");
    }
    else printf("Vazia.\n");
}

