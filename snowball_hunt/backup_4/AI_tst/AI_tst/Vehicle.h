#pragma once

class Vehicle :
	public Obstacle
{
	GLUquadric *siren;
	int damage;
	int maxDamage;
	bool isAlive;
	bool collisionOccurs;
	Point displacement;
	int strikeRange;

public:
	Vehicle(void);
	Vehicle(GLuint newName,
			Point newOrigin,
			Point newSize,
			float newMaxDamage,
			int newStrikeRange,
			Point newDisplacement);

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

	void setStrikeRange(int newStrikeRange);
	int getStrikeRange();

	void setCollision(bool newCollisionOccurs);

	float shadowX,shadowY,shadowZ;
};
