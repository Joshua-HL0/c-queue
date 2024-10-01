#include "queue.h"

void queue_init(Queue *queue, int elementSize, int capacity){
    queue->elementSize = elementSize;
    queue->capacity = capacity;
    queue->size = 0;
    queue->head = 0;
    queue->tail = -1;
    queue->data = malloc(elementSize * capacity);
}

void queue_enqueue(Queue *queue, void *element){
    if (queue_is_full(queue)){
        queue_resize(queue, queue->capacity);
    }
    
    queue->tail = (queue->tail + 1) % queue->capacity;
    memcpy((char*)queue->data + queue->tail * queue->elementSize, element, queue->elementSize);
    queue->size++;
}

void queue_dequeue(Queue *queue, void *element){
    if (queue_is_empty(queue)){
        return;
    }
    
    memcpy(element, (char*)queue->data + queue->head * queue->elementSize, queue->elementSize);
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;
}

void queue_peek(Queue *queue, void *element){
    if (queue_is_empty(queue)){
        return;
    }
    
    memcpy(element, (char*)queue->data + queue->head * queue->elementSize, queue->elementSize);
}

int queue_is_full(Queue *queue){
    return (queue->size == queue->capacity);
}

int queue_is_empty(Queue *queue){
    return (queue->size == 0);
}

void queue_resize(Queue *queue, int additional){
    ; // will implement soon! obviously more complicated because the queue is circular and just using realloc would case a gap in the queue (probably will use realloc then memcpy)
}

void queue_free(Queue *queue){
    free(queue->data);
    queue->data = NULL;
    queue->size = 0;
    queue->head = 0;
    queue->tail = -1;
}
