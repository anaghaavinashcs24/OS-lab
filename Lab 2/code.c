#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int pid;
    int arrival;
    int burst;
    int remaining;
    char type[10]; // "system" or "user"
} Process;

typedef struct {
    Process queue[MAX];
    int front, rear;
} Queue;

void enqueue(Queue *q, Process p) {
    if(q->rear == MAX-1) return;
    q->queue[++q->rear] = p;
    if(q->front == -1) q->front = 0;
}

Process dequeue(Queue *q) {
    Process p = q->queue[q->front++];
    if(q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return p;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process plist[n];
    for(int i=0; i<n; i++) {
        printf("Enter Process ID: ");
        scanf("%d", &plist[i].pid);
        printf("Enter Arrival Time: ");
        scanf("%d", &plist[i].arrival);
        printf("Enter Burst Time: ");
        scanf("%d", &plist[i].burst);
        printf("Enter Type (system/user): ");
        scanf("%s", plist[i].type);
        plist[i].remaining = plist[i].burst;
    }

    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(plist[i].arrival > plist[j].arrival) {
                Process temp = plist[i];
                plist[i] = plist[j];
                plist[j] = temp;
            }
        }
    }

    Queue systemQ = {.front=-1, .rear=-1};
    Queue userQ = {.front=-1, .rear=-1};

    int current_time = 0, completed = 0, i = 0;
    Process *current_process = NULL;

    while(completed < n) {
        while(i < n && plist[i].arrival <= current_time) {
            if(strcmp(plist[i].type, "system") == 0)
                enqueue(&systemQ, plist[i]);
            else
                enqueue(&userQ, plist[i]);
            i++;
        }

        if(current_process != NULL) {
            if(strcmp(current_process->type, "user") == 0 && !isEmpty(&systemQ)) {
                enqueue(&userQ, *current_process);
                current_process = NULL;
            }
        }

        if(current_process == NULL) {
            if(!isEmpty(&systemQ)) {
                Process p = dequeue(&systemQ);
                current_process = (Process*)malloc(sizeof(Process));
                *current_process = p;
            } else if(!isEmpty(&userQ)) {
                Process p = dequeue(&userQ);
                current_process = (Process*)malloc(sizeof(Process));
                *current_process = p;
            } else {
                current_time++;
                continue;
            }
        }

        current_process->remaining--;
        current_time++;


        if(current_process->remaining == 0) {
            printf("Process %d (%s) completed at time %d\n",
                   current_process->pid, current_process->type, current_time);
            completed++;
            free(current_process);
            current_process = NULL;
        }
    }

    return 0;
}

