#include"queue.h"

queue_t *queue_create() {
    queue_t* queue = malloc(sizeof(queue_t));
    queue = queue_init(queue);
    return queue;
}

queue_t *queue_init(queue_t *queue) {
    queue->mainQueue = malloc(sizeof(queueInner_t));
    queue->mainQueue->val = 0;
    queue->mainQueue->previous = NULL;
    queue->size = 0;
    queue->first = queue->mainQueue;

    return queue;
}

queue_t *queue_sort(queue_t *queue) {
    queue->mainQueue = sort(queue->mainQueue, queue->first, queue->size);
    queue = queue_new_main(queue);
    
    return queue;
}

queue_t *queue_add(queue_t *queue) {

    int n;

    scanf("%d", &n);
    if (queue->size == 0) {
        queue->mainQueue->val = n;
    }
    else {
        queue->mainQueue->previous = malloc(sizeof(queueInner_t));
        queue->mainQueue->previous->val = n;
        queue->mainQueue = queue->mainQueue->previous;
    }

    queue->size++;

    return queue;
}

queue_t *queue_del(queue_t *queue) {
    if (queue->mainQueue->val == 0) {
        printf("Empty\n");
    }
    else {
        printf("%d\n", queue->first->val);
        if (queue->first->previous == NULL)
            queue->first->val = 0;
        else {
            queue->first = queue->first->previous;
        }

        queue->size--;
    }
    return queue;
}

queue_t *queue_concat(queue_t *firstQueue, queue_t *secondQueue) {
    firstQueue->mainQueue->previous = secondQueue->first;
    firstQueue->mainQueue = secondQueue->mainQueue;
    firstQueue->size += secondQueue->size;

    return firstQueue;
}

void queue_print(queue_t *mainQueue) {
    int i;
    queueInner_t *go = mainQueue->first;

    for (i = 0; i < mainQueue->size; ++i) {
        printf("%d\n", go->val);
        go = go->previous;
        if (go == NULL) {
            break;
        }
    }
}

queue_t *queue_new_main(queue_t *queue){
    int i;
    for (i = 0; i < queue->size; ++i) {
        if (queue->mainQueue->previous != NULL)
            queue->mainQueue =
                queue->mainQueue->previous;
        else
            break;
    }
    return queue;
}

queueInner_t *sort(queueInner_t *queue, queueInner_t *last, int n) {

    if (n > 1) {
        int i, half = n / 2;
        int* mass = NULL;
        queueInner_t *x, *y;
        queueInner_t *temp = last;
        int xSize = n - half;
        int ySize = half;


        for (i = 1; i < half; ++i) {
            temp = temp->previous;
        }


        queue = sort(queue, temp->previous, n - half);
        queue = sort(temp, last, half);

        /** Так делать нельзя.
            int mass[n];
        **/
        mass = malloc(sizeof(int)*n);


        x = temp->previous;
        y = last;

        for (i = 0; i < n; ++i) {
            if ((xSize == 0 && ySize != 0) || (ySize > 0 && x->val > y->val)) {
                mass[i] = y->val;
                y = y->previous;
                ySize--;

                if (xSize == 0 && ySize == 0)
                    break;
            }
            else if ((ySize == 0 && xSize != 0) || (xSize > 0 && x->val <= y->val)) {
                mass[i] = x->val;
                x = x->previous;
                xSize--;

                if (xSize == 0 && ySize == 0)
                    break;
            }
        }
        x = last;

        for (i = 0; i < n; ++i) {
            x->val = mass[i];
            x = x->previous;
        }

        free(mass);
        return queue;
    }
    else
        return queue;
}
