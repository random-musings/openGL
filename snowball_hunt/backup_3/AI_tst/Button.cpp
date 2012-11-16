#include "stdafx.h"

Button::Button():corner(Point(0,0,0)),
	h(10),
	w(20),
	bgColor(Color(1.0,1.0,1.0,1.0)),
	fgColor(Color(0.0,0.0,0.0,1.0)),
	buttonPressed(false)
{}

Button::Button(char* Text, Point startPt,  GLfloat Height, GLfloat width,Color background, Color fontColor)
:corner(startPt),
	h(Height),
	w(width),
	bgColor(background),
	fgColor(fontColor),
	buttonPressed(false)
{
		text= Text;		
		//Initialize();
}

Button::~Button(void)
{
}


void Button::display()
{
	Color tmpBgColor = bgColor;
	Color tmpFgColor = fgColor;

	setButtonColors();
		//main button
		glColor3f(bgColor.red,bgColor.green,bgColor.blue);
		glBegin(GL_POLYGON);
		glVertex2f(corner.x,corner.y);
		glVertex2f(corner.x+w,corner.y);
		glVertex2f(corner.x+w,corner.y+h);
		glVertex2f(corner.x,corner.y+h);
		glEnd();
		
		glLineWidth(2);
		glBegin(GL_LINE_STRIP);
		glColor3f(0.3,0.3,0.3);
		glVertex2f(corner.x,corner.y+h);
		glVertex2f(corner.x,corner.y);
		glVertex2f(corner.x+w,corner.y);
		glColor3f(1.0,1.0,1.0);
		glVertex2f(corner.x+w,corner.y+h);
		glVertex2f(corner.x,corner.y+h);
		glColor3f(0.3,0.3,0.3);
		glEnd();

		glColor3f(fgColor.red,fgColor.green,fgColor.blue);
		//glRasterPos2f(corner.x+ 0.1*w, corner.y + h*0.25);
		glRasterPos2f(corner.x+1, corner.y+0.5 );
		int len = (int) strlen(text);
		for (int i = 0; i < len; i++) 
		{
			glutBitmapCharacter(Font, text[i]);
		}
		bgColor=tmpBgColor;
		fgColor=tmpFgColor;

}

bool Button::pointInButton(Point testPoint)
{
	if(testPoint.x>=corner.x 
		&& testPoint.x>=corner.x
		&& testPoint.x< corner.x+w
		&& testPoint.y>=corner.y
		&& testPoint.y< corner.y+h)
		return true;
	return false;
}

bool Button::isButtonPressed()
{
	return buttonPressed;
}

void Button::setButtonIsPressed(bool newButtonState)
{
	buttonPressed = newButtonState;
}


void Button::setDimensions(Point cornerPt,GLfloat newHeight,GLfloat newWidth )
{
	corner  = cornerPt;
	h = newHeight;
	w = newWidth;
}

void Button::setStyle(Color Background, Color fontColor,void *newFont)
{
	bgColor = Background;
	fgColor = fontColor;
	Font = newFont;
}


void Button::setButtonColors()
{
	//if button is pressed then change the hues so that user
	//notices that button is pressed
	if(buttonPressed)
	{
		Color tmpColor = bgColor;
		bgColor = fgColor;
		fgColor  = tmpColor;

	}
}

