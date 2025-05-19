#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

int queue[SIZE];
int front = -1, rear = -1;

void enqueue(int value) {
    if ((rear + 1) % SIZE == front) {
        printf("Queue Overflow! Cannot enqueue %d\n", value);
    } else {
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        queue[rear] = value;
        printf("Enqueued %d\n", value);
    }
}

int dequeue() {
    if (front == -1) {
        printf("Queue Underflow! Nothing to dequeue\n");
        return -1;
    } else {
        int val = queue[front];
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
        printf("Dequeued %d\n", val);
        return val;
    }
}

void display() {
    if (front == -1) {
        printf("Queue is empty\n");
    } else {
        printf("Queue contents: ");
        int i = front;
        while (1) {
            printf("%d ", queue[i]);
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
        printf("\n");
    }
}

int main() {
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);

    display();

    dequeue();
    dequeue();
    enqueue(5);
    enqueue(6);

    display();

    dequeue();
    dequeue();
    dequeue();
    dequeue();

    display();

    return 0;
}
