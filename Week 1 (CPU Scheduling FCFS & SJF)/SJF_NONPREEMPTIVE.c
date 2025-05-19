#include<stdio.h>
#include<stdlib.h>

struct Process{
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int remaining_bt;
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

void sortByBurstTime(struct Process *proc[], int n, int current_time) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if(proc[i]->at <= current_time && proc[j]->at <= current_time && proc[i]->remaining_bt > proc[j]->remaining_bt){
                struct Process *temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void completionTime(struct Process *proc[], int n) {
    int time = 0;
    int completed = 0;
    int processed[n];

    for (int i = 0; i < n; i++) {
        processed[i] = 0;
        proc[i]->remaining_bt = proc[i]->bt;
    }

    while (completed < n) {
        int index = -1;
        for (int i = 0; i < n; i++) {
            if (proc[i]->at <= time && !processed[i]) {
                if (index == -1 || proc[i]->remaining_bt < proc[index]->remaining_bt) {
                    index = i;
                }
            }
        }

        if (index != -1) {
            time += proc[index]->remaining_bt;
            proc[index]->ct = time;
            proc[index]->tat = proc[index]->ct - proc[index]->at;
            proc[index]->wt = proc[index]->tat - proc[index]->bt;
            processed[index] = 1;
            completed++;
        } else {
            time++;
        }
    }
}
void turnAroundTime(struct Process *proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i]->tat = proc[i]->ct - proc[i]->at;
}
}

void waitingTime(struct Process *proc[], int n){
    for (int i = 0; i < n; i++) {
        proc[i]->wt = proc[i]->tat - proc[i]->bt;
    }
}

void averageTime(struct Process *proc[], int n){
    int SumTAT = 0;
    int SumWT = 0;
    for (int i = 0; i < n; i++) {
        SumTAT += proc[i]->tat;
        SumWT += proc[i]->wt;
    }
    float avgtat = (float)SumTAT / n;
    float avgwt = (float)SumWT / n;
    printf("Average Waiting Time: %f\n", avgwt);
    printf("Average Turnaround Time: %f\n", avgtat);
}

void printDetails(struct Process *proc[], int n){
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
            proc[i]->id, proc[i]->at, proc[i]->bt, proc[i]->ct, proc[i]->tat, proc[i]->wt);
    }
}

int main(){
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
    completionTime(proc, n);
    turnAroundTime(proc, n);
    waitingTime(proc, n);
    printDetails(proc, n);
    averageTime(proc, n);
    return 0;

}





































