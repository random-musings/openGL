#include "stdafx.h"

Vehicle::Vehicle(void):
	maxDamage(0),
	strikeRange(0),
	damage(0),
	displacement(Point(0,0,0))
{
}

Vehicle::Vehicle(GLuint newName,
				 Point newOrigin,
				 Point newSize,
				 float newMaxDamage,
				 int newStrikeRange,
				 Point newDisplacement):
				Obstacle(newName,
					newOrigin,
					newSize,
					Point(0,0,0),
					true,0),
					maxDamage(newMaxDamage),
					strikeRange(newStrikeRange),
					damage(0),
					displacement(newDisplacement)
				{}



Vehicle::~Vehicle(void)
{
}


void Vehicle::display(
				Point translateToThirdPerson,//this point brings the car into View in first and third person mode
 				GLuint txtSiren,
				GLuint txtCar,
				bool firstPersonMode,
				bool overHeadView
				)
{

		int currName = getName();
		Point Centroid=displacement;//this is the coordinates to make the player visibl while in 3rd person mode
		Centroid.y=0;
		//vehicleOrigin(-27,5,-8);
		float height = getSpaceDimensions().y;
		float width = getSpaceDimensions().x;
		float depth = getSpaceDimensions().z;
		vector<Point> displayPoints;
		vector<Point> textureCoords;
	
	glPushMatrix();
	glLoadIdentity();
	glColor4f(1,1,1,0.9);

	glTranslatef(displacement.x,displacement.y,displacement.z);

	if (collisionOccurs)
	{ //shake
		glTranslatef(0.5,0.5,-0.5);
		//draw pieces flying off
		glPushMatrix();
		glTranslatef(displacement.x,0,displacement.z);
		glEnable(GL_COLOR_MATERIAL);
		glColor4f(0,0,0,1);

		glBegin(GL_TRIANGLES);
		glVertex3f(Centroid.x-2*height,Centroid.y+2.5*height,Centroid.z);
		glVertex3f(Centroid.x-2.1*height,Centroid.y+2.5*height,Centroid.z+height);
		glVertex3f(Centroid.x-2*height,Centroid.y+2.8*height,Centroid.z+height);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(Centroid.x-2*height,Centroid.y+height,Centroid.z);
		glVertex3f(Centroid.x-2.1*height,Centroid.y+1.5*height,Centroid.z);
		glVertex3f(Centroid.x-2*height,Centroid.y+1.8*height,Centroid.z+height);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(Centroid.x+height,Centroid.y+height,Centroid.z);
		glVertex3f(Centroid.x+height,Centroid.y+1.5*height,Centroid.z);
		glVertex3f(Centroid.x+height,Centroid.y+1,Centroid.z+height);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(Centroid.x+height,Centroid.y+1.8*height,Centroid.z);
		glVertex3f(Centroid.x,Centroid.y+1.5*height,Centroid.z-0.5*height);
		glVertex3f(Centroid.x+height,Centroid.y+2*height,Centroid.z);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(Centroid.x,Centroid.y+1,Centroid.z);
		glVertex3f(Centroid.x+2*height,Centroid.y+2*height,Centroid.z);
		glVertex3f(Centroid.x,Centroid.y+1,Centroid.z);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(Centroid.x-2*height,Centroid.y+2*height,Centroid.z);
		glVertex3f(Centroid.x-2*height,Centroid.y+1.5*height,Centroid.z);
		glVertex3f(Centroid.x-height,Centroid.y+2*height,Centroid.z);
		glEnd();

		glDisable(GL_COLOR_MATERIAL);
		glColor4f(1,1,1,1);

		glPopMatrix();
	}
	

	glBindTexture(GL_TEXTURE_2D,txtCar);

	float damageModifier=(float)damage/(float)maxDamage *2.5;
	
	//Draw Vehicle
	displayPoints.clear();
	textureCoords.clear();
	glLoadName(getName());
	displayPoints.push_back(Point(Centroid.x - width+damageModifier,  Centroid.y - height,  Centroid.z - depth));
	displayPoints.push_back(Point(Centroid.x + width,  Centroid.y - height+damageModifier,  Centroid.z - depth));
	displayPoints.push_back(Point(Centroid.x + width,  Centroid.y + height,  Centroid.z - depth));
	displayPoints.push_back(Point(Centroid.x - width,  Centroid.y + height,  Centroid.z - depth));
	textureCoords =calculateTextureCoords(displayPoints);
	displayShape(displayPoints,textureCoords);

	displayPoints.clear();
	textureCoords.clear();
	displayPoints.push_back(Point(Centroid.x - width+damageModifier,  Centroid.y - height,  Centroid.z + depth));
	displayPoints.push_back(Point(Centroid.x + width,  Centroid.y - height-+damageModifier,  Centroid.z + depth));
	displayPoints.push_back(Point(Centroid.x + width,  Centroid.y - height,  Centroid.z - depth));
	displayPoints.push_back(Point(Centroid.x - width,  Centroid.y - height,  Centroid.z - depth));
	textureCoords =calculateTextureCoords(displayPoints);
	displayShape(displayPoints,textureCoords);

	displayPoints.clear();
	textureCoords.clear();
	displayPoints.push_back(Point(Centroid.x + width,  Centroid.y - height,  Centroid.z - depth-damageModifier));
	displayPoints.push_back(Point(Centroid.x + width,  Centroid.y - height,  Centroid.z + depth-damageModifier));
	displayPoints.push_back(Point(Centroid.x + width,  Centroid.y + height,  Centroid.z + depth));
	displayPoints.push_back(Point(Centroid.x + width+damageModifier,  Centroid.y + height-damageModifier,  Centroid.z - depth));
	textureCoords =calculateTextureCoords(displayPoints);
	displayShape(displayPoints,textureCoords);

	displayPoints.clear();
	textureCoords.clear();
	displayPoints.push_back(Point(Centroid.x - width,  Centroid.y - height+damageModifier,  Centroid.z + depth));
	displayPoints.push_back(Point(Centroid.x - width+damageModifier,  Centroid.y - height+damageModifier,  Centroid.z - depth));
	displayPoints.push_back(Point(Centroid.x - width,  Centroid.y + height,  Centroid.z - depth+damageModifier));
	displayPoints.push_back(Point(Centroid.x - width,  Centroid.y + height,  Centroid.z + depth+damageModifier));
	displayShape(displayPoints,calculateTextureCoords(displayPoints));

	displayPoints.clear();
	textureCoords.clear();
	displayPoints.push_back(Point(Centroid.x - width,  Centroid.y + height,  Centroid.z - depth));
	displayPoints.push_back(Point(Centroid.x + width+damageModifier,  Centroid.y + height+damageModifier,  Centroid.z - depth));
	displayPoints.push_back(Point(Centroid.x + width+damageModifier,  Centroid.y + height+damageModifier,  Centroid.z + depth));
	displayPoints.push_back(Point(Centroid.x - width,  Centroid.y + height,  Centroid.z + depth));
	displayShape(displayPoints,calculateTextureCoords(displayPoints));

	displayPoints.clear();
	textureCoords.clear();
	displayPoints.push_back(Point(Centroid.x + width+damageModifier,  Centroid.y - height,  Centroid.z + depth));
	displayPoints.push_back(Point(Centroid.x - width+damageModifier,  Centroid.y - height,  Centroid.z + depth));
	displayPoints.push_back(Point(Centroid.x - width,  Centroid.y + height,  Centroid.z + depth));
	displayPoints.push_back(Point(Centroid.x + width,  Centroid.y + height,  Centroid.z + depth));
	displayShape(displayPoints,calculateTextureCoords(displayPoints));


glPopMatrix();
	collisionOccurs=false;
}





bool Vehicle::getIsAlive()
{ return isAlive;}

void Vehicle::setIsAlive(bool newIsAlive)
{ isAlive = newIsAlive;}

void Vehicle::applyDamage(int newDamage)
{
	damage +=newDamage;
	if( damage>=maxDamage)
	{
		setIsAlive(false);
	}
}

int Vehicle::getDamage()
{
	return damage;
}
void Vehicle::setDamage(int newDamage)
{
	damage = newDamage;
	if( damage>=maxDamage)
	{
		setIsAlive(false);
	}
}


void Vehicle::setMaxDamage(int newMaxDamage)
{
	maxDamage = newMaxDamage;
	if( damage>=maxDamage)
	{
		setIsAlive(false);
	}
}


int Vehicle::getMaxDamage()
{
	return maxDamage;
}


void Vehicle::setCollision(bool newCollisionOccurs)
{
	collisionOccurs = newCollisionOccurs;
}



void Vehicle::setStrikeRange(int newStrikeRange)
{
	strikeRange  = newStrikeRange;
}

int Vehicle::getStrikeRange(){return strikeRange;}
