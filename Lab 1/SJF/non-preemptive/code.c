#include<stdio.h>

int main()
{
    int p[20],at[20],bt[20],ct[20],tat[20],wt[20];
    int n,completed=0,time=0,min,idx;
    int visited[20]={0};
    float tatsum=0,wtsum=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter Process IDs:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);

    printf("Enter Arrival Time:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&at[i]);

    printf("Enter Burst Time:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&bt[i]);

    while(completed<n)
    {
        min=9999;
        idx=-1;

        for(int i=0;i<n;i++)
        {
            if(at[i]<=time && visited[i]==0 && bt[i]<min)
            {
                min=bt[i];
                idx=i;
            }
        }

        if(idx!=-1)
        {
            time += bt[idx];
            ct[idx]=time;
            visited[idx]=1;
            completed++;
        }
        else
        {
            time++;
        }
    }

    for(int i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        tatsum+=tat[i];

        wt[i]=tat[i]-bt[i];
        wtsum+=wt[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i],at[i],bt[i],ct[i],tat[i],wt[i]);

    printf("\nAverage TAT = %.2f",tatsum/n);
    printf("\nAverage WT = %.2f",wtsum/n);

    return 0;
}
