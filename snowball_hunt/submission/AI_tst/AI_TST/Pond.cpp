#include "stdafx.h"

Pond::Pond(void)
{
}

Pond::Pond(
		Point newPosition,
		GLuint newName,
		GLfloat newPondRadius,
		GLfloat newPondHeight
		):Obstacle(newName,newPosition,Point(newPondRadius,newPondHeight,newPondRadius),Point(0,0,0),true,0),
		pondRadius(newPondRadius),
		pondHeight(newPondHeight),
		pond(0)
{}

Pond::~Pond(void)
{
}



void Pond::display(GLuint marbleTexture,GLuint waterTexture)
{
	if (pond==0)
	{
		pond = gluNewQuadric();
		gluQuadricNormals(pond, GLU_SMOOTH);
		gluQuadricTexture (pond,GLU_TRUE);
	}

	glPushMatrix();
	glLoadName(getName());
	glTranslatef(getOrigin().x,getOrigin().y,getOrigin().z);
	glRotatef(90,1,0,0);
	glBindTexture(GL_TEXTURE_2D,marbleTexture);
	gluCylinder(pond,pondRadius,pondRadius+pondRadius*0.1,pondHeight, pondRadius*3,pondRadius*3);
	glBindTexture(GL_TEXTURE_2D,waterTexture);
	gluDisk(pond,0,pondRadius,pondRadius*3,pondRadius*3);
	glPopMatrix();
}