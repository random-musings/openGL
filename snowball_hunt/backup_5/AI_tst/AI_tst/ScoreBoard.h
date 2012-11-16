#pragma once

class ScoreBoard
{
	bool displayScore;
	int packagesFound;
	Button resetButton;
	char* defaultMessage;
	char* msg2;
	Point	cornerPt;
	GLfloat height;
	GLfloat width;
	GLuint scoreboardFont;

public:
	ScoreBoard(void);
	ScoreBoard(Point newCorner, GLfloat newHeight, GLfloat newWidth,char* Text, int newPackageFound=0);
	~ScoreBoard(void);

	void setDimensions(Point newCorner,GLfloat newHeight, GLfloat newWidth);
	void incrementPackagesFound();
	void resetPackagesFound();
	void display(bool overheadView);
	void setMessage(char* newMessage);
	void setMsg2(char* newMessage);
	Button& getResetButton();

	void setDisplayScore(bool newDisplayScore);

};
