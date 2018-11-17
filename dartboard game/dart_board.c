extern GLfloat xRot ;
extern GLfloat yRot ;
#define DISTANCE 1000.0

void disk (GLdouble inner, GLdouble outer, GLfloat *color) //draw a disk with inner radius= inner, outer radius=outer, color=color, at origin
{								//around z-axis
	GLUquadric *quad;
	glColor3f( color[0], color[1], color[2]);
	quad = gluNewQuadric();
	gluDisk (quad, inner, outer, 50, 20);
}

void dart_board_disk () //draws the front part of the dartboard, i.e., the colored thing at (0,0,0) around z-axis.
{

	GLfloat WHITE[] = {1, 1, 1};
	GLfloat BLACK[] = {0, 0, 0};
	GLfloat RED[] = {1, 0, 0};
	GLfloat GREEN[] = {0, 1, 0};
	GLfloat MAGENTA[] = {1, 0, 1};
	GLfloat YELLOW[] = {1, 1, 0};
	GLfloat BLUE[] = {0,0,1};

	disk(0.0, 12.7, RED);
	disk(12.7, 31.8, GREEN);
	disk(31.8, 204.0, BLUE);
	disk(204.0, 214.0, RED);
	disk(214.0, 330.0, YELLOW);
	disk(330.0, 340.0, RED);
	disk(340.0, 453.0, GREEN);
}

void board_at_origin () //dart board at origin
{
	GLUquadric *quad;

	glMatrixMode(GL_MODELVIEW);
	
	glBegin(GL_POLYGON);
	quad = gluNewQuadric();
	
	glColor3f (0.5, 0.5, 0.5);
	gluCylinder (quad, 453.0, 453.0,38.1, 50, 20);
	glEnd();
	dart_board_disk();
}

void dart_board() //dart board at  z=DISTANCE
{
	glPushMatrix();
	glTranslatef(0.0, 0.0, DISTANCE);
	board_at_origin();
	glPopMatrix();
}
