#pragma once

class Vehicle :
	public Obstacle
{
	GLUquadric *siren;
	int damage;
	int maxDamage;
	bool isAlive;
	bool collisionOccurs;
public:
	Vehicle(void);
	Vehicle(GLuint newName,
			Point newOrigin,
			Point newSize,
			float newMaxDamage);

	~Vehicle(void);

	void display(Point translateToThirdPerson,
				GLuint txtSiren,
				GLuint txtCar,
				bool firstPersonMode,
				bool overHeadView);

	bool getIsAlive();
	void setIsAlive(bool newIsAlive);

	void applyDamage(int newDamage);
	void setDamage(int newDamage);
	int getDamage();

	void setMaxDamage(int newMaxDamage);
	int getMaxDamage();


	void setCollision(bool newCollisionOccurs);
};
