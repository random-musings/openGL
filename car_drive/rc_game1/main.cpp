#include<windows.h>


#include<gl\gl.h>
#include<gl\glu.h>
#include<glut.h>
#include <iostream>
using namespace std;

#include "readBMP.h"

GLuint texName[2];

GLfloat modelViewMatrix[16];
int floorW, floorL;
GLubyte *floor;
int wallW, wallH;
GLubyte *wall;

void worldCube()
{

	// back
//	glColor3f(0,0,1);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 
                0, GL_BGR_EXT, GL_UNSIGNED_BYTE, wall);
		glBegin(GL_POLYGON);
		glTexCoord2f( 0, 0 );
		glVertex3f( -50, -50, -50 );
		glTexCoord2f( 1, 0 );
		glVertex3f(  50, -50, -50 );
		glTexCoord2f( 1, 1 );
		glVertex3f(  50,  50, -50 );
		glTexCoord2f( 0, 1 );
		glVertex3f( -50,  50, -50 );
	glEnd();

	//bottom. 
	   glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 
                0, GL_BGR_EXT, GL_UNSIGNED_BYTE, floor);
	glBegin(GL_POLYGON);
		glTexCoord2f( 0, 0 );
		glVertex3f( -50, -50,  50 );
		glTexCoord2f( 0, 1 );
		glVertex3f(  50, -50,  50 );
		glTexCoord2f( 1, 1 );
		glVertex3f(  50, -50, -50 );
		glTexCoord2f( 1, 0 );
		glVertex3f( -50, -50, -50 );
	glEnd();

	//right
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 
                0, GL_BGR_EXT, GL_UNSIGNED_BYTE, wall);
	glColor3f(0,1,1);
	glBegin(GL_POLYGON);
		glTexCoord2f( 0, 0 );
		glVertex3f(  50, -50, -50 );
		glTexCoord2f( 1, 0 );
		glVertex3f(  50, -50,  50 );
		glTexCoord2f( 1, 1 );
		glVertex3f(  50,  50,  50 );
		glTexCoord2f( 0, 1 );
		glVertex3f(  50,  50, -50 );
	glEnd();

//left
	glColor3f(1,1,0);
	glBegin(GL_POLYGON);
		glTexCoord2f( 0, 0 );
		glVertex3f(  -50, -50,  50 );
		glTexCoord2f( 1, 0 );
		glVertex3f(  -50, -50, -50 );
		glTexCoord2f( 1, 1 );
		glVertex3f(  -50,  50, -50 );
		glTexCoord2f( 0, 1 );
		glVertex3f(  -50,  50,  50 );
	glEnd();

	//top
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
		glVertex3f(  -50,  50, -50 );
		glVertex3f(   50,  50, -50 );
		glVertex3f(   50,  50,  50 );
		glVertex3f(  -50,  50,  50 );
	glEnd();


	// front
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
		glTexCoord2f( 0, 0 );
		glVertex3f(  50, -50, 50 );
		glTexCoord2f( 1, 0 );
		glVertex3f( -50, -50, 50 );
		glTexCoord2f( 1, 1 );
		glVertex3f( -50,  50, 50 );
		glTexCoord2f( 0, 1 );
		glVertex3f(  50,  50, 50 );
	glEnd();

}

int W, H;
const GLfloat worldX = 100; // 4.5 feet x 12 inches per foot 
const GLfloat worldY = 100; // 9   feet x 12 inches per foot 

void 
reshape(int w, int h)
{
    W = w;
    H = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glFrustum(-worldX/8, worldX/8, -worldY/8, worldY/8, 24.0f, 8000.0f);
	glFrustum(-worldX/8, worldX/8, -worldY/8, worldY/8,24.0f, 8000.0f);
    glMatrixMode(GL_MODELVIEW);
}


GLfloat D=0;
GLfloat T = -100;
GLfloat dir = -1;

void 
display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadMatrixf( modelViewMatrix );
		worldCube();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void 
update()
{
	D+=0.01f;
	if ( D >= 360 )
		D=0;
	if ( T <= -200 )
		dir = +1;
	if ( T > -100 )
		dir = -1;
	T += dir*0.01;

	display();
}
void translate( GLfloat x, GLfloat y, GLfloat z )
{
	GLfloat transform[16];
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glTranslatef( x, y, z );
		glGetFloatv( GL_MODELVIEW_MATRIX, transform );
		glLoadMatrixf( modelViewMatrix );
		glMultMatrixf( transform );
		glGetFloatv( GL_MODELVIEW_MATRIX, modelViewMatrix );
	glPopMatrix();
}

void specialChar( int key, int x, int y )
{
//	cout <<"special char " << key << " " << GLUT_KEY_UP << endl;
	switch( key )  {
		case GLUT_KEY_UP:
			translate( 0,0,10);
			display();
			break;
		case GLUT_KEY_DOWN:
			translate( 0,0,-10);
			display();
			break;
	}
}



void keyBoard( unsigned char, int x, int y )
{}


void initializeGraphics()
{
	// read textures
	bool t1, t2;
	floor = NULL;
	t1 = readBmp( "ground.bmp", floorW, floorL, floor);
	wall = NULL;
	t2 = readBmp( "side.bmp", wallW,  wallH,  wall );
	if ( t1 && t2 )  
		cout << "fine" << floorW << " " << floorL << " " << wallH << " " << wallW << endl;
	if ( floor == NULL || wall == NULL )
		cout << "Null pointer" << endl;
    glClearColor (0.0f, 0.6f, 0.0f, 0.0f);
	glEnable( GL_DEPTH_TEST );
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();     // save the modelviewMatrix
		glLoadIdentity();
		glTranslatef(0,30,-200);
		glGetFloatv( GL_MODELVIEW_MATRIX, modelViewMatrix );  // save MY copy in modelViewMatrix
	glPopMatrix();     // restore it
 
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

}

void main(int argc, char** argv)
{
	W = 250; H = 250;

	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    int windowHandle = glutCreateWindow("Program 2");
    glutSetWindow(windowHandle);
    glutPositionWindow ( 100, 100 );
    glutReshapeWindow( W, H );
	initializeGraphics();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutSpecialFunc( specialChar );
	glutKeyboardFunc( keyBoard );
              	
    glutMainLoop();


}
