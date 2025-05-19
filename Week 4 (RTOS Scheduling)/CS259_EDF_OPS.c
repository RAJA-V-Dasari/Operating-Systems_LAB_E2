#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int period;
    int burst;
    int remaining;
    int deadline;
} Task;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int calculate_lcm(Task *tasks, int n) {
    int lcm_value = tasks[0].period;
    for (int i = 1; i < n; i++) {
        lcm_value = lcm(lcm_value, tasks[i].period);
    }
    return lcm_value;
}

void sort_tasks(Task *tasks, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j].deadline > tasks[j + 1].deadline) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

void edf_scheduling(Task *tasks, int n, int total_time) {
    for (int time = 0; time < total_time; time++) {
        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining = tasks[i].burst;
                tasks[i].deadline = time + tasks[i].period;
            }
        }

        sort_tasks(tasks, n);

        Task *current_task = NULL;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                current_task = &tasks[i];
                break;
            }
        }

        if (current_task != NULL) {
            printf("Time %d: Task %d is running\n", time , current_task->id);
            current_task->remaining--;
            if (current_task->remaining == 0) {
                printf("Time %d: Task %d completed\n", time + 1, current_task->id);
            }
        } else {
            printf("Time %d: Idle\n", time+1 );
        }
    }
}

int main() {
    int n;
    printf("Enter the number of tasks: ");
    scanf("%d", &n);

    Task *tasks = (Task *)malloc(n * sizeof(Task));
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Enter period and burst time for Task %d: ", tasks[i].id);
        scanf("%d %d", &tasks[i].period, &tasks[i].burst);
    }

    int total_time = calculate_lcm(tasks, n);
    printf("LCM of periods: %d\n", total_time);

    edf_scheduling(tasks, n, total_time);

    free(tasks);
    return 0;
}
