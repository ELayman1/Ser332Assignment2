// Ser332Assignment2.cpp : Defines the entry point for the console application.
// Elizabeth Layman, Erik Isaacson, Jacob Janas

#include "stdafx.h"
#include <GL\glut.h>
#include <math.h>


void display();
void resizeWindow(int newWidth, int newHeight);
void mySpecial(int key, int x, int y);
void myKeyboard(unsigned char key, int x, int y);
void orientMe(float ang);
void moveMeFlat(int i);
void moveMeStrafe(int i);

int width = 1500;
int height = 700;

float cameraY = 5.0f;
float cameraX = 0.0f;
float cameraZ = 0.0f;

float x = 0.0f, y = 1.75f, z = 0.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;

float aspectRatio = 1;
float left, bottom = -1;
float right, top = 1;

float scaleFactor = 1;
float angle = 0;


void main(int argc, char ** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("Ser332 Assignment2");

	// Callback functions
	glutDisplayFunc(display);
	glutSpecialFunc(mySpecial);
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc(resizeWindow);
	glutMainLoop();

}

void resizeWindow(int newWidth, int newHeight) {

	aspectRatio = (float)newWidth / (float)newHeight;

	if (newWidth >= newHeight) {
		left = -1 * aspectRatio;
		right = aspectRatio;
		bottom = -1;
		top = 1;
	}
	else {
		left = -1;
		right = 1;
		bottom = -1 / aspectRatio;
		top = 1 / aspectRatio;
	}

	width = newWidth;
	height = newHeight;
}

