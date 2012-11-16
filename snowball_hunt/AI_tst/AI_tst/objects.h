#pragma once

const	GLfloat PI = 3.14159;

void drawWalls(GLuint txtWalls);
void drawFloor( GLuint txtFloor);
void drawCieling();
void displayShape(vector<Point> shape,
				  vector<Point> textureCoords);

vector<Point> calculateTextureCoords(vector<Point> shape);

void getRange(vector<Point> shape, 
			GLfloat &lowestX, GLfloat &highestX,
			GLfloat &lowestY, GLfloat &highestY,
			GLfloat &lowestZ, GLfloat &highestZ);

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
				);

void square (GLuint textureID);

void displaySnowman(GLUquadric *snowman, 
					GLuint txtSnow,
					GLuint carrot, 
					GLuint buttons,
					Point origin);