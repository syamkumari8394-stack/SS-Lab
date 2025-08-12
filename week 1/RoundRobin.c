// Algorithm

// 1. 
// 2. 
// 3. 


// Code

#include<stdio.h>


struct process
{
	int pid;
	int arrivalTime;
	int burstTime;
	int remainingTime;
	int completionTime;
	int turnaroundTime;
	int waitingTime;
};

// Implement Circular Queue

struct process queue[25];
int front = -1, rear = -1; 

void enqueue(int max_size, struct process item)
{
    if ((rear + 1) % max_size == front) {
        return;
    }
    else if (front == -1 && rear == -1) {
        // Queue is empty, set both front and rear to 0
        front = rear = 0;
    }
    else {
        rear = (rear + 1) % max_size;
    }
    queue[rear] = item;
}

struct process deque(int max_size)
{
    if (front == -1) {
        printf("Queue is empty\n");
        struct process empty_process = {0};
        return empty_process;
    }
    
    struct process temp = queue[front];
    
    if (front == rear) {
        front = rear = -1;
    }
    else {
        front = (front + 1) % max_size;
    }
    
    return temp;
}

// Check For New Arrivals

void checkNew(struct process p[],int n,int now)
{
    for(int i=0;i<n;i++){
        if(p[i].arrivalTime==now)
        {
            enqueue(n,p[i]);
        }
    }
}

void sortPID(struct process p[],int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(p[j].pid > p[j+1].pid)
			{
				struct process temp =  p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}
}

void calculateTATandWT(struct process p[],int n)
{
	for(int i=0;i<n;i++)
	{
		p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
		p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;		
	}
}

void Display(struct process p[],int n)
{
	sortPID(p,n);
	float totalWT=0;
	printf("\n|\tPID\t|\tAT\t|\tBT\t|\tCT\t|\tTAT\t|\tWT\t|\n");
    	for (int i = 0; i < n; i++) {
        // Adjust the width for each column for better alignment
        printf("|\t%-4d|\t%-4d|\t%-4d|\t%-4d|\t%-4d|\t%-4d|\n", 
                p[i].pid, 
                p[i].arrivalTime, 
                p[i].burstTime, 
                p[i].completionTime, 
                p[i].turnaroundTime, 
                p[i].waitingTime);
        totalWT+=p[i].waitingTime;
    	}
    	printf("\nAVERAGE WAITING TIME : %f\n",(totalWT/n));
}

void main()
{
    printf("Round Robin Scheduling\n\n");
    printf("Gannt Chart\n\n");
    printf("|\tTime\t|\tProcess\t|\n");
	// User Input
	int n=6,q=4;
	struct process p[]={
	    {1,0,5},
	    {2,1,6},
	    {3,2,3},
	    {4,3,1},
	    {5,4,5},
	    {6,6,4},
	};
	
	// Initialisation
	
	int current_time=0,complete=0;
	struct process completed[n];
	
	// Copy value of Burst Time to Remaining Time
	
	for(int i=0;i<n;i++)
	{
	    p[i].remainingTime=p[i].burstTime;
	}
	
	// Add Process initially
	checkNew(p,n,current_time);
	
	// Run Loop Until Everything is complete
	while(complete<n)
	{
        
	    // Deque the First one
	    struct process item=deque(n);

        // Check RoundRobin
		// Get Execution Time
		int execution_time = (item.remainingTime > q) ? q : item.remainingTime;

		// Update Current Time
		current_time += execution_time;

		for (int i =1; i <= execution_time; i++)
		{
		    // Check for New Arrivals
			checkNew(p,n,current_time-execution_time+i);
 		}
		

		// Update Remaining Time
        if(item.remainingTime>q)
        {
            item.remainingTime-=q;
            enqueue(n,item);
        }
        else if(item.remainingTime!=0)
        {
            item.remainingTime=0;
            item.completionTime=current_time;
            completed[complete++]=item;
        }
        printf("|\t%-8d|\tp%-7d|\n",current_time,item.pid);
	}
	calculateTATandWT(completed,n);
	Display(completed,n);
}
	

// Output


// Output
// Round Robin Scheduling

// Gannt Chart

// |	Time	|	Process	|
// |	4       |	p1      |
// |	8       |	p2      |
// |	11      |	p3      |
// |	12      |	p4      |
// |	16      |	p5      |
// |	17      |	p1      |
// |	21      |	p6      |
// |	23      |	p2      |
// |	24      |	p5      |

// |	PID	|	AT	|	BT	|	CT	|	TAT	|	WT	|
// |	1   |	0   |	5   |	17  |	17  |	12  |
// |	2   |	1   |	6   |	23  |	22  |	16  |
// |	3   |	2   |	3   |	11  |	9   |	6   |
// |	4   |	3   |	1   |	12  |	9   |	8   |
// |	5   |	4   |	5   |	24  |	20  |	15  |
// |	6   |	6   |	4   |	21  |	15  |	11  |

// AVERAGE WAITING TIME : 11.333333