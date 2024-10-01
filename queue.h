#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    void *data;
    int head;
    int tail;
    int elementSize;
    int capacity;
    int size;
} Queue;

void queue_init(Queue *queue, int elementSize, int capacity);

void queue_enqueue(Queue *queue, void *element);
void queue_dequeue(Queue *queue, void *element);
void queue_peek(Queue *queue, void *element);
int queue_is_empty(Queue *queue);
int queue_is_full(Queue *queue);

void queue_resize(Queue *queue, int additional);
void queue_free(Queue *queue);


#endif
