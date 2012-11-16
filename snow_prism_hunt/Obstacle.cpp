#include "stdafx.h"

	Obstacle::Obstacle()
			:name(0),
			origin(0,0,0),
			velocity(0,0,0),
			spaceDimensions(0,0,0),
			visible(true),
			listID(0)
	{}

	Obstacle::Obstacle(GLuint newName, 
				Point newOrigin,
				Point newSpaceDimensions,
				Point newVelocity, 
				bool newVisibility,
				GLuint newListID)
			:name(newName),
			origin(newOrigin),
			velocity(newVelocity),
			spaceDimensions(newSpaceDimensions),
			visible(newVisibility),
			listID(newListID),
			minX(newOrigin.x-newSpaceDimensions.x),
			maxX(newSpaceDimensions.x+newOrigin.x),
			minY(newOrigin.y-newSpaceDimensions.y),
			maxY(newSpaceDimensions.y+newOrigin.y),
			minZ(newOrigin.z-newSpaceDimensions.z),
			maxZ(newSpaceDimensions.z+newOrigin.z)
	{}

	Obstacle::~Obstacle()
	{}

	Point Obstacle::getSpaceDimensions(){return spaceDimensions;}
	Point Obstacle::getOrigin()			{return origin;}
	Point Obstacle::getVelocity()		{return velocity;}
	GLuint Obstacle::getName()			{return name;}
	bool Obstacle::getVisibility()		{return visible;}
	GLuint Obstacle::getListId()		{return listID;}
	
	void Obstacle::setOrigin(Point newOrigin){origin = newOrigin;
			setBoundingBox(	origin.x-spaceDimensions.x,
						origin.x+spaceDimensions.x,
						origin.y-spaceDimensions.y,
						origin.y+spaceDimensions.y,
						origin.z-spaceDimensions.z,
						origin.x+spaceDimensions.z);
				}
	void Obstacle::setVelocity(Point newVelocity){velocity = newVelocity;}
	void Obstacle::setName(GLuint newName){name = newName;}
	void Obstacle::setVisibility(bool newVisibility) { visible = newVisibility;}
	void Obstacle::setListId(GLuint newListId){listID = newListId;}
	void Obstacle::setSpaceDimensions(Point newSpaceDimensions)	
	{	spaceDimensions = newSpaceDimensions;
		setBoundingBox(	origin.x-spaceDimensions.x,
						origin.x+spaceDimensions.x,
						origin.y-spaceDimensions.y,
						origin.y+spaceDimensions.y,
						origin.z-spaceDimensions.z,
						origin.x+spaceDimensions.z);
	}


	GLfloat Obstacle::getBoundingRadius()
	{
		//calculate bounding shape (a circle) for this shape based on spaceDImensions;
		return abs(spaceDimensions.x-origin.x)<abs(spaceDimensions.y)-origin.y?
							abs(spaceDimensions.y-origin.y)<abs(spaceDimensions.z)-origin.z?
							abs(spaceDimensions.z)-origin.z:spaceDimensions.y-origin.y:spaceDimensions.x-origin.x;
	}

	void Obstacle::display()
	{
		if(listID>0)
			glCallList(listID);
	}


vector<Point> Obstacle::calculateTextureCoords(vector<Point> shape)
	{
		vector<Point> textureCoords;
		GLfloat lowestX, highestX;
		GLfloat lowestY, highestY;
		GLfloat lowestZ, highestZ;

		getRange(shape,lowestX, highestX,
				lowestY,  highestY,
				lowestZ,  highestZ);
		GLfloat rangeX = abs(lowestX - highestX);
		GLfloat rangeY = abs(lowestY - highestY);
		GLfloat rangeZ = abs(lowestZ - highestZ);

		for(int i=0;i<(int)shape.size();i++)
		{
			GLfloat texX = rangeX==0?0:(shape[i].x-lowestX)/rangeX;
			GLfloat texY = rangeY==0?0:(shape[i].y-lowestY)/rangeY;
			GLfloat texZ = rangeZ==0?0:(shape[i].z-lowestZ)/rangeZ;
			if (rangeX==0)
				textureCoords.push_back(Point(texZ,texY,0));
			else if (rangeY==0)
				textureCoords.push_back(Point(texX,texZ,0));
			else if (rangeZ ==0)
				textureCoords.push_back(Point(texX,texY,0));
			else
				textureCoords.push_back(Point(texX,texY,texZ));
		}
		return textureCoords;
	}


