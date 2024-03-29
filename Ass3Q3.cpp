#include <math.h>
#include <iostream>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdlib.h>
#include <unistd.h>
#include <png.h>
#include <cstdio>
#include "bmp.h"
//#include "glut.h"

using namespace std;

#define PI 3.14159265
GLfloat global_posImage = 0.6;

GLuint	texture[3];


void handleKeypress(unsigned char key, int x, int y) {    //The current mouse coordinates                                                                                  
        switch (key) {
                case 'q': //Escape key                                                                                                                                       
                  exit(0); //Exit the program                                                                                                                               
        }
}

AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

bool LoadGLTextures()									// Load Bitmaps And Convert To Textures
{
	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (!(TextureImage[0]=LoadBMP("bg.bmp")))
		return false;

	glGenTextures(1, &texture[0]);						// Create One Textures

	// Create MipMapped Texture
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

	if (TextureImage[0])								// If Texture Exists	
		delete TextureImage[0];							// destroy it
	return true;										// Return The Status
}


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

void drawCircle2(double posX, double posY, double radius)
{
	
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

/*

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

*/

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

void drawSpaceship(void){
	glColor3f(0.88,0.93,0.93);
	glBegin(GL_POLYGON);	
		glVertex2f(0.15,0);
		glVertex2f(0.05,0.07);
		glVertex2f(-0.05,0.13);
		glVertex2f(-0.15,0.18);
		glVertex2f(-0.25,0.22);
		glVertex2f(-0.35,0.23);
		glVertex2f(-0.45,0.22);
		glVertex2f(-0.55,0.21);
		
		glVertex2f(-0.55,-0.21);
		glVertex2f(-0.45,-0.22);
		glVertex2f(-0.35,-0.23);
		glVertex2f(-0.25,-0.22);
		glVertex2f(-0.15,-0.18);
		glVertex2f(-0.05,-0.13);
		glVertex2f(0.05,-0.07);
	glEnd();
	
	glColor3f(0.55,0.55,0.55);
	glBegin(GL_POLYGON);	
		
		glVertex2f(-0.35,0.23);
		glVertex2f(-0.55,0.21);
		glVertex2f(-0.65,0.3);
		glVertex2f(-0.48,0.3);
		
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(-0.35,-0.23);
		glVertex2f(-0.55,-0.21);
		glVertex2f(-0.65,-0.3);
		glVertex2f(-0.48,-0.3);
	glEnd();
	
	
	glColor3f(0.55,0.55,0.55);
	glBegin(GL_POLYGON);
		glVertex2f(-0.55,0.12);
		glVertex2f(-0.6,0.12);
		glVertex2f(-0.6,-0.12);
		glVertex2f(-0.55,-0.12);
	glEnd();
	
	//glColor3d(0.1,0.1,0.1);
	drawCircle2(-0.3,0,0.1);
	glColor3d(0.56,0.90,0.93);
	drawCircle2(-0.3,0,0.07);
	glColor3d(1,1,1);
	drawCircle2(-0.28,0.02,0.02);
	
}

void drawFire(){
	
	glColor3f(0.93,0.79,0);
	glBegin(GL_POLYGON);	
		glVertex2f(-0.6,0.1);
		glVertex2f(-0.8,0.2);
		glVertex2f(-0.75,0.1);
		glVertex2f(-0.9,0.15);
		glVertex2f(-0.8,0.05);
		
		glVertex2f(-0.95,0);
		
		glVertex2f(-0.8,-0.05);
		glVertex2f(-0.9,-0.15);
		glVertex2f(-0.75,-0.1);
		glVertex2f(-0.8,-0.2);
		glVertex2f(-0.6,-0.1);
	glEnd();
	
	glColor3f(0.8,0.07,0);
	glBegin(GL_POLYGON);	
		glVertex2f(-0.6,0.05);
		glVertex2f(-0.75,0.15);
		glVertex2f(-0.7,0.08);
		glVertex2f(-0.8,0.08);
		glVertex2f(-0.7,0.03);
		
		glVertex2f(-0.84,0);
		
		glVertex2f(-0.7,-0.03);
		glVertex2f(-0.8,-0.08);
		glVertex2f(-0.7,-0.08);
		glVertex2f(-0.75,-0.15);
		glVertex2f(-0.6,-0.05);
	glEnd();
	
	
	
}

void printAsteroid(double offset_x)
{
	// Sets the body of the asteroid	
	glColor3f(0.8,0.5,0.2);
	glBegin(GL_POLYGON);
		glVertex2f(0.45 + offset_x, 0);
		glVertex2f(0.45 + offset_x, 0.1);
		glVertex2f(0.5 + offset_x, 0.2);
		glVertex2f(0.6 + offset_x, 0.3);
		glVertex2f(0.6 + offset_x, 0.5);
		glVertex2f(0.7 + offset_x, 0.6);
		glVertex2f(0.8 + offset_x, 0.6);
		glVertex2f(0.85 + offset_x, 0.4);
		glVertex2f(0.9 + offset_x, 0.1);
		glVertex2f(0.95 + offset_x, -0.1);
		glVertex2f(0.9 + offset_x, -0.4);
		glVertex2f(0.85 + offset_x, -0.55);
		glVertex2f(0.75 + offset_x, -0.6);
		glVertex2f(0.625 + offset_x, -0.5);
		glVertex2f(0.55 + offset_x, -0.4);
		glVertex2f(0.525 + offset_x, -0.2);
		glVertex2f(0.475 + offset_x, -0.2);
	glEnd();
}

void printBackground(){
	glBindTexture(GL_TEXTURE_2D, texture[0]);			// use our texture
	glBegin(GL_QUADS);
		glVertex2f(-1,-1);
		glVertex2f(1,-1);
		glVertex2f(1,1);
		glVertex2f(-1,1);
	glEnd();
	
	
}

void display(void)
{	
	glClearColor(0.0, 0.0, 0.0, 1.0);	// Set the background color	
	glClear (GL_COLOR_BUFFER_BIT);		// Clear the buffer color
		
			
	glLoadIdentity();			// Load the identity matrix to reset our drawing

	//drawCircle(1.0,1.0,0.0, global_posImage, 0.7, 0.2);	// (r,g,b,x, y,rad)
	printAsteroid(global_posImage);
	// Spaceship
	// fire
	drawSpaceship();
	drawFire();

	//printGrid();
	glFlush();
	
	
	// Animation of the asteroid
	global_posImage = global_posImage - 0.001;
	usleep(1);
        if (global_posImage < -2.4)
        {
                global_posImage = 0.6;
        }
	
	glutPostRedisplay();
}


int main (int argc, char **argv) 
{	
	
	
	glutInit(&argc, argv);	//Initialize glut
	glutInitDisplayMode(GLUT_SINGLE);	// Sets up basic display buffer
	if (!LoadGLTextures())								// Jump To Texture Loading Routine
		return false;	
	glutInitWindowSize(800, 600);	// Set the width and the height of the window
	glutInitWindowPosition(100, 100);	// Set the position of the window
	
	glutCreateWindow("Le chef-d'oeuvre, par Tamarack et TonySpark");	// Create the window
		
	glutDisplayFunc(display);
	glutKeyboardFunc(handleKeypress);
	glutMainLoop();	// Infinite loop so that window stays open

}
