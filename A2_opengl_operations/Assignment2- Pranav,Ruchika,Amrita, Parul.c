#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.1456


GLfloat WHITE[] = {1, 1, 1};
GLfloat BLACK[] = {0, 0, 0};
GLfloat RED[] = {1, 0, 0};
GLfloat GREEN[] = {0, 1, 0};
GLfloat MAGENTA[] = {1, 0, 1};
GLfloat YELLOW[] = {1, 1, 0};

int per_angle=60; //Perspective Angle
int phi=0;  
float length;
int flag=-1;
float vec,theta,theta1,magnitude;
struct point{
float x,y,z;
}camera,look,up,u,v10,n1,temp,unit_n;




GLfloat n[6][3] = {  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };                /* Normals for the 6 faces of a cube. */

GLint faces[6][4] = {  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},        /* Vertex indices for the 6 faces of a cube. */
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };

GLfloat v[8][3], v1[8][3],v2[8][3],v3[8][3],t1[8][3],b1[8][3];          /* To fill the  X,Y,Z vertexes for each plane. */

  
void initialise(void);                                                  /*function prototypes used later*/
void initialiseChair(void);
void initialiseStage();

struct point cross_product(struct point a,struct point b)
{
        struct point result;
        result.x = a.y * b.z - a.z * b.y;
        result.y = a.z * b.x - a.x * b.z;
        result.z = a.x * b.y - a.y * b.x;
        return result;
}

void drawAC(void)                                /*To draw the AC by implementing a cube and applying appropriate scaling */
{
  int i;
  int red=0, green=0, blue=0;
  initialiseStage();
  for (i = 0; i < 6; i++) 
  {
    glPushMatrix();
    glBegin(GL_QUADS);
    
    glColor3ub(224,224,224);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);

    glEnd();
    glPopMatrix();
  }
}


void drawBox(void)                               /* Function to create a Table by implementing cubes, cuboids and applying scaling*/
{
  int i;
  initialise();                                  /* To initialise the vertex coordinates */

  for (i = 0; i < 6; i++) {
      glPushMatrix();                            /* Repeated four times for each leg. The for loop runs for every face of each leg */
      glScalef(0.15,0.15,0.15);
      glBegin(GL_QUADS);                        
      glColor3ub(102,51,0);
      glNormal3fv(&n[i][0]);
      glVertex3fv(&v[faces[i][0]][0]);
      glVertex3fv(&v[faces[i][1]][0]);
      glVertex3fv(&v[faces[i][2]][0]);
      glVertex3fv(&v[faces[i][3]][0]);
      glEnd();
      glPopMatrix();
      
      glPushMatrix();                      
      glScalef(0.15,0.15,0.15);
      glBegin(GL_QUADS);
      glColor3ub(102,51,0);
      glNormal3fv(&n[i][0]);
      glVertex3fv(&v1[faces[i][0]][0]);
      glVertex3fv(&v1[faces[i][1]][0]);
      glVertex3fv(&v1[faces[i][2]][0]);
      glVertex3fv(&v1[faces[i][3]][0]);
      glEnd();
      glPopMatrix();
      
      glPushMatrix();                  
      glScalef(0.15,0.15,0.15);
      glBegin(GL_QUADS);
      glColor3ub(102,51,0);
      glNormal3fv(&n[i][0]);
      glVertex3fv(&v2[faces[i][0]][0]);
      glVertex3fv(&v2[faces[i][1]][0]);
      glVertex3fv(&v2[faces[i][2]][0]);
      glVertex3fv(&v2[faces[i][3]][0]);
      glEnd();
      glPopMatrix();
      
      glPushMatrix();                  
      glScalef(0.15,0.15,0.15);
      glBegin(GL_QUADS);
      glColor3ub(102,51,0);
      glNormal3fv(&n[i][0]); 
      glVertex3fv(&v3[faces[i][0]][0]);
      glVertex3fv(&v3[faces[i][1]][0]);
      glVertex3fv(&v3[faces[i][2]][0]);
      glVertex3fv(&v3[faces[i][3]][0]);
      glEnd();
      glPopMatrix();
      
      glPushMatrix();                                        /*Table Top by implementing a cuboid */                     
      glScalef(0.15,0.15,0.15);
      glBegin(GL_QUADS);
      glColor3f(0.6,0.4,0.14);
      glNormal3fv(&n[i][0]);
      if(i==5 || i==0 || i==4 || i==2)                       /* For giving different colours to different sets of faces of the table top*/
      glColor3f(0.52,0.37,0.26);
      glVertex3fv(&t1[faces[i][0]][0]);
      glVertex3fv(&t1[faces[i][1]][0]);
      glVertex3fv(&t1[faces[i][2]][0]);
      glVertex3fv(&t1[faces[i][3]][0]);
      glEnd();
      glPopMatrix();
    }

}

