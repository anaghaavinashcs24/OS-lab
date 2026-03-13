#include<stdio.h>
#include<conio.h>
int main(){
    int n;
int at[20],bt[20],ct[20],tat[20],wt[20];
int t,ti;
float tatsum=0,wtsum=0;
printf("enter number of process id");
scanf("%d",&n);
printf("enter arrival time:\n");
for(int i=0;i<n;i++){
    scanf("%d",&at[i]);
}
printf("enter burst time:");
for(int i=0;i<n;i++){
    scanf("%d",&bt[i]);
}
ct[0]=bt[0];

for(int i=1;i<n;i++){
    ct[i]=ct[i-1]+bt[i];

}
for(int i=0;i<n;i++)
{

tat[i]=ct[i]-at[i];
tatsum+=tat[i];
}
for(int i=0;i<n;i++){
    wt[i]=tat[i]-bt[i];
    wtsum+=wt[i];

}
printf("process id\tat\tbt\tct\ttat\twt\t\n");
for(int i=0;i<n;i++){
    printf("%d \t\t %d \t %d \t %d\t %d\t %d\n",i,at[i],bt[i],ct[i],tat[i],wt[i]);
}
printf("average tat=%f",tatsum/n);
printf("average waiting time:%f",wtsum/n);

}









