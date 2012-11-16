#pragma once

class Particle:public Obstacle
{
	int jitterRange;	//how far to veer off course with each step (a percentage of the max velocity assigned to the particle)
	int jitterIx;		//how long to allow particle to veer off course before correct
    GLfloat jitter;		//the randomly generated value (constrained by jitterRange)
	Point direction;	//the overal direction that particles should flow (zero or 1 for each value)
	Point startRange;	//the range between Starting points (the origin in the obstacle class will be the centre)
	Point endRange;		//if the particles origin falls outside of the range then reset the particle
	float size;
	GLUquadric *particle;
	float angle;
	float radius;
	float radiusIncr;
	float heightIncr;
	float particleInnerRadius;
	float particleOuterRadius;

	public: 

	Particle();	
	Particle(	GLuint newName,
				Point newDirection,
				Point newStartRange,
				Point newEndRange,
				float newSize,
				GLfloat jitterRange,
				float newInnerRadius,
				float newOuterRadius);
	~Particle();

	void advance();
	void display(GLuint texture);
	void reset(bool firstTimeThrough);
	bool objectWithinRadius(Obstacle testObj);	

};
