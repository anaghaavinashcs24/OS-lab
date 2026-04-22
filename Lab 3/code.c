#include <stdio.h>
#include <math.h>

typedef struct {
    int id;
    int burst;
    int deadline;
    int period;
    int completion;
    int waiting;
    int tat;
} Process;

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    printf("Enter process details:\n");
    for(int i=0; i<n; i++) {
        p[i].id = i;
        printf("Process %d:\n", i);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);
        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);
    }

    // CPU Utilization
    double utilization = 0.0;
    for(int i=0; i<n; i++) {
        utilization += (double)p[i].burst / p[i].period;
    }

    // EDF schedulability
    printf("\nEarliest Deadline First (EDF) Scheduling\n");
    printf("CPU Utilization:\n%.2f\n", utilization);
    if(utilization <= 1.0)
        printf("Schedulable (Utilization <= 1)\n");
    else
        printf("NOT Schedulable (Utilization > 1)\n");

    printf("ID\tBF\tDeadline\tCT\tWT\tTAT\n");
    for(int i=0; i<n; i++) {
        p[i].completion = p[i].burst + (i==0?0:p[i-1].completion);
        p[i].tat = p[i].completion; // since arrival=0
        p[i].waiting = p[i].tat - p[i].burst;
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].id, p[i].burst, p[i].deadline,
               p[i].completion, p[i].waiting, p[i].tat);
    }

    // RMS schedulability
    double bound = n * (pow(2.0, 1.0/n) - 1.0);
    printf("\nRate Monotonic Scheduling (RMS)\n");
    printf("CPU Utilization: %.2f\n", utilization);
    printf("RM Bound: %.4f\n", bound);
    if(utilization <= bound)
        printf("Schedulable (Utilization <= RM Bound)\n");
    else
        printf("NOT Schedulable (Utilization > RM Bound)\n");

    printf("ID\tBF\tPeriod\tCT\tWT\tTAT\n");
    for(int i=0; i<n; i++) {
        p[i].completion = p[i].burst + (i==0?0:p[i-1].completion);
        p[i].tat = p[i].completion;
        p[i].waiting = p[i].tat - p[i].burst;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].burst, p[i].period,
               p[i].completion, p[i].waiting, p[i].tat);
    }

    return 0;
}
