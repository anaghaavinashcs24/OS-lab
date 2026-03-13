#include <stdio.h>

struct Process {
    int pid, bt, at, pr;
    int wt, tat, ct, completed;
};

int main() {
    int n, time = 0, completed = 0;
    struct Process p[20];
    float avgwt = 0, avgtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter Arrival Time, Burst Time and Priority for P%d: ", i+1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].pid = i+1;
        p[i].completed = 0;
    }

    while(completed < n) {
        int idx = -1;
        int highest = 9999;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].completed == 0) {
                if(p[i].pr < highest) {
                    highest = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = 1;
            completed++;
        } else {
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tWT\tTAT\n");

    for(int i = 0; i < n; i++) {
        avgwt += p[i].wt;
        avgtat += p[i].tat;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f", avgwt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat/n);

    return 0;
}
