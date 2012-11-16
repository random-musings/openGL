#include "stdafx.h"

Car::Car(void):
		rotation(),
		position(0,0,0),
		speed(0)
	{}


Car::~Car(void){}

Car::Car(Point startPosition):
	position(startPosition),
	rotation(0,0,0,1),
	speed(0)
	{}


void Car::moveX(float translateX)
{
	position = position + (rotation * Point(translateX,0,0));
}

void Car::moveY(float translateY)
{
	position.y = -translateY;
}

void Car::moveZ(float translateZ)
{
	if(translateZ!=0)
		cout <<" translateZ="<<translateZ<<endl;
	position = position + (rotation * Point(0,0,-translateZ));
}

void Car::rotateX(float degreesX)
{
	Quaternion nrot(Point(1.0,0.0,0.0), degreesX*PI/180);	
	rotation = rotation * nrot;
}
void Car::rotateY(float degreesY)
{
	Quaternion nrot(Point(0.0,1.0,0.0), degreesY*PI/180);	
	rotation = nrot * rotation ;
}

void Car::adjustSpeed(float speedModifier)
{
	speed +=speedModifier;
}


void Car::move()
{
 if (speed!=0)
	moveZ(speed);
}


float Car::getSpeed()
{
	return speed;
}


Point Car::getPosition()
{
	/*
	sfvec3d transform(sfvec3d p1){
	sfvec3d p2 = new sfvec3f();
	p2.x = w*w*p1.x + 2*y*w*p1.z - 2*z*w*p1.y + x*x*p1.x + 2*y*x*p1.y + 2*z*x*p1.z - z*z*p1.x - y*y*p1.x;
	p2.y = 2*x*y*p1.x + y*y*p1.y + 2*z*y*p1.z + 2*w*z*p1.x - z*z*p1.y + w*w*p1.y - 2*x*w*p1.z - x*x*p1.y;
	p2.z = 2*x*z*p1.x + 2*y*z*p1.y + z*z*p1.z - 2*w*y*p1.x - y*y*p1.z + 2*w*x*p1.y - x*x*p1.z + w*w*p1.z;
	return p2;
}
	*/
	return rotation.toPoint(position);
}
