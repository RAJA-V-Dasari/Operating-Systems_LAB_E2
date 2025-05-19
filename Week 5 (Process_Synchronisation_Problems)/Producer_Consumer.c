#include <stdio.h>

#define SIZE 5
#define STEPS 30 // total operations to simulate

int buffer[SIZE];
int in = 0, out = 0;

// Semaphores
int full = 0;
int empty = SIZE;

// Mutex lock
int available = 1;

// Semaphore functions
void wait(int *S) {
    while (*S <= 0); // busy wait
    (*S)--;
}

void signal(int *S) {
    (*S)++;
}

// Mutex lock functions
void acquire() {
    while (!available); // busy wait
    available = 0;
}

void release() {
    available = 1;
}

void producer() {
    static int item = 1;

    wait(&empty);
    acquire();

    buffer[in] = item;
    printf("Produced item %d at index %d\n", item, in);
    in = (in + 1) % SIZE;
    item++;

    release();
    signal(&full);
}

void consumer() {
    wait(&full);
    acquire();

    int item = buffer[out];
    printf("Consumed item %d from index %d\n", item, out);
    out = (out + 1) % SIZE;

    release();
    signal(&empty);
}

int main() {
    int operations[STEPS] = {
        1, 1, 2, 1, 2, 2, 1, 2, 2, 1,
        1, 2, 1, 2, 2, 2, 1, 2, 2, 1,
        1, 1, 1, 1, 1, 1, 1, 2, 1, 1
    };

    for (int i = 0; i < STEPS; i++) {
        if (operations[i] == 1) {
            if (empty > 0) producer();
            else printf("Buffer full. Skipping production.\n");
        } else {
            if (full > 0) consumer();
            else printf("Buffer empty. Skipping consumption.\n");
        }
    }

    return 0;
}
