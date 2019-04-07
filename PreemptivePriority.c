#include<stdio.h>

main()

{

int n;

printf("Enter the no. of processes: ");

scanf("%d",&n);

int id[n],bt[n],at[n],wt[n],tat[n],p[n],i,j,temp;

for(i=0;i<n;i++)

{

printf("Enter process %d id: ",i+1);

scanf("%d",&id[i]);

printf("Enter process %d arrival time:",i+1);

scanf("%d",&at[i]);

printf("Enter process %d burst time: ",i+1);

scanf("%d",&bt[i]);

printf("Enter process %d priority: ",i+1);

scanf("%d",&p[i]);

}

for(i=0;i<n;i++)

{

for(j=i+1;j<n;j++)

{

if(p[i]>p[j])

{

temp=p[i];

p[i]=p[j];

p[j]=temp;

temp=at[i];

at[i]=at[j];

at[j]=temp;

temp=bt[i];

bt[i]=bt[j];

bt[j]=temp;

temp=id[i];

id[i]=id[j];

id[j]=temp;


}

}

wt[i]=0;

}

for(i=0;i<n;i++)

{

for(j=0;j<i;j++)

{

wt[i]=wt[i]+bt[j];

}

tat[i]=wt[i]+bt[i];

}

float avwt=0,avtat=0;

printf("Process\tP\tBT\tWT\tTAT\n");

for(i=0;i<n;i++)

{

printf("%d\t%d\t%d\t%d\t%d\n",id[i],p[i],bt[i],wt[i],tat[i]);

avwt=avwt+wt[i];

avtat=avtat+tat[i];

}

avwt=avwt/n;

avtat=avtat/n;

printf("Average Waiting Time: %f\n",avwt);

printf("\nAverage Turnaround Time: %f",avtat);

}

