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

void preemptiveSJF(struct Process *proc[], int n) {
    int time = 0, completed = 0;
    int min_bt, idx;

    for (int i = 0; i < n; i++) {
        proc[i]->remaining_bt = proc[i]->bt;
        proc[i]->completed = 0;
    }

    while (completed < n) {
        min_bt = INT_MAX;
        idx = -1;

        for (int i = 0; i < n; i++) {
            if (proc[i]->at <= time && proc[i]->completed == 0 && proc[i]->remaining_bt < min_bt) {
                min_bt = proc[i]->remaining_bt;
                idx = i;
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
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
            proc[i]->id, proc[i]->at, proc[i]->bt,
            proc[i]->ct, proc[i]->tat, proc[i]->wt);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process *proc[n];
    for (int i = 0; i < n; i++) {
        proc[i] = (struct Process *)malloc(sizeof(struct Process));
        printf("Enter PID, Arrival Time, Burst Time: ");
        scanf("%d %d %d", &proc[i]->id, &proc[i]->at, &proc[i]->bt);
    }

    sortByArrivalTime(proc, n);
    preemptiveSJF(proc, n);
    printDetails(proc, n);
    averageTime(proc, n);

    for (int i = 0; i < n; i++) {
        free(proc[i]);
    }

    return 0;
}
