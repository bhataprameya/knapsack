#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void greedy1(int items,int weight[items],int profit[items],int itemno[items],int size);
void greedy2(int items,int weight[items],int profit[items],int itemno[items],int size);
void greedy3(int items,int weight[items],int profit[items],int itemno[items],int size);
void greedy4(int items,int weight[items],int profit[items],int itemno[items],int size);
void swap(int*,int *);

int main(int argc, char *argv[])
{

	int items,size, i,j,k,n;
	char *elements;
	/*	if (argc != 2)
		{
		printf("Invalid no of Arguments\n");
		exit(1);
		}*/
	FILE *fp;
	char *line = NULL;
	size_t lineSize = 0;
	 if(argc!=2)
        fp=fopen("knapsack.txt","r");
        else
        fp=fopen(argv[1], "r");

	if (fp == NULL)
	{
		printf("Could not open file knapsack.txt");
		exit(1);
	}
	//Get count of items from file
	if((n = getline(&line, &lineSize, fp)) > 0) 
		items=atoi(line);
	else
	{
		printf("Coudent read from file\n");
		exit(1);
	}
	int weight[items], profit[items],itemno[items];

	//Get all Weights from File
	if((n = getline(&line, &lineSize, fp)) > 0)
	{	i=0;
		if (line[n - 1] == '\n') 
			line[n - 1] = '\0';
		elements = strtok(line, ", ");
		weight[i++]=atoi(elements);
		elements = strtok(NULL, ", ");
		while(elements != NULL && i<items)
		{
			weight[i++]=atoi(elements);
			elements = strtok(NULL, " ");


		}
	}
	else
	{
		printf("Coudent read from file\n");
		exit(1);
	}

	//Get all Profit from File
	if((n = getline(&line, &lineSize, fp)) > 0)
	{       i=0;
		if (line[n - 1] == '\n')
			line[n - 1] = '\0';
		elements = strtok(line, ", ");
		profit[i++]=atoi(elements);
		elements = strtok(NULL, ", ");
		while(elements != NULL && i<items)
		{
			profit[i++]=atoi(elements);
			elements = strtok(NULL, " ");


		}
	}
	else
	{
		printf("Coudent read from file\n");
		exit(1);
	}

	//Get size of knapsack
	if((n = getline(&line, &lineSize, fp)) > 0)
		size=atoi(line);
	else
	{
		printf("Coudent read from file\n");
		exit(1);
	}
	fclose(fp);
	for(i=0;i<items;i++)
		itemno[i]=i+1;
	greedy1(items,weight,profit,itemno,size);
	greedy2(items,weight,profit,itemno,size);
	greedy3(items,weight,profit,itemno,size);
	greedy4(items,weight,profit,itemno,size);
	return 0;
}

//Maxium benifit first calculation code
void greedy1(int items,int weight[items],int profit[items],int itemno[items],int size)
{
	int i,j;
	for (i = 0; i < items-1; i++)
		for (j = 0; j < items-i-1; j++)
			if (profit[j] < profit[j+1])		//Sorts items on maxium benifit 
			{
				swap(&profit[j], &profit[j+1]);
				swap(&weight[j], &weight[j+1]);
				swap(&itemno[j], &itemno[j+1]);

			}
	int remWeight=size,profitAmt=0;
	printf("\n\nMaximum Benifit First: The selected items are:-\n ");
	for(i=0;i<items;i++)
		if(weight[i]<=remWeight && remWeight!=0)	//Performs adding item to knapsack based on maxium benifit
		{
			printf("Item%d Profit=%d, weight=%d\n ",itemno[i],profit[i],weight[i]);
			remWeight-=weight[i];
			profitAmt+=profit[i];
		}
		else if(remWeight==0)
		{
			break;
		}

	printf(" The Total Profit= %d, Total Weight= %d\n",profitAmt,size-remWeight);

}

//Minimum weight first calculation code
void greedy2(int items,int weight[items],int profit[items],int itemno[items],int size)
{
	int i,j;
	for (i = 0; i < items-1; i++)
		for (j = 0; j < items-i-1; j++)
			if (weight[j] > weight[j+1])            //Sorts items on minimum weight
			{
				swap(&profit[j], &profit[j+1]);
				swap(&weight[j], &weight[j+1]);
				swap(&itemno[j], &itemno[j+1]);

			}
	int remWeight=size,profitAmt=0;
	printf("\n\nMinimum Weight First: The selected items are:-\n ");
	for(i=0;i<items;i++)
		if(weight[i]<=remWeight && remWeight!=0)        //Performs adding item to knapsack based on minimum weight
		{
			printf("Item%d Profit=%d, weight=%d\n ",itemno[i],profit[i],weight[i]);
			remWeight-=weight[i];
			profitAmt+=profit[i];
		}
		else if(remWeight==0)
		{
			break;
		}

	printf(" The Total Profit= %d, Total Weight= %d\n",profitAmt,size-remWeight);

}

//Maximum weight first calculation code
void greedy3(int items,int weight[items],int profit[items],int itemno[items],int size)
{
	int i,j;
	for (i = 0; i < items-1; i++)
		for (j = 0; j < items-i-1; j++)
			if (weight[j] < weight[j+1])            //Sorts items on maximum weight first
			{
				swap(&profit[j], &profit[j+1]);
				swap(&weight[j], &weight[j+1]);
				swap(&itemno[j], &itemno[j+1]);

			}
	int remWeight=size,profitAmt=0;
	printf("\n\nMaximum Weight First: The selected items are:-\n ");
	for(i=0;i<items;i++) 
		if(weight[i]<=remWeight && remWeight!=0)        //Performs adding item to knapsack based on maximum weight
		{
			printf("Item%d Profit=%d, weight=%d\n ",itemno[i],profit[i],weight[i]);
			remWeight-=weight[i];
			profitAmt+=profit[i];
		}
		else if(remWeight==0)
		{
			break;
		}

	printf(" The Total Profit= %d, Total Weight= %d\n",profitAmt,size-remWeight);

}


//Maximum benifit per unit first calculation code
void greedy4(int items,int weight[items],int profit[items],int itemno[items],int size)
{
	int i,j;
	float benefit[items];
	for(i=0;i<items;i++)
		benefit[i]=profit[i]/weight[i];
	for (i = 0; i < items-1; i++)
		for (j = 0; j < items-i-1; j++)
			if (benefit[j] < benefit[j+1])            //Sorts items on maximum benefit per unit
			{
				swap(&profit[j], &profit[j+1]);
				swap(&weight[j], &weight[j+1]);
				swap(&itemno[j], &itemno[j+1]);
				float temp=benefit[j];benefit[j]=benefit[j+1];benefit[j+1]=temp;

			}
	int remWeight=size,profitAmt=0;
	printf("\n\nMaximum Benefit per Unit: The selected items are:-\n ");
	for(i=0;i<items;i++)
		if(weight[i]<=remWeight && remWeight!=0)        //Performs adding item to knapsack based on max benefit per unit
		{
			printf("Item%d Profit=%d, weight=%d\n ",itemno[i],profit[i],weight[i]);
			remWeight-=weight[i];
			profitAmt+=profit[i];
		}
		else if(remWeight==0)
		{
			break;
		}

	printf(" The Total Profit= %d, Total Weight= %d\n",profitAmt,size-remWeight);

}

//Function to swap the elements
void swap(int *a, int *b)
{
	int temp =*a;
	*a=*b;
	*b=temp;
}

