#include "stdafx.h"

#ifndef PI
#define PI 3.1415972
#endif

#define DEG_TO_RAD(x) x * PI /180
#define RAD_TO_DEG(x) x * PI /180

FractalTree::FractalTree(void)
{
}

FractalTree::FractalTree( 
	Point newPosition,
	GLuint newName,
	GLfloat newMaxDepth,
	GLfloat newBranchHeight,
	GLfloat newTrunkWidth,
	GLuint newTextureId,
	GLfloat newReductionPct, //amount to reduce the trunk width and the branch length as levels are added.
	bool newRandomAngles,	//if true then the branches will be created via random angles
	GLfloat newFixedAngle) //if randomAngle=false then use a fixed set of angles
	:Obstacle(newName, 
				newPosition,
				Point(cos(DEG_TO_RAD(45))*newMaxDepth*newBranchHeight, //the buffer to give the treefor collision
					   cos(DEG_TO_RAD(45))*newMaxDepth*newBranchHeight,//calculations
					   cos(DEG_TO_RAD(45))*newMaxDepth*newBranchHeight),
				Point(0,0,0)), //velocity
				position(newPosition),
				maxDepth(newMaxDepth),
				branchHeight(newBranchHeight),
				trunkWidth(newTrunkWidth),
				reductionPct(newReductionPct),
				randomAngles(newRandomAngles),
				fixedAngle(newFixedAngle),
				textureID(newTextureId)

	{
		float incr=0;
		branchQuad=0;
		genTree();
		adjustAngles(0,0,incr);
	}

FractalTree::~FractalTree(void)
{
	gluDeleteQuadric(branchQuad);
}



void FractalTree::genTree()
{
	if(branchQuad==0)
	{
		branchQuad = gluNewQuadric();
		gluQuadricNormals(branchQuad, GLU_SMOOTH);
		gluQuadricTexture (branchQuad,GLU_TRUE);
	}

	//setListId(glGenLists(1));
	//GLint listif=getListId();
	//glNewList(getListId(),GL_COMPILE);
	glPushMatrix();
	glLoadName(getName());
	glTranslatef(position.x,position.y,position.z);
	create3dTree(branch3D(branchHeight,
							trunkWidth,
							Point(0,0,0),
							90,
							0,
							textureID,
							0,
							position,
							Point(position.x,position.y+branchHeight,position.z)),0);
	glPopMatrix();
	//glEndList();
}

float getRand(int lower, int upper)
{
	int tmp =abs(rand())*1000;
	return (tmp % (upper-lower) +lower);
}

branch3D FractalTree::getNextTier(branch3D branch, float newAngleX, float newAngleY,float newHeight,float newWidth)
{
	Point nextPoint(0,0,0);

	//move to end of branch
	if(branch.angleX!=0 && branch.depth>=2)
		nextPoint =Point( cos(DEG_TO_RAD(-branch.angleX))*branch.height,sin(DEG_TO_RAD(-branch.angleX))*branch.height,0);

	//move to end of branch
	if(branch.angleY!=0 && branch.depth>=2)
	{
		nextPoint.z=branch.angleY>0?nextPoint.x:-nextPoint.x;
		nextPoint.x=0;
		nextPoint.y += cos(DEG_TO_RAD(branch.angleY))*branch.height;
	}
	

	return branch3D(newHeight,
					newWidth,
					branch.position+ nextPoint,
					newAngleX,
					newAngleY,
					branch.textureID,
					branch.depth+1,
					branch.endPoint1,
					branch.endPoint2);
}

void FractalTree::draw3DBranch(branch3D branch)
{
	if (branchQuad==0)
	{
		branchQuad = gluNewQuadric();
		gluQuadricNormals(branchQuad, GLU_SMOOTH);
		gluQuadricTexture (branchQuad,GLU_TRUE);
	}

	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,branch.textureID);
		glTranslatef(branch.position.x,branch.position.y,branch.position.z);	
		glRotatef(branch.angleY,0,1,0);		
		glRotatef(branch.angleX,1,0,0);		
		gluCylinder(branchQuad,branch.width,branch.width,branch.height, 6,6);
	glPopMatrix();

}

void FractalTree::create3dTree(branch3D branch,int currDepth)
{


	draw3DBranch(branch);
	if (currDepth==maxDepth)
		return;
	int theDepth = currDepth+1;

	create3dTree(getNextTier(branch,fixedAngle,90,branchHeight*0.3,trunkWidth*reductionPct),theDepth);
	create3dTree(getNextTier(branch,fixedAngle,-90,branchHeight*0.3,trunkWidth*reductionPct),theDepth);
	create3dTree(getNextTier(branch,180-fixedAngle,0,branchHeight*0.3,trunkWidth*reductionPct),theDepth);
	create3dTree(getNextTier(branch,fixedAngle,0,branchHeight*0.3,trunkWidth*reductionPct),theDepth);	
}

void FractalTree::display()
{
	//glCallList(getListId());
	//reset the bounding box so that we can get generate a new bounding box
	genTree();

}


void FractalTree::setTextureId(GLuint newTextureId)
{
	textureID = newTextureId;
}

GLuint FractalTree::getTextureId()
{
	return textureID;
}

void FractalTree::adjustAngles(float Max,float Min,float &Incr)
{
	if(fixedAngle>=Max ||  fixedAngle<=Min) //if max and we were going up
		Incr = -Incr;
	fixedAngle +=Incr;
}



bool FractalTree::objectWithinBoundingBox(Obstacle testObj)
{
	float y_variation = abs(sin(DEG_TO_RAD(fixedAngle)) )* branchHeight*1.1;//;* (maxDepth-1) * branchHeight/2);
	float radius = (cos(DEG_TO_RAD(fixedAngle))*branchHeight/2 * (maxDepth-1));
	float distance = sqrt( (getOrigin().x - testObj.getOrigin().x)*(getOrigin().x - testObj.getOrigin().x) + (getOrigin().z - testObj.getOrigin().z)*(getOrigin().z - testObj.getOrigin().z));

	if(distance< 5)
	{
			setAboveBelowLimbs(testObj);
			return true;
	}
	return Obstacle::objectWithinBoundingBox(testObj);
}


void 	FractalTree::setAboveBelowLimbs(Obstacle testObj)
{
	if ( abs(testObj.getOrigin().y- getMinY())< (testObj.getOrigin().y-getMaxY() ))
		collisionOverTree=false;
	else 
		collisionOverTree=true;
}


bool FractalTree::isCollisionOverBranches()
{
	return collisionOverTree;
}


void FractalTree::setFixedAngle(float newAngle)
{
	fixedAngle=newAngle;
}
