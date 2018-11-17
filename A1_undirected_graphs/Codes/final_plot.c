#include<stdio.h>
#include<X11/Xlib.h>
#include<GL/glut.h>
#include<GL/freeglut.h>
#include"main_algo.c"
#include"line_drawing.c"

double maxim (double *arr, int v)
{
	int i;
	double max_val = 0;
	for(i=0; i<v; i++)
		if(arr[i] > max_val)
			max_val = arr[i];
	return max_val;
}

double minim (double *arr, int v)
{
	int i;
	double min_val = 100000;
	for(i=0; i<v; i++)
		if(arr[i] < min_val)
			min_val = arr[i];
	return min_val;
}

void final_func (double *X, double *Y, int *adj, int v)
{
	int i, j;
	GLint width, height;
	
	algo (X,Y,adj,v);
	
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glClear (GL_COLOR_BUFFER_BIT ); //clear the window
	
	glLoadIdentity();	
	glFlush();
	//glViewport(minim(X,v),maxim(Y,v), width, height);
	printf("final points: ");	//drawing final vertices.
	for(i=0; i<v; i++)
	{	
		printf("(%d,%d) ",(int)X[i],(int)Y[i]);
		circles((int)X[i],(int) Y[i]);
	}

	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity ( );

	for(i=0; i<v; i++) //drawing edges
	{
		for(j=i+1; j<v; j++)
			if( (*(adj+i*v+j)) != -1)
			{
				
				draw_line ((int)X[i], (int)Y[i], (int)X[j], (int)Y[j]);
			}
	}
	
	glFlush();
	

	printf("now press Ctrl+C to exit the program\n");
	return;
}
