#include<stdio.h>
#include<stdlib.h>


struct node
{
	double x;
	double y;
	struct node * next;
};


struct node * create_node (double x, double y)
{
	struct node * temp = (struct node *)malloc(sizeof(struct node));
	temp->x = x;
	temp->y = y;
	temp->next = NULL;
	return temp;
}

void insert_ll (struct node ** head, struct node ** end, double x, double y)
{
	struct node * temp = create_node (x, y);
	if ((*end)==NULL)
	{
		(*head) =(*end) = temp;
	}
	else
	{
		(*end) = (*end)->next = temp;
	}

	return;
}

void form_arrays (struct node * start, double **X_return, double **Y_return, int v)
{
	int i;
	double *X, *Y;
	struct node * temp;
	X = (double *)malloc(sizeof(double)*v);
	Y = (double *)malloc(sizeof(double)*v);
	for(i=0; i<v; i++)
	{
		X[i] = start->x;
		Y[i] = start->y;
		temp=start->next;
		free(start);
		start=temp;
	}
	(*X_return) = X;
	(*Y_return) = Y;
}

void print_ll (struct node * start)
{
	printf("linked LIst : \t");
	while(start!=NULL)
	{
		printf("(%lf, %lf)\t", start->x, start->y);
		start=start->next;
	}
	printf("done\n\n");
}

