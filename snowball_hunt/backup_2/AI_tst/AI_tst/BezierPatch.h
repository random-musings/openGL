#pragma once

#define levelOfDetail 20

class BezierPatch:public Obstacle
{

	BoundingPts boundingBoxes[levelOfDetail];
	Point Points[4][4];//the control points
	float ctlPoints[levelOfDetail][levelOfDetail][3];
	float polyStripPoints[levelOfDetail*levelOfDetail][4][3];
	float polyStripNormals[levelOfDetail*levelOfDetail][4][3];
	bool showPoints;

	void resetMesh();
	void resetVertices();

	Point CalculateU(float t,int row);
	Point CalculateV(float t,Point* pnts) ;
	Point Calculate(float u,float v); 
	void calculateBezierTextureCoords();
	void setBoundingBoxes();

public:
	BezierPatch(void);
	BezierPatch(GLuint newName, 
				Point newOrigin);
	~BezierPatch(void);


	void display(GLuint texture);
	void setShowPoints(bool newShowPoints);
	void resetPoints();
	void resetPoints(float newCtlPoints[4][4][3]);
	bool objectWithinBoundingBox(Obstacle testObj);
	void setBoundingBoxes(int boxIx, Point newMinPoints, Point newMaxPoints);
	void setBoundingBoxes(float buffer);
};
