#pragma once

class Car
{
		Quaternion rotation;
		Point position;
		float speed;
public:
	Car(void);
	Car(Point startPosition);

	~Car(void);

	void moveX(float translateX);
	void moveY(float translateY);
	void moveZ(float translateZ);

	void rotateX(float degreesX);
	void rotateY(float degreesY);
	void rotateZ(float degreesZ);
	void adjustSpeed(float speedModifier);
	float getSpeed();
	void move();
	Point getPosition();

};
