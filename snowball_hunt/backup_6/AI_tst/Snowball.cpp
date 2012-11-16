#include "stdafx.h"

Snowball::Snowball(void):
			minCoords(Point(0,0,0)),
			maxCoords(Point(0,0,0)),
			damage(0),
			gravity(0),
			airFriction(0),
			txtSnow(0),
			destination(Point(0,0,0)),
			circle(0),
			crashed(false),
			stageCrashed(0)

{
}

Snowball::Snowball(	GLuint newName,
					Point newOrigin, //startPoint
					Point newDestination,// endPoint
					float newSize,
					float newSpeed, //speed at which the snowball flies through the air
					Point newMinCoords, //the coords that the snowball will crash and dissolve
					Point newMaxCoords,
					int newDamage,
					float newGravity,
					float newAirFriction,
					GLuint newTexture): //the coords that the snowball will crash and dissolve
					Obstacle(newName,
								newOrigin,
								Point(newSize,newSize,newSize),
								Point(0,0,0),
								true,
								0),
								minCoords(newMinCoords),
								maxCoords(newMaxCoords),
								damage(newDamage),
								gravity(newGravity),
								airFriction(newAirFriction),
								txtSnow(newTexture),
								destination(newDestination),
								circle(0),
								crashed(false),
								stageCrashed(0)
					{
						setSpeed(newSpeed);
						setVelocity(calculateSnowballVelocity());
					}

Snowball::~Snowball(void)
{
}


//calculate the velocity of the snowball based on the start and end points and the gravity,air friction
Point Snowball::calculateSnowballVelocity()
{
	Point newVelocity = makeUnitVector(destination-getOrigin());
	newVelocity.x = newVelocity.x*getSpeed();
	newVelocity.z = newVelocity.z*getSpeed();
	newVelocity.y =0;  //add enough of an incrment so that the gravity is offset
		//get number of steps then add that many 
	return newVelocity;
}


float Snowball::getAirFriction(){return airFriction;}
void Snowball::setAirFriction(float newAirFriction){airFriction= newAirFriction;}

float Snowball::getGravity(){return gravity;}
void Snowball::getGravity(float newGravity){gravity = newGravity;}

Point Snowball::getMinCoords(){return minCoords;}
void Snowball::setMinCoords(Point newMinCoords){minCoords = newMinCoords;}

Point Snowball::getMaxCoords(){return maxCoords;}
void Snowball::setMaxCoords(Point newMaxCoords){maxCoords =newMaxCoords;}

int Snowball::getDamage(){return damage;}
void Snowball::setDamage(int newDamage){damage= newDamage;}

void Snowball::display()
{
	if (circle==0)
	{
		circle = gluNewQuadric();
		gluQuadricTexture(circle,GL_TRUE);
		gluQuadricNormals(circle,GL_SMOOTH);
	}

	if(!crashed)
	{
		glPushMatrix();
		glColor4f(1,1,1,1);
		glTranslatef(getOrigin().x,getOrigin().y,getOrigin().z);
		glBindTexture(GL_TEXTURE_2D,txtSnow);
		gluSphere(circle,getSpaceDimensions().x,getSpaceDimensions().x*3,getSpaceDimensions().x*3);
		glPopMatrix();
	}else
	{
		glPushMatrix();
		glColor4f(0.7,0.7,0.7,1);
		glTranslatef(getOrigin().x,getOrigin().y,getOrigin().z);
		glBindTexture(GL_TEXTURE_2D,txtSnow);
		gluSphere(circle,getSpaceDimensions().x/2,getSpaceDimensions().x,getSpaceDimensions().x);
		glTranslatef(getSpaceDimensions().x/2,0,0);
		gluSphere(circle,getSpaceDimensions().x/4,getSpaceDimensions().x,getSpaceDimensions().x);
		glTranslatef(-getSpaceDimensions().x/3,2*getSpaceDimensions().y,0);
		gluSphere(circle,getSpaceDimensions().x/4,getSpaceDimensions().x,getSpaceDimensions().x);
		glTranslatef(-getSpaceDimensions().x/3,2*getSpaceDimensions().y,-getSpaceDimensions().z*2);
		gluSphere(circle,getSpaceDimensions().x/8,getSpaceDimensions().x,getSpaceDimensions().x);
		glPopMatrix();
		setSpeed(getSpeed()*0.1);
		stageCrashed++;
	}
	if (stageCrashed>30)
	{
		setVisibility(false);
	}
}



void Snowball::setCrashed(bool newCrashed)
{
	crashed = newCrashed;
}

bool Snowball::getCrashed()
{
	return crashed;
}

void Snowball::setStageCrashed(int newStageCrashed)
{
	stageCrashed = newStageCrashed;
}

int Snowball::getStageCrashed()
{
	return stageCrashed;
}