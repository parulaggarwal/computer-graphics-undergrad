

void setPixel(GLint x,GLint y)
{
  glBegin(GL_POINTS);
     glVertex2i(x,y);
  glEnd();
}

void initialize_attr (int *x0, int *y0, int *x1, int *y1) //to ensure x0<x1
{
	int temp;
	if((*x0) > (*x1))
	{
		temp = (*x0);
		(*x0) = (*x1);
		(*x1) = temp;

		temp = (*y0);
		(*y0) = (*y1);
		(*y1) = temp;
	}
	return;
}
void draw_stline(int x, int y0, int y1)
{
     int y= y0;
     //glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(1,0,0);
     setPixel(x,y);
     while(y<=y1)
     {
                 y++;
                 setPixel(x,y);
                  glFlush();
     }
} 

void draw_line(int x0, int y0, int x1, int y1)
{
     int flag=0;     // to check for negative slope
     int m=0;
     // initialising the coordinates
     initialize_attr (&x0, &y0, &x1, &y1); //to ensure x0 < x1
   
     // slope calculation
     int dx=abs(x1-x0);
     //printf("dx is %d",dx);
     int dy=abs(y1-y0);
     //printf("dy is %d",dy);
     if(dx==0)
     {
      draw_stline( x0,  y0,  y1);
      return;
     } 
     double slope= dy/dx;
     //printf("slope is %lf",slope);
     if(slope>=1)  //if |m|>1 exchange dy and dx
     {
                int temp=dx;
                dx=dy;
                dy=temp;
                m=1;
     }
     //printf("m is %d\n new dx is %d new dy is %d/n",m,dx,dy);
     if(y1<y0)      // to check for negative slope *assumption: the starting point always has lesser x coordinate*
      flag=-1;
                 
     int d=2*dy-dx;
     int incrE=2*dy;
     int incrNE=2*(dy-dx);
     if(flag==-1)
     dx=dx*(-1);   
     int x=x0;
     int y=y0;
     if(m==0)
     {
       //       glClear(GL_COLOR_BUFFER_BIT);
              glColor3f( 0 ,0, 0);  
              setPixel(x, y);
              while(x<x1)
              {
                if(d<=0)
                {
                    d+=incrE;
                }
                else
                {
                    d+=incrNE;
                    if(flag==-1)
                    y--;
                    else
                    y++;
                }
                x++;
                setPixel(x,y);
              }
              glFlush();
     }
     else if(m==1)
     {
            glColor3f( 0 ,0, 0);  
            setPixel(x, y);
     
            if(flag!=-1)
            {
                 
                 while(y<y1)
                 {
                  if(d<=0)
                  {
                        d+=incrE;
                        
                  }
                  else
                  {
                        d+=incrNE;
                   
                        x++;
                  }
                 
                 y++;
                 setPixel(x,y);
                }
            }
            else if(flag==-1)
            {
                 while(y1<y)
                 {
                  if(d<=0)
                  {
                        d+=incrE;
                        
                  }
                  else
                  {
                        d+=incrNE;
                   
                        x++;
                   }
                 
                   y--;
                   setPixel(x,y);
                 }
            }
            glFlush();
     }
    // getch();
}



     
/*int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(700,700);
    glutCreateWindow("Bresenham Line");
    init();
    //check slope;
   // glutDisplayFunc( slopecheck );
    draw_line(161,497,156,182);
    glutMainLoop();
   
    return 0;
}*/
   
                        
                        
 
