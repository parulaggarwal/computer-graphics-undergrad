#include<stdio.h>
#include<stdlib.h>

#define K 1
const double error = 0.000001;
int L=100;

/*
Terminology:

a : dE2/dxm2
b : dE2/dxm dym
c : dE/dxm
d : dE2/dym dxm
e : dE2/dym2
f : dE/dym
*/


double calculate_denominator (double *X, double *Y, int v, int m, int i)
{
	double den=0;
	den = pow ((pow (X[m]-X[i], 2) + pow(Y[m]-Y[i], 2) ), 0.5);
	return den;
}

struct ans
{
	double a,b,c,d,e,f;
};



struct ans * calculate (int *l, double *k, double *X, double *Y, int v, int m) //calculate all a,b,c,d,e,f
{
	double d1, d2, d3, d4;
	double  kmi=0, lmi=0;
	struct ans* tp= (struct ans *)malloc(sizeof(struct ans));	 
	int  i;

	tp->a=0; tp->b=0; tp->c=0; tp->d=0; tp-> e=0; tp->f=0;
	
	for(i=0; i<v; i++)
	{
		if(i!=m)
		{
			d1 = calculate_denominator(X,Y,v,m,i);
			d2 = pow(d1, 3);
			d3 = X[m]-X[i];
			d4 = Y[m]-Y[i];
			
			kmi = *(k+m*v+i);
			lmi = *(l+m*v+i);
			
			(tp->a) += kmi*(1- lmi*pow(d4,2)/d2);
			(tp->b) += kmi*(lmi * d3* d4 / d2 );
			(tp->c) += kmi*d3 * (1 - lmi/d1);
			(tp->d) += kmi * lmi* d3* d4 /d2;
			(tp->e) += kmi * (1- lmi*pow(d3,2)/d2 );
			(tp->f) += kmi* d4 * (1 - lmi/d1 );
		}
	}

	return tp;	
}


void compute_l_and_k_matrices (int * dij, int v, int **ll, double **kk)
{
	int i, j, *l;
	double temp, *k;
	(l) = (int *)malloc(sizeof(int)*v*v);
	(k) = (double*)malloc(sizeof(double)*v*v);

	for(i=0; i<v; i++)
		for(j=0; j<v; j++)
		{	
			
			temp = *(dij+i*v+j);
			if(i!=j)
				*(k + i*v + j) = K / pow(temp,2);
			else *(k + i*v + j) = -1;
			*(l+i*v+j) = L * temp;
		}
	*ll = l;
	*kk = k;
	return;
}

void print_array (double *arr, int v)
{
	int i;
	for(i=0;i <v; i++)
		printf("%f ", arr[i]);
	printf("\n");
}

double calculate_delta_m (double *X, double *Y, int *l, double *k, int v, int m)
{
	double d1, d3, d4;
	double  kmi=0, c=0, f=0, answer=0;
	int lmi=0;
	int  i;

	for(i=0; i<v; i++)
	{
		if(i!=m)
		{
			d1 = calculate_denominator(X,Y,v,m,i);
			d3 = X[m]-X[i];
			d4 = Y[m]-Y[i];
			
			kmi = *(k+m*v+i);
			lmi = *(l+m*v+i);
			
			c += kmi*d3 * (1 - lmi/d1);
			f += kmi* d4 * (1 - lmi/d1 );

		}
	}
	
	answer = c*c + f*f;
	answer = sqrt(answer);

	return answer;	
}

void compute_delta_m_array (double *X, double *Y, int *l, double *k, int v, double *delta_m)
{
	int i;

	for(i=0; i<v; i++)
		delta_m[i] = calculate_delta_m (X,Y, l, k, v, i);
	
	return ;		
}

int maximum_in_array (double *arr, int v)
{
	//Returns index of maximum element in arr of v non-negative elements
	double maximum=0;
	int i, index=0;
	
	for(i=0; i<v; i++)
		if(arr[i] >= maximum)
		{
			index = i;
			maximum = arr[i];
		}
	return index;
}

double energy (double*X, double *Y, int *l, double *k, int v) // returns energy of the system
{
	int i, j;
	double sum=0, temp1, temp, temp_y, l_val;
	for(i=0; i<v-1; i++)
	{
		for(j=i+1; j<v; j++)
		{
			temp1 = X[i] - X[j];
			temp1 = temp1*temp1;
			l_val = (*(l+i*v+j));
			temp_y =  (Y[i]-Y[j])*(Y[i]-Y[j]) ;
			temp = temp1 + temp_y + l_val * l_val - 2.0*l_val * pow(temp1+ temp_y,0.5);
			temp = temp * (*(k+i*v+j)) * 0.5;
			sum = sum + temp;
		}
	}
	return sum;
}

void algo (double *X, double *Y, int *adj, int v)
{
	int *d = floyd (adj, v); //get shortest distances b/w every pair of vertices
	int st,end=0;

	int *l;
        double *k;
	double * delta_m_array = (double*) malloc(sizeof(double)*v);
	struct ans * temp;
	int m, max_index;
	double delta_x, delta_y, denominator;
	double previous=0, new_value=1, difference=1;
	printf("K = %d\t Error = %lf\n", K, error);
	compute_l_and_k_matrices (d, v, &l, &k);
	printf("\n\ninitial energy if the system: %f\n", energy(X,Y,l,k,v));
	
	compute_delta_m_array (X,Y,l, k, v, delta_m_array);
	
	max_index = maximum_in_array (delta_m_array, v);
	printf("initial max error array\t");
	print_array(delta_m_array, v);
	
	m=max_index;
	 int count =0;
	int itr=10;

	while ( delta_m_array [max_index] > error )
	{

		difference = 2;
		while (delta_m_array[m] > error) 
		{	temp = calculate (l, k, X, Y, v, m);

			denominator = temp->a * temp->e - temp->b * temp->d;
			delta_x = (-(temp->e*temp->c)+(temp->b*temp->f)) / denominator;
			delta_y = ((temp->d*temp->c)-(temp->a*temp->f)) / denominator;
			free(temp);
			(*(X+m)) += delta_x ; 
			(*(Y+m)) += delta_y ; 


			previous = delta_m_array[m];

			delta_m_array[m]=calculate_delta_m (X,Y,l, k, v, m);
			new_value = delta_m_array[m];	
			difference = new_value - previous;

			
		}
		compute_delta_m_array (X,Y,l, k, v, delta_m_array);
		max_index=maximum_in_array(delta_m_array,v);
		m=max_index;
}
	printf("final max error array\t");
	print_array(delta_m_array, v);
	printf("\n\nfinal energy of the system: %f\n", energy(X,Y,l,k,v));
}






