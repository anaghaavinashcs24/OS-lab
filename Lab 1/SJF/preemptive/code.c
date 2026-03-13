#include<stdio.h>

int main()
{
    int n;
    int p[20],at[20],bt[20],rt[20];
    int ct[20],tat[20],wt[20],rtm[20];
    int completed=0,time=0,min,idx;
    float tatsum=0,wtsum=0,rtsum=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter Process ID:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);

    printf("Enter Arrival Time:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&at[i]);

    printf("Enter Burst Time:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&bt[i]);
        rt[i]=bt[i];       // remaining time
        rtm[i]=-1;         // response time marker
    }

    while(completed<n)
    {
        min=9999;
        idx=-1;

        for(int i=0;i<n;i++)
        {
            if(at[i]<=time && rt[i]>0 && rt[i]<min)
            {
                min=rt[i];
                idx=i;
            }
        }

        if(idx!=-1)
        {
            if(rtm[idx]==-1)
                rtm[idx]=time-at[idx];   // response time

            rt[idx]--;
            time++;

            if(rt[idx]==0)
            {
                ct[idx]=time;
                completed++;
            }
        }
        else
        {
            time++;
        }
    }

    for(int i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];

        tatsum+=tat[i];
        wtsum+=wt[i];
        rtsum+=rtm[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i=0;i<n;i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i],at[i],bt[i],ct[i],tat[i],wt[i],rtm[i]);

    printf("\nAverage TAT = %.2f",tatsum/n);
    printf("\nAverage WT = %.2f",wtsum/n);
    printf("\nAverage RT = %.2f",rtsum/n);

    return 0;
}
