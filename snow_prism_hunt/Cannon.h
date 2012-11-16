#pragma once


class Cannon :
	public Obstacle
{

Vector<CannonBalls>
GLUquadric *cannon;

GLuint cannonBallTexureId;
GLuint cannonTexureId;

public:
	Cannon(void);
	~Cannon(void);
};
