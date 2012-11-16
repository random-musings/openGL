#include "stdafx.h"

ScoreBoard::ScoreBoard(void)
	:packagesFound(0),
	displayScore(true),
	resetButton("Reset",Point(0,0,0),20,20,Color(1.0,1.0,1.0,1.0),Color(0.0,0.0,0.0,1.0))
{
	defaultMessage="Packages Found: ";
}

ScoreBoard::ScoreBoard(Point newCorner, GLfloat newHeight, GLfloat newWidth,char* Text, int newPackagesFound)
	:cornerPt(newCorner),
	height(newHeight),
	width(newWidth),
	displayScore(true),
	packagesFound(newPackagesFound),
	resetButton("Reset",newCorner,20,30,Color(1.0,1.0,1.0,1.0),Color(0.0,0.0,0.0,1.0))
{
	defaultMessage = Text;	
}

ScoreBoard::~ScoreBoard(void)
{

}



void ScoreBoard::incrementPackagesFound()
{
	packagesFound++;
}

void ScoreBoard::resetPackagesFound()
{
	packagesFound=0;
}

void ScoreBoard::display(bool overheadView)
{
	//resetButton.display();
	 stringstream ss (stringstream::in | stringstream::out);

		glColor3f(1.0,1.0,1.0);
		glRasterPos2f(cornerPt.x,cornerPt.y);
		int len = (int) strlen(defaultMessage);
		for (int i = 0; i < len; i++) 
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, defaultMessage[i]);
		}

		if(displayScore)
		{
			ss << packagesFound;
			string tmpMsg;
			ss>>tmpMsg;
			len = (int)strlen(tmpMsg.c_str());
			for (int i = 0; i < len; i++) 
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, tmpMsg[i]);
			}
		}
		 stringstream ss2 (stringstream::in | stringstream::out);
		
		len=strlen(msg2);
		if(overheadView)
			glRasterPos2f(cornerPt.x,cornerPt.y+2);
		else
			glRasterPos2f(cornerPt.x,cornerPt.y+1.5);
		for (int i = 0; i < len; i++) 
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg2[i]);
		}


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
	defaultMessage = newMessage;
}

void ScoreBoard::setMsg2(char* newMessage)
{
	msg2 = newMessage;
}

void ScoreBoard::setDisplayScore(bool newDisplayScore)
{
	displayScore = newDisplayScore;
}