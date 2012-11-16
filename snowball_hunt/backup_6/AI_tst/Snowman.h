#pragma once


class Snowman :
	public Obstacle
{
	GLfloat size;
	GLuint txtSnow;
	GLuint txtCarrot;
	GLuint txtButtons;
	GLUquadric *snowman;
	
	GLfloat bodySnowballPct;
	GLfloat torsoSnowballPct;
	GLfloat headSnowballPct;
	GLfloat featuresSnowballPct;

public:
	Snowman(void);

	Snowman(
		Point newPosition,
		GLuint newName,
		GLfloat newSize,
		GLuint newTxtSnow,
		GLuint newTxtCarrot,
		GLuint newTxtButtons);

	~Snowman(void);

	void setSize(GLfloat newSize);
	void setTexture(GLuint newTxtSnow);

	GLfloat getBodySnowballPct();
	GLfloat getTorsoSnowballPct();
	GLfloat getHeadSnowballPct();
	GLfloat getFeaturesSnowballPct();

	void setBodySnowballPct(GLfloat newBodySnowballPct);
	void setTorsoSnowballPct(GLfloat newTorsoSnowballPct);
	void setHeadSnowballPct(GLfloat newHeadSnowballPct);
	void setFeaturesSnowballPct(GLfloat newFeaturesSnowballPct);


	GLfloat getSize();
	GLuint getSnowTexture();



	void display(void);
};


