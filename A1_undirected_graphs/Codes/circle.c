#include<stdio.h>
#include<X11/Xlib.h>
#include<GL/glut.h>

GLint radius=10;

/*void init()
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0f, 0.0f, 0.0f); //black
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (0.0, (GLdouble) wid, 0.0, (GLdouble) ht); //display area
	glFlush();
	
}
*/

void CirclePoints (int x, int y)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(1);
	glBegin (GL_POINTS);
	glVertex2i (x,y);
	glVertex2i (-x,y);
	glVertex2i (x,-y);
	glVertex2i (-x,-y);
	glVertex2i (y,x);
	glVertex2i (-y,x);
	glVertex2i (y,-x);
	glVertex2i (-y, -x);
	glEnd();
	glFlush();
}

void circles(int xcentre, int ycentre)
{
     int x=0;
     int y=radius; 
     int d=1-radius;
     int deltaE=3;
     int deltaSE=-2*radius+5;
     //Draw circle (x,y,val);
    
     glMatrixMode ( GL_MODELVIEW );
     glLoadIdentity ( );
     glTranslated(xcentre, ycentre, 0);
     
     CirclePoints (x,y);
     while(y>x)
     {
               if(d<0)
               {
                      d+=deltaE;
                      deltaE+=2;
                      deltaSE+=2;
                      }
               else
               {
                   d+=deltaSE;
                   deltaE+=2;
                   deltaSE+=4;
                   y--;
                   }
                   x++;
                   //Call Point display
                   CirclePoints (x,y);
     }
     glFlush();
}

/*void main (int argc, char **argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (wid, ht);
	glutInitWindowPosition (180,0);
	glutCreateWindow ("Take input");
	init();
	
	circle(60,60);
	glutMainLoop();
}
*/
