#include<stdio.h>
//#include<time.h>
#include<GL/glut.h>
#include<X11/Xlib.h>

#include<math.h>
#include"dart_board.c"
#include"dart.c"
#include"text_display.c"

#define G -9.8
#define PI 3.1456

float r = 453.0;
float h = 38.1;
float d =1000.0; //If you change this, also change DISTANCE in projectile_calculations.c and dart_board.c

GLfloat start_time=0.0; //time when user presses enter: i.e., start the animation
GLdouble width = 3000.0;
GLdouble height = 3000.0;
int score=0;

/*
below variables are used in animation
*/
float theta=90.0;
float phi=0.0;
float max_time=0.0;
float time=0.0;
float vel_initial_y;//For storing the initial velocity in y component:only this component will change
float vel;

float translation_x=0.0,translation_y=0.0,rotate_x=0.0,rotate_y=0.0;
float delay=5.0; //after how may milliseconds the picture should be redisplayed

struct point
{
	float x,y,z;
};

struct state
{
	struct point location;
	struct point velocity;
	float angle;
};
struct state dart;
struct point board = {0,0, 0};
struct point initial_dart = {0,0,0};
struct point initial;
int flag = 0;

void new_game_initialize ()
{
	phi =  0.0;
	theta= 0.0;
	dart.location.x = dart.location.y = dart.location.z = 0.0; //place dart at origin
	initial_dart.x = initial_dart.y = initial_dart.z=0.0;
	vel = 0;
	time = max_time = 0.0;
	initial.x = initial.y = initial.z=0;
	dart.angle=0.0;
	board.z=d;
	
	if(flag == 1)
	{
		board.x = (float)(rand()%300 -150);
		board.y = (float)(rand()%300 -150);
		//printf("board.x=%f, board.y=%f\n", board.x, board.y);
	}
	
}

void scores()
{
	//float r_square = dart.location.x*(dart.location.x) /* (dart_x-0)^2 */ + (dart.location.y)*(dart.location.y);
	float r_square= (dart.location.x - board.x )*(dart.location.x - board.x ) + (dart.location.y - board.y )*(dart.location.y - board.y );
	float r = sqrt(r_square);	
	//printf("for score: r = %f\n\n", r);
	flag=1;
	if(dart.location.z != d)
	{
		flag=0;
		score = score+0;
	}

	else if(r <= 12.7)
		score =score + 7;
	else if (r<=31.8)
		score = score + 6;
	else if (r<=204.0)
		score= score + 5;
	else if (r<=214.0)
		score = score+ 4;
	else if (r<=330.0)
		score = score+3;
	else if (r<=340.0)
		score = score+2;
	else if(r <=453.0)
		score = score+ 1;
	else flag=0;

	//printf("Score=%d\n", score);	
	glutPostRedisplay();
}

void final () //when dart has just reached the dart board
{
	/*if((dart.location.y > (r+5) ) || (dart.location.x > (r+5)))
	{
		printf("final position of dart:(%f,%f,%f)\n", dart.location.x, dart.location.y, dart.location.z);
		glutPostRedisplay();
		scores(); //display the scores
		return;
	}
	*/

	dart.location.z = d; //d:DISTANCE of dart board from origin(i.e., initial dart position).
	time = max_time;
	dart.location.x= initial.x + dart.velocity.x*time;
    	dart.location.y= initial.y + vel_initial_y*time + 0.5*G*time*time;


	dart.angle = atan(dart.velocity.y/sqrt((dart.velocity.x*dart.velocity.x)+(dart.velocity.z*dart.velocity.z)));
	
	//printf("final position of dart:(%f,%f,%f)\n", dart.location.x, dart.location.y, dart.location.z);
	scores(); //display the scores
	glutPostRedisplay();
	
}

void fail ()
{
	//printf("final position of dart:(%f,%f,%f)\n", dart.location.x, dart.location.y, dart.location.z);
	glutPostRedisplay();
	scores(); //display the scores
}

void update(int n) //n is just nothing
{
    
	if(dart.location.z >=  d && (dart.location.y -board.y)<= r) ////d:DISTANCE of dart board from origin(i.e., initial dart position).
	{
		final();
		return;
	}
    	
	/*if(dart.location.z >= d && dart.location.y > r)
	{
		
	}*/

	if((dart.location.y-board.y) < -r) //y can only decrease..this means it'll never hit the board now
	{
		//fail();
		final();
		return;
	}
	
	if((dart.location.x-board.x) > r || (dart.location.x-board.x) < -r) //x will either keep on increasing or keep on decreasing
	{
		//fail(); 
		final();
		return;
	}
	

	//At any time t, the equations for the positions of the dart.
   	dart.location.z=dart.velocity.z*time;
    	dart.location.x= initial.x + dart.velocity.x*time;
    	dart.location.y= initial.y + vel_initial_y*time + 0.5*G*time*time;
    	dart.velocity.y=vel_initial_y + G*time; //v=u+at

   	 dart.angle = atan(dart.velocity.y/sqrt((dart.velocity.x*dart.velocity.x)+(dart.velocity.z*dart.velocity.z)));

   	 //We can use this angle to redraw the inclined dart at every instant by taking 90-theta as the angle.
   	 //I mostly think it will be 90-theta. However thoda visualize kam ho raha hai. We can try that by hit and trial.
    	//Should take much time.

 	time=time+0.1; //After every 0.1 units we should the dart position
	
	//printf("dart location=(%f,%f,%f)\n",dart.location.x, dart.location.y, dart.location.z);

	glutPostRedisplay();
	glutTimerFunc(delay, update, ++n);
}

