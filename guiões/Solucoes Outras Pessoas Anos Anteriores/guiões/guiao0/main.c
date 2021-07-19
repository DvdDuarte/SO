#include <stdio.h>
#include "queue.h"

int main () {
    int n, i = 0, x;
    QUEUE *q;
    printf("Quantos elementos a pôr na queue?\n");
    scanf("%d", &n);
    printf("\n");
    initQueue(q,n);
    while (i < n) {
        scanf("%d", &x);
        enqueue(q,x);
        i++;
    }
    list(q);
    return 0;
}