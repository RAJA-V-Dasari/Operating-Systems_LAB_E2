#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 10
typedef struct{
    int id,at,bt,ct,tat,wt,rt,remaining;
    bool started;
}Process;

void sort_by_arrival_time(Process p[],int n){
    for(int i = 0; i<n-1;i++){
        for(int j = 0;j<n-i-1;j++){
            if(p[j].at>p[j+1].at){
                Process temp = p[j];
                p[j]= p[j+1];
                p[j+1]=p[j];
            }
        }
    }
}

void printDetails(Process p[],int n){
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i = 0; i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }
}

int main(){
    int n;
    int sys_count= 0;
    int user_count = 0;
    int time = 0;
    int completed = 0;
    Process sys[MAX];
    Process user[MAX];
    printf("Enter number of processes:");
    scanf("%d",&n);
    if(n>MAX){
        printf("Number of Processes exceeded limit\n");
        return 1;
    }
    printf("Enter PID,AT,BT,TYPE\nTYPE : 0->System 1->User\n");
    for(int i = 0; i<n;i++){
        Process temp;
        int type;
        printf("P%d: ",i+1);
        scanf("%d %d %d %d",&temp.id,&temp.at,&temp.bt,&type);
        temp.remaining=temp.bt;
        temp.started=false;

        if(type==0)sys[sys_count++]=temp;
        else if(type ==1)user[user_count++]=temp;
        else{
            printf("Invalid Type, Re enter attributes\n");
            i--;
        }
    }

    sort_by_arrival_time(sys,sys_count);
    sort_by_arrival_time(user,user_count);

    int sys_index = 0;
    int user_index = 0;
    Process *current = NULL;

    while(completed <n){
        if(sys_index<sys_count && sys[sys_index].at<=time) current = &sys[sys_index];
        else if((user_index<user_count && user[user_index].at<=time)&&(!current || current->remaining == 0)) current = &user[user_index];
        if(current && current->remaining>0){
            if(!current->started){
                current->rt = time - current->at;
                current->started = true;
            }
            current->remaining--;
            time++;

            if(current->remaining == 0){
                current ->ct = time;
                current->tat = current->ct - current->at;
                current->wt = current->tat - current->bt;
                completed++;

                if(current == &sys[sys_index])sys_index++;
                else user_index++;
                current = NULL;
            }
        }
        else time++;
    }

    printf("System Process :\n");
    printDetails(sys,sys_count);

    printf("User Process :\n");
    printDetails(user,user_count);

    double total_wt = 0;
    double total_tat = 0;

    for(int i = 0;i<sys_count;i++){
        total_wt += sys[i].wt;
        total_tat += sys[i].tat;
    }

    for(int i = 0;i<user_count;i++){
        total_wt += user[i].wt;
        total_tat += user[i].tat;
    }
    printf("Average TAT: %f", (total_tat)/(double)n);
    printf("Average WT: %f", (total_wt)/(double)n);

}
