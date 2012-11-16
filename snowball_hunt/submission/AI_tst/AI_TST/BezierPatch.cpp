#include "stdafx.h"


BezierPatch::BezierPatch(void)
	:showPoints(false)
{ 

}

BezierPatch::~BezierPatch(void)
{
}


BezierPatch::BezierPatch(
				GLuint newName, 
				Point newOrigin):
					Obstacle(newName,newOrigin,Point(0,0,0),Point(0,0,0),true,0),
						showPoints(false)
					{ 
					setBoundingBoxes();
					}


void BezierPatch::display(GLuint texture)
{
	glPushMatrix();
	glTranslatef(getOrigin().x,getOrigin().y,getOrigin().z);
	glBindTexture(GL_TEXTURE_2D,texture);
	//glColor4f(1,1,1,1);
	for(int i=0;i<levelOfDetail*levelOfDetail;i++)
	{
		glBegin(GL_POLYGON);
		glTexCoord3f(polyStripNormals[i][0][0],polyStripNormals[i][0][1],polyStripNormals[i][0][2]);
		glVertex3f(polyStripPoints[i][0][0],polyStripPoints[i][0][1],polyStripPoints[i][0][2]);
		glTexCoord3f(polyStripNormals[i][1][0],polyStripNormals[i][1][1],polyStripNormals[i][1][2]);
		glVertex3f(polyStripPoints[i][1][0],polyStripPoints[i][1][1],polyStripPoints[i][1][2]);
		glTexCoord3f(polyStripNormals[i][3][0],polyStripNormals[i][3][1],polyStripNormals[i][3][2]);
		glVertex3f(polyStripPoints[i][3][0],polyStripPoints[i][3][1],polyStripPoints[i][3][2]);
		glTexCoord3f(polyStripNormals[i][2][0],polyStripNormals[i][2][1],polyStripNormals[i][2][2]);
		glVertex3f(polyStripPoints[i][2][0],polyStripPoints[i][2][1],polyStripPoints[i][2][2]);
		glEnd();
	}
	glPopMatrix();
}

void BezierPatch::setShowPoints(bool newShowPoints)
{
	showPoints = newShowPoints;
}


void BezierPatch::resetPoints()
{
	  int u, v;
   for (u = 0; u < 4; u++) 
   {
      for (v = 0; v < 4; v++) 
	  {
         Points[u][v].x = 20.0*((GLfloat)u - 1.5);
         Points[u][v].y = 20.0*((GLfloat)v - 1.5);

         if ( (u == 1 || u == 2) && (v == 1 || v == 2))
           Points[u][v].z = 40.0;
         else
            Points[u][v].z = -30.0;
		 if ( ( u==2) && v==0)
			Points[u][v].z = 30.0;
		 if ( ( u==1) && v==0)
			Points[u][v].z = -30.0;
      }
   }    
   resetVertices();
   resetMesh();
	calculateBezierTextureCoords();
	setBoundingBoxes();

}

void BezierPatch::resetPoints(float newctlPoints[4][4][3])
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			Points[i][j].x=newctlPoints[i][j][0];
			Points[i][j].y=newctlPoints[i][j][1];
			Points[i][j].z=newctlPoints[i][j][2];
		}
	resetVertices();
	resetMesh();
	calculateBezierTextureCoords();
	setBoundingBoxes();
}



Point BezierPatch::CalculateU(float t,int row) {

	// the final point
	Point p;

	// the t value inverted
	float it = 1.0f-t;

	// calculate blending functions
	float b0 = t*t*t;
	float b1 = 3*t*t*it;
	float b2 = 3*t*it*it;
	float b3 =  it*it*it;

	// sum the effects of the Points and their respective blending functions
	p.x = b0*Points[row][0].x +
		  b1*Points[row][1].x +
		  b2*Points[row][2].x +
		  b3*Points[row][3].x ;

	p.y = b0*Points[row][0].y +
		  b1*Points[row][1].y +
		  b2*Points[row][2].y +
		  b3*Points[row][3].y ;

	p.z = b0*Points[row][0].z +
		  b1*Points[row][1].z +
		  b2*Points[row][2].z +
		  b3*Points[row][3].z ;

	return p;
}

