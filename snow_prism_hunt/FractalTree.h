#pragma once


float getRand(int lower, int upper);

class branch3D
{

public:
		Point endPoint1; //two bounding boxes for every cylinder
		Point endPoint2; //two bounding boxes for every cylinder
		Point position;
		float angleX;
		float angleY;
		float height;
		float width;
		int depth;
		GLuint textureID;
		branch3D():position(0,0,0),angleX(0),angleY(0),textureID(0),height(0),width(0),depth(0){}
		branch3D(float newHeight,float newWidth,Point newPosition,float newAngleX,float newAngleY,GLuint newTextureID,int newDepth, Point newEndPoint1,Point newEndPoint2):
				height(newHeight),width(newWidth),position(newPosition),angleX(newAngleX),angleY(newAngleY),textureID(newTextureID),depth(newDepth),endPoint1( newEndPoint1),endPoint2(newEndPoint2)
				{
				Point temp  = endPoint1;
				}
}; //end of 3dtree class


class FractalTree:public Obstacle
{
	vector<BoundingPts> boundingBoxes;
	GLUquadric *branchQuad;
	Point position;
	GLuint textureID;
	GLfloat maxDepth;
	GLfloat branchHeight;
	GLfloat trunkWidth;
	GLfloat reductionPct; //amount to reduce the trunk width and the branch length as levels are added.
	bool randomAngles;	//if true then the branches will be created via random angles
	GLfloat fixedAngle; //if randomAngle=false then use a fixed set of angles
	GLuint listId;
	

	branch3D getNextTier(branch3D branch, float newAngleX, float newAngleY,float newHeight,float newWidth);
	void draw3DBranch(branch3D branch);
	void create3dTree(branch3D branch,int currDepth);

	void genTree();

	bool collisionOverTree; //this variable indicates if vehicle over the fractal tree at the time of collision
							//or if user under fractal tree at time of collision
public:
	FractalTree(void);
	FractalTree(
		Point newPosition,
		GLuint newName,
		GLfloat newMaxDepth,
		GLfloat newBranchHeight,
		GLfloat newTrunkWidth,
		GLuint newTextureId,
		GLfloat newReductionPct=0.75, //amount to reduce the trunk width and the branch length as levels are added.
		bool newRandomAngles=true,	//if true then the branches will be created via random angles
		GLfloat newFixedAngle=-45 );//if randomAngle=false then use a fixed set of angles

	~FractalTree(void);

	void setTextureId(GLuint newTextureId);
	GLuint getTextureId();

	void display();
	void adjustAngles(float Max,float Min,float &Incr);
	bool objectWithinBoundingBox(Obstacle testObj); //indicates if vehicle collides with tree
	bool isCollisionOverBranches();
	void setAboveBelowLimbs(Obstacle testObj);
	void setFixedAngle(float newAngle);
};


