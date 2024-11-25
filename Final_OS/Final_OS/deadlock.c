#include <stdio.h>
#include <stdbool.h>

#define MaxProcesses 10
#define MaxResources 10

int processes, resources;
int allocation[MaxProcesses][MaxResources];
int max[MaxProcesses][MaxResources];
int avaliable[MaxResources];
int need[MaxProcesses][MaxResources];

void calculateNeed(){
	for (int i = 0; i < processes; ++i)
	{
		for (int j = 0; j < resources; ++j)
		{
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
}

bool isStateSafe(){
	int work[MaxResources];
	int finish[MaxProcesses] = {false};
	int safesequence[MaxProcesses];
	int count = 0;

	for (int i = 0; i < resources; ++i)
	{
		work[i] = avaliable[i];
	}

	while(count < processes){
		bool found = false;

		for (int i = 0; i < processes; ++i)
		{
			if(!finish[i]){
				bool canAllocate = true;
				for (int j = 0; j < resources; ++j)
				{
					if(need[i][j] > work[j]){
						canAllocate = false;
						break;
					}
				}

				if(canAllocate){
					for (int k = 0; k < resources; ++k)
					{
						work[k] += allocation[i][k];
					}
					safesequence[count++] = i;
					finish[i] = true;
					found = true;
				}
			}
		}
		if(!found){
			printf("System is not in safe state \n");
			return false;
		}
	}

	printf("System is in safe sequence. \nSafe sequence is : ");
	for (int i = 0; i < processes; ++i)
	{
		
		printf("%d ", safesequence[i]);
		
	}
	printf("\n");
	return true;

}

int main(int argc, char const *argv[])
{
	printf("Enter number of processes: ");
	scanf("%d", &processes);

	printf("Enter number of resources: ");
	scanf("%d", &resources);

	printf("Enter number of allocation: ");
	for (int i = 0; i < processes; ++i)
	{
		for (int j = 0; j < resources; ++j)
		{
			scanf("%d", &allocation[i][j]);

		}
	}

	printf("Enter number of Maximum need: ");
	for (int i = 0; i < processes; ++i)
	{
		for (int j = 0; j < resources; ++j)
		{
			scanf("%d", &max[i][j]);
			
		}
	}

	printf("Enter number of avaliable resources: ");
	for (int i = 0; i < resources; ++i)
	{
		scanf("%d", &avaliable[i]);
	}

	calculateNeed();
	isStateSafe();
	

	return 0;
}