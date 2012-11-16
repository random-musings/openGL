#include "stdafx.h"

Vehicle::Vehicle(void)
{
}

Vehicle::Vehicle(GLuint newName,
				 Point newOrigin,
				 Point newSize,
				 float newMaxDamage):
				Obstacle(newName,
					newOrigin,
					newSize,
					Point(0,0,0),
					true,0),
					maxDamage(newMaxDamage)
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
		Point Centroid=getOrigin();
		float height = getSpaceDimensions().y;
		float width = getSpaceDimensions().x;
		float depth = getSpaceDimensions().z;
		vector<Point> displayPoints;
		vector<Point> textureCoords;
		glPushMatrix();

		// **********CHANGE FOR OVEHEAD
		if (overHeadView)
		{
			glTranslatef(0,-45,0);
			glTranslatef(getOrigin().x,getOrigin().y,getOrigin().z);
		}else
			glLoadIdentity();
		
		//Light/Siren on Vehicle
		if (siren==0)
		{
			siren= gluNewQuadric();
			gluQuadricNormals(siren, GLU_SMOOTH);
			gluQuadricTexture (siren,GLU_TRUE);			
		}

	if(firstPersonMode)
	{
		glPopMatrix();
		glTranslatef(0,-4,0);
		return;
	}
		
	glColor4f(1,1,1,0.9);

	if(!overHeadView)
	{
		glTranslatef(8,-24,-8);
	}
	else
		glTranslatef(-getOrigin().x,getOrigin().y,-getOrigin().z);

	if (collisionOccurs)
	{ //shake
		glTranslatef(0.5,0.5,-0.5);
		//draw pieces flying off
		glPushMatrix();
		glTranslatef(getOrigin().x,getOrigin().y+2*height,getOrigin().z);
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

	//draw siren
	float lightEmissive[]={1.0,1.0,1.0};
	glMaterialfv(GL_FRONT, GL_EMISSION,lightEmissive);
	glTranslatef(getOrigin().x,getOrigin().y+height,getOrigin().z);
	glBindTexture(GL_TEXTURE_2D,txtSiren);
	gluSphere(siren,height/4, 20,20);
	float lightEmissive2[]={0.0,0.0,0.0};
	glMaterialfv(GL_FRONT, GL_EMISSION,lightEmissive2);
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
