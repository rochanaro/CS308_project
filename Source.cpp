#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define PI 3.1428571428571428571428571428571

//light
GLfloat ambientLight[] = { 0,0,0,0 };
GLfloat diffuseLight[] = { 0.2,0.2,0.2,1.0 };
GLfloat specular[] = { 0.60, 0.6, 0.6,1.0 };
GLfloat specref[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat position[] = { 10, 100, 150, 1.0 };

float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle = 0.0;
float lastx, lasty;


void init(void) {
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);


	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 400);
}

void enable(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

}

void camera(void) {
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glTranslated(-xpos, -ypos, -zpos);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
}

float building1[] = { .929,.832,.715 };
float building2[] = { .976,.5,.445 };
float FontColor[] = { .976,.5,.445 };

void platform() {
	glPushMatrix();
	glColor3fv(building1);
	glTranslated(50, -10,-50);
	glScaled(2, 1, 1);
	glutSolidCube(6.0);
	/*glPopMatrix();

	glPushMatrix();*/
	glColor3fv(building2);
	//glTranslated(40, -10, -50);
	glScaled(1,0.5, 7);
	glutSolidCube(10.0);
	glPopMatrix();
}


//train
void train(int x, int y, int z)
{
	GLUquadricObj * qobj = gluNewQuadric();


	glPushMatrix();
	glColor3fv(cement);
	glTranslated(x + 36, y, z - 20);
	glRotated(180, 0, 1, 0);
	glScaled(1, .5, .6);
	glutSolidCube(25.0);
	glPopMatrix();

	//engine- cylinder
	glPushMatrix();
	glColor3fv(trainEngine);
	glTranslated(x + 5, y, z - 20);
	glRotatef(90, 0.0, 1, 0.0);
	//glScaled(0.3, 0.3, 0.3);
	gluCylinder(qobj, 5, 5, 20, 36, 36);
	glPopMatrix();

	//chimini
	glPushMatrix();
	glColor3fv(trainEngine);
	glTranslated(x + 7, y + 8, z - 20);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(qobj, 1, 1, 5, 36, 36);
	//lamp - cylinder
	//gluCylinder(qobj, 4.2, 0.8, 5, 36, 36);
	glPopMatrix();


}

void sarasaviUyanaNameBoard() {

	char _facName[20];
	strcpy_s(_facName, "Sarasavi Uyana");
	glPushMatrix();

	glColor3fv(FontColor);
	glRotated(90, 0, 1, 0);
	glRotated(180, 0, 1, 0);

	glTranslated(100, 10, -50);
	glScaled(.9, .2, .2);
	for (int i = 0; i < 15; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, _facName[i]);
	glPopMatrix();


	glPushMatrix();
}


void display(void) {
	glClearColor(0.0, 0.79, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	init();
	glLoadIdentity();
	camera();
	enable();



	glColor3f(1.0, 0.0, 0.0);
	GLUquadricObj* cylin = gluNewQuadric();
	//gluCylinder(cylin, 0.5, 0.5, 10, 20, 20);
	//gluDisk(cylin, 0.5, 1.0, 20, 20);

	platform();
	sarasaviUyanaNameBoard();

	glRotatef(180, 0.0, 1.0, 0.0);
	train(0, 0, 0);

	
	/*glPushMatrix();
	glBegin(GL_QUAD_STRIP);

	glColor3fv(building2);

	glVertex3d(0, -4, -20);
	glVertex3d(-10, -4, -20);
	glVertex3d(0, -1, -20);
	glVertex3d(-10, -1, -20);

	glVertex3d(0, -1, 20);
	glVertex3d(-10, -1, 20);
	glVertex3d(0, -4, 20);
	glVertex3d(-10, -4, 20);

	glVertex3d(-10, -4, 20);
	glVertex3d(-10, -4, -20);
	glVertex3d(-10, -1, 20);
	glVertex3d(-10, -1, -20);
	
	glEnd();
	glPopMatrix();*/
	
	glutSwapBuffers();
	angle++;
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'q')
	{
		xrot += 1;
		if (xrot > 360)
			xrot -= 360;
	}

	if (key == 'z')
	{
		xrot -= 1;
		if (xrot < -360) xrot += 360;
	}

	if (key == 'w')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * PI);
		xrotrad = (xrot / 180 * PI);
		xpos += float(sin(yrotrad));
		zpos -= float(cos(yrotrad));
		ypos -= float(sin(xrotrad));
	}

	if (key == 's')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * PI);
		xrotrad = (xrot / 180 * PI);
		xpos -= float(sin(yrotrad));
		zpos += float(cos(yrotrad));
		ypos += float(sin(xrotrad));
	}

	if (key == '.')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * PI);
		xpos += float(cos(yrotrad)) * 0.2;
		zpos += float(sin(yrotrad)) * 0.2;
	}

	if (key == ',')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * PI);
		xpos -= float(cos(yrotrad)) * 0.2;
		zpos -= float(sin(yrotrad)) * 0.2;
	}

	if (key == 'd')
	{
		yrot += 1;
		if (yrot > 360) yrot -= 360;
	}

	if (key == 'a')
	{
		yrot -= 1;
		if (yrot < -360)yrot += 360;
	}

	if (key == 27)
	{
		exit(0);
	}
}

void mouseMovement(int x, int y) {
	int diffx = x - lastx;
	int diffy = y - lasty;
	lastx = x;
	lasty = y;
	xrot += (float)diffy / 10;
	yrot += (float)diffx / 10;

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sarasavi Uyana Railway Station");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutPassiveMotionFunc(mouseMovement);

	glutKeyboardFunc(keyboard);
	std::cout << "Hello World!\n";
	glutMainLoop();
	return 0;
}