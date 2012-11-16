#pragma once

#define MAX_POINTS 24
#define NORMAL_POINTS 6
class Gift :
	public Obstacle
{

	float size;
	bool found;
public:
	Gift(void);

	Gift(Point newPosition,
		GLuint newName,
		GLfloat newSize
		);

	~Gift(void);

	void setFound(bool newFound);
	bool isFound();
	void display();
};
