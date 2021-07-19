#ifndef _QUEUE
#define _QUEUE

typedef struct queue {
    int size; 
    int inicio, fim;
    int *valores;
} QUEUE;

int dupQueue (QUEUE *q);
void initQueue (QUEUE *q, int size);
int isEmptyQ (QUEUE *q);
int enqueue (QUEUE *q, int x);
int dequeue (QUEUE *q, int *x);
int front (QUEUE *q, int *x);
int end (QUEUE *q, int *x);
void list (QUEUE *q);

#endif