void display() {

	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);

	// Viewport 1 : Left
	glViewport(0, 0, width * .75, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
	glScissor(0, 0, width * .75, height);
	glEnable(GL_SCISSOR_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluPerspective(45, aspectRatio, 1, 1000);

	// View
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x + cameraX, y + cameraY, z + cameraZ, (x + cameraX) + lx, (y + cameraY) + ly, (z + cameraZ) + lz, 0.0f, 1.0f, 0.0f);


	//Color: Brown
	glColor3f(0.4f, 0.2f, 0.0f);

	//Draw Room Floor
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 1.0f, -100.0f);
	glVertex3f(100.0f, 1.0f, -100.0f);
	glVertex3f(100.0f, 1.0f, 100.0f);
	glVertex3f(-100.0f, 1.0f, 100.0f);
	glEnd();

	//Color: White
	glColor3f(0.8f, 0.8f, 0.8f);

	//Draw Room Wall 1
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 1.0f, -100.0f);
	glVertex3f(-100.0f, 30.0f, -100.0f);
	glVertex3f(100.0f, 30.0f, -100.0f);
	glVertex3f(100.0f, 1.0f, -100.0f);
	glEnd();

	//Draw Room Wall 2
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 1.0f, 100.0f);
	glVertex3f(-100.0f, 30.0f, 100.0f);
	glVertex3f(100.0f, 30.0f, 100.0f);
	glVertex3f(100.0f, 1.0f, 100.0f);
	glEnd();

	//Top Left(Trapezoid 1 Blue)
	glShadeModel(GL_FLAT);
	glColor3f(.13, .70, .66);
	glBegin(GL_POLYGON);
	glVertex3f(-70.0f, 22.0f, 100.0f);
	glVertex3f(-60.0f, 19.0f, 100.0f);
	glVertex3f(-40.0f, 19.0f, 100.0f);
	glVertex3f(-50.0f, 22.0f, 100.0f);
	glEnd();
	//Top Left(Triangle 1 Red)
	glShadeModel(GL_FLAT);
	glColor3f(.86, .08, .23);
	glBegin(GL_POLYGON);
	glVertex3f(-50.0f, 22.0f, 100.0f);
	glVertex3f(-30.0f, 16.0f, 100.0f);
	glVertex3f(-30.0f, 22.0f, 100.0f);
	glEnd();
	//Upper Left(Trapezoid 2 Gray)
	glShadeModel(GL_FLAT);
	glColor3f(.25, .25, .25);
	glBegin(GL_POLYGON);
	glVertex3f(-60.0f, 19.0f, 100.0f);
	glVertex3f(-40.0f, 13.0f, 100.0f);
	glVertex3f(-30.0f, 16.0f, 100.0f);
	glVertex3f(-40.0f, 19.0f, 100.0f);
	glEnd();
	//Top Mid Left(Triangle 2 White)
	glShadeModel(GL_FLAT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-30.0f, 22.0f, 100.0f);
	glVertex3f(-30.0f, 16.0f, 100.0f);
	glVertex3f(-20.0f, 19.0f, 100.0f);
	glEnd();
	//Upper Mid Left(Trapezoid 3 Blue)
	glShadeModel(GL_FLAT);
	glColor3f(.13, .70, .66);
	glBegin(GL_POLYGON);
	glVertex3f(-20.0f, 19.0f, 100.0f);
	glVertex3f(-40.0f, 13.0f, 100.0f);
	glVertex3f(-20.0f, 13.0f, 100.0f);
	glVertex3f(-10.0f, 16.0f, 100.0f);
	glEnd();
	//Upper Left Center(Triangle 3 Red)
	glShadeModel(GL_FLAT);
	glColor3f(.86, .08, .23);
	glBegin(GL_POLYGON);
	glVertex3f(-10.0f, 16.0f, 100.0f);
	glVertex3f(-20.0f, 13.0f, 100.0f);
	glVertex3f(0.0f, 13.0f, 100.0f);
	glEnd();
	//Mid Left(Triangle 4 Red)
	glShadeModel(GL_FLAT);
	glColor3f(.86, .08, .23);
	glBegin(GL_POLYGON);
	glVertex3f(-40.0f, 13.0f, 100.0f);
	glVertex3f(-30.0f, 10.0f, 100.0f);
	glVertex3f(-20.0f, 13.0f, 100.0f);
	glEnd();
	//Lower Left Center(Triangle 5 White)
	glShadeModel(GL_FLAT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-20.0f, 13.0f, 100.0f);
	glVertex3f(-20.0f, 7.0f, 100.0f);
	glVertex3f(0.0f, 13.0f, 100.0f);
	glEnd();
	//Lower Mid Left(Triangle 6 Gray)
	glShadeModel(GL_FLAT);
	glColor3f(.25, .25, .25);
	glBegin(GL_POLYGON);
	glVertex3f(-20.0f, 13.0f, 100.0f);
	glVertex3f(-30.0f, 10.0f, 100.0f);
	glVertex3f(-20.0f, 7.0f, 100.0f);
	glEnd();
	//Bottom Center(Triangle 7 Red)
	glShadeModel(GL_FLAT);
	glColor3f(.86, .08, .23);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 13.0f, 100.0f);
	glVertex3f(-10.0f, 10.0f, 100.0f);
	glVertex3f(10.0f, 10.0f, 100.0f);
	glEnd();
	//Bottom Left(Triangle 8 Blue)
	glShadeModel(GL_FLAT);
	glColor3f(.13, .70, .66);
	glBegin(GL_POLYGON);
	glVertex3f(-10.0f, 10.0f, 100.0f);
	glVertex3f(-20.0f, 7.0f, 100.0f);
	glVertex3f(-10.0f, 4.0f, 100.0f);
	glEnd();
	//Bottom Mid(Square 1 Gray)
	glShadeModel(GL_FLAT);
	glColor3f(.25, .25, .25);
	glBegin(GL_POLYGON);
	glVertex3f(-10.0f, 10.0f, 100.0f);
	glVertex3f(-10.0f, 4.0f, 100.0f);
	glVertex3f(10.0f, 4.0f, 100.0f);
	glVertex3f(10.0f, 10.0f, 100.0f);
	glEnd();
	//Bottom(Triangle 9 Blue)
	glShadeModel(GL_FLAT);
	glColor3f(.13, .70, .66);
	glBegin(GL_POLYGON);
	glVertex3f(-10.0f, 4.0f, 100.0f);
	glVertex3f(0.0f, 1.0f, 100.0f);
	glVertex3f(10.0f, 4.0f, 100.0f);
	glEnd();
	//Bottom Right(Triangle 10 White)
	glShadeModel(GL_FLAT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(10.0f, 10.0f, 100.0f);
	glVertex3f(20.0f, 7.0f, 100.0f);
	glVertex3f(10.0f, 4.0f, 100.0f);
	glEnd();
	//Lower Right Center(Triangle 11 Blue)
	glShadeModel(GL_FLAT);
	glColor3f(.13, .70, .66);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 13.0f, 100.0f);
	glVertex3f(20.0f, 7.0f, 100.0f);
	glVertex3f(20.0f, 13.0f, 100.0f);
	glEnd();
	//Upper Right Center(Triangle 12 White)
	glShadeModel(GL_FLAT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 13.0f, 100.0f);
	glVertex3f(20.0f, 13.0f, 100.0f);
	glVertex3f(10.0f, 16.0f, 100.0f);
	glEnd();
	//Right Mid(Triangle 13 Red)
	glShadeModel(GL_FLAT);
	glColor3f(.86, .08, .23);
	glBegin(GL_POLYGON);
	glVertex3f(10.0f, 16.0f, 100.0f);
	glVertex3f(20.0f, 13.0f, 100.0f);
	glVertex3f(20.0f, 19.0f, 100.0f);
	glEnd();
	//Right Lower(Triangle 14 Red)
	glShadeModel(GL_FLAT);
	glColor3f(.86, .08, .23);
	glBegin(GL_POLYGON);
	glVertex3f(20.0f, 13.0f, 100.0f);
	glVertex3f(20.0f, 7.0f, 100.0f);
	glVertex3f(30.0f, 10.0f, 100.0f);
	glEnd();
	//Right Mid(Trapezoid 4 Gray)
	glShadeModel(GL_FLAT);
	glColor3f(.25, .25, .25);
	glBegin(GL_POLYGON);
	glVertex3f(20.0f, 19.0f, 100.0f);
	glVertex3f(20.0f, 13.0f, 100.0f);
	glVertex3f(30.0f, 10.0f, 100.0f);
	glVertex3f(40.0f, 13.0f, 100.0f);
	glEnd();
	//Right Mid(Triangle 15 Blue)
	glShadeModel(GL_FLAT);
	glColor3f(.13, .70, .66);
	glBegin(GL_POLYGON);
	glVertex3f(30.0f, 16.0f, 100.0f);
	glVertex3f(40.0f, 13.0f, 100.0f);
	glVertex3f(50.0f, 16.0f, 100.0f);
	glEnd();
	//Upper Right(Square 2 White)
	glShadeModel(GL_FLAT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(20.0f, 19.0f, 100.0f);
	glVertex3f(30.0f, 16.0f, 100.0f);
	glVertex3f(40.0f, 19.0f, 100.0f);
	glVertex3f(30.0f, 22.0f, 100.0f);
	glEnd();
	//Upper Mid Right(Trapezoid 5 Gray)
	glShadeModel(GL_FLAT);
	glColor3f(.25, .25, .25);
	glBegin(GL_POLYGON);
	glVertex3f(30.0f, 16.0f, 100.0f);
	glVertex3f(50.0f, 16.0f, 100.0f);
	glVertex3f(60.0f, 19.0f, 100.0f);
	glVertex3f(40.0f, 19.0f, 100.0f);
	glEnd();
	//Top Right(Trapezoid 6 Red)
	glShadeModel(GL_FLAT);
	glColor3f(.86, .08, .23);
	glBegin(GL_POLYGON);
	glVertex3f(30.0f, 22.0f, 100.0f);
	glVertex3f(40.0f, 19.0f, 100.0f);
	glVertex3f(60.0f, 19.0f, 100.0f);
	glVertex3f(50.0f, 22.0f, 100.0f);
	glEnd();
	//Top Right(Triangle 16 Blue)
	glShadeModel(GL_FLAT);
	glColor3f(.13, .70, .66);
	glBegin(GL_POLYGON);
	glVertex3f(50.0f, 22.0f, 100.0f);
	glVertex3f(60.0f, 19.0f, 100.0f);
	glVertex3f(70.0f, 22.0f, 100.0f);
	glEnd();

	//Color: Grey
	glColor3f(0.75f, 0.75f, 0.75f);

	//Draw Room Wall 3
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 1.0f, -100.0f);
	glVertex3f(-100.0f, 30.0f, -100.0f);
	glVertex3f(-100.0f, 30.0f, 100.0f);
	glVertex3f(-100.0f, 1.0f, 100.0f);
	glEnd();

	//Draw Room Wall 4
	glBegin(GL_QUADS);
	glVertex3f(100.0f, 1.0f, -100.0f);
	glVertex3f(100.0f, 30.0f, -100.0f);
	glVertex3f(100.0f, 30.0f, 100.0f);
	glVertex3f(100.0f, 1.0f, 100.0f);
	glEnd();

	//Color: Brown
	glColor3f(0.85f, 0.85f, 0.85f);

	//Draw Room Ceiling
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 30.0f, -100.0f);
	glVertex3f(100.0f, 30.0f, -100.0f);
	glVertex3f(100.0f, 30.0f, 100.0f);
	glVertex3f(-100.0f, 30.0f, 100.0f);
	glEnd();

	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);

	// Viewport 1: Right
	glViewport(width * .75, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
	glScissor(width * .75, 0, width, height);
	glEnable(GL_SCISSOR_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glVertex2f(-0.5f, 0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(-0.5f, -0.5f);
	glEnd();

	glutPostRedisplay();
	glutSwapBuffers();

}

void mySpecial(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
		ly = ly + .1;
		break;
	case GLUT_KEY_DOWN:
		ly = ly - .1;
		break;
	case GLUT_KEY_LEFT:
		angle -= 0.2f;
		orientMe(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.2f;
		orientMe(angle);
		break;
	}

	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'w':
		moveMeFlat(20);
		glutPostRedisplay();
		break;
	case 's':
		moveMeFlat(-20);
		glutPostRedisplay();
		break;
	case 'a':
		cameraX--;
		cameraX--;
		glutPostRedisplay();
		break;
	case 'd':
		cameraX++;
		cameraX++;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void moveMeFlat(int i) {
	x = x + i * (lx) * 0.1;
	z = z + i * (lz) * 0.1;
}

void moveMeStrafe(int i) {

}

void orientMe(float ang) {
	lx = sin(ang);
	lz = -cos(ang);
}