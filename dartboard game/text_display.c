extern float theta;
extern float phi;
extern float vel;
extern int score;


void text(float x, float y, float z, float bx, float by, float bz) //(x,y,z):dart initial loc, (bx,by,bz):board position
{
    	char text[50], *t;
	int i;
	glColor3f(1, 1, 1);
    	

	/*char t2[] = "UP:vel inc, DOWN:vel dec, i: inc theta, k:dec theta, l:inc phi, j:dec phi";
	glRasterPos3f(  250, -800 , 50);
    	for( i = 0; t2[i] != '\0'; i++)
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t2[i]);
	*/

	t = "KEYBOARD UP: Increase velocity";
	glRasterPos3f(  200, -900 , 25);
	for( i = 0; t[i] != '\0'; i++)
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t[i]);
		
	t = "KEYBOARD DOWN: Decrease velocity";
	glRasterPos3f(  200, -850 , 50);
    	for( i = 0; t[i] != '\0'; i++)
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t[i]);
		
	t = "i:Increase theta   k:Decrease theta";
	glRasterPos3f(  200, -800 , 50);
    	for( i = 0; t[i] != '\0'; i++)
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t[i]);
		

	/*t = "k: Decrease theta";
	glRasterPos3f(  200, -950 , 50);
    	for( i = 0; t[i] != '\0'; i++)
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t[i]);
	*/

	t = "l: Increase phi   j: Decrease phi";
	glRasterPos3f(  200, -750 , 50);
    	for( i = 0; t[i] != '\0'; i++)
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t[i]);

	/*t = "j: Decrease phi";
	glRasterPos3f(  200, -850 , 50);
    	for( i = 0; t[i] != '\0'; i++)
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t[i]);
	*/

	t = "a: Move left   d: Move right";
	glRasterPos3f(  200, -700 , 50);
    	for( i = 0; t[i] != '\0'; i++)
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t[i]);

	/*t = "d: Move right";
	glRasterPos3f(  200, -750 , 50);
    	for( i = 0; t[i] != '\0'; i++)
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t[i]);
	*/
	
	t = "w: Move up   s: Move down";
	glRasterPos3f(  200, -650 , 50);
    	for( i = 0; t[i] != '\0'; i++)
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t[i]);
		
	/*t = " s: Move down";
	glRasterPos3f(  200, -650 , 50);
    	for( i = 0; t[i] != '\0'; i++)
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t[i]);
	*/	

	
	glColor3f(1,0,1);

	sprintf(text, "DART board:(%0.f,%0.f,%0.f)", bx,by,bz);
	glRasterPos3f(  200, -600 , 50);
	for( i = 0; text[i] != '\0'; i++)
	{
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
	}

	sprintf(text, "DART inital:(%0.f,%0.f,%0.f)", x,y,z);
	glRasterPos3f(  200, -550 , 50);
	for( i = 0; text[i] != '\0'; i++)
	{
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
	}

	sprintf(text, "VELOCITY=%.0f", vel);	
	glRasterPos3f(  200, -500 , 50);
    	for( i = 0; text[i] != '\0'; i++)
	{
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
	}

	sprintf(text, "THETA=%.0f", theta);
	glRasterPos3f(  200, -450 , 50);
	for( i = 0; text[i] != '\0'; i++)
	{
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
	}

	sprintf(text, "PHI=%.0f", phi);
	glRasterPos3f(  200, -400 , 50);
	for( i = 0; text[i] != '\0'; i++)
	{
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
	}

	sprintf(text, "SCORE=%d", score);
	glRasterPos3f(  200, -350 , 50);
	for( i = 0; text[i] != '\0'; i++)
	{
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		
	}

}

