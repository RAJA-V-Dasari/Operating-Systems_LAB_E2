#include <stdio.h>

#define N 5

int chopstick[N] = {1, 1, 1, 1, 1};  // 1 = available, 0 = unavailable

// Wait (P) operation
void wait(int *S) {
    while (*S <= 0)
        ;  // busy wait
    (*S)--;
}

// Signal (V) operation
void signal(int *S) {
    (*S)++;
}

// Simulate philosopher i
void philosopher(int i) {
    printf("Philosopher %d is HUNGRY\n", i);

    wait(&chopstick[i]);                  // pick up left
    wait(&chopstick[(i + 1) % N]);        // pick up right

    printf("Philosopher %d is EATING with chopsticks %d and %d\n", i, i, (i + 1) % N);

    // Simulate eating
    for (volatile int t = 0; t < 10000000; t++);

    signal(&chopstick[i]);                // put down left
    signal(&chopstick[(i + 1) % N]);      // put down right

    printf("Philosopher %d is THINKING\n\n", i);

    // Simulate thinking
    for (volatile int t = 0; t < 10000000; t++);
}

int main() {
        // Fixed order, philosophers take turns
        for (int i = 0; i < N; i++) {
            philosopher(i);
        }


    return 0;
}
