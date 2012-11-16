#include "stdafx.h"




void drawFloor(GLuint textureID)
{
// ** OVERHEAD
	glBindTexture(GL_TEXTURE_2D,textureID);
   //top
	vector<Point> floor;
	floor.push_back(Point(-50,  -50, -50 ));
	floor.push_back(Point(50,  -50, -50 ));
	floor.push_back(Point(50,  -50, 50 ));
	floor.push_back(Point(-50,  -50, 50 ));	
	displayShape(floor,calculateTextureCoords(floor));
	floor.clear();
}

void drawWalls(GLuint textureID)
{
	glBindTexture(GL_TEXTURE_2D,textureID);
	//BACK
	glBegin(GL_POLYGON);
		glTexCoord2f( 0, 0 );
		glVertex3f( -50, -50, -50 );
		glTexCoord2f( 1, 0 );
		glVertex3f(  50, -50, -50 );
		glTexCoord2f( 1, 1 );
		glVertex3f(  50,  50, -50 );
		glTexCoord2f( 0, 1 );
		glVertex3f( -50,  50, -50 );
	glEnd();

	//right
	glBegin(GL_POLYGON);
		glTexCoord2f( 0, 0 );
		glVertex3f(  50, -50, -50 );
		glTexCoord2f( 1, 0 );
		glVertex3f(  50, -50,  50 );
		glTexCoord2f( 1, 1 );
		glVertex3f(  50,  50,  50 );
		glTexCoord2f( 0, 1 );
		glVertex3f(  50,  50, -50 );
	glEnd();

	//left
	glBegin(GL_POLYGON);
		glTexCoord2f( 0, 0 );
		glVertex3f(  -50, -50,  50 );
		glTexCoord2f( 1, 0 );
		glVertex3f(  -50, -50, -50 );
		glTexCoord2f( 1, 1 );
		glVertex3f(  -50,  50, -50 );
		glTexCoord2f( 0, 1 );
		glVertex3f(  -50,  50,  50 );
	glEnd();

	// front
	glBegin(GL_POLYGON);
		glTexCoord2f( 0, 0 );
		glVertex3f(  50, -50, 50 );
		glTexCoord2f( 1, 0 );
		glVertex3f( -50, -50, 50 );
		glTexCoord2f( 1, 1 );
		glVertex3f( -50,  50, 50 );
		glTexCoord2f( 0, 1 );
		glVertex3f(  50,  50, 50 );
	glEnd();

}

void drawCieling()
{
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.25,0.45,0.60,1);

	// front
	vector<Point> ceiling;
	ceiling.push_back(Point(-50,  50, -50 ));
	ceiling.push_back(Point(50,  50, -50 ));
	ceiling.push_back(Point(50,  50, 50 ));
	ceiling.push_back(Point(-50, 50, 50 ));	
	displayShape(ceiling,calculateTextureCoords(ceiling));
	ceiling.clear();
	glEnable(GL_TEXTURE_2D);
}



void displayShape(vector<Point> shape, vector<Point> textureCoords)
{
	glBegin(GL_POLYGON);
	for(int i=0;i<(int)shape.size();i++)
	{
		glTexCoord3f( textureCoords[i].x,textureCoords[i].y,textureCoords[i].z );
		glVertex3f(  shape[i].x, shape[i].y, shape[i].z );
	}
	glEnd();
}


vector<Point> calculateTextureCoords(vector<Point> shape)
	{
		vector<Point> textureCoords;
		GLfloat lowestX, highestX;
		GLfloat lowestY, highestY;
		GLfloat lowestZ, highestZ;

		getRange(shape,lowestX, highestX,
				lowestY,  highestY,
				lowestZ,  highestZ);
		GLfloat rangeX = abs(lowestX - highestX);
		GLfloat rangeY = abs(lowestY - highestY);
		GLfloat rangeZ = abs(lowestZ - highestZ);

		for(int i=0;i<(int)shape.size();i++)
		{
			GLfloat texX = rangeX==0?0:(shape[i].x-lowestX)/rangeX;
			GLfloat texY = rangeY==0?0:(shape[i].y-lowestY)/rangeY;
			GLfloat texZ = rangeZ==0?0:(shape[i].z-lowestZ)/rangeZ;
			if (rangeX==0)
				textureCoords.push_back(Point(texZ,texY,0));
			else if (rangeY==0)
				textureCoords.push_back(Point(texX,texZ,0));
			else if (rangeZ ==0)
				textureCoords.push_back(Point(texX,texY,0));
			else
				textureCoords.push_back(Point(texX,texY,texZ));
		}
		return textureCoords;
	}


