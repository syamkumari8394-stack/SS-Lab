// Algorithm

// 1. 
// 2. 
// 3. 


// Code
#include<stdio.h>

typedef struct
{
	int pid;
	int arrivalTime;
	int burstTime;
	int completionTime;
	int turnaroundTime;
	int waitingTime;
}Process;


void sortProcess(Process p[],int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(p[j].arrivalTime > p[j+1].arrivalTime)
			{
				Process temp =  p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}
}

void sortPID(Process p[],int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(p[j].pid > p[j+1].pid)
			{
				Process temp =  p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}
}

void calculateTATandWT(Process p[],int n)
{
	for(int i=0;i<n;i++)
	{
		p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
		p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;		
	}
}

void Display(Process p[],int n)
{
	sortPID(p,n);
	float totalWT=0;
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("|\tPID\t|\tAT\t|\tBT\t|\tCT\t|\tTAT\t|\tWT\t|\n");
	printf("-------------------------------------------------------------------------------------------------\n");
    	for (int i = 0; i < n; i++) {
        // Adjust the width for each column for better alignment
        printf("|\t%-8d|\t%-8d|\t%-8d|\t%-8d|\t%-8d|\t%-8d|\n", 
                p[i].pid, 
                p[i].arrivalTime, 
                p[i].burstTime, 
                p[i].completionTime, 
                p[i].turnaroundTime, 
                p[i].waitingTime);
        totalWT+=p[i].waitingTime;
    	}
    	printf("-------------------------------------------------------------------------------------------------\n");
    	printf("AVERAGE WAITING TIME : %f\n",(totalWT/n));
}

void main()
{
	// User Input
	
	int n;
	printf("Enter the Number of process:");
	scanf("%d",&n);
	Process p[n];
	printf("Enter the Details Of Processes\n");
	for(int i=0;i<n;i++)
	{
		printf("==================================================================================================\n");
		printf("Enter the pid:");
		scanf("%d",&p[i].pid);
		printf("Enter the arrivalTime:");
		scanf("%d",&p[i].arrivalTime);
		printf("Enter the burstTime:");		
		scanf("%d",&p[i].burstTime);
	}
	printf("==================================================================================================\n");
	
	// Sort process based on arrival Time
	
	sortProcess(p,n);
	
	// Excecution
	
	int time=0;
	int currentTime;
	for(int i=0;i<n;i++)
	{
		currentTime = p[i].arrivalTime;
		while(currentTime > time)
		{
			time+=1;
		}
		time+=p[i].burstTime;
		p[i].completionTime = time;
		
	}
	
	// Calculate TAT and WT
	
	calculateTATandWT(p,n);
	
	// Display
	
	Display(p,n);
}

// Output
