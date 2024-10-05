#include "queue.h"
#include <string.h>

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
   // currently instead of using realloc this just copies the data to a new array and sets the head back to 0, which potentially 
   // could cause some problems if you don't look at the source code and are lazy with pointers but it will do for now

    int total = queue->capacity + additional;
    void *tmp = malloc(total * queue->elementSize);

    if (!tmp){
        return;
    }

    if (queue->head < queue->tail){
        memcpy(tmp, (char*)queue->data + queue->head * queue->elementSize, queue->elementSize * queue->elementSize);

    }
    else{
        int arrayEndSize = queue->capacity - queue->head;
        memcpy(tmp, (char*)queue->data + queue->head * queue->elementSize, arrayEndSize * queue->elementSize);

        int wrapAroundSize = queue->tail + 1;
        memcpy((char*)tmp + arrayEndSize * queue->elementSize, queue->data, wrapAroundSize * queue->elementSize);
    }

    queue->head = 0;
    queue->tail = queue->size - 1;
    queue->capacity = total;

    free(queue->data);
    queue->data = tmp;
}

void queue_free(Queue *queue){
    free(queue->data);
    queue->data = NULL;
    queue->size = 0;
    queue->head = 0;
    queue->tail = -1;
}
