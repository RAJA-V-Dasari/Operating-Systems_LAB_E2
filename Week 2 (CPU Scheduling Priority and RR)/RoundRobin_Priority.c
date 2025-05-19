#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process {
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int remaining_bt;
    int priority;   // Set to -1 when not used
    int completed;
};

void sortByArrivalTime(struct Process *proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i]->at > proc[j]->at) {
                struct Process *temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void averageTime(struct Process *proc[], int n) {
    int total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        total_tat += proc[i]->tat;
        total_wt += proc[i]->wt;
    }
    float avg_tat = (float)total_tat / n;
    float avg_wt = (float)total_wt / n;

    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
}

void printDetails(struct Process *proc[], int n) {
    printf("\nPID\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        if (proc[i]->priority != -1)
            printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
                proc[i]->id, proc[i]->at, proc[i]->bt,
                proc[i]->priority, proc[i]->ct, proc[i]->tat, proc[i]->wt);
        else
            printf("%d\t%d\t%d\t--\t%d\t%d\t%d\n",
                proc[i]->id, proc[i]->at, proc[i]->bt,
                proc[i]->ct, proc[i]->tat, proc[i]->wt);
    }
}

// Round Robin
void roundRobin(struct Process *proc[], int n, int quantum) {
    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;
    int visited[n];
    for (int i = 0; i < n; i++) {
        proc[i]->remaining_bt = proc[i]->bt;
        proc[i]->completed = 0;
        visited[i] = 0;
    }

    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n) {
        int index = queue[front++];

        if (proc[index]->remaining_bt > quantum) {
            time += quantum;
            proc[index]->remaining_bt -= quantum;
        } else {
            time += proc[index]->remaining_bt;
            proc[index]->remaining_bt = 0;
            proc[index]->ct = time;
            proc[index]->tat = proc[index]->ct - proc[index]->at;
            proc[index]->wt = proc[index]->tat - proc[index]->bt;
            proc[index]->completed = 1;
            completed++;
        }

        for (int i = 0; i < n; i++) {
            if (i != index && proc[i]->at <= time && !visited[i] && proc[i]->remaining_bt > 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (proc[index]->remaining_bt > 0)
            queue[rear++] = index;

        if (front == rear) {
            for (int i = 0; i < n; i++) {
                if (!proc[i]->completed && proc[i]->at > time) {
                    time = proc[i]->at;
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }
}

// Priority Scheduling - Non-Preemptive
void priorityNonPreemptive(struct Process *proc[], int n) {
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        proc[i]->completed = 0;
    }

    while (completed < n) {
        int idx = -1, highest = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!proc[i]->completed && proc[i]->at <= time) {
                if (proc[i]->priority < highest) {
                    highest = proc[i]->priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            time = (time < proc[idx]->at) ? proc[idx]->at : time;
            time += proc[idx]->bt;
            proc[idx]->ct = time;
            proc[idx]->tat = proc[idx]->ct - proc[idx]->at;
            proc[idx]->wt = proc[idx]->tat - proc[idx]->bt;
            proc[idx]->completed = 1;
            completed++;
        } else {
            time++;
        }
    }
}

// Priority Scheduling - Preemptive
void priorityPreemptive(struct Process *proc[], int n) {
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        proc[i]->remaining_bt = proc[i]->bt;
        proc[i]->completed = 0;
    }

    while (completed < n) {
        int idx = -1, highest = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!proc[i]->completed && proc[i]->at <= time) {
                if (proc[i]->priority < highest ||
                   (proc[i]->priority == highest && proc[i]->remaining_bt < proc[idx]->remaining_bt)) {
                    highest = proc[i]->priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            proc[idx]->remaining_bt--;
            time++;

            if (proc[idx]->remaining_bt == 0) {
                proc[idx]->ct = time;
                proc[idx]->tat = proc[idx]->ct - proc[idx]->at;
                proc[idx]->wt = proc[idx]->tat - proc[idx]->bt;
                proc[idx]->completed = 1;
                completed++;
            }
        } else {
            time++;
        }
    }
}

int main() {
    int n, choice, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process *proc[n];
    for (int i = 0; i < n; i++) {
        proc[i] = (struct Process *)malloc(sizeof(struct Process));
        printf("Enter PID, Arrival Time, Burst Time: ");
        scanf("%d %d %d", &proc[i]->id, &proc[i]->at, &proc[i]->bt);
        proc[i]->priority = -1; // default
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. Round Robin\n");
    printf("2. Priority Scheduling (Non-Preemptive)\n");
    printf("3. Priority Scheduling (Preemptive)\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &choice);

    if (choice == 2 || choice == 3) {
        for (int i = 0; i < n; i++) {
            printf("Enter Priority for PID %d (Lower = Higher priority): ", proc[i]->id);
            scanf("%d", &proc[i]->priority);
        }
    }

    sortByArrivalTime(proc, n);

    if (choice == 1) {
        printf("Enter Time Quantum: ");
        scanf("%d", &quantum);
        roundRobin(proc, n, quantum);
    } else if (choice == 2) {
        priorityNonPreemptive(proc, n);
    } else if (choice == 3) {
        priorityPreemptive(proc, n);
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    printDetails(proc, n);
    averageTime(proc, n);

    for (int i = 0; i < n; i++)
        free(proc[i]);

    return 0;
}
