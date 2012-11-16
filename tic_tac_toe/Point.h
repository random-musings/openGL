#ifndef POINT_H
#define POINT_H


class Point
{

	public:	
	GLfloat x;
	GLfloat y;
	GLfloat z;

	Point();
	Point(GLfloat ptX,GLfloat ptY,GLfloat ptZ);		//Create a Point in space
	~Point();
	const Point operator +(Point ptIncr);	//Increment the Coordinates
	const Point operator -(Point ptDecr);	//decerement the Coordinates
	const Point operator *(Point multiplier);	//decerement the Coordinates

	void setPoints(GLfloat newX,GLfloat newY, GLfloat newZ);

	bool operator ==(Point ptDecr);	//decerement the Coordinates
	bool operator !=(Point ptDecr);	//decerement the Coordinates
	friend std::ostream& operator <<(ostream &out_stream, const Point& pt); //print out the Coordinates
	
};
#endif