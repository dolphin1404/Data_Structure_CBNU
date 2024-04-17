#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int front, rear;
  int capacity;
  int *array;
} CircularQueue;

CircularQueue* createQueue(int capacity) {
  CircularQueue *queue = (CircularQueue*) malloc(sizeof(CircularQueue));
  queue->capacity = capacity;
  queue->front = -1;
  queue->rear = -1;
  queue->array = (int*) malloc(queue->capacity * sizeof(int));
  return queue;
}

int isFull(CircularQueue *queue) {
  return (queue->rear + 1) % queue->capacity == queue->front;
}

int isEmpty(CircularQueue *queue) {
  return queue->front == -1;
}

void enqueue(CircularQueue *queue, int item) {
  if (isFull(queue)) {
    printf("Queue is full. Cannot enqueue.\n");
    return;
  }
  if (isEmpty(queue)) {
    queue->front = 0;
    queue->rear = 0;
  } else {
    queue->rear = (queue->rear + 1) % queue->capacity;
  }
  queue->array[queue->rear] = item;
  printf("%d enqueued to the queue.\n", item);
}

int dequeue(CircularQueue *queue) {
  if (isEmpty(queue)) {
    printf("Queue is empty. Cannot dequeue.\n");
    return -1;
  }
  int item = queue->array[queue->front];
  if (queue->front == queue->rear) {
    queue->front = -1;
    queue->rear = -1;
  } else {
    queue->front = (queue->front + 1) % queue->capacity;
  }
  return item;
}

void display(CircularQueue *queue) {
  if (isEmpty(queue)) {
    printf("Queue is empty.\n");
    return;
  }
  int i = queue->front;
  printf("Queue: ");
  while (i != queue->rear) {
    printf("%d ", queue->array[i]);
    i = (i + 1) % queue->capacity;
  }
  printf("%d\n", queue->array[i]);
}

int main() {
  int capacity, choice, item;
  printf("Enter the capacity of the circular queue: ");
  scanf("%d", &capacity);
  CircularQueue *queue = createQueue(capacity);
  while (1) {
    printf("\nCircular Queue Operations:\n");
    printf("1. Enqueue\n");
    printf("2. Dequeue\n");
    printf("3. Display\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        printf("Enter the item to enqueue: ");
        scanf("%d", &item);
        enqueue(queue, item);
        break;
      case 2:
        item = dequeue(queue);
        if (item != -1) {
          printf("%d dequeued from the queue.\n", item);
        }
        break;
      case 3:
        display(queue);
        break;
      case 4:
        printf("Exiting...\n");
        exit(0);
      default:
        printf("Invalid choice. Please try again.\n");
    }
  }
  return 0;
}