void myKeyboard(unsigned char press, int x, int y)
{
	if(press=='n') //new game
	{
		new_game_initialize ();
		glutPostRedisplay();
		return;
	}

	else if(press == '\n' || press=='\r') //Enter is to fire/shoot
	{
		dart.velocity.x= vel*cos(theta*PI/180)*sin(phi*PI/180);
    		dart.velocity.y= vel*sin(theta*PI/180);
    		vel_initial_y=dart.velocity.y;
    		dart.velocity.z= vel*cos(theta*PI/180)*cos(phi*PI/180);
    		//Velocity across z axis will remain constant
    		max_time = (d-dart.location.z)/dart.velocity.z;

		glutTimerFunc(delay, update, 0);
		return;
	}

	else if(press == 'l')
    	{
        	phi=phi+1; //Angle between negative z axis and dart position
        	rotate_y=1; //This factor to be used for redrawing the scene. That is rotate dart about y axis in clockwise direction by 5 				//	degree
    	}

    	else if (press == 'j' )
    	{
        	phi=phi-1;
        	rotate_y=-1 ;// This factor to be used for redrawing the scene. That is rotate dart about y axis in anti-clockwise direction 				//by 5 degree
  	}

    	else if (press == 'k') // For increasing theta i.e. our angle of projection
    	{
        	theta=theta-5; //initially theta is 90(angle between positive y axis and negative z axis
        	rotate_x = 5; // rotate dart upwards by this factor about x axis
    	}

    	else if (press == 'i')
    	{
        	theta = theta+5;
        	rotate_x = -5; // rotate dart upwards by this factor about x axis
    	} 
	
	else if(press == 'a')
    	{
        	translation_x = 1; //This is just an arbitrary factor to move towards right
		dart.location.x = dart.location.x+1;
		initial_dart.x = dart.location.x;
    	}
    	else if(press == 'd')
    	{
        	translation_x = - 1; //Move towards right
		dart.location.x = dart.location.x-1;	
		initial_dart.x = dart.location.x;
    	}
 	else if(press == 'w')
    	{
        	translation_y = 1; //Move upwards
		dart.location.y = dart.location.y+1;
		initial_dart.y = dart.location.y;
   	}
    	else if(press == 's')
    	{
        	translation_y = - 1; //Move Down
		dart.location.y = dart.location.y-1;	
		initial_dart.y = dart.location.y;
	}
	glutPostRedisplay();
}

void ArrowKeys (int key, int x, int y)
{
	if(key==GLUT_KEY_UP)
	{
		
		vel = vel + 5.0; //add 5 mm/msec
	}
	else if(key==GLUT_KEY_DOWN)
	{
		
		vel = vel-5.0;
	}
	glutPostRedisplay();
}


void init2(void)
{

	float fovy=0.0;
  /* Use depth buffering for hidden surface elimination. */
	  glEnable(GL_DEPTH_TEST);
	  glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0,0.0,0.0,1.0);	


//NOTE: DO NOT CHANGE ANYTHING IN THE CODE BELOW IN THIS FUNCTION. 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	fovy = atan((d/2+15*h)/(3*r));
	fovy = fovy * 180.0/PI;
	fovy = 2*fovy;
	
	gluPerspective (fovy,  1, r, 8*r);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (3*r,0,d/2,  2.5*r,0,d/2, 0.0,1.0,0.0);
	
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	text(initial_dart.x, initial_dart.y,initial_dart.z, board.x, board.y, board.z); 

	glPushMatrix();
	glTranslatef(board.x, board.y, 0);
	dart_board();
	glPopMatrix();

	glPushMatrix();
	//printf("dart.angle=%f\n", dart.angle*180.0/PI);
	//printf("dart location=(%f,%f,%f)\n", dart.location.x, dart.location.y, dart.location.z);
	glTranslatef(translation_x, translation_y, 0.0);
	initial.x += translation_x;
	initial.y += translation_y;


	//if(time > (vel_initial_y/(-5*G)))
		final_dart(dart.location.x, dart.location.y, dart.location.z, dart.angle*180.0/PI);
	//else
	//	final_dart(dart.location.x, dart.location.y, dart.location.z, -dart.angle*180.0/PI);
	glPopMatrix();

	glutSwapBuffers();
}



int main(int argc, char **argv)
{

  glutInit(&argc, argv);
	//float x=atan(7);
	//printf("%f\n",x*180/PI);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glColor3d(1.0,1.0,1.0);
  glutInitWindowSize (1300, 1300);
  glutInitWindowPosition (0, 0);
  glutCreateWindow("GAME");
  
  init2();
	//from_behind();
  new_game_initialize();
  glutDisplayFunc(display);
  	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(ArrowKeys);
  glutMainLoop();
  return 0;
}

