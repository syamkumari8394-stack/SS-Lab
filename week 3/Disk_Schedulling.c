// Algorithm

// 1. 
// 2. 
// 3. 


// Code

#include<stdio.h>
#include<stdlib.h>

void FCFS(int r[], int n, int head);
void SCAN(int r[], int n, int head, int max, int min);
void CSCAN(int r[], int n, int head, int max, int min);
void bubblesort(int p[],int n);
int locate(int r[], int n, int head);

void main()
{
    // User input
    int n, head, max, min;     
    printf("Enter the number of request:");
    scanf("%d", &n);
    printf("Enter the head position:");
    scanf("%d", &head);
    printf("Enter the max disk size:");
    scanf("%d", &max);
    printf("Enter the min disk size:");
    scanf("%d", &min);
    
    int request[n];
    
    for(int i = 0; i < n; i++)
    {
        printf("req %d:", i+1);
        scanf("%d", &request[i]);
    }
    FCFS(request, n, head);
    SCAN(request, n, head, max, min);
    CSCAN(request, n, head, max, min);
}

void bubblesort(int p[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(p[j]>p[j+1])
            {
                int temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

int locate(int r[], int n, int head)
{
    for(int i = 0; i < n; i++)
    {
        if(r[i] > head)
            return i;
    }
    return n;
}

void FCFS(int r[], int n, int head)
{
   printf("-------------------------------------------------\n");
    printf("FCFS Algorithm\n");
    printf("FCFS order\n");
    
    int head_count=0;
    int seek = 0, seektime;
    for(int i = 0; i < n; i++)
    {
        printf("%d->",head);
        seektime = abs(r[i] - head);
        head_count+=1;
        seek += seektime;
        head = r[i];
    }
    printf("%d\n",head);
    printf("FCFS Head count:%d\n",head_count);
    printf("FCFS Total seek time: %d\n",seek);
   printf("-------------------------------------------------\n");
}

void SCAN(int r[], int n, int head, int max, int min)
{
   printf("-------------------------------------------------\n");
    printf("SCAN Algorithm\n");
    printf("SCAN order\n");
    int seek = 0,head_count=0;
    bubblesort(r, n);
    
    int index = locate(r, n, head);
    
    // Moving towards max (right)
    for(int i = index; i < n; i++)
    {
        printf("%d->",head);
        seek += abs(r[i] - head);
        head_count++;
        head = r[i];
    }
    if(head != 200)
    {
        seek += abs(max - head);
        head = max;
        head_count++;

    }
    
    // Moving back towards min (left)
    for(int i = index - 1; i >= 0; i--)
    {
        printf("%d->",head);
        seek += abs(r[i] - head);
        head_count++;
        head = r[i];
    }
    
    if(head!=min)
    {
        seek+=abs(head-min);
        head=min;
        head_count++;
    }
    printf("%d\n",head);
    printf("SCAN Head count:%d\n",head_count);
    printf("SCAN Total seek time: %d\n",seek);
   printf("-------------------------------------------------\n");
}

void CSCAN(int r[], int n, int head, int max, int min)
{
   printf("-------------------------------------------------\n");
    printf("C-SCAN Algorithm\n");
    printf("C-SCAN order\n");
    int seek = 0,head_count=0;
    bubblesort(r,n);
    
    int index = locate(r, n, head);
    
    // Moving towards max (right)
    for(int i = index; i < n; i++)
    {
        printf("%d->",head);
        seek += abs(r[i] - head);
        head = r[i];
        head_count++;
    }
    if(head != 200)
    {
        seek += abs(max - head);
        head = max;
        head_count++;
        printf("%d->",200);
    }
    
    // Jump to min and continue moving right
    seek+=abs(max-min);
    head = min;
    
    for(int i = 0; i < index; i++)
    {
        printf("%d->",head);
        seek += abs(r[i] - head);
        head = r[i];
        head_count++;
    }
    printf("%d\n",head);
    printf("c-SCAN Head count:%d\n",head_count);
    printf("c-SCAN Total seek time: %d\n",seek);
   printf("-------------------------------------------------\n");
}

// Output

// Enter the number of request:5
// Enter the head position:50
// Enter the max disk size:100
// Enter the min disk size:0
// req 1:20
// req 2:60
// req 3:10
// req 4:80
// req 5:40
// FCFS Total seek time: 230
// SCAN Total seek time: 150
// C-SCAN Total seek time: 190
