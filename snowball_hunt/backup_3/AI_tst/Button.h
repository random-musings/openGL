#pragma once

class Button
{
	Point corner;
	Color bgColor;
	Color fgColor;
	GLfloat h;
	GLfloat w;
	char* text;
	bool buttonPressed;
	GLuint listIdButtonPressed;
	GLuint listIdButtonUp;
	void *Font;

	void setButtonColors();

public:
	Button();
	Button(char* Text, Point startPt, GLfloat Height, GLfloat width,Color Background, Color fontColor);
	~Button(void);

	void display();
	bool pointInButton(Point testPoint);
	bool isButtonPressed();
	void setButtonIsPressed(bool newButtonState);
	void setDimensions(Point cornerPt,GLfloat newHeight,GLfloat newWidth );
	void setStyle(Color Background, Color fontColor,void *newFont);
};
