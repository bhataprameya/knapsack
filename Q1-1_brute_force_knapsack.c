#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void bruteforce(int items,int weight[items],int profit[items],int itemno[items],int size);

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
		printf("Could not open file\n");
		exit(1);
	}
	//Get count of items from file
	if((n = getline(&line, &lineSize, fp)) > 0)		//Reads the no iof elements from file   
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
	bruteforce(items,weight,profit,itemno,size);
	return 0;
}


//Fuction to 0/1 knapsack by bruteforce methord

void bruteforce(int items,int weight[items],int profit[items],int itemno[items],int size)
{
	int i,k,j,l,temp1[items],temp2[items],profit1=0,profit2=0,remweight1=size,remweight2,flag=-1;
	for(i = 0; i<pow(2,items);i++)
	{
		profit2=0;remweight2=size;k=0;
		for(j = 0; j < items; j++)
		{
			if(i & (1<<j))
			{
				//	printf("%d", itemno[j]);
				temp2[k]=j;k++;
			}
		}
		for(l=0;l<k;l++)
		{
			remweight2-=weight[temp2[l]];
			profit2+=profit[temp2[l]];
		}
		if(remweight2>=0 && profit2>profit1)
		{
			remweight1=remweight2;
			profit1=profit2;
			for(l=0;l<k;l++)
				temp1[l]=temp2[l];
			flag=k;
		}


		//	printf("\n");
	}
	printf("Items Selected By Bruteforce are:\n");
	for(i=0;i<flag;i++)
		printf("Item%d, Profit= %d Weight=%d\n",itemno[temp1[i]],profit[temp1[i]],weight[temp1[i]]);
	printf(" The Total Profit=%d,Total Weight= %d\n",profit1,size-remweight1);
	printf("\n");
}

