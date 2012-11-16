#pragma once

class Pond:public Obstacle
{
	GLUquadric *pond;
	GLfloat pondRadius;
	GLfloat pondHeight;
	
public:
	Pond(void);
	Pond(
		Point newPosition,
		GLuint newName,
		GLfloat newPondRadius,
		GLfloat newPondHeight
		);

	~Pond(void);
	void display(GLuint marbleTexture,GLuint waterTexture);
};
