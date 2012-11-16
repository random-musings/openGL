#pragma once



enum npcAction {RUN_FOR_LIFE, MAKE_SNOWBALL,CARRY_SNOWBALL, THROW_SNOWBALL, RELEASE_SNOWBALL, DIE,IDLE};

class Enemy:public Obstacle
{

	enum npcAction currentState;
	GLUquadric *circle;
	Color clr;

//drawingVariables
	GLfloat snowRadius;
	GLfloat bodyRadius;


	int angleLegSwing;
	int angleArmSwing;
	int currLegAngle;
	int currArmAngle;
	int incr;
	int snowballThrowStage;
	int snowballMakeStage;
	int maxSnowBallMakeStage;
	int maxSnowBallThrowStage;
	int aincr;
	int throwRange;


	bool inDanger;
	bool inRange;

public:
	Enemy(void);
	Enemy(Point newPosition,
				GLuint newName,
				GLfloat newSize,
				GLfloat newLimbSwing);
	~Enemy(void);

	//angle of arms and legs when drawing
	GLfloat getAngleLegs(enum npcAction currState);
	GLfloat getAngleArms(enum npcAction currState);

	void display(GLuint displayTxt);

	void UpdateCurrentState();
	void setInDanger(bool newInDanger);
	bool getInDanger();


	void setCurrentState(npcAction newState);
	npcAction getCurrentState();

	void setInRange(bool newInRange);
	bool getInRange();

	void setThrowRange(int newThrowRange);
	int getThrowRange();

	float getSnowRadius();
	void setSnowRadius(float newSnowRadius);
};
