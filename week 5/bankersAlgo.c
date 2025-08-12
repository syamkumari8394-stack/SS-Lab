// Algorithm

// 1. 
// 2. 
// 3. 


// Code

#include<stdio.h>
#include<stdbool.h>

#define maxProcess 5
#define maxResources 3

int available[maxResources];
int max[maxProcess][maxResources];
int allocated[maxProcess][maxResources];
int need[maxProcess][maxResources];
int finish[maxProcess];

bool canProcessComplete(int process,int nR)
{
	for(int i=0;i<nR;i++)
	{
		if(need[process][i]>available[i])
		{
			return false; 
		}
	}
	return true;
}

void calculateNeed(int nP,int nR)
{
	for(int i=0;i<nP;i++)
	{
		for(int j=0;j<nR;j++)
		{
			need[i][j] = max[i][j]-allocated[i][j];
		}
	}
}

bool isSafe(int nP,int nR,int temp[])
{
	// Initialisation
	int k=0;
	int work[maxResources];
	bool finish[maxProcess]={false};
	int count=0;
	bool found,flag;
	
	// Copy to work
	for (int i = 0; i < nR; i++) {
        work[i] = available[i];
    	}
	
	// Check for Process
	while(count<nP)
	{
		found=false;
		for(int i=0;i<nP;i++)
		{
			if(!finish[i])
			{
				flag=true;
				for(int j=0;j<nR;j++)
				{
					if(need[i][j]>work[j])
					{
						flag=false;
						break;
					}	
				}
				
				if(flag)
				{
				  	printf("Available Resources");
                    		  	for (int k = 0; k < nR; k++){printf("-%d",work[k]);} 
					printf("\nprocess-p%d can be allocated resources\n",i); 
					temp[k++]=i;
					for (int j = 0; j <nR ; j++) {
                        			work[j] += allocated[i][j];}
                        		finish[i]=true;
                        		count++;
                        		found=true;
                        		break;	
				}
			}
		}
	if(!found)
	{
		return false;
	}
	}
	return true;	
}

void bankers(int nP,int nR)
{
	int temp[nP];
	if (isSafe(nP,nR,temp)) {
		printf("Safe state, allocating resources...\n");
		printf("\nSafe Sequence\n");
		for(int i =0;i<nP-1;i++)
		{
			printf("p%d->",temp[i]);
		}
		printf("p%d\n",temp[nP-1]);
		} 
	else {printf("Unsafe state, cannot allocate resources. Possible deadlock.\n");
    }
}

int main()
{
	// // Initialise Required Variables
	
	// int nP = 5;
	// int nR = 3;
	
	// available[0]=3;
	// available[1]=3;
	// available[2]=2;
	
	// max[0][0] = 7; max[0][1] = 5; max[0][2] = 3;
    // 	max[1][0] = 3; max[1][1] = 2; max[1][2] = 2;
    // 	max[2][0] = 9; max[2][1] = 0; max[2][2] = 2;
    // 	max[3][0] = 2; max[3][1] = 2; max[3][2] = 2;
    // 	max[4][0] = 4; max[4][1] = 3; max[4][2] = 3;
    	
    // 	allocated[0][0] = 0; allocated[0][1] = 1; allocated[0][2] = 0;
    // 	allocated[1][0] = 2; allocated[1][1] = 0; allocated[1][2] = 0;
    // 	allocated[2][0] = 3; allocated[2][1] = 0; allocated[2][2] = 2;
    // 	allocated[3][0] = 2; allocated[3][1] = 1; allocated[3][2] = 1;
    // 	allocated[4][0] = 0; allocated[4][1] = 0; allocated[4][2] = 2;
    	

	int nP, nR;

	printf("Enter number of processes (max %d): ", maxProcess);
	scanf("%d", &nP);

	printf("Enter number of resource types (max %d): ", maxResources);
	scanf("%d", &nR);

	if (nP > maxProcess || nR > maxResources)
	{
		printf("Error: Exceeded max limits.\n");
		return 1;
	}

	printf("Enter available resources (%d values):\n", nR);
	for (int i = 0; i < nR; i++)
	{
		scanf("%d", &available[i]);
	}

	printf("Enter max matrix (%d x %d):\n", nP, nR);
	for (int i = 0; i < nP; i++)
	{
		printf("Process %d: ", i);
		for (int j = 0; j < nR; j++)
		{
			scanf("%d", &max[i][j]);
		}
	}

	printf("Enter allocated matrix (%d x %d):\n", nP, nR);
	for (int i = 0; i < nP; i++)
	{
		printf("Process %d: ", i);
		for (int j = 0; j < nR; j++)
		{
			scanf("%d", &allocated[i][j]);
		}
	}

	calculateNeed(nP, nR);

	// Display Need Matrix
	printf("Need Matrix\n");
	printf("Process\t");
	for(int i=0;i<nR;i++){
		printf("%c\t",'A'+i);
	}
	printf("\n");
	for(int i=0;i<nP;i++)
	{
		printf("%d\t",i);
		for(int j=0;j<nR;j++)
		{
			printf("%d\t",need[i][j]);
		}
		printf("\n");
	}

	bankers(nP, nR);

	return 0;
}

// Output
