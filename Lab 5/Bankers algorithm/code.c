#include <stdio.h>

int main()
{
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m];


    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);


    printf("\nEnter Maximum Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);


    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < m; i++)
        scanf("%d", &avail[i]);


    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\nNeed Matrix:\n");

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int process;
    int request[m];

    printf("\nEnter process number requesting resources: ");
    scanf("%d", &process);

    printf("Enter request for each resource:\n");

    for(int i = 0; i < m; i++)
        scanf("%d", &request[i]);

    for(int i = 0; i < m; i++)
    {
        if(request[i] > need[process][i])
        {
            printf("\nError: Process has exceeded maximum claim.\n");
            return 0;
        }
    }

    for(int i = 0; i < m; i++)
    {
        if(request[i] > avail[i])
        {
            printf("\nResources are not available. Process must wait.\n");
            return 0;
        }
    }

    for(int i = 0; i < m; i++)
    {
        avail[i] -= request[i];
        alloc[process][i] += request[i];
        need[process][i] -= request[i];
    }

    int finish[n], safeSeq[n];

    for(int i = 0; i < n; i++)
        finish[i] = 0;

    int work[m];

    for(int i = 0; i < m; i++)
        work[i] = avail[i];

    int count = 0;

    while(count < n)
    {
        int found = 0;

        for(int p = 0; p < n; p++)
        {
            if(finish[p] == 0)
            {
                int j;

                for(j = 0; j < m; j++)
                {
                    if(need[p][j] > work[j])
                        break;
                }

                if(j == m)
                {
                    for(int k = 0; k < m; k++)
                        work[k] += alloc[p][k];

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
        {
            printf("\nRequest cannot be granted.");
            printf("\nSystem will enter unsafe state.\n");
            return 0;
        }
    }

    printf("\nRequest can be granted.\n");
    printf("System is in SAFE state.\n");

    printf("Safe Sequence: ");

    for(int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);

    printf("\n");

    return 0;
}
