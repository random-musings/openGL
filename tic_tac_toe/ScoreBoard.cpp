#include "stdafx.h"

ScoreBoard::ScoreBoard(void)
	:resetButton("Reset",Point(0,0,0),20,20,Color(1.0,1.0,1.0),Color(0.0,0.0,0.0))
{
	defaultMessage="Tic Tac Toe ";
	msgLine2=" ";
	msgLine3=" ";
}

ScoreBoard::ScoreBoard(Point newCorner, GLfloat newHeight, GLfloat newWidth,char* Text)
	:cornerPt(newCorner),
	height(newHeight),
	width(newWidth),
	resetButton("Reset",newCorner,20,30,Color(1.0,1.0,1.0),Color(0.0,0.0,0.0)),
	player1Turn(true)
{
	defaultMessage = Text;	
	msgLine2=" ";
	msgLine3=" ";
}

ScoreBoard::~ScoreBoard(void)
{

}


void displayMessage(Point startPoint, char* message)
{
	if (message!=0)
	{
		glColor3f(1.0,1.0,1.0);
		glRasterPos2f(startPoint.x,startPoint.y);
		int len = (int) strlen(message);
		for (int i = 0; i < len; i++) 
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
		}
	}
}



void ScoreBoard::display()
{
	resetButton.display();

		//glColor3f(1.0,1.0,1.0);
		//glRasterPos2f(cornerPt.x,cornerPt.y);
		//int len = (int) strlen(defaultMessage);
		//for (int i = 0; i < len; i++) 
		//{
		//	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, defaultMessage[i]);
		//}

	 displayMessage(cornerPt,defaultMessage);
	 Point line2 = cornerPt;
	 line2.y -=5;
	 displayMessage(line2,msgLine2);
	 Point line3 = line2;
	 line3.y -=5;
	 displayMessage(line3,msgLine3);

}


void 	ScoreBoard::setDimensions(Point newCorner,GLfloat newHeight, GLfloat newWidth)
{
	cornerPt = newCorner;
	height = newHeight;
	width = newWidth;

	resetButton.setDimensions(Point(cornerPt.x+newWidth/2,cornerPt.y,0),newHeight/15,newWidth/5);
}



Button& ScoreBoard::getResetButton()
{
	return resetButton;
}

void ScoreBoard::setMessage(char* newMessage)
{
	defaultMessage=newMessage;
}

void ScoreBoard::setMessage2(char* newMessage)
{
	msgLine2=newMessage;
}

void ScoreBoard::setMessage3(char* newMessage)
{
	msgLine3=newMessage;
}