void drawChairT(void)
{

  int i;
  initialiseChair();                                         /* Initialise the coordinate values for each vertex of the chair*/

  for (i = 0; i < 6; i++) {                                  /* The four legs are implemented same as table*/
      glPushMatrix();
      glScalef(0.15,0.29,0.15);
      glBegin(GL_QUADS);
      glColor3ub(139 ,69 ,0);
      glNormal3fv(&n[i][0]);
      glVertex3fv(&v[faces[i][0]][0]);
      glVertex3fv(&v[faces[i][1]][0]);
      glVertex3fv(&v[faces[i][2]][0]);
      glVertex3fv(&v[faces[i][3]][0]);
      glEnd();
      glPopMatrix();
      
      glPushMatrix();
      glScalef(0.15,0.29,0.15);
      glBegin(GL_QUADS);
      glColor3ub(139 ,69 ,0);                               /*dark shade is 139,69,0*/
      glNormal3fv(&n[i][0]);
      glVertex3fv(&v1[faces[i][0]][0]);
      glVertex3fv(&v1[faces[i][1]][0]);
      glVertex3fv(&v1[faces[i][2]][0]);
      glVertex3fv(&v1[faces[i][3]][0]);
      glEnd();
      glPopMatrix();
      
      glPushMatrix();
      glScalef(0.15,0.29,0.15);
      glBegin(GL_QUADS);
      glColor3ub(139 ,69 ,0);
      glNormal3fv(&n[i][0]);
      glVertex3fv(&v2[faces[i][0]][0]);
      glVertex3fv(&v2[faces[i][1]][0]);
      glVertex3fv(&v2[faces[i][2]][0]);
      glVertex3fv(&v2[faces[i][3]][0]);
      glEnd();
      glPopMatrix();
      
      glPushMatrix();
      glScalef(0.15,0.29,0.15);
      glBegin(GL_QUADS);
      glColor3ub(139 ,69 ,0);
      glNormal3fv(&n[i][0]);
      glVertex3fv(&v3[faces[i][0]][0]);
      glVertex3fv(&v3[faces[i][1]][0]);
      glVertex3fv(&v3[faces[i][2]][0]);
      glVertex3fv(&v3[faces[i][3]][0]);
      glEnd();
      glPopMatrix();

      glPushMatrix();                                       /*back of chair implemented as a cuboid and scaled*/
      glScalef(0.15,0.3,0.15);
      glBegin(GL_QUADS);
      glColor3ub(178 ,34 ,34);
      glNormal3fv(&n[i][0]);
      glVertex3fv(&b1[faces[i][0]][0]);
      glVertex3fv(&b1[faces[i][1]][0]);
      glVertex3fv(&b1[faces[i][2]][0]);
      glVertex3fv(&b1[faces[i][3]][0]);
      glEnd();
      glPopMatrix();

    }
    
    glPushMatrix();                                         /*seat for the chair has been implemented as a plane*/
    glScalef(0.15,0.3,0.15);
    glBegin(GL_QUADS);
    glColor3ub(205 ,102 ,0);
    glNormal3fv(&n[i][0]);
    glVertex3f(-2,t1[3][1], t1[3][2]);
    glVertex3f(t1[2][0],t1[2][1], t1[2][2]);
    glVertex3f(t1[7][0],t1[7][1], t1[7][2]);
    glVertex3f(9,t1[6][1], t1[6][2]);
    glEnd();
    glPopMatrix();
}

