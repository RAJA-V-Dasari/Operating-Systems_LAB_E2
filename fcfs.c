#include<stdio.h>
#include<stdlib.h>

struct Process{
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

void sortByArrivalTime(struct Process *proc[],int n){
    for(int i = 0; i<n-1;i++){
        for(int j = i+1;j<n;j++){
            if(proc[i]->at > proc[j]->at){
                struct Process *temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}
void completionTime(struct Process *proc[],int n){
    proc[0]->ct = proc[0]->at+ proc[0]->bt;
    for(int i = 1; i < n; i++ ){
        proc[i]->ct= proc[i-1]->ct +proc[i]->bt;
    }
}
void turnAroundTime(struct Process *proc[],int n){
    for(int i = 0; i<n; i++){
        proc[i]->tat = proc[i]->ct - proc[i]->at;
    }
}
void waitingTime(struct Process *proc[],int n){
    for(int i = 0; i<n; i++){
        proc[i]->wt = proc[i]->tat - proc[i]->bt;
    }
}

void averageTime(struct Process *proc[],int n){
    int SumTAT=0;
    int SumWT=0;
    for(int i = 0;i<n;i++){
        SumTAT+=proc[i]->tat;
        SumWT+=proc[i]->wt;

    }
    float avgtat = (float)SumTAT/(float)n;
    float avgwt = (float)SumWT/(float)n;
    printf("Average Waiting Time : %f \n Average Turn Around Time : %f\n",avgwt,avgtat);
}

void printDetails(struct Process *proc[],int n){
    printf ("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",proc[i]->id,proc[i]->at,proc[i]->bt,proc[i]->ct,proc[i]->tat,proc[i]->wt);
    }
}

void main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    struct Process *proc[n];
    for(int i =0;i<n;i++){
        proc[i] = (struct Process *)malloc(sizeof(struct Process));
        printf("Enter PID, Arrival Time, Burst Time: ");
        scanf("%d %d %d",&proc[i]->id,&proc[i]->at,&proc[i]->bt);
    }
    sortByArrivalTime(proc, n);
    completionTime(proc, n);
    turnAroundTime(proc,n);
    waitingTime(proc,n);
    printDetails(proc,n);
    averageTime(proc,n);
}



































