#pragma once

typedef enum nodeState{OBSTACLE,EMPTY,GIFT,OPPONENT};

class MapNode
{
	enum nodeState state;
	Point location;
	GLfloat dimension;
	GLfloat hideRating;
	Point nodeIndex;

public:
	MapNode(void);
	MapNode(enum nodeState newState,
			Point newPoint,
			Point newMinPoints,
			Point newMaxPoints,
			float newSize,
			float newHideRating,
			Point newNodeIndex);
	~MapNode(void);


	Point minPts; //the bounding box minimums
	Point maxPts; //the bounding box maximums

	bool itemInNode(Obstacle item);
	bool itemInNode(Point item);
	void setBoundingBox(Point newMinPoints,Point newMaxPoints);
	void setSize(GLfloat newSize);
	void setLocation(Point newPoint);
	void setHideRating(GLfloat newHideRating);
	void setState(enum nodeState newState);

	GLfloat getSize();
	Point getLocation();
	GLfloat getHideRating();
	enum nodeState getState();
	Point getNodeIndex();
};
