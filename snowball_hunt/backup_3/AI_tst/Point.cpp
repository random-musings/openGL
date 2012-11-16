#include "stdafx.h"


//Create a Point
Point::Point()
{
	x =0;
	y =0;
}


//Create a point with specific coordinates
Point::Point(GLfloat ptX, GLfloat ptY,GLfloat ptZ)
{
	x =ptX;
	y =ptY;
	z =ptZ;
}

//Destructor
Point::~Point()
{

}

//Overload the operator + so that we can 
//incremenet the coordinates using another point
const Point Point::operator +(Point ptIncr)
{
	Point newPoint(x,y,z);
	newPoint.x = x + ptIncr.x;
	newPoint.y = y + ptIncr.y;
	newPoint.z = z + ptIncr.z;
	return newPoint;
}

//Overload the operator - so that we can
//increment the coordinates using another point
const Point Point::operator -(Point ptDecr)
{
	Point newPoint =*this;
	newPoint.x =x - ptDecr.x;
	newPoint.y =y - ptDecr.y;
	newPoint.z =z - ptDecr.z;
	return newPoint;
}

bool Point::operator ==(Point ptCompare)
{
	if( x == ptCompare.x && y == ptCompare.y && z == ptCompare.z)
	{return true;}
	return false;
}
bool Point::operator !=(Point ptCompare)
{
	if( x == ptCompare.x && y == ptCompare.y && z == ptCompare.z)
	{return false;}
	return true;
}
const Point Point::operator *(Point multiplier)
{
	Point newPoint = *this;
	newPoint.x = multiplier.x*x;
	newPoint.y = multiplier.y*y;
	newPoint.z = multiplier.z*z;
	return newPoint;
}

//overload the operator<< so that we print out point coordinates
//to an outstream
ostream& operator<<(ostream& out_stream,const Point& pt)
{
	out_stream<<"("<<pt.x<<","<<pt.y<<","<<pt.z<<")"<<" ";
	return out_stream;
}


void 	Point::setPoints(GLfloat newX,GLfloat newY, GLfloat newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}
