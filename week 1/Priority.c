#include <stdio.h>


struct Process {

    int id, at, bt, ct, tat, wt, pt;
};

void main(){
	int n;
	printf("Enter number of processes: ");
	scanf("%d",&n);
	struct Process p[n];
	
	
	printf("Enter the at,bt and priority of each process:\n");
	for (int i = 0; i<n; i++) {
		p[i].id = i+1;
		scanf("%d%d%d",&p[i].at, &p[i].bt, &p[i].pt);
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <n-i-1; j++) {
			if(p[j].at > p[j+1].at || (p[j].at == p[j+1].at && p[j].pt > p[j+1].pt)){
				struct Process temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
			
		}
	}
	/*
	for (int i = 0; i < n; i++) {
		printf("%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].pt);
	}
	*/
	int current=0;
	printf("Gantt Chart\n");
	for (int i=0; i<n; i++){
		current=current+p[i].bt;
		p[i].ct=current;
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt= p[i].tat - p[i].bt;
		printf("|P%d |%d->%d\n",p[i].id,current-p[i].bt,current);		
	}
	
	float avgwt=0.0,avgtat=0.0;
	
	for (int i=0; i<n; i++){
		avgwt+=p[i].wt;
		avgtat+=p[i].tat;
		
	}	
	printf("PID\tAT\tBT\tPT\tCT\tTAT\tWT\n");	
	for (int i = 0; i < n; i++) {
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].pt,p[i].ct,p[i].tat,p[i].wt);
	}
	
	printf("Avg waiting time: %d\n",avgwt/n);
	printf("Avg turnaround time: %d\n", avgtat/n);

	
}



