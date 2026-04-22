#include <stdio.h>

int main() {
    int n, i, time = 0, remain;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n], RT[n], CT[n], WT[n], TAT[n];

    for(i = 0; i < n; i++) {
        printf("Enter Arrival Time for P%d: ", i+1);
        scanf("%d", &AT[i]);
        printf("Enter Burst Time for P%d: ", i+1);
        scanf("%d", &BT[i]);
        RT[i] = BT[i];
    }

    int tq;
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    remain = n;
    int flag = 0;

    while(remain > 0) {
        flag = 0;
        for(i = 0; i < n; i++) {
            if(RT[i] > 0 && AT[i] <= time) {
                flag = 1;
                if(RT[i] <= tq) {
                    time += RT[i];
                    RT[i] = 0;
                    CT[i] = time;
                    remain--;
                } else {
                    time += tq;
                    RT[i] -= tq;
                }
            }
        }
        if(flag == 0) time++;
    }

    float totalWT = 0, totalTAT = 0;

    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, AT[i], BT[i], CT[i], WT[i], TAT[i]);
        totalWT += WT[i];
        totalTAT += TAT[i];
    }

    printf("\nAverage WT = %.2f", totalWT / n);
    printf("\nAverage TAT = %.2f\n", totalTAT / n);

    return 0;
}
