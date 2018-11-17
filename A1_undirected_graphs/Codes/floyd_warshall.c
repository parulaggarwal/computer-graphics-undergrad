#include<stdio.h>
#include<stdlib.h>

//mat[i][j] = *(mat + i*V + j)

int min (int a, int b)
{
	if(a<b)
		return a;
	return b;
}

int max( int a, int b)
{
	if(a>b)
		return a;
	return b;
}

void print_matrix (int *mat, int v)
{
	int i, j;
	for(i=0; i<v; i++)
	{
		for(j=0; j<v; j++)
			printf("%d  ", *(mat+i*v+j));
		printf("\n");
	}
	return;
}

int * floyd (int * adj, int v) //to get shortest distance b/w every pair of vertices
{
	int n = v,a,b,c,ans;
	int * d1, *d2;
	int i, j, k, flag=0;

	d1 = (int *)malloc(sizeof(int)*v*v);
	d2 = (int *)malloc(sizeof(int)*v*v);
	
	for(i=0; i<v; i++)
		for(j=0; j<v; j++)
			*(d1 + i*v+ j) = *(adj + i*v + j);
	
	flag=0;
	
	for(k=0; k<v; k++)
	{
		if(flag==0)
		{
			for(i=0; i<v; i++)
				for(j=0; j<v; j++)
				{
					a = *(d1 + i*v+ j);
					b = *(d1 + i*v+ k);
					c = *(d1 + k*v+ j);
					if (a == -1)
					{
						if(b==-1 || c==-1) 
							ans = -1;
						else ans = b+c;
					}
					else
					{
						if(b==-1 || c==-1)  ans = a;
						else ans = min(a, b+c);
					}
					*(d2 + i*v+ j) = ans;
						
				}
					//*(d2 + i*v+ j) = min( (*(d1 + i*v+ j)),*(d1 + i*v+ k)+*(d1 + k*v+ j)  );
		}
		else
		{
				for(i=0; i<v; i++)
				for(j=0; j<v; j++)
				{
					a = *(d2 + i*v+ j);
					b = *(d2 + i*v+ k);
					c = *(d2 + k*v+ j);
					if (a == -1) //i.e. the dist b/w i and j is infinity
					{
						if(b==-1 || c==-1) 
							ans = -1; //-1 stands for infinity
						else ans = b+c;
					}
					else
					{
						if(b==-1 || c==-1)  ans = a;
						else ans = min(a, b+c);
					}
					*(d1 + i*v+ j) = ans;
						
				}
					
		}

		flag = 1-flag;
	}

	if (flag==0)
	{
		for(i=0; i<v; i++)
			*(d1 + i*v+ i) = 0;
		free(d2);
		return d1;
	}
	else
	{
		for(i=0; i<v; i++)
			*(d2 + i*v+ i) = 0;
		free(d1);
		return d2;
	}
}

int * take_input(int v)
{
	//enter adjacency matrix
	int i, j, *mat;
	mat = (int *)malloc(sizeof(int)*v*v);
	for(i=0; i<v; i++)
		for(j=0; j<v; j++)
			scanf("%d", mat+i*v+j);
	return mat;
}

int max_element_in_matrix (int *mat, int v)
{
	int max_el=-1;
	int i, j;
	for(i=0; i<v; i++)
		for(j=0; j<v; j++)
			max_el = max(max_el, *(mat+i*v+j));
	return max_el;
}

/*int main()
{
	int v, *mat;
	
	printf("Enter no of vertices\n");
	scanf("%d", &v);
	mat = take_input(v);
	mat = floyd (mat, v);
	print_matrix(mat, v);
	return 0;
	
}
*/
