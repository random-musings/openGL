#pragma once

class Pond:public Obstacle
{
	GLUquadric *pond;
	GLfloat pondRadius;
	
public:
	Pond(void);
	Pond(
		Point newPosition,
		GLuint newName,
		GLfloat newPondRadius
		);

	~Pond(void);
	void display(GLuint marbleTexture,GLuint waterTexture);
};