// Having generated 4 points in the u direction, we need to
// use those points to generate the final point on the surface
// by calculating a final bezier curve in the v direction.
//     This function takes the temporary points and generates
// the final point for the rendered surface
//
Point BezierPatch::CalculateV(float t,Point* pnts) 
{
	Point p;

	// the t value inverted
	float it = 1.0f-t;

	// calculate blending functions
	float b0 = t*t*t;
	float b1 = 3*t*t*it;
	float b2 = 3*t*it*it;
	float b3 =  it*it*it;

	// sum the effects of the Points and their respective blending functions
	p.x = b0*pnts[0].x + 
		  b1*pnts[1].x + 
		  b2*pnts[2].x + 
		  b3*pnts[3].x ;

	p.y = b0*pnts[0].y + 
		  b1*pnts[1].y + 
		  b2*pnts[2].y + 
		  b3*pnts[3].y ;

	p.z = b0*pnts[0].z + 
		  b1*pnts[1].z + 
		  b2*pnts[2].z + 
		  b3*pnts[3].z ;

	return p;
}


//calculate all points/vertices in the bezier patch
Point BezierPatch::Calculate(float u,float v) {

	Point temp[4];	
	// calculate each point on our final v curve
	temp[0] = CalculateU(u,0);
	temp[1] = CalculateU(u,1);
	temp[2] = CalculateU(u,2);
	temp[3] = CalculateU(u,3);

	// final point
	return CalculateV(v,temp);
}



void BezierPatch::resetVertices()
{
	
	// use the parametric time value 0 to 1
	for(int i=0;i!=levelOfDetail;++i) 
	{
		// calculate the parametric u valueset
		float u = (float)i/(levelOfDetail-1);
		for(int j=0;j!=levelOfDetail;++j) 
		{
			// calculate the parametric v value
			float v = (float)j/(levelOfDetail-1);

			// calculate the point on the surface
			Point p = Calculate(u,v);
			ctlPoints[j][i][0]=p.x;
			ctlPoints[j][i][1]=p.y;
			ctlPoints[j][i][2]=p.z;			
		}
	}
}


void BezierPatch::resetMesh()
{
//rearrange the points into  a triangle strip
int tri_ix =0;
	for(int i=0;i<levelOfDetail-1;i++)
	{
		int j = 0;
		while ((j+1) <levelOfDetail-1)
		{
		//	cout <<" tri_Strip _"<<tri_ix<<" _ "<<ctlPoints[i][j][0]<<","<<ctlPoints[i][j][0]<<","<<ctlPoints[i][j][0]<<" _ " ;
		//	cout <<ctlPoints[i][j+1][0]<<","<<ctlPoints[i][j+1][1]<<","<<ctlPoints[i][j+1][2]<<" _ " ;
		//	cout <<ctlPoints[i+1][j][0]<<","<<ctlPoints[i+1][j][1]<<","<<ctlPoints[i+1][j][2]<<" _ " ;
		//	cout <<ctlPoints[i+1][j+1][0]<<","<<ctlPoints[i+1][j+1][1]<<","<<ctlPoints[i+1][j+1][2]<<endl ;
			polyStripPoints[tri_ix][0][0] =ctlPoints[i][j][0]; 
			polyStripPoints[tri_ix][0][1] =ctlPoints[i][j][1]; 
			polyStripPoints[tri_ix][0][2] =ctlPoints[i][j][2]; 

			polyStripPoints[tri_ix][1][0] =ctlPoints[i][j+1][0]; 
			polyStripPoints[tri_ix][1][1] =ctlPoints[i][j+1][1]; 
			polyStripPoints[tri_ix][1][2] =ctlPoints[i][j+1][2]; 

			polyStripPoints[tri_ix][2][0] =ctlPoints[i+1][j][0]; 
			polyStripPoints[tri_ix][2][1] =ctlPoints[i+1][j][1]; 
			polyStripPoints[tri_ix][2][2] =ctlPoints[i+1][j][2]; 

			polyStripPoints[tri_ix][3][0] =ctlPoints[i+1][j+1][0]; 
			polyStripPoints[tri_ix][3][1] =ctlPoints[i+1][j+1][1]; 
			polyStripPoints[tri_ix][3][2] =ctlPoints[i+1][j+1][2]; 
			j = j+1;
			tri_ix++; 
		}
	}
}

