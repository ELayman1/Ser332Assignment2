// Ser332Assignment2.cpp : Defines the entry point for the console application.
// Elizabeth Layman, Erik Isaacson, Jacob Janas

#include "stdafx.h"
#include "glut.h"
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
float cameraZ = -50.0f;

float x = 0.0f, y = 1.75f, z = 0.0f;
float lx = 0.0f, ly = 0.0f, lz = 1.0f;

float posX = 0.0f;

float aspectRatio = 1;
float left, bottom = -1;
float right, top = 1;

float scaleFactor = 1;
float angle = 0;
float rotAngle = 0;

bool rise = true;

int main(int argc, char ** argv) {

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
	return(0);
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
	glColor3f(0.65f, 0.50f, 0.39f);

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

	//---Added-Image-------------------------
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

	//Right Roof Triangle
	glBegin(GL_TRIANGLES);  // fill connected polygon
	glColor3f(1.0f, 0.0f, 0.0f);  // red
	glVertex3f(41.0f, 30.0f, 55.0f);  // vertices of the triangle 2
	glVertex3f(41.0f, 30.0f, 20.0f);
	glVertex3f(12.5f, 30.0f, 55.0f);
	glEnd();
	//Right Roof Square
	glBegin(GL_QUADS);  // fill connected polygon
	glColor3f(1.0f, 0.0f, 0.0f);  // red
	glVertex3f(41.0f, 30.0f, 55.0f);  // vertices of the square 1
	glVertex3f(41.0f, 30.0f, 20.0f);
	glVertex3f(70.0f, 30.0f, 20.0f);
	glVertex3f(70.0f, 30.0f, 55.0f);
	glEnd();
	//Left Roof Triangle
	glBegin(GL_TRIANGLES);  // fill connected polygon
	glColor3f(1.0f, 0.0f, 0.0f);  // red
	glVertex3f(-41.0f, 30.0f, 55.0f);  // vertices of the triangle 3
	glVertex3f(-41.0f, 30.0f, 20.0f);
	glVertex3f(-12.5f, 30.0f, 55.0f);
	glEnd();
	//Left Roof Square
	glBegin(GL_QUADS);  // fill connected polygon
	glColor3f(1.0f, 0.0f, 0.0f);  // red
	glVertex3f(-41.0f, 30.0f, 55.0f);  // vertices of the square 2
	glVertex3f(-41.0f, 30.0f, 20.0f);
	glVertex3f(-70.0f, 30.0f, 20.0f);
	glVertex3f(-70.0f, 30.0f, 55.0f);
	glEnd();
	//Roof Lines
	glLineWidth(1.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-70.0f, 30.0f, 25.0f);
	glVertex3f(70.0f, 30.0f, 25.0f);
	glEnd();
	//Roof Lines
	glLineWidth(1.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-70.0f, 30.0f, 30.0f);
	glVertex3f(70.0f, 30.0f, 30.0f);
	glEnd();
	//Roof Lines
	glLineWidth(1.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-70.0f, 30.0f, 35.0f);
	glVertex3f(70.0f, 30.0f, 35.0f);
	glEnd();
	//Roof Lines
	glLineWidth(1.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-70.0f, 30.0f, 40.0f);
	glVertex3f(70.0f, 30.0f, 40.0f);
	glEnd();
	//Roof Lines
	glLineWidth(1.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-70.0f, 30.0f, 45.0f);
	glVertex3f(70.0f, 30.0f, 45.0f);
	glEnd();
	//Roof Lines
	glLineWidth(1.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-70.0f, 30.0f, 50.0f);
	glVertex3f(70.0f, 30.0f, 50.0f);
	glEnd();
	//Middle Roof Triangle
	glBegin(GL_TRIANGLES);  // fill connected polygon
	glColor3f(1.0f, 1.0f, 0.95f);  // off white
	glVertex3f(-40.0f, 30.0f, 20.0f);  // vertices of the triangle 1
	glVertex3f(40.0f, 30.0f, 20.0f);
	glVertex3f(0.0f, 30.0f, 70.0f);
	glEnd();

	//--MainHouse------------------------------------------
	//Main House Square
	glBegin(GL_QUADS);  // fill connected polygon
	glColor3f(1.0f, 1.0f, 0.95f);  // off white
	glVertex3f(-70.0f, 30.0f, -60.0f);  // vertices of the square 2
	glVertex3f(-70.0f, 30.0f, 20.0f);
	glVertex3f(70.0f, 30.0f, 20.0f);
	glVertex3f(70.0f, 30.0f, -60.0f);
	glEnd();
	//--Windows--------------------------------------------
	//High Window
	glBegin(GL_QUADS);  // fill connected polygon
	glColor3f(0.6f, 0.77f, 0.8f);  // grey-blue
	glVertex3f(-10.0f, 30.0f, 40.0f);  // vertices of the square 2
	glVertex3f(-10.0f, 30.0f, 15.0f);
	glVertex3f(10.0f, 30.0f, 15.0f);
	glVertex3f(10.0f, 30.0f, 40.0f);
	glEnd();
	//Left Window
	glBegin(GL_QUADS);  // fill connected polygon 
	glColor3f(0.6f, 0.77f, 0.8f);  // grey-blue
	glVertex3f(-60.0f, 30.0f, -50.0f);  // vertices of the square 2
	glVertex3f(-60.0f, 30.0f, -10.0f);
	glVertex3f(-20.0f, 30.0f, -10.0f);
	glVertex3f(-20.0f, 30.0f, -50.0f);
	glEnd();
	//Window Reflection
	glLineWidth(5.0);
	glColor3f(1.0f, 1.0f, 1.0f); // white
	glBegin(GL_LINES);
	glVertex3f(-50.0f, 30.0f, -40.0f);
	glVertex3f(-30.0f, 30.0f, -20.0f);
	glEnd();
	//Window Reflection
	glLineWidth(5.0);
	glColor3f(1.0f, 1.0f, 1.0f); // white
	glBegin(GL_LINES);
	glVertex3f(-42.5f, 30.0f, -42.5f);
	glVertex3f(-27.5f, 30.0f, -27.5f);
	glEnd();
	//Window Reflection
	glLineWidth(5.0);
	glColor3f(1.0f, 1.0f, 1.0f); // white
	glBegin(GL_LINES);
	glVertex3f(-35.0f, 30.0f, -42.5f);
	glVertex3f(-25.0f, 30.0f, -35.0f);
	glEnd();
	//Right Window
	glBegin(GL_QUADS);  // fill connected polygon
	glColor3f(0.6f, 0.77f, 0.8f);  // grey-blue
	glVertex3f(60.0f, 30.0f, -50.0f);  // vertices of the square 2
	glVertex3f(60.0f, 30.0f, -10.0f);
	glVertex3f(20.0f, 30.0f, -10.0f);
	glVertex3f(20.0f, 30.0f, -50.0f);
	glEnd();
	//Window Reflection
	glLineWidth(5.0);
	glColor3f(1.0f, 1.0f, 1.0f); // white
	glBegin(GL_LINES);
	glVertex3f(50.0f, 30.0f, -40.0f);
	glVertex3f(30.0f, 30.0f, -20.0f);
	glEnd();
	//Window Reflection
	glLineWidth(5.0);
	glColor3f(1.0f, 1.0f, 1.0f); // white
	glBegin(GL_LINES);
	glVertex3f(42.5f, 30.0f, -42.5f);
	glVertex3f(27.5f, 30.0f, -27.5f);
	glEnd();
	//Window Reflection
	glLineWidth(5.0);
	glColor3f(1.0f, 1.0f, 1.0f); // white
	glBegin(GL_LINES);
	glVertex3f(35.0f, 30.0f, -42.5f);
	glVertex3f(25.0f, 30.0f, -35.0f);
	glEnd();

	//--Floor----------------------------------------------
	//Street
	glBegin(GL_QUADS);  // fill connected polygon
	glColor3f(0.0f, 0.0f, 0.0f);  // black
	glVertex3f(-100.0f, 30.0f, -100.0f);  // vertices of the square 2
	glVertex3f(-100.0f, 30.0f, -80.0f);
	glVertex3f(100.0f, 30.0f, -80.0f);
	glVertex3f(100.0f, 30.0f, -100.0f);
	glEnd();
	//Concrete Square
	glBegin(GL_QUADS);  // fill connected polygon
	glColor3f(0.6f, 0.6f, 0.6f);  // grey
	glVertex3f(-100.0f, 30.0f, -60.0f);  // vertices of the square 2
	glVertex3f(-100.0f, 30.0f, -80.0f);
	glVertex3f(100.0f, 30.0f, -80.0f);
	glVertex3f(100.0f, 30.0f, -60.0f);
	glEnd();
	//Back House Square
	glBegin(GL_QUADS);  // fill connected polygon
	glColor3f(1.0f, 1.0f, 0.95f);  // off white
	glVertex3f(85.0f, 30.0f, -60.0f);  // vertices of the square 2
	glVertex3f(85.0f, 30.0f, -73.0f);
	glVertex3f(-85.0f, 30.0f, -73.0f);
	glVertex3f(-85.0f, 30.0f, -60.0f);
	glEnd();
	//Dirt Left Square
	glBegin(GL_QUADS);  // fill connected polygon
	glColor3f(0.4f, 0.15f, 0.03f);  // brown
	glVertex3f(-85.0f, 30.0f, -60.0f);  // vertices of the square 2
	glVertex3f(-85.0f, 30.0f, -73.0f);
	glVertex3f(-20.0f, 30.0f, -73.0f);
	glVertex3f(-20.0f, 30.0f, -60.0f);
	glEnd();
	//Dirt Right Square
	glBegin(GL_QUADS);  // fill connected polygon
	glColor3f(0.4f, 0.15f, 0.03f);  // brown
	glVertex3f(85.0f, 30.0f, -60.0f);  // vertices of the square 2
	glVertex3f(85.0f, 30.0f, -73.0f);
	glVertex3f(20.0f, 30.0f, -73.0f);
	glVertex3f(20.0f, 30.0f, -60.0f);
	glEnd();
	//Main Lower House Square
	glBegin(GL_QUADS);  // fill connected polygon
	glColor3f(1.0f, 1.0f, 0.95f);  // off white
	glVertex3f(-75.0f, 30.0f, -55.0f);  // vertices of the square 2
	glVertex3f(-75.0f, 30.0f, -65.0f);
	glVertex3f(75.0f, 30.0f, -65.0f);
	glVertex3f(75.0f, 30.0f, -55.0f);
	glEnd();

	//--Door-----------------------------------------------
	//Door
	glBegin(GL_QUADS);  // fill connected polygon
	glColor3f(0.4f, 0.0f, 0.1f);  // brown
	glVertex3f(-10.0f, 30.0f, -65.0f);  // vertices of the square 2
	glVertex3f(-10.0f, 30.0f, -25.0f);
	glVertex3f(10.0f, 30.0f, -25.0f);
	glVertex3f(10.0f, 30.0f, -65.0f);
	glEnd();
	//Door Window
	glBegin(GL_QUADS);  // fill connected polygon
	glColor3f(0.6f, 0.77f, 0.8f);  // grey-blue
	glVertex3f(-5.0f, 30.0f, -40.0f);  // vertices of the square 2
	glVertex3f(-5.0f, 30.0f, -30.0f);
	glVertex3f(5.0f, 30.0f, -30.0f);
	glVertex3f(5.0f, 30.0f, -40.0f);
	glEnd();
	//-----------------------------------------------------

	//MaroonHouseLines-------------------------------------
	//Roof Diagonal Right
	glLineWidth(10.0);
	glColor3f(0.5f, 0.0f, 0.2f); // maroon
	glBegin(GL_LINES);
	glVertex3f(40.0f, 30.0f, 20.0f);
	glVertex3f(0.0f, 30.0f, 70.0f);
	glEnd();
	//Roof Diagonal Left
	glLineWidth(10.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-40.0f, 30.0f, 20.0f);
	glVertex3f(0.0f, 30.0f, 70.0f);
	glEnd();
	//Roof Horizontal Left
	glLineWidth(10.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-39.0f, 30.0f, 20.0f);
	glVertex3f(-70.0f, 30.0f, 20.0f);
	glEnd();
	//Roof Horizontal Right
	glLineWidth(10.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(39.0f, 30.0f, 20.0f);
	glVertex3f(70.0f, 30.0f, 20.0f);
	glEnd();
	//Roof Vertical Left
	glLineWidth(10.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-70.0f, 30.0f, 57.0f);
	glVertex3f(-70.0f, 30.0f, 18.7f);
	glEnd();
	//Roof Vertical Right
	glLineWidth(10.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(70.0f, 30.0f, 57.0f);
	glVertex3f(70.0f, 30.0f, 18.7f);
	glEnd();
	//Roof Horizontal LowerLedge
	glLineWidth(10.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-72.0f, 30.0f, 5.0f);
	glVertex3f(72.0f, 30.0f, 5.0f);
	glEnd();
	//Roof Horizontal UpperLedge
	glLineWidth(10.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-74.0f, 30.0f, 7.0f);
	glVertex3f(74.0f, 30.0f, 7.0f);
	glEnd();
	//Left Window Horizontal UpperLedge 1
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-62.0f, 30.0f, -10.0f);
	glVertex3f(-18.0f, 30.0f, -10.0f);
	glEnd();
	//Left Window Horizontal UpperLedge 2
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-64.0f, 30.0f, -8.0f);
	glVertex3f(-16.0f, 30.0f, -8.0f);
	glEnd();
	//Left Window Vertical 1 
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-60.0f, 30.0f, -50.0f);
	glVertex3f(-60.0f, 30.0f, -10.0f);
	glEnd();
	//Left Window Vertical 2
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-20.0f, 30.0f, -50.0f);
	glVertex3f(-20.0f, 30.0f, -10.0f);
	glEnd();
	//Left Window Vertical 3
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-40.0f, 30.0f, -50.0f);
	glVertex3f(-40.0f, 30.0f, -10.0f);
	glEnd();
	//Right Window Horizontal 
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-61.0f, 30.0f, -20.0f);
	glVertex3f(-19.0f, 30.0f, -20.0f);
	glEnd();
	//Left Window Horizontal LowerLedge
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-61.0f, 30.0f, -50.0f);
	glVertex3f(-19.0f, 30.0f, -50.0f);
	glEnd();
	//Right Window Horizontal UpperLedge 1
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(62.0f, 30.0f, -10.0f);
	glVertex3f(18.0f, 30.0f, -10.0f);
	glEnd();
	//Right Window Horizontal UpperLedge 2
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(64.0f, 30.0f, -8.0f);
	glVertex3f(16.0f, 30.0f, -8.0f);
	glEnd();
	//Right Window Vertical 1 
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(60.0f, 30.0f, -50.0f);
	glVertex3f(60.0f, 30.0f, -10.0f);
	glEnd();
	//Right Window Vertical 2
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(20.0f, 30.0f, -50.0f);
	glVertex3f(20.0f, 30.0f, -10.0f);
	glEnd();
	//Right Window Vertical 3
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(40.0f, 30.0f, -50.0f);
	glVertex3f(40.0f, 30.0f, -10.0f);
	glEnd();
	//Right Window Horizontal 
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(61.0f, 30.0f, -20.0f);
	glVertex3f(19.0f, 30.0f, -20.0f);
	glEnd();
	//Right Window Horizontal LowerLedge
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(61.0f, 30.0f, -50.0f);
	glVertex3f(19.0f, 30.0f, -50.0f);
	glEnd();
	//High Window Left Trim
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-10.0f, 30.0f, 41.0f);  // vertices of the square 2
	glVertex3f(-10.0f, 30.0f, 14.0f);
	//High Window Middle Trim
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(0.0f, 30.0f, 40.0f);  // vertices of the square 2
	glVertex3f(0.0f, 30.0f, 15.0f);
	//High Window Right Trim
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(10.0f, 30.0f, 14.0f);
	glVertex3f(10.0f, 30.0f, 41.0f);
	//High Window Top Trim
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-10.0f, 30.0f, 40.0f);
	glVertex3f(10.0f, 30.0f, 40.0f);
	//High Window Middle Trim
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-10.0f, 30.0f, 30.0f);
	glVertex3f(10.0f, 30.0f, 30.0f);
	//High Window Bottom Trim
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-10.0f, 30.0f, 15.0f);
	glVertex3f(10.0f, 30.0f, 15.0f);
	glEnd();
	//Door Window Horizontal Trim
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-5.0f, 30.0f, -35.0f);
	glVertex3f(5.0f, 30.0f, -35.0f);
	glEnd();
	//Door Window Vertical Trim
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(0.0f, 30.0f, -30.0f);
	glVertex3f(0.0f, 30.0f, -40.0f);
	glEnd();
	//Middle Roof Vertical
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(0.0f, 30.0f, 70.0f);
	glVertex3f(0.0f, 30.0f, 50.0f);
	glEnd();
	//Middle Roof Horizontal
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-17.0f, 30.0f, 50.0f);
	glVertex3f(17.0f, 30.0f, 50.0f);
	glEnd();
	//Middle Roof Horizontal
	glLineWidth(5.0);
	glColor3f(0.5f, 0.0f, 0.2f); //maroon
	glBegin(GL_LINES);
	glVertex3f(-17.0f, 30.0f, 50.0f);
	glVertex3f(17.0f, 30.0f, 50.0f);
	glEnd();


	glPushMatrix();
	glTranslatef(posX, 0, 0);
	//Table Top
	glColor3f(0.4f, 0.2f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 4.0f, -4.0f);
	glVertex3f(5.0f + posX, 4.0f, -4.0f);
	glVertex3f(5.0f + posX, 4.0f, 4.0f);
	glVertex3f(-5.0f + posX, 4.0f, 4.0f);
	glEnd();
	glColor3f(0.45f, 0.25f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 4.0f, -4.0f);
	glVertex3f(5.0f + posX, 4.0f, -4.0f);
	glVertex3f(5.0f + posX, 4.5f, -4.0f);
	glVertex3f(-5.0f + posX, 4.5f, -4.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 4.0f, 4.0f);
	glVertex3f(5.0f + posX, 4.0f, 4.0f);
	glVertex3f(5.0f + posX, 4.5f, 4.0f);
	glVertex3f(-5.0f + posX, 4.5f, 4.0f);
	glEnd();
	glColor3f(0.43f, 0.23f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(5.0f + posX, 4.0f, 4.0f);
	glVertex3f(5.0f + posX, 4.0f, -4.0f);
	glVertex3f(5.0f + posX, 4.5f, -4.0f);
	glVertex3f(5.0f + posX, 4.5f, 4.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 4.0f, 4.0f);
	glVertex3f(-5.0f + posX, 4.0f, -4.0f);
	glVertex3f(-5.0f + posX, 4.5f, -4.0f);
	glVertex3f(-5.0f + posX, 4.5f, 4.0f);
	glEnd();
	glColor3f(0.4f, 0.2f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 4.5f, -4.0f);
	glVertex3f(5.0f + posX, 4.5f, -4.0f);
	glVertex3f(5.0f + posX, 4.5f, 4.0f);
	glVertex3f(-5.0f + posX, 4.5f, 4.0f);
	glEnd();

	//Leg 1 
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 4.0f, -4.0f);
	glVertex3f(-4.5f + posX, 4.0f, -4.0f);
	glVertex3f(-4.5f + posX, 4.0f, -3.5f);
	glVertex3f(-5.0f + posX, 4.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 4.0f, -4.0f);
	glVertex3f(-4.5f + posX, 4.0f, -4.0f);
	glVertex3f(-4.5f + posX, 1.0f, -4.0f);
	glVertex3f(-5.0f + posX, 1.0f, -4.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 4.0f, -3.5f);
	glVertex3f(-4.5f + posX, 4.0f, -3.5f);
	glVertex3f(-4.5f + posX, 1.0f, -3.5f);
	glVertex3f(-5.0f + posX, 1.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 4.0f, -4.0f);
	glVertex3f(-5.0f + posX, 1.0f, -4.0f);
	glVertex3f(-5.0f + posX, 1.0f, -3.5f);
	glVertex3f(-5.0f + posX, 4.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-4.5f + posX, 4.0f, -4.0f);
	glVertex3f(-4.5f + posX, 1.0f, -4.0f);
	glVertex3f(-4.5f + posX, 1.0f, -3.5f);
	glVertex3f(-4.5f + posX, 4.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 1.0f, -4.0f);
	glVertex3f(-4.5f + posX, 1.0f, -4.0f);
	glVertex3f(-4.5f + posX, 1.0f, -3.5f);
	glVertex3f(-5.0f + posX, 1.0f, -3.5f);
	glEnd();

	//Leg 2
	glBegin(GL_QUADS);
	glVertex3f(5.0f + posX, 4.0f, -4.0f);
	glVertex3f(4.5f + posX, 4.0f, -4.0f);
	glVertex3f(4.5f + posX, 4.0f, -3.5f);
	glVertex3f(5.0f + posX, 4.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f + posX, 4.0f, -4.0f);
	glVertex3f(4.5f + posX, 4.0f, -4.0f);
	glVertex3f(4.5f + posX, 1.0f, -4.0f);
	glVertex3f(5.0f + posX, 1.0f, -4.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f + posX, 4.0f, -3.5f);
	glVertex3f(4.5f + posX, 4.0f, -3.5f);
	glVertex3f(4.5f + posX, 1.0f, -3.5f);
	glVertex3f(5.0f + posX, 1.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f + posX, 4.0f, -4.0f);
	glVertex3f(5.0f + posX, 1.0f, -4.0f);
	glVertex3f(5.0f + posX, 1.0f, -3.5f);
	glVertex3f(5.0f + posX, 4.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(4.5f + posX, 4.0f, -4.0f);
	glVertex3f(4.5f + posX, 1.0f, -4.0f);
	glVertex3f(4.5f + posX, 1.0f, -3.5f);
	glVertex3f(4.5f + posX, 4.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f + posX, 1.0f, -4.0f);
	glVertex3f(4.5f + posX, 1.0f, -4.0f);
	glVertex3f(4.5f + posX, 1.0f, -3.5f);
	glVertex3f(5.0f + posX, 1.0f, -3.5f);
	glEnd();

	//Leg 3
	glBegin(GL_QUADS);
	glVertex3f(5.0f + posX, 4.0f, 4.0f);
	glVertex3f(4.5f + posX, 4.0f, 4.0f);
	glVertex3f(4.5f + posX, 4.0f, 3.5f);
	glVertex3f(5.0f + posX, 4.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f + posX, 4.0f, 4.0f);
	glVertex3f(4.5f + posX, 4.0f, 4.0f);
	glVertex3f(4.5f + posX, 1.0f, 4.0f);
	glVertex3f(5.0f + posX, 1.0f, 4.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f + posX, 4.0f, 3.5f);
	glVertex3f(4.5f + posX, 4.0f, 3.5f);
	glVertex3f(4.5f + posX, 1.0f, 3.5f);
	glVertex3f(5.0f + posX, 1.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f + posX, 4.0f, 4.0f);
	glVertex3f(5.0f + posX, 1.0f, 4.0f);
	glVertex3f(5.0f + posX, 1.0f, 3.5f);
	glVertex3f(5.0f + posX, 4.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(4.5f + posX, 4.0f, 4.0f);
	glVertex3f(4.5f + posX, 1.0f, 4.0f);
	glVertex3f(4.5f + posX, 1.0f, 3.5f);
	glVertex3f(4.5f + posX, 4.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f + posX, 1.0f, 4.0f);
	glVertex3f(4.5f + posX, 1.0f, 4.0f);
	glVertex3f(4.5f + posX, 1.0f, 3.5f);
	glVertex3f(5.0f + posX, 1.0f, 3.5f);
	glEnd();

	//Leg 4
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 4.0f, 4.0f);
	glVertex3f(-4.5f + posX, 4.0f, 4.0f);
	glVertex3f(-4.5f + posX, 4.0f, 3.5f);
	glVertex3f(-5.0f + posX, 4.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 4.0f, 4.0f);
	glVertex3f(-4.5f + posX, 4.0f, 4.0f);
	glVertex3f(-4.5f + posX, 1.0f, 4.0f);
	glVertex3f(-5.0f + posX, 1.0f, 4.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 4.0f, 3.5f);
	glVertex3f(-4.5f + posX, 4.0f, 3.5f);
	glVertex3f(-4.5f + posX, 1.0f, 3.5f);
	glVertex3f(-5.0f + posX, 1.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 4.0f, 4.0f);
	glVertex3f(-5.0f + posX, 1.0f, 4.0f);
	glVertex3f(-5.0f + posX, 1.0f, 3.5f);
	glVertex3f(-5.0f + posX, 4.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-4.5f + posX, 4.0f, 4.0f);
	glVertex3f(-4.5f + posX, 1.0f, 4.0f);
	glVertex3f(-4.5f + posX, 1.0f, 3.5f);
	glVertex3f(-4.5f + posX, 4.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f + posX, 1.0f, 4.0f);
	glVertex3f(-4.5f + posX, 1.0f, 4.0f);
	glVertex3f(-4.5f + posX, 1.0f, 3.5f);
	glVertex3f(-5.0f + posX, 1.0f, 3.5f);
	glEnd();

	glPopMatrix();

	if (posX >= 10) {
		//begin to shrink
		rise = false;
	}
	else {
		if (posX <= -10) {
			rise = true;
		}
	}

	if (rise) {
		posX = posX + .05;
	}
	else {
		posX = posX - .05;
	}

	glPushMatrix();
	glTranslatef(60.0f, 0.0f, 0.0f);
	glRotatef(rotAngle, 0, 1, 1);
	//Table Top
	glColor3f(0.4f, 0.2f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 4.0f, -4.0f);
	glVertex3f(5.0f, 4.0f, -4.0f);
	glVertex3f(5.0f, 4.0f, 4.0f);
	glVertex3f(-5.0f, 4.0f, 4.0f);
	glEnd();
	glColor3f(0.45f, 0.25f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 4.0f, -4.0f);
	glVertex3f(5.0f, 4.0f, -4.0f);
	glVertex3f(5.0f, 4.5f, -4.0f);
	glVertex3f(-5.0f, 4.5f, -4.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 4.0f, 4.0f);
	glVertex3f(5.0f, 4.0f, 4.0f);
	glVertex3f(5.0f, 4.5f, 4.0f);
	glVertex3f(-5.0f, 4.5f, 4.0f);
	glEnd();
	glColor3f(0.43f, 0.23f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(5.0f, 4.0f, 4.0f);
	glVertex3f(5.0f, 4.0f, -4.0f);
	glVertex3f(5.0f, 4.5f, -4.0f);
	glVertex3f(5.0f, 4.5f, 4.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 4.0f, 4.0f);
	glVertex3f(-5.0f, 4.0f, -4.0f);
	glVertex3f(-5.0f, 4.5f, -4.0f);
	glVertex3f(-5.0f, 4.5f, 4.0f);
	glEnd();
	glColor3f(0.4f, 0.2f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 4.5f, -4.0f);
	glVertex3f(5.0f, 4.5f, -4.0f);
	glVertex3f(5.0f, 4.5f, 4.0f);
	glVertex3f(-5.0f, 4.5f, 4.0f);
	glEnd();

	//Leg 1 
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 4.0f, -4.0f);
	glVertex3f(-4.5f, 4.0f, -4.0f);
	glVertex3f(-4.5f, 4.0f, -3.5f);
	glVertex3f(-5.0f, 4.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 4.0f, -4.0f);
	glVertex3f(-4.5f, 4.0f, -4.0f);
	glVertex3f(-4.5f, 1.0f, -4.0f);
	glVertex3f(-5.0f, 1.0f, -4.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 4.0f, -3.5f);
	glVertex3f(-4.5f, 4.0f, -3.5f);
	glVertex3f(-4.5f, 1.0f, -3.5f);
	glVertex3f(-5.0f, 1.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 4.0f, -4.0f);
	glVertex3f(-5.0f, 1.0f, -4.0f);
	glVertex3f(-5.0f, 1.0f, -3.5f);
	glVertex3f(-5.0f, 4.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-4.5f, 4.0f, -4.0f);
	glVertex3f(-4.5f, 1.0f, -4.0f);
	glVertex3f(-4.5f, 1.0f, -3.5f);
	glVertex3f(-4.5f, 4.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 1.0f, -4.0f);
	glVertex3f(-4.5f, 1.0f, -4.0f);
	glVertex3f(-4.5f, 1.0f, -3.5f);
	glVertex3f(-5.0f, 1.0f, -3.5f);
	glEnd();

	//Leg 2
	glBegin(GL_QUADS);
	glVertex3f(5.0f, 4.0f, -4.0f);
	glVertex3f(4.5f, 4.0f, -4.0f);
	glVertex3f(4.5f, 4.0f, -3.5f);
	glVertex3f(5.0f, 4.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f, 4.0f, -4.0f);
	glVertex3f(4.5f, 4.0f, -4.0f);
	glVertex3f(4.5f, 1.0f, -4.0f);
	glVertex3f(5.0f, 1.0f, -4.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f, 4.0f, -3.5f);
	glVertex3f(4.5f, 4.0f, -3.5f);
	glVertex3f(4.5f, 1.0f, -3.5f);
	glVertex3f(5.0f, 1.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f, 4.0f, -4.0f);
	glVertex3f(5.0f, 1.0f, -4.0f);
	glVertex3f(5.0f, 1.0f, -3.5f);
	glVertex3f(5.0f, 4.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(4.5f, 4.0f, -4.0f);
	glVertex3f(4.5f, 1.0f, -4.0f);
	glVertex3f(4.5f, 1.0f, -3.5f);
	glVertex3f(4.5f, 4.0f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f, 1.0f, -4.0f);
	glVertex3f(4.5f, 1.0f, -4.0f);
	glVertex3f(4.5f, 1.0f, -3.5f);
	glVertex3f(5.0f, 1.0f, -3.5f);
	glEnd();

	//Leg 3
	glBegin(GL_QUADS);
	glVertex3f(5.0f, 4.0f, 4.0f);
	glVertex3f(4.5f, 4.0f, 4.0f);
	glVertex3f(4.5f, 4.0f, 3.5f);
	glVertex3f(5.0f, 4.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f, 4.0f, 4.0f);
	glVertex3f(4.5f, 4.0f, 4.0f);
	glVertex3f(4.5f, 1.0f, 4.0f);
	glVertex3f(5.0f, 1.0f, 4.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f, 4.0f, 3.5f);
	glVertex3f(4.5f, 4.0f, 3.5f);
	glVertex3f(4.5f, 1.0f, 3.5f);
	glVertex3f(5.0f, 1.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f, 4.0f, 4.0f);
	glVertex3f(5.0f, 1.0f, 4.0f);
	glVertex3f(5.0f, 1.0f, 3.5f);
	glVertex3f(5.0f, 4.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(4.5f, 4.0f, 4.0f);
	glVertex3f(4.5f, 1.0f, 4.0f);
	glVertex3f(4.5f, 1.0f, 3.5f);
	glVertex3f(4.5f, 4.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(5.0f, 1.0f, 4.0f);
	glVertex3f(4.5f, 1.0f, 4.0f);
	glVertex3f(4.5f, 1.0f, 3.5f);
	glVertex3f(5.0f, 1.0f, 3.5f);
	glEnd();

	//Leg 4
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 4.0f, 4.0f);
	glVertex3f(-4.5f, 4.0f, 4.0f);
	glVertex3f(-4.5f, 4.0f, 3.5f);
	glVertex3f(-5.0f, 4.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 4.0f, 4.0f);
	glVertex3f(-4.5f, 4.0f, 4.0f);
	glVertex3f(-4.5f, 1.0f, 4.0f);
	glVertex3f(-5.0f, 1.0f, 4.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 4.0f, 3.5f);
	glVertex3f(-4.5f, 4.0f, 3.5f);
	glVertex3f(-4.5f, 1.0f, 3.5f);
	glVertex3f(-5.0f, 1.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 4.0f, 4.0f);
	glVertex3f(-5.0f, 1.0f, 4.0f);
	glVertex3f(-5.0f, 1.0f, 3.5f);
	glVertex3f(-5.0f, 4.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-4.5f, 4.0f, 4.0f);
	glVertex3f(-4.5f, 1.0f, 4.0f);
	glVertex3f(-4.5f, 1.0f, 3.5f);
	glVertex3f(-4.5f, 4.0f, 3.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5.0f, 1.0f, 4.0f);
	glVertex3f(-4.5f, 1.0f, 4.0f);
	glVertex3f(-4.5f, 1.0f, 3.5f);
	glVertex3f(-5.0f, 1.0f, 3.5f);
	glEnd();

	glPopMatrix();

	rotAngle += .5;

	//---------------------------------------

	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);

	// Viewport 2: Right
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