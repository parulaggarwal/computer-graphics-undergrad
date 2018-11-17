extern float theta;
extern float phi;
extern float vel;
extern int score;

void dart_draw()
{
	
	/*glColor3ub(255,255,255); //ORIGIN IS A WHITE DOT
	glPointSize(5.0);
	glBegin(GL_POINTS);
		glVertex3i(0,0,0);
	glEnd();
	*/
	glColor3ub(0, 205, 255); //white
	//glutSolidSphere(30, 20,20);

	glPushMatrix();
	//glRotated (, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, -120.0);
		glPushMatrix();
		glTranslatef(0.0, 0.0, 70.0);
		glutWireCone(15.0, 50.0, 12, 9); //cone: radius=15.0, height=50.0
		glPopMatrix();

		GLUquadric *quad;
	
		glBegin(GL_POLYGON);
		quad = gluNewQuadric();
		gluCylinder (quad, 5.0, 5.0,75.0, 50, 20);
		glEnd();
	glPopMatrix();
}

void final_dart(float x, float y, float z, float angle)
{

	glPushMatrix();
	
	glTranslatef(x,y,z);
	glRotatef(-theta, 1.0, 0.0, 0.0);
	glRotatef(-angle,1.0, 0.0, 0.0);		
	
	glRotatef(phi, 0.0, 1.0, 0.0);
		dart_draw();
	glPopMatrix();
}