void BezierPatch::calculateBezierTextureCoords()
{
	for(int tri_ix=0;tri_ix<levelOfDetail*levelOfDetail;tri_ix++)
	{
		vector<Point> shape;
		shape.push_back(Point(polyStripPoints[tri_ix][0][0],polyStripPoints[tri_ix][0][1],polyStripPoints[tri_ix][0][2]));
		shape.push_back(Point(polyStripPoints[tri_ix][1][0],polyStripPoints[tri_ix][1][1],polyStripPoints[tri_ix][1][2]));
		shape.push_back(Point(polyStripPoints[tri_ix][3][0],polyStripPoints[tri_ix][3][1],polyStripPoints[tri_ix][3][2]));
		shape.push_back(Point(polyStripPoints[tri_ix][2][0],polyStripPoints[tri_ix][2][1],polyStripPoints[tri_ix][2][2]));
		vector<Point> textureCoords = calculateTextureCoords(shape);
		polyStripNormals[tri_ix][0][0] =shape[0].x; 
		polyStripNormals[tri_ix][0][1] =shape[0].y;
		polyStripNormals[tri_ix][0][2] =shape[0].z;

		polyStripNormals[tri_ix][1][0] =shape[1].x;
		polyStripNormals[tri_ix][1][1] =shape[1].y;
		polyStripNormals[tri_ix][1][2] =shape[1].z;

		polyStripNormals[tri_ix][2][0] =shape[2].x;
		polyStripNormals[tri_ix][2][1] =shape[2].y;
		polyStripNormals[tri_ix][2][2] =shape[2].z;

		polyStripNormals[tri_ix][3][0] =shape[3].x;
		polyStripNormals[tri_ix][3][1] =shape[3].y;
		polyStripNormals[tri_ix][3][2] =shape[3].z;
	}

}



//set the bounding boxes according to the default points
void BezierPatch::setBoundingBoxes()
{
	//scroll through all the points
	for(int i=0;i<levelOfDetail;i++)
	{
		//set the default min/max to the first Point
		boundingBoxes[i].minPoints = getOrigin() - Point( ctlPoints[i][0][0] , ctlPoints[i][0][1] , ctlPoints[i][0][2]);
		boundingBoxes[i].maxPoints = getOrigin() + Point( ctlPoints[i][0][0] , ctlPoints[i][0][1] , ctlPoints[i][0][2]);
		for(int j=1;j<levelOfDetail;j++)
		{
			boundingBoxes[i].minPoints.x = boundingBoxes[i].minPoints.x > getOrigin().x-ctlPoints[i][j][0] ? getOrigin().x- (float)ctlPoints[i][j][0]:boundingBoxes[i].minPoints.x;
			boundingBoxes[i].minPoints.y = boundingBoxes[i].minPoints.y > getOrigin().y-ctlPoints[i][j][1] ? getOrigin().y- (float)ctlPoints[i][j][1]:boundingBoxes[i].minPoints.y;
			boundingBoxes[i].minPoints.z = boundingBoxes[i].minPoints.z > getOrigin().z-ctlPoints[i][j][2] ? getOrigin().z- (float)ctlPoints[i][j][2]:boundingBoxes[i].minPoints.z;

			boundingBoxes[i].maxPoints.x = boundingBoxes[i].maxPoints.x < getOrigin().x + ctlPoints[i][j][0] ?getOrigin().x + (float)ctlPoints[i][j][0]:boundingBoxes[i].minPoints.x;
			boundingBoxes[i].maxPoints.y = boundingBoxes[i].maxPoints.y < getOrigin().y + ctlPoints[i][j][1] ?getOrigin().y + (float)ctlPoints[i][j][1]:boundingBoxes[i].minPoints.y;
			boundingBoxes[i].maxPoints.z = boundingBoxes[i].maxPoints.z < getOrigin().z + ctlPoints[i][j][2] ?getOrigin().z + (float)ctlPoints[i][j][2]:boundingBoxes[i].minPoints.z;
		}
	}
}


