#pragma once


class Snowball :
	public Obstacle
{
	GLUquadric *circle;
	GLuint txtSnow; //the snowball of the texture
	float gravity;   //coefficient to determine the vertical degredation of the snowballs path.
	float airFriction; //coefficient to determine the degradation the the snowballs horizontal path
	int damage;

	Point minCoords; //the point at which the snowball smashes into the floor/walls and distintgrates
	Point maxCoords; //the point at which the snowball smashes into the floor/walls and distintgrates

	Point destination;
	bool crashed;
	int stageCrashed;
public:
	Snowball(void);
	Snowball(	GLuint newName,
					Point newOrigin, //startPoint
					Point newDestination,// endPoint
					float newSize,
					float newSpeed, //speed at which the snowball flies through the air
					Point newMinCoords, //the coords that the snowball will crash and dissolve
					Point newMaxCoords,
					int newDamage,
					float newGravity,
					float newAirFriction,
					GLuint newTexture);

	~Snowball(void);

	void display();

	float getAirFriction();
	void setAirFriction(float newAirFriction);

	float getGravity();
	void getGravity(float newGravity);

	Point getMinCoords();
	void setMinCoords(Point newMinCoords);

	Point getMaxCoords();
	void setMaxCoords(Point newMaxCoords);
	
	int getDamage();
	void setDamage(int newDamage);

	Point calculateSnowballVelocity();

	void setCrashed(bool newCrashed);
	bool getCrashed();

	void setStageCrashed(int newStageCrashed);
	int getStageCrashed();
};