void Obstacle::getRange(vector<Point> shape, GLfloat &lowestX, GLfloat &highestX,
							GLfloat &lowestY, GLfloat &highestY,
							GLfloat &lowestZ, GLfloat &highestZ)
	{

		for(int i=0;i<(int) shape.size();i++)
		{
			if (i==0)
			{
				lowestX  =shape[i].x; lowestY = shape[i].y; lowestZ = shape[i].z; 
				highestX =shape[i].x; highestY = shape[i].y; highestZ = shape[i].z; 
			}else
			{
				lowestX = lowestX>shape[i].x?shape[i].x:lowestX;
				lowestY = lowestY>shape[i].y?shape[i].y:lowestY;
				lowestZ = lowestZ>shape[i].z?shape[i].z:lowestZ;

				highestX = highestX<shape[i].x?shape[i].x:highestX;
				highestY = highestY<shape[i].y?shape[i].y:highestY;
				highestZ = highestZ<shape[i].z?shape[i].z:highestZ;
			}
		}
	}


float Obstacle::getDistanceFromObject(Obstacle testObj)
{
	float distance = ( sqrt( (testObj.getOrigin().x-getOrigin().x)*(testObj.getOrigin().x-getOrigin().x) +
			 (testObj.getOrigin().y-getOrigin().y)*(testObj.getOrigin().y-getOrigin().y) +
			  (testObj.getOrigin().z-getOrigin().z)*(testObj.getOrigin().z-getOrigin().z) ));
	return distance;
}

float Obstacle::getDistanceFromObject(Point testObj)
{
	float distance = ( sqrt((testObj.x-getOrigin().x)*(testObj.x-getOrigin().x) +
			(testObj.y-getOrigin().y)*(testObj.y-getOrigin().y) +
			(testObj.z-getOrigin().z)*(testObj.z-getOrigin().z) ));
	return distance;
}

bool Obstacle::objectWithinRadius(Obstacle testObj)
{
 float actualDistance= getDistanceFromObject(testObj.getOrigin());
	if( actualDistance < (spaceDimensions.x ) &&
		actualDistance < (spaceDimensions.y ) &&
		actualDistance < (spaceDimensions.z ) )
		return true;

	return objectWithinBoundingBox(testObj);
}

//test if object is within BoundingBox
bool Obstacle::objectWithinBoundingBox(Obstacle testObj)
{
	if (   (testObj.getOrigin().x>=minX && testObj.getOrigin().x<=maxX)
		&& (testObj.getOrigin().y>=minY && testObj.getOrigin().y<=maxY)
		&& (testObj.getOrigin().z>=minZ && testObj.getOrigin().z<=maxZ))
	{ 
			return true;
	}
	return false;
}


void Obstacle::setBoundingBox(float newMinX,float newMaxX,
						float newMinY,float newMaxY,
						float newMinZ,float newMaxZ)
{
	minX = newMinX;
	minY = newMinY;
	minZ = newMinZ;
	maxX = newMaxX;
	maxY = newMaxY;
	maxZ = newMaxZ;
}

void Obstacle::setMinY(float newMinY){ minY = newMinY;}
void Obstacle::setMinX(float newMinX){ minX = newMinX;}
void Obstacle::setMinZ(float newMinZ){ minZ = newMinZ;}
void Obstacle::setMaxY(float newMaxY){ maxY = newMaxY;}
void Obstacle::setMaxX(float newMaxX){ maxX = newMaxX;}
void Obstacle::setMaxZ(float newMaxZ){ maxZ = newMaxZ;}

float Obstacle::getMinY(){return minY;}
float Obstacle::getMinX(){return minX;}
float Obstacle::getMinZ(){return minZ;}
float Obstacle::getMaxY(){return maxY;}
float Obstacle::getMaxX(){return maxX;}
float Obstacle::getMaxZ(){return maxZ;}