void getRange(vector<Point> shape, GLfloat &lowestX, GLfloat &highestX,
							GLfloat &lowestY, GLfloat &highestY,
							GLfloat &lowestZ, GLfloat &highestZ)
	{

		for(int i=0;i<(int) shape.size();i++)
		{
			if (i==0)
			{
				lowestX  =shape[i].x; lowestY = shape[i].y; lowestZ = shape[i].z; 
				highestX =shape[i].x; highestY = shape[i].y; highestZ = shape[i].z; 
			}else
			{
				lowestX = lowestX>shape[i].x?shape[i].x:lowestX;
				lowestY = lowestY>shape[i].y?shape[i].y:lowestY;
				lowestZ = lowestZ>shape[i].z?shape[i].z:lowestZ;

				highestX = highestX<shape[i].x?shape[i].x:highestX;
				highestY = highestY<shape[i].y?shape[i].y:highestY;
				highestZ = highestZ<shape[i].z?shape[i].z:highestZ;
			}
		}
	}


void drawVehicle(GLuint VehicleID,
				Point origin,
				GLUquadric *siren,
				GLuint txtSiren,
				GLuint txtCar,
				GLfloat height,
				GLfloat width,
				GLfloat depth,
				bool firstPersonMode,
				bool overHeadView
				)
{
		int currName = VehicleID;
		Point Centroid=origin;
		vector<Point> displayPoints;
		vector<Point> textureCoords;
		glPushMatrix();

		// **********CHANGE FOR OVEHEAD


		if (overHeadView)
		{
			//glTranslatef(-35,40,origin.z);
			//glTranslatef(origin.x+15,origin.y,origin.z+10);
			glTranslatef(origin.x,origin.y,origin.z);
		}else
		{
			glLoadIdentity();
		}

		//Light/Siren on Vehicle
		if (siren==0)
		{
			siren= gluNewQuadric();
			gluQuadricNormals(siren, GLU_SMOOTH);
			gluQuadricTexture (siren,GLU_TRUE);			
		}


	if(firstPersonMode)
	{
		glPopMatrix();
		glTranslatef(0,-4,0);
		return;
	}
		
	glColor4f(1,1,1,0.9);
	//glBindTexture(GL_TEXTURE_2D,txtCar);

	if(!overHeadView)
		glTranslatef(35,-27,0);
	else
		glTranslatef(-origin.x,-50,-origin.z);
		glBindTexture(GL_TEXTURE_2D,txtCar);
		//Draw Vehicle
		displayPoints.clear();
		textureCoords.clear();
		glLoadName(VehicleID);
		displayPoints.push_back(Point(Centroid.x - width,  Centroid.y - height,  Centroid.z - depth));
		displayPoints.push_back(Point(Centroid.x + width,  Centroid.y - height,  Centroid.z - depth));
		displayPoints.push_back(Point(Centroid.x + width,  Centroid.y + height,  Centroid.z - depth));
		displayPoints.push_back(Point(Centroid.x - width,  Centroid.y + height,  Centroid.z - depth));
		textureCoords =calculateTextureCoords(displayPoints);
		displayShape(displayPoints,textureCoords);

		displayPoints.clear();
		textureCoords.clear();
		displayPoints.push_back(Point(Centroid.x - width,  Centroid.y - height,  Centroid.z + depth));
		displayPoints.push_back(Point(Centroid.x + width,  Centroid.y - height,  Centroid.z + depth));
		displayPoints.push_back(Point(Centroid.x + width,  Centroid.y - height,  Centroid.z - depth));
		displayPoints.push_back(Point(Centroid.x - width,  Centroid.y - height,  Centroid.z - depth));
		textureCoords =calculateTextureCoords(displayPoints);
		displayShape(displayPoints,textureCoords);

		displayPoints.clear();
		textureCoords.clear();
		displayPoints.push_back(Point(Centroid.x + width,  Centroid.y - height,  Centroid.z - depth));
		displayPoints.push_back(Point(Centroid.x + width,  Centroid.y - height,  Centroid.z + depth));
		displayPoints.push_back(Point(Centroid.x + width,  Centroid.y + height,  Centroid.z + depth));
		displayPoints.push_back(Point(Centroid.x + width,  Centroid.y + height,  Centroid.z - depth));
		textureCoords =calculateTextureCoords(displayPoints);
		displayShape(displayPoints,textureCoords);

		displayPoints.clear();
		textureCoords.clear();
		displayPoints.push_back(Point(Centroid.x - width,  Centroid.y - height,  Centroid.z + depth));
		displayPoints.push_back(Point(Centroid.x - width,  Centroid.y - height,  Centroid.z - depth));
		displayPoints.push_back(Point(Centroid.x - width,  Centroid.y + height,  Centroid.z - depth));
		displayPoints.push_back(Point(Centroid.x - width,  Centroid.y + height,  Centroid.z + depth));
		displayShape(displayPoints,calculateTextureCoords(displayPoints));

		displayPoints.clear();
		textureCoords.clear();
		displayPoints.push_back(Point(Centroid.x - width,  Centroid.y + height,  Centroid.z - depth));
		displayPoints.push_back(Point(Centroid.x + width,  Centroid.y + height,  Centroid.z - depth));
		displayPoints.push_back(Point(Centroid.x + width,  Centroid.y + height,  Centroid.z + depth));
		displayPoints.push_back(Point(Centroid.x - width,  Centroid.y + height,  Centroid.z + depth));
		displayShape(displayPoints,calculateTextureCoords(displayPoints));

		displayPoints.clear();
		textureCoords.clear();
		displayPoints.push_back(Point(Centroid.x + width,  Centroid.y - height,  Centroid.z + depth));
		displayPoints.push_back(Point(Centroid.x - width,  Centroid.y - height,  Centroid.z + depth));
		displayPoints.push_back(Point(Centroid.x - width,  Centroid.y + height,  Centroid.z + depth));
		displayPoints.push_back(Point(Centroid.x + width,  Centroid.y + height,  Centroid.z + depth));
		displayShape(displayPoints,calculateTextureCoords(displayPoints));

		//draw siren
		float lightEmissive[]={1.0,1.0,1.0};
		glMaterialfv(GL_FRONT, GL_EMISSION,lightEmissive);
		glTranslatef(origin.x,origin.y+height,origin.z);
		glBindTexture(GL_TEXTURE_2D,txtSiren);
		gluSphere(siren,height/4, 20,20);
		float lightEmissive2[]={0.0,0.0,0.0};
		glMaterialfv(GL_FRONT, GL_EMISSION,lightEmissive2);
		glPopMatrix();
}




