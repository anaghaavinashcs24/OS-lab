#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int burst;
    int deadline;
    int period;
    int ct, wt, tat;
};

// Utility function to calculate metrics
void calculateMetrics(struct Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct;                  // TAT = CT - AT (AT=0 assumed)
        p[i].wt = p[i].tat - p[i].burst;     // WT = TAT - BT
    }
}

// Rate Monotonic Scheduling (RMS) – priority by period
void RMS(struct Process p[], int n) {
    printf("\n--- Rate Monotonic Scheduling ---\n");
    // Sort by period (shorter period = higher priority)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].period > p[j].period) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    int time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].burst;
        p[i].ct = time;
    }
    calculateMetrics(p, n);
    for (int i = 0; i < n; i++)
        printf("P%d: CT=%d WT=%d TAT=%d\n", p[i].pid, p[i].ct, p[i].wt, p[i].tat);
}

// Earliest Deadline First (EDF) – priority by deadline
void EDF(struct Process p[], int n) {
    printf("\n--- Earliest Deadline First ---\n");
    // Sort by deadline
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].deadline > p[j].deadline) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    int time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].burst;
        p[i].ct = time;
    }
    calculateMetrics(p, n);
    for (int i = 0; i < n; i++)
        printf("P%d: CT=%d WT=%d TAT=%d\n", p[i].pid, p[i].ct, p[i].wt, p[i].tat);
}

// Proportional Scheduling – allocate CPU proportionally to burst/period ratio
void Proportional(struct Process p[], int n) {
    printf("\n--- Proportional Scheduling ---\n");
    // Sort by burst/period ratio (lower ratio = higher priority)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            double r1 = (double)p[i].burst / p[i].period;
            double r2 = (double)p[j].burst / p[j].period;
            if (r1 > r2) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    int time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].burst;
        p[i].ct = time;
    }
    calculateMetrics(p, n);
    for (int i = 0; i < n; i++)
        printf("P%d: CT=%d WT=%d TAT=%d\n", p[i].pid, p[i].ct, p[i].wt, p[i].tat);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter PID, Burst, Deadline, Period for process %d: ", i+1);
        scanf("%d %d %d %d", &p[i].pid, &p[i].burst, &p[i].deadline, &p[i].period);
    }

    RMS(p, n);
    EDF(p, n);
    Proportional(p, n);

    return 0;
}
