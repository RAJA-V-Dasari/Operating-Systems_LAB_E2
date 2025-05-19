#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

int stack[SIZE];
int top = -1;

void push(int value) {
    if (top == SIZE - 1) {
        printf("Stack Overflow! Cannot push %d\n", value);
    } else {
        top++;
        stack[top] = value;
        printf("Pushed %d\n", value);
    }
}

int pop() {
    if (top == -1) {
        printf("Stack Underflow! Nothing to pop\n");
        return -1;
    } else {
        int popped = stack[top];
        top--;
        printf("Popped %d\n", popped);
        return popped;
    }
}

void display() {
    if (top == -1) {
        printf("Stack is empty\n");
    } else {
        printf("Stack contents: ");
        for (int i = top; i >= 0; i--) {
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
}

int main() {
    push(10);
    push(20);
    push(30);
    push(40);

    display();

    int p1 = pop();
    int p2 = pop();
    int p3 = pop();
    int p4 = pop();

    display();

    return 0;
}
