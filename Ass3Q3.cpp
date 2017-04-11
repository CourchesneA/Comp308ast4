#include <math.h>
#include <iostream>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdlib.h>
#include <unistd.h>

using namespace std;

#define PI 3.14159265
GLfloat global_posImage = 1.5;

void ground(void)
{
	glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
                glVertex3f(-1.0, -1.0, 0.0);
                glVertex3f(-1.0, -0.5, 0.0);
                glVertex3f(1.0, -0.5, 0.0);
                glVertex3f(1.0, -1.0, 0.0);


        glEnd();

}

/*
Draws circle

@param R , Red color
@param G , Green color
@param B, Blue color
@param posX, x position of the middle of the circle
@param posY, y position of the middle of the circle
*/
void drawCircle(double R, double G, double B, double posX, double posY, double radius)
{
	glColor3f(R, G, B);
	
	glBegin(GL_TRIANGLE_FAN);
	
		for (int counterDegree = 0; counterDegree < 360; counterDegree++)
		{
			double angle = 2*PI * counterDegree/360;
			double x = posX + (((cos(angle) * radius)/800)*600);
			double y = posY + sin(angle) * radius;
			glVertex2f(x,y);
		}
	glEnd();
}

void drawEmptyCircle(double R, double G, double B, double posX, double posY, double radius)
{
        glColor3f(R, G, B);

	/*	
	GLfloat lineWidthRange[2];
	glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
	glLineWitdh(lineWidthRange[1]);	
	*/

        glBegin(GL_LINE_STRIP);
//		glLineWitdh(thickness);
                for (int counterDegree = 0; counterDegree < 360; counterDegree++)
                {
                        double angle = 2*PI * counterDegree/360;
                        double x = posX + (((cos(angle) * radius)/800)*600);
                        double y = posY + sin(angle) * radius;
                        glVertex2f(x,y);
                }
        glEnd();
}


void printGrid(void)
{
	
	// x lines 
	for (double counter = -1; counter < 10; counter = counter + 0.1)
	{
		glColor3f(1, 1, 1); 
		glBegin(GL_LINE_STRIP);
			 glVertex2f(-1.0,counter);
			 glVertex2f(1.0, counter);
		glEnd();
	}

	// y lines 
        for (double counter = -1; counter < 1.0; counter = counter + 0.1)
        {
                glColor3f(1, 1, 1);
                glBegin(GL_LINE_STRIP);
                         glVertex2f(counter,-1.0);
                         glVertex2f(counter, 1.0);
                glEnd();
        }
	

}

void sunRays(void)
{
	
	glColor3f(1.0, 1.0, 0);
        glBegin(GL_LINE_STRIP);
		glVertex2f(0.4,0.7);
      		glVertex2f(0.7, 0.7);
      	glEnd();

        glColor3f(1.0, 1.0, 0);
        glBegin(GL_LINE_STRIP);          
                glVertex2f(1.0,0.7);
                glVertex2f(0.7, 0.7);
        glEnd();

	glColor3f(1.0, 1.0, 0);
        glBegin(GL_LINE_STRIP);
                glVertex2f(0.7,1.0);
                glVertex2f(0.7, 0.7);
        glEnd();

        glColor3f(1.0, 1.0, 0);
        glBegin(GL_LINE_STRIP);          
                glVertex2f(0.7,0.35);
                glVertex2f(0.7, 0.7);
        glEnd();

        glColor3f(1.0, 1.0, 0);
        glBegin(GL_LINE_STRIP);          
                glVertex2f(0.7,0.7);
                glVertex2f(0.9, 0.4);
        glEnd();

        glColor3f(1.0, 1.0, 0);
        glBegin(GL_LINE_STRIP);          
                glVertex2f(0.5,1.0);
                glVertex2f(0.7, 0.7);
        glEnd();

        glColor3f(1.0, 1.0, 0);
        glBegin(GL_LINE_STRIP);          
                glVertex2f(0.5,0.4);
                glVertex2f(0.7, 0.7);
        glEnd();

}

