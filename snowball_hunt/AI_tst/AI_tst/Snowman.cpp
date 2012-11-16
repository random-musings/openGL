#include "stdafx.h"

Snowman::Snowman(void)
{
	snowman = 0;
}

Snowman::~Snowman(void)
{
		gluDeleteQuadric(snowman);
}


 Snowman::Snowman(
				Point newPosition,
				GLuint newName,
				GLfloat newSize,
				GLuint newTxtSnow,
				GLuint newTxtCarrot,
				GLuint newTxtButtons)
				:Obstacle(newName, 
							newPosition,
							Point(newSize,newSize,newSize), //the maximum depth space
							Point(0,0,0)), //velocity
				size(newSize),
				txtSnow(newTxtSnow),
				bodySnowballPct(1),
				torsoSnowballPct(0.6666666),
				headSnowballPct(0.3333333),
				featuresSnowballPct(0.0666666),
				txtCarrot(newTxtCarrot),
				txtButtons(newTxtButtons)
{
		setSpaceDimensions( Point(
			bodySnowballPct*size*1, //width
			bodySnowballPct*size*3, //height
			bodySnowballPct*size*1) //depth
			);
		
			snowman = 0;

}


void Snowman::setSize(GLfloat newSize) 
{
	size= newSize; 		
	setSpaceDimensions( Point(
		bodySnowballPct*size, //width
		bodySnowballPct*size+ torsoSnowballPct*size+headSnowballPct*size, //height
		bodySnowballPct*size) //depth
	);
}
void Snowman::setTexture(GLuint newTxtSnow){txtSnow = newTxtSnow;}
void Snowman::setBodySnowballPct(GLfloat newBodySnowballPct)
{
	bodySnowballPct = newBodySnowballPct;
	setSpaceDimensions( Point(
		bodySnowballPct*size, //width
		bodySnowballPct*size+ torsoSnowballPct*size+headSnowballPct*size, //height
		bodySnowballPct*size) //depth
	);
}

void Snowman::setTorsoSnowballPct(GLfloat newTorsoSnowballPct)
{
	torsoSnowballPct =newTorsoSnowballPct;
	setSpaceDimensions( Point(
		bodySnowballPct*size, //width
		bodySnowballPct*size+ torsoSnowballPct*size+headSnowballPct*size, //height
		bodySnowballPct*size) //depth
	);
}

void Snowman::setHeadSnowballPct(GLfloat newHeadSnowballPct)
{
	headSnowballPct =newHeadSnowballPct;
	setSpaceDimensions( Point(
		bodySnowballPct*size, //width
		bodySnowballPct*size+ torsoSnowballPct*size+headSnowballPct*size, //height
		bodySnowballPct*size) //depth
	);
}

void Snowman::setFeaturesSnowballPct(GLfloat newFeatureSnowballPct){featuresSnowballPct =newFeatureSnowballPct;}

GLfloat Snowman::getSize(){return size;}
GLuint Snowman::getSnowTexture(){return txtSnow;}
GLfloat Snowman::getBodySnowballPct(){return bodySnowballPct;}
GLfloat Snowman::getTorsoSnowballPct(){return torsoSnowballPct;}
GLfloat Snowman::getHeadSnowballPct(){return headSnowballPct;}
GLfloat Snowman::getFeaturesSnowballPct(){return featuresSnowballPct;}


void Snowman::display(void)
{
	if (snowman==0)
		snowman = gluNewQuadric();
	GLfloat featureSize= size*featuresSnowballPct;
	GLfloat bodySize= size*bodySnowballPct;
	GLfloat torsoSize= size*torsoSnowballPct;
	GLfloat headSize= size*headSnowballPct;

	//setListId(glGenLists(1));
	//glNewList(getListId(),GL_COMPILE_AND_EXECUTE);
		glPushMatrix();
		gluQuadricNormals(snowman, GLU_SMOOTH);
		gluQuadricTexture (snowman,GLU_TRUE);
		glBindTexture(GL_TEXTURE_2D,txtSnow);

		//move to snowman location
		glTranslatef(getOrigin().x,getOrigin().y,getOrigin().z);

		//snowballs
		gluSphere(snowman,bodySize,10,20);
		glTranslatef(0,bodySize,0);
		gluSphere(snowman,torsoSize,20,10);
		glTranslatef(0,torsoSize,0);
		gluSphere(snowman,headSize,20,20);

		//Face
		glBindTexture(GL_TEXTURE_2D,txtCarrot);
		glPushMatrix();
		glTranslatef(0,0,headSize);
		gluCylinder(snowman,featureSize,0.01,headSize,10,10); //nose

		glBindTexture(GL_TEXTURE_2D,txtButtons);
		glTranslatef(-featureSize,.1,0);	
		gluSphere(snowman,featureSize,20,20);	//eyes
		glTranslatef(featureSize*2,0,0);
		gluSphere(snowman,featureSize,20,20); //eyes
		glPopMatrix();

		//Buttons
		glTranslatef(0,-torsoSize/2,torsoSize);
		gluSphere(snowman,featureSize,20,20);
		glTranslatef(0,-featureSize*3,0);
		gluSphere(snowman,featureSize,20,20);
		glTranslatef(0,-featureSize*3,0);
		gluSphere(snowman,featureSize,20,20);
		glPopMatrix();
		
	//glEndList();

}
