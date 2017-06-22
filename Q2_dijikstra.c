#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
void dijkstras(int count,int matrix[count][count]);
int minheap(int count, int d[count],int value[count]);

int main(int argc, char *argv[])
{

	int items,size, i,j,n;
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
		fp=fopen("matrix_input.txt","r");
	else
		fp=fopen(argv[1], "r");
	if (fp == NULL)
	{
		printf("Could not open file ");
		exit(1);
	}
	//Get count of items from file

	int count=1;
	//Get all Weights from File
	if((n = getline(&line, &lineSize, fp)) > 0)
	{	i=0;
		if (line[n - 1] == '\n') 
			line[n - 1] = '\0';
		elements = strtok(line, ", ");
		elements = strtok(NULL, ", ");
		while(elements != NULL)
		{	count++;
			elements = strtok(NULL, ", ");


		}
	}
	fclose(fp);
	int matrix [count][count];
	 if(argc!=2)
                fp=fopen("matrix_input.txt","r");
        else
                fp=fopen(argv[1], "r");

	if (fp == NULL)
	{
		printf("Could not open file");
		exit(1);
	}
	for(j=0;j<count;j++)
	{
		if((n = getline(&line, &lineSize, fp)) > 0)
		{
			i=0;
			if (line[n - 1] == '\n')
				line[n - 1] = '\0';
			elements = strtok(line, ", ");
			matrix[j][i++]=atoi(elements);
			elements = strtok(NULL, ", ");
			while(elements != NULL)
			{
				matrix[j][i++]=atoi(elements);
				elements = strtok(NULL, ", ");


			}
		}

	}
	fclose(fp);
	/*printf("count= %d\n",count);
	  for(i=0;i<count;i++)
	  {
	  for(j=0;j<count;j++)
	  printf("%d ",matrix[i][j]);
	  printf("\n");
	  }*/

	dijkstras(count,matrix);
	return 0;
}


//Fuction to 0/1 knapsack by bruteforce methord

void dijkstras(int count,int matrix[count][count])
{
	int i,j,d[count],value[count],n=count;
	for(i=0;i<count;i++)
	{
		value[i]=0;d[i]=INT_MAX;
	}
	d[0]=0;
	int min=minheap(count,d,value);
	while(min>=0)
	{
		value[min]=1;
		for(i=0;i<count;i++)
		{
			if(matrix[min][i]>=0 && d[i]>d[min]+matrix[min][i])	//Checks for adjesent nodes which satisify d[i]>d[min]+matrix[min][i]
			{
				d[i]=d[min]+matrix[min][i];
			}
		}
		min=minheap(count,d,value);
		n--;
	}
	printf("\n\nThe Shortest Path is: { ");			//Print the distance
	for (i=0;i<count;i++)
	{	if(d[i]==INT_MAX)
		printf("(s%d,%s)",i,"Unreachable");
		else
			printf("(s%d,%d)",i,d[i]);
		if(i==count-1)
			printf(" }\n\n");
		else 
			printf(", ");

	}
}

//Performers the operation of min heap
int minheap(int count, int d[count],int value[count])
{
	int min=100,index=-1,i;

	for (i=0;i< count;i++)
		if (d[i] <= min && value[i]==0 && d[i]!=1000)
		{
			min = d[i];
			index=i;
		}
	return index;
}