//set the bounding boxes according to the default points and a buffer
void BezierPatch::setBoundingBoxes(float buffer)
{
	//scroll through all the points
	for(int i=0;i<levelOfDetail;i++)
	{
		//set the default min/max to the first Point
		boundingBoxes[i].minPoints = getOrigin() + Point( ctlPoints[i][0][0]-buffer, ctlPoints[i][0][1]-buffer , ctlPoints[i][0][2]-buffer);
		boundingBoxes[i].maxPoints = getOrigin() + Point( ctlPoints[i][0][0]+buffer , ctlPoints[i][0][1]+buffer , ctlPoints[i][0][2]+buffer);
		for(int j=1;j<levelOfDetail;j++)
		{
			boundingBoxes[i].minPoints.x = boundingBoxes[i].minPoints.x > getOrigin().x+ctlPoints[i][j][0]-buffer ? getOrigin().x+ (float)ctlPoints[i][j][0]-buffer:boundingBoxes[i].minPoints.x;
			boundingBoxes[i].minPoints.y = boundingBoxes[i].minPoints.y > getOrigin().y+ctlPoints[i][j][1]-buffer ? getOrigin().y+ (float)ctlPoints[i][j][1]-buffer:boundingBoxes[i].minPoints.y;
			boundingBoxes[i].minPoints.z = boundingBoxes[i].minPoints.z > getOrigin().z+ctlPoints[i][j][2]-buffer ? getOrigin().z+ (float)ctlPoints[i][j][2]-buffer:boundingBoxes[i].minPoints.z;

			boundingBoxes[i].maxPoints.x = boundingBoxes[i].maxPoints.x < getOrigin().x + ctlPoints[i][j][0]+buffer ?getOrigin().x + (float)ctlPoints[i][j][0]+buffer:boundingBoxes[i].maxPoints.x;
			boundingBoxes[i].maxPoints.y = boundingBoxes[i].maxPoints.y < getOrigin().y + ctlPoints[i][j][1]+buffer ?getOrigin().y + (float)ctlPoints[i][j][1]+buffer:boundingBoxes[i].maxPoints.y;
			boundingBoxes[i].maxPoints.z = boundingBoxes[i].maxPoints.z < getOrigin().z + ctlPoints[i][j][2]+buffer ?getOrigin().z + (float)ctlPoints[i][j][2]+buffer:boundingBoxes[i].maxPoints.z;
		}
	}
}


bool BezierPatch::objectWithinBoundingBox(Obstacle testObj)
{
	//test each bounding box
	for(int i=0;i<levelOfDetail;i++)
	{
		if (   testObj.getOrigin().x>=boundingBoxes[i].minPoints.x
			&& testObj.getOrigin().x<=boundingBoxes[i].maxPoints.x
			&& testObj.getOrigin().y>=boundingBoxes[i].minPoints.y 
			&& testObj.getOrigin().y<=boundingBoxes[i].maxPoints.y
			&& testObj.getOrigin().z>=boundingBoxes[i].minPoints.z
			&& testObj.getOrigin().z<=boundingBoxes[i].maxPoints.z)
		{ 
				return true;
		}
	}
	return false;
}


void BezierPatch::setBoundingBoxes(int boxIx, Point newMinPoints, Point newMaxPoints)
{
	if (boxIx>=0 && boxIx<levelOfDetail)
	{
		boundingBoxes[boxIx].minPoints = newMinPoints;
		boundingBoxes[boxIx].maxPoints = newMaxPoints;
	}
}
