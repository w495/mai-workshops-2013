#ifndef __QUEUE_H__
#define __QUEUE_H__

#include<stdlib.h>
#include<stdio.h>

typedef struct __queueInner__ queueInner_t;

struct __queueInner__ {
    int val;
    queueInner_t *previous;
};


typedef struct {
    queueInner_t *mainQueue;
    queueInner_t *first;
    int size;
} queue_t;

queue_t *queue_create();

queue_t *queue_init(queue_t *Queue);

queue_t *queue_sort(queue_t *Queue);

queue_t *queue_add(queue_t *Queue);

queue_t *queue_del(queue_t *Queue);

queue_t *queue_concat(queue_t *firstQueue, queue_t *secondQueue);

queue_t *queue_new_main(queue_t *Queue);

void queue_print(queue_t *mainQueue);

queueInner_t *sort(queueInner_t *Queue, queueInner_t *last, int n);

#endif /* __QUEUE_H__ */