void drawLine(double x1, double y1, double x2, double y2)
{
	glColor3f(0.0, 0.0, 0);
        glBegin(GL_LINE_STRIP);
                glVertex2f(x1,y1);
                glVertex2f(x2, y2);
        glEnd();

	glColor3f(0.0, 0.0, 0);
        glBegin(GL_LINE_STRIP);
                glVertex2f(x1+0.001,y1+0.001);
                glVertex2f(x2 + 0.001, y2 + 0.001);
        glEnd();

	glColor3f(0.0, 0.0, 0);
        glBegin(GL_LINE_STRIP);
                glVertex2f(x1 - 0.001,y1 - 0.001);
                glVertex2f(x2 - 0.001, y2 - 0.001);
        glEnd();

}

void stickFigure(void)
{
	drawCircle(0,0,0,0.2,0,0.1);         // Head of the figure
	drawLine(0.2,0,0.225, -0.4);		// Body

	drawLine(0.225,-0.4, 0.250, -0.55);	// Legs
	drawLine(0.250,-0.55, 0.3, -0.7);
	drawLine(0.225,-0.4, 0.15, -0.55);
	drawLine(0.15, -0.55, 0.15, -0.7);
	
	drawLine(0.21,-0.125,0.280, -0.2);	// Left Arm
	drawLine(0.280, -0.2, 0.31, -0.3);

	drawLine(0.21,-0.125,0.14, -0.22);	// Right arm
	drawLine(0.14, -0.22, 0.06, -0.25);	

}

void drawRectangle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double R, double G, double B)
{
	glColor3f(R, G, B);

	glBegin(GL_QUADS);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);		
		glVertex2f(x4, y4);
	glEnd();
	
}

void house(void)
{
	drawRectangle(-1, -0.7,-1, 0.1, -0.3, 0.1, -0.3, -0.7, 0.5, 0, 0);	// house
	glColor3f(1,0,0);
	glBegin(GL_TRIANGLES);	// Roof
		glVertex2f(-1, 0.1);
		glVertex2f( -0.65, 0.6);
		glVertex2f( -0.3, 0.1);
	glEnd();
	drawRectangle(-0.6, -0.7, -0.6, -0.2, -0.4, -0.2, -0.4, -0.7, 0.66, 0.66, 0.66);	// door
	drawRectangle(-0.9, -0.2, -0.7, -0.2, -0.7, -0.4, -0.9, -0.4, 0.11, 0.564, 1);	// Window

}

void display(void)
{	
	glClearColor(0.0, 0.0, 0.0, 1.0);	// Set the background color	
	glClear (GL_COLOR_BUFFER_BIT);		// Clear the buffer color
		
			
	glLoadIdentity();			// Load the identity matrix to reset our drawing

	drawCircle(1.0,1.0,0.0, global_posImage, 0.7, 0.2);	// (r,g,b,x, y,rad)
	// Asteroid
	// Spaceship
	// fire

	sunRays();
	stickFigure();		// Draw the figure
	house();			// Draw the house
	printGrid();
	glFlush();
	
	
	// Animation of the asteroid
	global_posImage = global_posImage - 0.001;

	usleep(1);
        if (global_posImage < -1.5)
        {
                global_posImage = 1.5;
        }
	
	glutPostRedisplay();

}


int main (int argc, char **argv) 
{	

	
	glutInit(&argc, argv);	//Initialize glut
	glutInitDisplayMode(GLUT_SINGLE);	// Sets up basic display buffer

	glutInitWindowSize(800, 600);	// Set the width and the height of the window
	glutInitWindowPosition(100, 100);	// Set the position of the window
	
	glutCreateWindow("Le chef-d'oeuvre, par Samuel Beaubien et titolepro");	// Create the window
		
	glutDisplayFunc(display);
	
	glutMainLoop();	// Infinite loop so that window stays open


	





}
