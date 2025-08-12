#include<stdio.h>

typedef struct
{
	int pid;
	int at;
	int bt;
	int ct;
	int wt;
	int tat;
	int pt;
}process;


void bubble_sort_AT(process A[],int n)
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
	printf("Priority\n");
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

int findPriority(process p[],int n,int time)
{
	int min=-1;
	for(int i=0;i<n;i++)
	{
		if(p[i].at<=time && p[i].ct==-1 )
		{
			if(min==-1 || p[min].pt>p[i].pt)
			{
				min=i;
			}
		}
	}
	return min;
	
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
		printf("Enter the Priority of p%d",p[i].pid);
		scanf("%d",&p[i].pt);
		p[i].ct=-1;
	}
	
	// Sort based on Arrival Time
	
	bubble_sort_AT(p,n);
	
	int time=0;
	int i=0;
	printf("Gannt Chart\n");
	printf("|\tpid|\ttime|\n");
	while(i<n)
	{
		int p_now=findPriority(p,n,time);
		if(p_now==-1)
		{
			time+=1;
			
		}
		else
		{
			time+=p[p_now].bt;
			p[p_now].ct=time;
			printf("|p%-9d|%d->%-9d|\n",p_now,time-p[p_now].bt,p[p_now].ct);
			i++;
		}
	}
	display(p,n);
	
	
	
	
}
