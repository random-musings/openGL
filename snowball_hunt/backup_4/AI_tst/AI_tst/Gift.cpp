#include "stdafx.h"

Gift::Gift(void):size(1),found(false)
{
}

Gift::~Gift(void)
{
}


Gift::Gift(Point newPosition,
		GLuint newName,
		GLfloat newSize) 
		:Obstacle(newName,newPosition,Point(newSize,newSize,newSize),Point(0,0,0),true,0),
		size(newSize),
		found(false)
{}


	void Gift::display()
	{
		if( !getVisibility())
			return;

	glEnable(GL_COLOR_MATERIAL);
		glLoadName(getName());
		glPushMatrix();
		glBegin(GL_TRIANGLE_FAN);     	// draw triangle
			  glColor4f(1.0f,0.0f,0.0f,1.0f);                	// set color to red
			  glVertex3f(  getOrigin().x, getOrigin().y, getOrigin().z);
			  glColor4f(0.0f,1.0f,0.0f,1.0f);                	// set color to green
			  glVertex3f(getOrigin().x-size,  getOrigin().y-3.0f*size, getOrigin().z+size);
			  glColor4f(1.0f,1.0f,0.0f,1.0f);                	// set color to yellow
			  glVertex3f(getOrigin().x+ size,  getOrigin().y-3.0f*size, getOrigin().z+size);
			  glColor4f(0.0f,0.0f,1.0f,1.0f);                	// set color to blue
			  glVertex3f(getOrigin().x+ size,  getOrigin().y-3.0f*size, getOrigin().z-size);
			  glColor4f(1.0f,1.0f,1.0f,1.0f);                	// set color to white
			  glVertex3f(getOrigin().x -size,  getOrigin().y-3.0f*size, getOrigin().z-size);
			  glColor4f(0.0f,1.0f,0.0f,1.0f);                	// set color to green
			  glVertex3f(getOrigin().x-size,  getOrigin().y-3*size, getOrigin().z+size);
		   glEnd();
	   glPopMatrix();
	 	glLoadName(0);//remove item from stack

	}

void Gift::setFound(bool newFound)
{
	found = newFound;
	setVisibility(!found);
}

bool Gift::isFound()
{ return found;}
