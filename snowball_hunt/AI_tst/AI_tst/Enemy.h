#pragma once



enum npcAction {RUN_FOR_LIFE, MAKE_SNOWBALL,CARRY_SNOWBALL, THROW_SNOWBALL, DIE,IDLE};

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

	void setCurrentState(npcAction newState);
	npcAction getCurrentState();

};
