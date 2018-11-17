#include<X11/Xlib.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"circle.c"
#include"floyd_warshall.c"
#include"final_plot.c"
#include"linked_list.c"

GLint wid = 500;
GLint ht = 500;
int mouseState, mouseButton, mouseX, mouseY;
GLint circle_x, circle_y;

int vertices = 0;
int final_vertices = 0;
double *X;
double *Y;
int *adj;


/*struct node
{
	int x;
	int y;
	struct node * next;
};
*/

struct node *head = NULL;
struct node * end = NULL;

void mouse(int btn, int state, int x, int y)
{
	if(state == GLUT_DOWN)
	{
		y = ht - y; //since initially y was pixel distance from top of display window
		printf("coordinates : (%d,%d)\n", x,y);
		vertices ++; // number of veertices increase

		insert_ll (&head, &end, x,y); //record vertex coordinates in a linked list

		circles(x,y);
	}
	else mouseState = 0;
}

void keyboard(int key, int x, int y)
{
	if(key == GLUT_KEY_LEFT)
	{
		printf("Enter adjacency matix: 1 for egdes present, and -1 for edges not present\n");
		form_arrays (head, &X, &Y, vertices); //put X coordinates and Y coordinates of vertices in 2 arrays:X and Y
		final_vertices = vertices; //final number of vertices
		adj = take_input ( final_vertices); //defined in file floyd_warshall.c: take in adjacency matrix
		final_func (X,Y, adj, final_vertices); //this will do rest of the work: rearranging vertices and display the graph
	}
}

void myInit ()
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glColor3f (1.0f, 0.0f, 0.0f);
	glClear (GL_COLOR_BUFFER_BIT);
	
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (0.0, (GLdouble) wid, 0.0, (GLdouble) ht); //display area
	glFlush();
}

void main (int argc, char **argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize (wid, ht);
	glutInitWindowPosition (180,0);
	glutCreateWindow ("Graph drawing");
	myInit();
	glutMouseFunc (mouse);	
	glutSpecialFunc (keyboard);
	glutMainLoop ();
}