void drawChair(void)                                        /*Benches for students. Same as chair except for scaling factor and colour and seat*/
{
     int i;
     initialiseChair();
     for (i = 0; i < 6; i++) {
     glPushMatrix();
     glScalef(0.15,0.14,0.15);
     glTranslatef(0.0,0.8,0.0);
     glBegin(GL_QUADS);
     glColor3ub(255 ,165 ,79);
	 if(i==4)                                                /*Different colour for the back of the bench*/
     glColor3ub(205 ,102 ,29);
     glNormal3fv(&n[i][0]);
     glVertex3fv(&v[faces[i][0]][0]);
     glVertex3fv(&v[faces[i][1]][0]);
     glVertex3fv(&v[faces[i][2]][0]);
     glVertex3fv(&v[faces[i][3]][0]);
     glEnd();
     glPopMatrix();
     
     glPushMatrix();
     glScalef(0.15,0.14,0.15);
     glTranslatef(0.0,0.8,0.0);
     glBegin(GL_QUADS);
     glColor3ub(255 ,165 ,79);
     glNormal3fv(&n[i][0]);
     if(i==4)
     glColor3ub(205 ,102 ,29);
     glVertex3fv(&v1[faces[i][0]][0]);
     glVertex3fv(&v1[faces[i][1]][0]);
     glVertex3fv(&v1[faces[i][2]][0]);
     glVertex3fv(&v1[faces[i][3]][0]);
     glEnd();
     glPopMatrix();
     
     glPushMatrix();
     glScalef(0.15,0.14,0.15);
     glTranslatef(0.0,0.8,0.0);
     glBegin(GL_QUADS);
     glColor3ub(255 ,165 ,79);
     glNormal3fv(&n[i][0]);
     if(i==4)
     glColor3ub(205 ,102 ,29);
     glVertex3fv(&v2[faces[i][0]][0]);
     glVertex3fv(&v2[faces[i][1]][0]);
     glVertex3fv(&v2[faces[i][2]][0]);
     glVertex3fv(&v2[faces[i][3]][0]);
     glEnd();
     glPopMatrix();
     
     glPushMatrix();
     glScalef(0.15,0.14,0.15);
     glTranslatef(0.0,0.8,0.0);
     glBegin(GL_QUADS);
     glColor3ub(255 ,165 ,79);
     glNormal3fv(&n[i][0]);
     if(i==4)
     glColor3ub(205 ,102 ,29);
     glVertex3fv(&v3[faces[i][0]][0]);
     glVertex3fv(&v3[faces[i][1]][0]);
     glVertex3fv(&v3[faces[i][2]][0]);
     glVertex3fv(&v3[faces[i][3]][0]);
     glEnd();
     glPopMatrix();

     glPushMatrix();
     glScalef(0.15,0.25,0.15);
     glBegin(GL_QUADS);
     glColor3ub(255 ,165 ,79);
     glNormal3fv(&n[i][0]);
     if(i==4);
     glColor3ub(205 ,102 ,29);
     glVertex3fv(&b1[faces[i][0]][0]);
     glVertex3fv(&b1[faces[i][1]][0]);
     glVertex3fv(&b1[faces[i][2]][0]);
     glVertex3fv(&b1[faces[i][3]][0]);
     glEnd();
     glPopMatrix();

    } 
    glPushMatrix();
    glScalef(0.15,0.25,0.15);
    glBegin(GL_QUADS);
    glColor3ub(255 ,165 ,79);
    glNormal3fv(&n[i][0]);
    glVertex3f(t1[3][0],t1[3][1], t1[3][2]);
    glVertex3f(t1[2][0],t1[2][1], t1[2][2]);
    glVertex3f(t1[7][0],t1[7][1], t1[7][2]);
    glVertex3f(t1[6][0],t1[6][1], t1[6][2]);
    glEnd();
    glPopMatrix();
}

