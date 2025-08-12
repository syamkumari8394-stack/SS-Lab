#include<stdio.h>

typedef struct
{
	int pid;
	int at;
	int bt;
	int ct;
	int wt;
	int tat;
}process;


void bubble_sort(process A[],int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(A[j].at>A[j+1].at)
			{
				process temp = A[j];
				A[j]=A[j+1];
				A[j+1]=temp;
			}
		}
	}
}

void display(process p[],int n)
{
	printf("First Come First Serve\n");
	printf("|pid\t|AT\t|BT\t|CT\t|WT\t|TAT\t|\n");
	float wt=0,tat=0;
	for(int i=0;i<n;i++)
	{
		printf("|%-7d|%-7d|%-7d|%-7d|%-7d|%-7d|\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].ct-p[i].bt,p[i].ct-p[i].at);
		wt+=p[i].ct-p[i].bt;
		tat+=p[i].ct-p[i].at;
	}
	printf("Average WT:%f\n",wt/n);
	printf("Average TAT:%f\n",tat/n);
}

void main()
{
	int n;
	printf("Enter the number of process:");
	scanf("%d",&n);
	process p[n];
	
	// Initialization
	for(int i=0;i<n;i++)
	{
		p[i].pid=i;
		printf("Enter the Arrival Time of p%d",p[i].pid);
		scanf("%d",&p[i].at);
		printf("Enter the Burst Time of p%d",p[i].pid);
		scanf("%d",&p[i].bt);
	}
	
	// Sort based on Arrival Time
	
	bubble_sort(p,n);
	
	int time=0;
	int i=0;
	printf("Gannt Chart\n");
	printf("|\tpid|\ttime|\n");
	while(i<n)
	{
		if(p[i].at<=time)
		{
			time+=p[i].bt;
			p[i].ct=time;
			printf("|p%-9d|%d->%-9d|\n",p[i].pid,time-p[i].bt,p[i].ct);
			i++;
			
		}
		else
		{
			time+=1;
		}
	}
	display(p,n);
	
	
	
	
}
