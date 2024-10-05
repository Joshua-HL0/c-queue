#include <stdio.h>
#include "queue.h"

int main(){
    Queue q;
    queue_init(&q, sizeof(int), 5);

    int x = 12;
    queue_enqueue(&q, &x);
    x = 56;
    queue_enqueue(&q, &x);

    queue_resize(&q, 20);

    int y;
    queue_dequeue(&q, &y);
    printf("Dequeue: %d\n", y);

    queue_peek(&q, &y);
    printf("Peek: %d\n", y);

    queue_dequeue(&q, &y);
    printf("Dequeue: %d\n", y);

    printf("IsEmpty: %d\n", queue_is_empty(&q));
}