void square (GLuint textureID) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,textureID);
    glTranslatef(0,2.5,0);
    glScalef(2,2,2);
    glBegin(GL_QUADS);
        glTexCoord2f(1,0);
    glVertex3f(-10,-50,0);
        glTexCoord2f(1,1);
    glVertex3f(-10,10,0);
        glTexCoord2f(0,1);
    glVertex3f(10,10,0);
        glTexCoord2f(0,0);
    glVertex3f(10,-50,0);
    glEnd();
    glPopMatrix();
}




void displaySnowman(GLUquadric *snowman, 
					GLuint txtSnow,
					GLuint carrot, 
					GLuint buttons,
					Point origin)
{
	if (snowman==0)
		snowman = gluNewQuadric();
	GLfloat size=5;
	GLfloat featuresSnowballPct=0.15;
	GLfloat bodySnowballPct=1;
	GLfloat torsoSnowballPct=0.5;
	GLfloat headSnowballPct=0.25;

	GLfloat featureSize= size*featuresSnowballPct;
	GLfloat bodySize= size*bodySnowballPct;
	GLfloat torsoSize= size*torsoSnowballPct;
	GLfloat headSize= size*headSnowballPct;

	glBindTexture(GL_TEXTURE_2D,txtSnow);
	glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		//glColor4f(0.8,0.8,0.8,1);
		gluQuadricNormals(snowman, GLU_SMOOTH);
		gluQuadricTexture (snowman,GLU_TRUE);

		//move to snowman location
		glTranslatef(origin.x,origin.y,origin.z);

		//snowballs
		gluSphere(snowman,bodySize,10,20);
		glTranslatef(0,bodySize,0);
		gluSphere(snowman,torsoSize,20,10);
		glTranslatef(0,torsoSize,0);
		gluSphere(snowman,headSize,20,20);

		//Face
		glBindTexture(GL_TEXTURE_2D,carrot);
		glPushMatrix();
		glTranslatef(0,0,headSize);
		gluCylinder(snowman,featureSize,0.01,headSize,10,10); //nose
		glBindTexture(GL_TEXTURE_2D,buttons);
		glTranslatef(-featureSize,.1,0);	
		gluSphere(snowman,featureSize,20,20);	//eyes
		glTranslatef(featureSize*2,0,0);
		gluSphere(snowman,featureSize,20,20); //eyes
		glPopMatrix();

		//Buttons
		glTranslatef(0,-torsoSize/2,torsoSize);
		gluSphere(snowman,featureSize,20,20);
		glTranslatef(0,-featureSize*3,0);
		gluSphere(snowman,featureSize,20,20);
		glTranslatef(0,-featureSize*3,0);
		gluSphere(snowman,featureSize,20,20);
		glPopMatrix();
		
	//glEndList();

}