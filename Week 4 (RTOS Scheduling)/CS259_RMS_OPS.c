#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int id, period, burst, remaining, next_deadline;
} Task;

int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int calculate_lcm(Task *t, int n) {
    int lcm_value = t[0].period;
    for (int i = 1; i < n; i++) {
        lcm_value = lcm(lcm_value, t[i].period);
    }
    return lcm_value;
}

void sort_tasks(Task *t, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (t[j].period > t[j + 1].period) {
                Task temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }
}

double calculate_utilization(Task *t, int n) {
    double total = 0.0;
    for (int i = 0; i < n; i++) {
        total += (double)t[i].burst / t[i].period;
    }
    return total;
}

double calculate_bound(int n) {
    return n * (pow(2, 1.0 / n) - 1);
}

void rate_monotonic_scheduling(Task *t, int n, int total_time) {
    for (int time = 0; time < total_time; time++) {
        Task *current = NULL;
        for (int i = 0; i < n; i++) {
            if (time % t[i].period == 0) {
                t[i].remaining = t[i].burst;
                t[i].next_deadline = time + t[i].period;
            }
            if (t[i].remaining > 0) {
                if (!current || t[i].period < current->period) {
                    current = &t[i];
                }
            }
        }
        if (current) {
            printf("Time %d: Task %d is running\n", time+1, current->id);
            current->remaining--;
            if (current->remaining == 0) {
                printf("Time %d: Task %d completed\n", time + 1, current->id);
            }
        } else {
            printf("Time %d: Idle\n", time+1);
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

    double total_utilization = calculate_utilization(tasks, n);
    double bound = calculate_bound(n);
    int lcm_value = calculate_lcm(tasks, n);

    printf("Total Utilization: %.2f\n", total_utilization);
    printf("Utilization Bound: %.2f\n", bound);
    printf("LCM of periods: %d\n", lcm_value);

    if (total_utilization <= bound) {
        printf("Scheduling is possible.\n");
        sort_tasks(tasks, n);
        rate_monotonic_scheduling(tasks, n, lcm_value);
    } else {
        printf("Scheduling is not possible.\n");
    }

    free(tasks);
    return 0;
}
