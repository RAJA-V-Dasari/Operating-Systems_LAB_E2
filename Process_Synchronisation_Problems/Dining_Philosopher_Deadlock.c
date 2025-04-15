#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

int chopstick[N] = {1, 1, 1, 1, 1};  // Semaphores for chopsticks

void sem_wait(int *S) {
    while (*S <= 0)
        ; // busy wait
    (*S)--;
}

void sem_signal(int *S) {
    (*S)++;
}

void* philosopher(void* num) {
    int i = *(int*)num;

    while (1) {
        printf("Philosopher %d is thinking\n", i);
        sleep(rand() % 3);  // Random think time

        printf("Philosopher %d is hungry\n", i);

        sem_wait(&chopstick[i]);
        printf("Philosopher %d picked up LEFT chopstick %d\n", i, i);

        usleep(1000);  // Delay to increase deadlock chance

        sem_wait(&chopstick[(i + 1) % N]);
        printf("Philosopher %d picked up RIGHT chopstick %d\n", i, (i + 1) % N);

        printf("Philosopher %d is eating\n", i);
        sleep(rand() % 2);

        sem_signal(&chopstick[i]);
        sem_signal(&chopstick[(i + 1) % N]);
        printf("Philosopher %d put down chopsticks\n\n", i);

        sleep(1); // Think a bit before next cycle
    }

    return NULL;
}

int main() {
    pthread_t threads[N];
    int indices[N];

    for (int i = 0; i < N; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &indices[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
