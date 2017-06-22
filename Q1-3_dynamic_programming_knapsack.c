#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void knapsack(int items,int weight[items],int profit[items],int itemno[items],int size);

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
	knapsack(items,weight,profit,itemno,size);
	return 0;
}


//Cacullates the dynamic Knapsack solution for 0/1 knapsack
void knapsack(int items,int weight[items],int profit[items],int itemno[items],int size)
{
	int result[items+1][size+1],i,w,k;

	for(i=0;i<=size;i++)
		result[0][i]=0;

	for(k=1;k<=items;k++)
	{
		result[k][0]=0;
		for(i=1;i<=size;i++)
		{
			if((weight[k-1]<=i)&&(result[k-1][i-weight[k-1]]+profit[k-1]>result[k-1][i]))	//Compute the table of dynamic knapsack
				result[k][i]=result[k-1][i-weight[k-1]]+profit[k-1];
			else
				result[k][i]=result[k-1][i];
		}

	}
/*	for(i=0;i<=items;i++)
		{
		for(k=0;k<=size;k++)
		printf("%d ",result[i][k]);
		printf("\n");
		}


for(k=1;k<=items;k++)
for(i=1;i<=size;i++)
{
if(weight[k-1]>i)
{
printf("B[%d, %d] =B[%d, %d]=> \n",k,i,k-1,i,result[k-1][i]);

}
else
{
printf("B[%d, %d] =max { B[%d, %d], B[%d, %d-%d]+b%d }\n",k,i,k-1,i,k-1,i,weight[k-1],k);
printf("max { %d, %d+%d }\n",result[k-1][i],result[k-1][i-weight[k-1]],profit[k-1]);
}
printf("%d\n\n ",result[k][i]);
}*/
	int totalprofit=0, totalweight=0;
	printf("\n\nThe items selected by Dynamic Programming are:\n");
	i=items,k=size;

	//Code to print the items
	while(i>0 && k>0)
	{
		if(result[i-1][k]!=result[i][k])
		{	
			totalprofit+=profit[i-1];totalweight+=weight[i-1];
			printf("Item%d, Profit= %d, Weight= %d\n",itemno[i-1],profit[i-1],weight[i-1]);
			k=k-weight[i-1];
			i--;
		}
		else i--;
	}

printf("The total Profit= %d, Total Weight=%d\n\n",totalprofit,totalweight);
}
