#include <GL/glut.h>
#include <stdlib.h>
#include<stdio.h>
#include <math.h>
#include <iosfwd>
#include<fstream>

//#include "surface_help.c"

const double pi=3.14158265;

struct surfaces
{
double xpts[11];
double ypts[11];
double xsurface[11][36];	//assumption: rotated bout y-axis by 10 degrees 
double zsurface[11][36];
}sr;

//struct surface s2;
void initSurfaces()
{
int i;
std::fstream infile("POINTS.txt",std::ios::in);
  for( i = 0; i < 11; i++)
        {
        infile >> sr.xpts[i];
        infile >> sr.ypts[i];
        }

}
void rotate_points()			// determines the x and z values for the points being rotated
    {
    double degree;
    double change = (10 * pi / 180);
    for(int i = 0; i < 11; i++)
        {
        degree = 0;
        for(int j = 0; j < 36; j++)
            {
            	if(j==0)
            	{
            		sr.xsurface[i][j]= sr.xpts[i];
            		sr.zsurface[i][j]=0;
            	}
            	else if(j==9)
            	{
            		sr.xsurface[i][j]=0;
            		sr.zsurface[i][j]=sr.xpts[i];
            	}
            	else if(j==18)
            	{
            		sr.xsurface[i][j]=-sr.xpts[i];
            		sr.zsurface[i][j]=0;
            	}
            	else if(j==27)
            	{
            		sr.xsurface[i][j]=0;
            		sr.zsurface[i][j]=-sr.xpts[i];
            	}
            	else				
         	{
                	sr.xsurface[i][j] = sr.xpts[i] * cos(degree);
                	sr.zsurface[i][j] = sr.xpts[i]* sin(degree);
               	        
                }
                degree += change;
            }
        }
    }
   
void surface_points()					//plotting the points
    {
    glBegin(GL_POINTS);
    for(int i = 0; i < 11; i++)
        {
        for(int j = 0; j < 36; j ++)
            {
            glVertex3d(sr.xsurface[i][j],sr.ypts[i],sr.zsurface[i][j]);
            }
        }
    glEnd();
    }
   
   void file_write()			// making the OFF file
   {
    std::fstream file("off1.txt",std::ios::out);
    file<<"OFF"<<"\n";
    file<<"396"<<" "<<"360"<<" "<<"756"<<"\n";
    int i,j;
    for( i = 0; i < 11; i++)
       {
        for(j = 0; j < 36; j ++)
           {
           file<<sr.xsurface[i][j]<<" "<<sr.ypts[i]<<" "<<sr.zsurface[i][j]<<"\n ";	//vertex write
           }
        }
        int f;
        i=0,j=0;
 for( i=0;i<10;i++)
   {
   for(j=0;j<36;j++)
    {
    if(j==35)
     {
       int lef_bot=(i*36)+j;
       int bot_rig=i*36;
       int top_rig=(i+1)*36;
       int top_left=top_rig+j;
    file<<"4"<<" "<<lef_bot<<" "<<bot_rig<<" "<<top_rig<<" "<<top_left<<"\n";
     } 
     else
     { int lef_bot=(i*36)+j;
       int bot_rig=lef_bot+1;
       int top_rig=(i+1)*36+j+1;
       int top_left=top_rig-1;
     file<<"4"<<" "<<lef_bot<<" "<<bot_rig<<" "<<top_rig<<" "<<top_left<<"\n";
     }  
    }
   }    
   
   file.close();
}
void connect_points()				//drawing the mesh structure
{
   
    glBegin(GL_LINE_STRIP);
     
    for(int i = 0; i < 11; i++)
       {
        for(int j = 0; j < 36; j ++)
           {
      
            if(j == 35 && i==10)
               {
              glColor3f(1,0,0);
                glVertex3d(sr.xsurface[10][35],
                            sr.ypts[10],
                            sr.zsurface[10][35]);
               
                glVertex3d(sr.xsurface[10][0],
                            sr.ypts[10],
                            sr.zsurface[10][0]);
          }
           else if(j==35 && i!=10)
           {
           glColor3f(1,0,0);
                glVertex3d(sr.xsurface[i][j],
                            sr.ypts[i],
                            sr.zsurface[i][j]);

                
                glVertex3d(sr.xsurface[i][0],
                            sr.ypts[i],
                            sr.zsurface[i][0]);

               glColor3f(0,1,0);
                glVertex3d(sr.xsurface[i+1][0],
                            sr.ypts[i+1],
                           sr.zsurface[i+1][0]);

           }
           else if(i==10 && j!=35)
           {
           glVertex3d(sr.xsurface[i][j],
                            sr.ypts[i],
                            sr.zsurface[i][j]);

                
                glVertex3d(sr.xsurface[i][j+1],
                            sr.ypts[i],
                            sr.zsurface[i][j+1]);

           }
           if(j!=35 && i!=10)
             {
           glColor3f(1,0,0);
                glVertex3d(sr.xsurface[i][j],
                            sr.ypts[i],
                            sr.zsurface[i][j]);

                glVertex3d(sr.xsurface[i][j+1],
                            sr.ypts[i ],
                            sr.zsurface[i ][j+1]);

                 glColor3f(0,1,0);
                glVertex3d(sr.xsurface[i + 1][j + 1],
                           sr.ypts[i + 1],
                             sr.zsurface[i + 1][j + 1]);
               }
           }
        }

    glEnd();
    
}
    
			
void myDisplay(void)
    {
    glClear(GL_COLOR_BUFFER_BIT);
    initSurfaces();
    rotate_points();
    surface_points();
    connect_points();
    file_write();
    glFlush();
    }

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-500.0, 500.0, -500.0, 500.0, 0,1000.0);
    gluLookAt(0.0, 0.0, 500.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glRotated(15, 1, 1, 0);

}


int main (int argc, char** argv) 
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (0, 0);
    glutInitWindowSize (1000, 1000);
    glutCreateWindow ("SURFACE OF REVOLUTION");
    glutDisplayFunc(myDisplay);
    init();
    glutMainLoop ();
   
}
