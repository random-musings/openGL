#pragma once
#include "obstacle.h"

class SnowMountain :
	public Obstacle
{

public:
	SnowMountain(void);
	SnowMountain(GLuint newName,
				Point newOrigin);

	~SnowMountain(void);

	void display(GLuint texture);
};
