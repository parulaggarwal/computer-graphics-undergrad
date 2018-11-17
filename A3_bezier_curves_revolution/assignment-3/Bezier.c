#include <GL/glut.h>
#include <stdlib.h>
#include<stdio.h>
#include <math.h>

int  N=0,i=0;

GLfloat ht=700;
GLfloat wd=700;
int mouseState, mouseButton, mouseX,mouseY,xold[10],yold[10],xnew,ynew,flag,xlast,ylast;
void setPixel(GLfloat x,GLfloat y);


struct points{						//To store the control points
       GLfloat x;
       GLfloat y;
       };
       typedef struct points point;
       
point p[10]; 


void setPixelC(GLfloat x,GLfloat y)
{
glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(5);
  glBegin(GL_POINTS);
     glVertex2f(x,y);
  glEnd();
  glFlush();
  	//circles(x,y);//
  
}

  void initialize(GLint x, GLint y)
  {    
 
       p[i].x= (GLfloat)x;
       p[i].y=(GLfloat)y;
       i++;
      
}    
       
 void setPixel(GLfloat x,GLfloat y)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(1);
        glBegin(GL_POINTS);
        glVertex2f(x,y);
        glEnd();
}

void update()						// To get the updated value of the control point
{
	int i,mind=100000,mink,dx,dy,d,k;
	for(i=0;i<N;i++)
	{
		dx=(int)p[i].x-xlast;
		dy=(int)p[i].y-ylast;
		d=dx*dx + dy*dy;
		k=i;
		printf("d=%d for point %d\n",d,k);
		if(d<mind)
		{
		 mind=d;
		 mink=k;
		} 
		
	}
		p[mink].x=(GLfloat)xnew;
		p[mink].y=(GLfloat)ynew;
		

	printf("updated %d point to %d,%d\n",mink,xnew,ynew);
	
}			
      
point getCasteljauPoint(int r, int k, double t);

void drawCasteljau()  //array of pts in struct form to be accepted by the user
{
                      
              point tmp;
              double t=0;
              for ( t = 0; t <= 1; t += 0.001)
              { 
              	  tmp = getCasteljauPoint(N-1, 0, t);   // no. of control points
              	  printf("x=%f,y=%f\n",tmp.x,tmp.y);
              	  setPixel(tmp.x, tmp.y);
              }
              glFlush();
  }

point getCasteljauPoint(int r, int k, double t)
{ 
	  if(r == 0) 
        {
            // setPixel(p[k].x,p[k].y);
             return p[k];
             }
        point p1 = getCasteljauPoint(r - 1, k, t);
        point p2 = getCasteljauPoint(r - 1, k + 1, t);
        point p3;
        p3.x=((1-t)*p1.x + t*p2.x);
        p3.y=((1-t)*p1.y + t*p2.y);
        return p3;
    }

void init(void)
{
        glClearColor (1.0, 1.0, 1.0, 1.0);
	glColor3f (1.0f, 0.0f, 0.0f);
	glClear (GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(0.0,(GLdouble)wd,0.0,(GLdouble)ht);
}

void Mouse(int btn, int state, int x, int y)
{
     if(state==GLUT_DOWN)
     {
                         N++;
                         mouseState=state;
                         mouseButton=btn;
                         printf("accepted x=%d,y=%d\n",x,(int)ht-y);
                         xold[N]=x;
                         yold[N]=ht-y;
                         xlast=x;
                         ylast=ht-y;
                         setPixelC(x,ht-y);
                         }
       else
       {
           mouseState=0;
           }
           glutPostRedisplay();
}               

void keyboard(int key, int x, int y)
{
	if(key == GLUT_KEY_LEFT)
	{
		
		int i;
		if(flag==0) {
		for(i=1;i<=N;i++)
		{
			initialize(xold[i],yold[i]);
 		}	                        
		drawCasteljau(); 
		}
		else
		{
		glClear(GL_COLOR_BUFFER_BIT); 
		N--;
		printf("OLD: %d,%d\n",xlast,ylast);
		 
		update();
		for(i=0;i<N;i++)
		{
			setPixelC(p[i].x,p[i].y);
 		}
		drawCasteljau();
		}
	}
}

void motion(int x, int y)
{
	flag=0;
	if (mouseState == GLUT_DOWN){
	if (mouseButton == GLUT_LEFT_BUTTON){
		xnew=x;
		ynew=ht-y;
		printf("%d,%d\n",xnew,ynew);
		flag=1;
		
	}
	setPixelC(xnew,ynew);
        }
	
	
	
	glutPostRedisplay();
	
}



int main (int argc, char** argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (0, 0);
    glutInitWindowSize (wd, ht);
    glutCreateWindow ("Bezier Curve");
    init ();
    glFlush();
    glutMouseFunc(Mouse);
    glutSpecialFunc (keyboard);
    glutMotionFunc(motion);
    glutMainLoop ();
   
}