void drawStage(void)                                         /* The stage is implemented using a cuboid and scaled appropriately.*/
{
    int i;
    initialiseStage();
    for (i = 0; i < 6; i++) {
        glPushMatrix();
        glBegin(GL_QUADS);
        glColor3ub(238 ,221 ,130);
        if(i==5)                                             /*A different colour is given for the front plane. */
        glColor3ub(218, 165, 32);
        glNormal3fv(&n[i][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
        glPopMatrix();
    }
}

void initialiseStage(void)                                   /* Coordinate values for the stage */
{
  
  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = 7;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = 0;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 0.5;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = -6;

}

void initialiseChair(void)                                   /*Coordinate values for the the chair and benches */
{

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;                /*v, v1,v2 and v3 are for each of the four legs */
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

  v1[0][0] = v1[1][0] = v1[2][0] = v1[3][0] = 6;
  v1[4][0] = v1[5][0] = v1[6][0] = v1[7][0] = 8;
  v1[0][1] = v1[1][1] = v1[4][1] = v1[5][1] = -1;
  v1[2][1] = v1[3][1] = v1[6][1] = v1[7][1] = 1;
  v1[0][2] = v1[3][2] = v1[4][2] = v1[7][2] = 1;
  v1[1][2] = v1[2][2] = v1[5][2] = v1[6][2] = -1;

  v2[0][0] = v2[1][0] = v2[2][0] = v2[3][0] = -1;
  v2[4][0] = v2[5][0] = v2[6][0] = v2[7][0] = 1;
  v2[0][1] = v2[1][1] = v2[4][1] = v2[5][1] = -1;
  v2[2][1] = v2[3][1] = v2[6][1] = v2[7][1] = 1;
  v2[0][2] = v2[3][2] = v2[4][2] = v2[7][2] = -6;
  v2[1][2] = v2[2][2] = v2[5][2] = v2[6][2] = -8;

  v3[0][0] = v3[1][0] = v3[2][0] = v3[3][0] = 6;
  v3[4][0] = v3[5][0] = v3[6][0] = v3[7][0] = 8;
  v3[0][1] = v3[1][1] = v3[4][1] = v3[5][1] = -1;
  v3[2][1] = v3[3][1] = v3[6][1] = v3[7][1] = 1;
  v3[0][2] = v3[3][2] = v3[4][2] = v3[7][2] = -6;
  v3[1][2] = v3[2][2] = v3[5][2] = v3[6][2] = -8;

  b1[0][1] = b1[1][1] = b1[2][1] = b1[3][1] = 1;                     /* Coordinates for back of the chair/benches */
  b1[4][1] = b1[5][1] = b1[6][1] = b1[7][1] = 3;
  b1[0][0] = b1[1][0] = b1[4][0] = b1[5][0] = 8;
  b1[2][0] = b1[3][0] = b1[6][0] = b1[7][0] = -1;
  b1[0][2] = b1[3][2] = b1[4][2] = b1[7][2] = -6;
  b1[1][2] = b1[2][2] = b1[5][2] = b1[6][2] = -8;


  t1[3][0]=t1[2][0]=-1;                                              /*Coordinates for the seat of the chair/benches */
  t1[3][1]=t1[3][2]=t1[6][2]=1;
  t1[6][1]=t1[2][1]=t1[7][1]=1;        
  t1[6][0]=t1[7][0]=8;
  t1[2][2]=t1[7][2]=-8;
}

 void drawBoard(void)                                                /* Function to draw Black Board as a plane */
{
    glPushMatrix();
    glScalef(0.15,0.17,0.15);
    glBegin(GL_QUADS);
    glColor3ub(69,139,116);
    glVertex3f(-6.0,1.0,1.0);                                        /* the coordinates have been provided directly */
    glVertex3f(-8.0,1.0,1.0);
    glVertex3f(-8.0,1.25,1.0);
    glVertex3f(-6,1.25,1.0);
    glEnd();
    glPopMatrix();
}

void drawWindow(void)                                               /* To draw the two windows */
{
    glPushMatrix();
    glScalef(0.15,0.15,0.15);
    glBegin(GL_QUADS);
    glColor3ub(238,221,130);
    glVertex3f(-6.0,1.0,1.0);
    glVertex3f(-8.0,1.0,1.0);
    glVertex3f(-8.0,1.75,1.0);
    glVertex3f(-6,1.75,1.0);
    glEnd();
    glPopMatrix();

}

void drawDoor(void)                                                 /* to draw a door as a plane */
{
     glPushMatrix();
     glScalef(0.15,0.15,0.15);
     glBegin(GL_QUADS);
     glColor3ub(139,137,112);
     glVertex3f(-6.0,1.0,1.0);
     glVertex3f(-8.0,1.0,1.0);
     glVertex3f(-8.0,1.75,1.0);
     glVertex3f(-6,1.75,1.0);
     glEnd();
     glPopMatrix();
}

void drawRails(void)                                                   /* to draw the railings of the window.*/
{
    
    glPushMatrix();
    glScalef(0.15,0.15,0.15);
    t1[7][2]=-8;
    glBegin(GL_LINE_STRIP);
    glColor3ub(255,255,255);
    glVertex3f(-7.0,1.0,1.0);
    glVertex3f(-7,1.75,1.0);
    glEnd();
    glPopMatrix();
}

void
initialise(void)
{

  /* Setup cube vertex data. */
  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -5;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = -4;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

  v1[0][0] = v1[1][0] = v1[2][0] = v1[3][0] = 6;
  v1[4][0] = v1[5][0] = v1[6][0] = v1[7][0] = 7;
  v1[0][1] = v1[1][1] = v1[4][1] = v1[5][1] = -1;
  v1[2][1] = v1[3][1] = v1[6][1] = v1[7][1] = 1;
  v1[0][2] = v1[3][2] = v1[4][2] = v1[7][2] = 1;
  v1[1][2] = v1[2][2] = v1[5][2] = v1[6][2] = -1;

  v2[0][0] = v2[1][0] = v2[2][0] = v2[3][0] = -5;
  v2[4][0] = v2[5][0] = v2[6][0] = v2[7][0] = -4;
  v2[0][1] = v2[1][1] = v2[4][1] = v2[5][1] = -1;
  v2[2][1] = v2[3][1] = v2[6][1] = v2[7][1] = 1;
  v2[0][2] = v2[3][2] = v2[4][2] = v2[7][2] = -6;
  v2[1][2] = v2[2][2] = v2[5][2] = v2[6][2] = -8;

  v3[0][0] = v3[1][0] = v3[2][0] = v3[3][0] = 6;
  v3[4][0] = v3[5][0] = v3[6][0] = v3[7][0] = 7;
  v3[0][1] = v3[1][1] = v3[4][1] = v3[5][1] = -1;
  v3[2][1] = v3[3][1] = v3[6][1] = v3[7][1] = 1;
  v3[0][2] = v3[3][2] = v3[4][2] = v3[7][2] = -6;
  v3[1][2] = v3[2][2] = v3[5][2] = v3[6][2] = -8;

  t1[0][0] = t1[1][0] = t1[2][0] = t1[3][0] = -6;
  t1[4][0] = t1[5][0] = t1[6][0] = t1[7][0] =8;
  t1[0][1] = t1[1][1] = t1[4][1] = t1[5][1] = 1;
  t1[2][1] = t1[3][1] = t1[6][1] = t1[7][1] = 1.25;
  t1[0][2] = t1[3][2] = t1[4][2] = t1[7][2] = 1;
  t1[1][2] = t1[2][2] = t1[5][2] = t1[6][2] = -8;

}
void floor_draw(void)                                                  /* draw the room */
{

										                               //right
	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	glColor3ub(252,251,227);
	glVertex3d(2,-1,-1);
	glVertex3d(2,1,-1);
    glVertex3d(2,1,5);
	glVertex3d(2,-1,5);
	glEnd();

	glBegin(GL_QUADS);                                                 //front
	glNormal3d(0, 1, 0);
	glColor3f(1.0,1.0,1.0);
	glVertex3d(-1,-1,-1);
	glVertex3d(-1,1,-1);
	glVertex3d(2,1,-1);
	glVertex3d(2,-1,-1);
	glEnd();

	glBegin(GL_QUADS);                                                 //floor
	glNormal3d(0, 1, 0);
	glColor3ub(238,205,145);
	glVertex3d(-1,-1,-1);
    glVertex3d(-1,-1,5);
	glVertex3d(2,-1,5);
	glVertex3d(2,-1,-1);
	glEnd();

	glBegin(GL_QUADS);		                                           	//left
	glNormal3d(0, 1, 0);
	glColor3ub(252,251,227);
	glVertex3d(-1,-1,-1);
	glVertex3d(-1,1,-1);
	glVertex3d(-1,1,5);
	glVertex3d(-1,-1,5);
	glEnd();

	glBegin(GL_QUADS);			                                        //top
	glColor3ub(238,205,145);
	glVertex3d(2,1,-1);
	glVertex3d(2,1,5);
	glVertex3d(-1,1,5);
	glVertex3d(-1,1,-1);
	glEnd();

	glBegin(GL_QUADS);
    glNormal3d(0, 1, 0);		                                        //back
	glColor3ub(255,153,51);
	glVertex3d(2,-1,5);
	glVertex3d(-1,-1,5);
	glVertex3d(-1,1,5);
	glVertex3d(2,1,5);
	glEnd();

}

/* Functions to call respective object creation functions and to scale or translate them. The scaling factors or translations are done by trial and error method to suit the scene*/

void Box_draw(void)
{
     glPushMatrix();
     glTranslatef(0.0, -0.5, -1.0);
     drawBox();
     glPopMatrix();
}

void Chair_draw(void)
{
     glPushMatrix();
     glTranslatef(0.0, -0.5, -1.0);
     drawChair();
     glPopMatrix();

}
void Chair_drawT(void)
{
     glPushMatrix();
     glTranslatef(0.0, -0.5, -1.0);
     drawChairT();
     glPopMatrix();
}


void AC_draw(void)
{
    glPushMatrix();
    glTranslatef(1.0, 1.5, -1.0);
    drawAC();
    glPopMatrix();
}

void Board_draw(void)
{
     glPushMatrix();
     glTranslatef(0.0, 0.5, -1.0);
     drawBoard();
     glPopMatrix();
}

void Stage_draw(void)
{
     glPushMatrix();
     glTranslatef(0.0, 0.5, -1.0);
     drawStage();
     glPopMatrix();
}

void Window_draw(void)
{
     drawWindow();
}

void Rails_draw(void)
{
     drawRails();
}

void Door_draw(void)
{
     drawDoor();
}



void myKeyboard(unsigned char press, int x, int y)
{

        vec = sqrt((look.x-camera.x)*(look.x-camera.x) + (look.z-camera.z)*(look.z-camera.z));
		n1.x = look.x-camera.x;
		n1.y = look.y-camera.y;
		n1.z = look.z-camera.z;
		magnitude = sqrt((look.x-camera.x)*(look.x-camera.x) +(look.y-camera.y)*(look.y-camera.y)+ (look.z-camera.z)*(look.z-camera.z));
		unit_n.x=n1.x/magnitude;
		unit_n.y=n1.y/magnitude;
		unit_n.z=n1.z/magnitude;
        up.x=0 ;up.y =1; up.z=0;
		u = cross_product(up, n1);
		v10 = cross_product(n1 , u);

    if (press == 'z') //Zoom in
    {
        per_angle=per_angle-2.5;
    }

    else if(press== 'x' ) //Zoom out
    {
        per_angle=per_angle+2.5;
    }

    else if(press == 'f') //Sliding in front
    {
        camera.x+=(n1.x/vec)*0.01;
        camera.y+=(n1.y/vec)*0.01;
        camera.z+=(n1.z/vec)*0.01;
    }

    else if(press == 'g') //Sliding Back
       
        {
            camera.x-=(n1.x/vec)*0.01;
			camera.y-=(n1.y/vec)*0.01;
			camera.z-=(n1.z/vec)*0.01;
        }

    else if(press == 'd') //Slide Right
        {
        camera.x=camera.x-u.x*0.01;
        look.x= look.x -u.x*0.01;
        camera.y=camera.y-u.y*0.01;
        look.y= look.y -u.y*0.01;
        camera.z=camera.z-u.z*0.01;
        look.z= look.z -u.z*0.01;
        }

    else if (press == 'a') //Slide Left
        {
        camera.x=camera.x+u.x*0.01;
        look.x= look.x +u.x*0.01;
        camera.y=camera.y+u.y*0.01;
        look.y= look.y +u.y*0.01;
        camera.z=camera.z+u.z*0.01;
        look.z= look.z +u.z*0.01;
        }

    else if (press == 'w') //Slide Up
    {

        camera.x=camera.x+v10.x*0.01;
        look.x= look.x +v10.x*0.01;
        camera.y=camera.y+v10.y*0.01;
        look.y= look.y +v10.y*0.01;
        camera.z=camera.z+v10.z*0.01;
        look.z= look.z +v10.z*0.01;
    }

    else if( press == 's') //Slide Down
    {

        camera.x=camera.x-v10.x*0.01;
        look.x= look.x -v10.x*0.01;
        camera.y=camera.y-v10.y*0.01;
        look.y= look.y -v10.y*0.01;
        camera.z=camera.z-v10.z*0.01;
        look.z= look.z -v10.z*0.01;
    }

    else if(press == 'l') //Panning Right
    {
    look.x-=camera.x;
    look.y-=camera.y;
    look.z-=camera.z;

    look.x=look.x*cos(5*PI/180) - look.z*sin(3.5*PI/180);
    look.z=look.x*sin(5*PI/180) + look.z*cos(3.5*PI/180);
    look.x+=camera.x;
    look.y+=camera.y;
    look.z+=camera.z;

    }

    else if (press == 'j') //Panning Left
    {
    look.x-=camera.x;
    look.y-=camera.y;
    look.z-=camera.z;
    look.x=look.x*cos(-5*PI/180)- look.z*sin(-3.5*PI/180);
    look.z=look.x*sin(-5*PI/180) + look.z*cos(-3.5*PI/180);
    look.x+=camera.x;
    look.y+=camera.y;
    look.z+=camera.z;
    }

    else if(press == 'k' ) //Pitch Up
    {
    double c = cos(-0.05);
	double s = sin(-0.05);
	double t = 1 - c;
	double x = unit_n.y*up.z - up.y*unit_n.z;
    double y = unit_n.x*up.z - up.x*unit_n.z;
    double z = unit_n.x*up.y - up.x*unit_n.y;
    look.z = look.z - camera.z;
	look.x = look.x - camera.x;
	look.y = look.y - camera.y;
    look.x = look.x*(t*x*x+c) + look.y*(t*x*y - s*z) + look.z*(t*x*z + s*y);
	look.y = look.x*(t*x*y + s*z) + look.y*(t*y*y + c) + look.z*(t*y*z - s*x);
	look.z = look.x*(t*x*z - s*y) + look.y*(t*y*z + s*x) + look.z*(t*z*z + c);
    look.z = look.z + camera.z;
	look.x = look.x + camera.x;
	look.y = look.y + camera.y;
}

    else if(press == 'i') //Pitch Down
    {
    double c = cos(0.05);
	double s = sin(0.05);
	double t = 1 - c;
	double x = unit_n.y*up.z - up.y*unit_n.z;
    double y = unit_n.x*up.z - up.x*unit_n.z;
    double z = unit_n.x*up.y - up.x*unit_n.y;
    look.z = look.z - camera.z;
	look.x = look.x - camera.x;
	look.y = look.y - camera.y;
    look.x = look.x*(t*x*x+c) + look.y*(t*x*y - s*z) + look.z*(t*x*z + s*y);
	look.y = look.x*(t*x*y + s*z) + look.y*(t*y*y + c) + look.z*(t*y*z - s*x);
	look.z = look.x*(t*x*z - s*y) + look.y*(t*y*z + s*x) + look.z*(t*z*z + c);
    look.z = look.z + camera.z;
	look.x = look.x + camera.x;
	look.y = look.y + camera.y;

    }

}

void display(void)
{
     glClearColor(0.0,0.0,0.0,1.0);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(per_angle,1,1,100);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     if(flag == -1) //Default Initialization 
     {
             camera.x=-0.5;camera.y=0;camera.z=3;
             look.x=0;look.y=0;look.z=0;
             flag=0;
     }

    gluLookAt(camera.x,camera.y,camera.z,
    look.x,look.y,look.z,
    0.0, 1.0, 0.0);
    glTranslatef(-0.875,0.5,-0.85);                                      /* Transformations applied to the room */
    glScalef(1.0,1.0,1.0);
    glRotatef(0,1.0,0.0,0.0);
    floor_draw();                                                        /*  Create the room.*/
    /*It has three columns and 4 rows of benches and tables*/

    glPushMatrix();                                                      /* Create the tables. Row 2.*/
    glTranslatef(-0.6,-0.75,1.25);
    glRotatef(0.0,1.0,0.0,0.0);
    glScalef(0.3,0.4,0.25);
    Box_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.45,-0.75,1.25);
    glRotatef(0.0,1.0,0.0,0.0);
    glScalef(0.3,0.4,0.25);
    Box_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,-0.75,1.25);
    glRotatef(0.0,1.0,0.0,0.0);
    glScalef(0.3,0.4,0.25);
    Box_draw();
    glPopMatrix();

    glPushMatrix();                                                        /* benches, row 2 */
    glTranslatef(-0.35,-0.75,1.0);
    glRotatef(180.0,0.0,1.0,0.0);
    glScalef(0.25,0.5,0.125);
    Chair_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.61,-0.75,1.0);
    glRotatef(180.0,0.0,1.0,0.0);
    glScalef(0.25,0.5,0.125);
    Chair_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.63,-0.75,1.0);
    glRotatef(180.0,0.0,1.0,0.0);
    glScalef(0.25,0.5,0.125);
    Chair_draw();
    glPopMatrix();

    glPushMatrix();
    glRotatef(0.0,0.0,1.0,0.0);
    glScalef(5.5,12.0,1.0);
    glTranslatef(1.148,-0.68,0.0);
    Board_draw();
    glPopMatrix();                                                       //black board

    glPushMatrix();
    glScalef(0.37,0.3,0.5);
    glTranslatef(-1.6,-3.85,0.0);
    Stage_draw();                                                        //draw stage
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.45,-0.3,0.5);
    glRotatef(0.0,1.0,0.0,0.0);
    glScalef(0.5,1.0,0.75);
    Box_draw();
    glPopMatrix();                                                       // teacher's table

    glPushMatrix();
    glScalef(0.25,0.55,0.125);
    glTranslatef(0.0,-1.0,-1.5);
    glRotatef(0.0,0.0,1.0,0.0);
    glTranslatef(-1.5,0.0,0.0);
    Chair_drawT();                                                       //teacher's chair
    glPopMatrix();

    glPushMatrix();                                                       //row 1 tables
    glTranslatef(-0.6,-0.75,2.0);
    glRotatef(0.0,1.0,0.0,0.0);
    glScalef(0.25,0.4,0.25);
    Box_draw();
    glPopMatrix();
 
    glPushMatrix();
    glTranslatef(0.45,-0.75,2.0);
    glRotatef(0.0,1.0,0.0,0.0);
    glScalef(0.25,0.4,0.25);
    Box_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,-0.75,2.0);
    glRotatef(0.0,1.0,0.0,0.0);
    glScalef(0.25,0.4,0.25);
    Box_draw();                                                         

    glPopMatrix();                                                      //row 1 benches
    glPushMatrix();
    glTranslatef(-0.4,-0.75,1.7);
    glRotatef(180.0,0.0,1.0,0.0);
    glScalef(0.25,0.5,0.125);
    Chair_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.61,-0.75,1.7);
    glRotatef(180.0,0.0,1.0,0.0);
    glScalef(0.25,0.5,0.125);
    Chair_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.63,-0.75,1.7);
    glRotatef(180.0,0.0,1.0,0.0);
    glScalef(0.25,0.5,0.125);
    Chair_draw();
    glPopMatrix();           

    glPushMatrix();                                                     //row 3 tables
    glTranslatef(-0.6,-0.75,2.7);
    glRotatef(0.0,1.0,0.0,0.0);
    glScalef(0.25,0.4,0.25);
    Box_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.45,-0.75,2.7);
    glRotatef(0.0,1.0,0.0,0.0);
    glScalef(0.25,0.4,0.25);
    Box_draw();
    
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.5,-0.75,2.7);
    glRotatef(0.0,1.0,0.0,0.0);
    glScalef(0.25,0.4,0.25);
    Box_draw();                

    glPopMatrix();                                                      // Row 3 Benches
    glPushMatrix();
    glTranslatef(-0.4,-0.75,2.5);
    glRotatef(180.0,0.0,1.0,0.0);
    glScalef(0.25,0.5,0.125);
    Chair_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.61,-0.75,2.5);
    glRotatef(180.0,0.0,1.0,0.0);
    glScalef(0.25,0.5,0.125);
    Chair_draw();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.63,-0.75,2.5);
    glRotatef(180.0,0.0,1.0,0.0);
    glScalef(0.25,0.5,0.125);
    Chair_draw();
    glPopMatrix();           
    glPopMatrix();

    glPushMatrix();                                                     // Row 4 tables
    glTranslatef(-0.6,-0.75,3.5);
    glRotatef(0.0,1.0,0.0,0.0);
    glScalef(0.25,0.4,0.25);
    Box_draw();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.45,-0.75,3.5);
    glRotatef(0.0,1.0,0.0,0.0);
    glScalef(0.25,0.4,0.25);
    Box_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,-0.75,3.5);
    glRotatef(0.0,1.0,0.0,0.0);
    glScalef(0.25,0.4,0.25);
    Box_draw();
    glPopMatrix();
    
    glPushMatrix();                                                        // Row 4 benches
    glTranslatef(-0.4,-0.75,3.3);
    glRotatef(180.0,0.0,1.0,0.0);
    glScalef(0.25,0.5,0.125);
    Chair_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.61,-0.75,3.3);
    glRotatef(180.0,0.0,1.0,0.0);
    glScalef(0.25,0.5,0.125);
    Chair_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.63,-0.75,3.3);
    glRotatef(180.0,0.0,1.0,0.0);
    glScalef(0.25,0.5,0.125);
    Chair_draw();
    glPopMatrix();  
             
    glPushMatrix();
    glTranslatef(0.4,-0.4,-1.2);
    glScalef(2.47,3.0,2.2);
    glRotatef(90.0,0.0,1.0,0.0);
    glTranslatef(-0.07,0.0,-0.7);
    Window_draw();                                                         //window1
    glPopMatrix();

    glPushMatrix();
    glScalef(2.6,3.08,2.18);
    glRotatef(90.0,0.0,1.0,0.0);
    glTranslatef(0.46,-0.135,-0.515);
    Rails_draw();                                                          //railings1
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4,-0.4,-1.2);
    glScalef(2.0,9.0,2.2);
    glRotatef(90.0,0.0,1.0,0.0);
    glTranslatef(0.3,-0.217,0.645);
    Door_draw();                                                           //door
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1,0.055,0.22);
    glTranslatef(21.65,6.5,4.5);
    glRotatef(92,0.0,0.0,1.0);
    AC_draw();
    glPopMatrix();



   glScalef(2.47,3.0,2.2);
   glRotatef(90.0,0.0,1.0,0.0);
   glTranslatef(-0.2,-0.14,-0.55);
   Window_draw();                                                          //window2
   glPopMatrix();
   
   glPushMatrix();
   glScalef(1.0,1.0,0.7);
   glRotatef(0.0,0.0,0.1,0.0);
   glTranslatef(0.0,0.0,0.07);
   Rails_draw();                                                           //railings2
   glPopMatrix();



   glutSwapBuffers();
   glFlush();


}

void init(void)
{

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  
}
int main(int argc, char **argv)
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glColor3d(1.0,1.0,1.0);
  glutInitWindowSize (800, 800);
  glutInitWindowPosition (0, 0);
  glutCreateWindow(" 3-D Classroom");
  glutKeyboardFunc(myKeyboard);
  glutDisplayFunc(display);
  glutIdleFunc(display);
  init();
  glutMainLoop();
  return 0;
}


