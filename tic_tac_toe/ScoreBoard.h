#pragma once

class ScoreBoard
{
	bool player1Turn;
	Button resetButton;
	char* defaultMessage;
	char* msgLine2;
	char* msgLine3;
	Point	cornerPt;
	GLfloat height;
	GLfloat width;
	GLuint scoreboardFont;

public:
	ScoreBoard(void);
	ScoreBoard(Point newCorner, GLfloat newHeight, GLfloat newWidth,char* Text);
	~ScoreBoard(void);

	void setDimensions(Point newCorner,GLfloat newHeight, GLfloat newWidth);
	void incrementPlayersTurn();
	void display();
	void setMessage(char* newMessage);
	void setMessage2(char* newMessage);
	void setMessage3(char* newMessage);
	Button& getResetButton();
};
