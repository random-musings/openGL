#include "stdafx.h"

SnowMountain::SnowMountain(void)
{
}

SnowMountain::SnowMountain(	
				GLuint newName, 
				Point newOrigin,
				Point newDimensions):
					Obstacle(newName,newOrigin,newDimensions,Point(0,0,0),true,0),
					{}

SnowMountain::~SnowMountain(void)
{
}



void SnowMountain::display(GLuint texture)
{
	glPushMatrix();
	glTranslatef(getOrigin().x,getOrigin().y,getOrigin().z);
	glBindTexture(GL_2D_TEXTURE,texture);
	glBegin(GL_POLYGON);//build path
	glEnd();

	glPopMatrix();

}