#include "stdafx.h"

Enemy::Enemy(void):circle(0),
					maxSnowBallMakeStage(50),
					maxSnowBallThrowStage(50),
					currentState(IDLE),
					angleLegSwing(10),
					angleArmSwing(10),
					incr(1),
					aincr(1),
					snowballThrowStage(0),
					snowballMakeStage(0),
					snowRadius(1),
					bodyRadius(1),
					inRange(false)
{
}


Enemy::Enemy(Point newPosition,
				GLuint newName,
				GLfloat newSize,
				GLfloat newLimbSwing)
				:Obstacle(newName, 
							newPosition,
							Point(newSize,newSize,newSize), //the maximum depth space
							Point(0,0,0)),
					maxSnowBallMakeStage(250),
					maxSnowBallThrowStage(50),
					currentState(IDLE),
					angleLegSwing(newLimbSwing),
					angleArmSwing(newLimbSwing),
					incr(1),
					snowballThrowStage(0),
					snowballMakeStage(0),
					snowRadius(newSize),
					bodyRadius(newSize),
					clr(0.6,0.6,1.0,1.0),
					currLegAngle(0),
					currArmAngle(0),
					inRange(false)
{}


Enemy::~Enemy(void)
{
}


void Enemy::display(GLuint displayTxt)
{
	if(circle==0)	
	{
		circle = gluNewQuadric();
		gluQuadricNormals(circle,GLU_SMOOTH);
		gluQuadricTexture(circle,GLU_TRUE);
	}

	//glEnable(GL_TEXTURE_2D);
	//set the angles that we will move the legs at
	float currLegSwing = getAngleLegs(currentState);
	float currArmSwing = getAngleArms(currentState);
	

	glPushMatrix();
	glTranslatef(getOrigin().x,getOrigin().y,getOrigin().z); //move to spot on board
	glRotatef(getFacingAngle(),0,1,0); //face the correct direction

	glEnable(GL_COLOR_MATERIAL);
	glColor4f(clr.red,clr.green,clr.blue,clr.transparency);

	//draw body	
	glTranslatef(0,-bodyRadius/3,bodyRadius/3); //move body out infront of legs
	gluSphere(circle,bodyRadius,10,10);//body


	//draw Arms
	glPushMatrix();
	switch(currentState)
	{
	case MAKE_SNOWBALL:
		glTranslatef(-bodyRadius/2,bodyRadius/3,bodyRadius/3);
		glRotatef(60,1,0,0);
		break;
	case CARRY_SNOWBALL:
		glTranslatef(-bodyRadius/2,bodyRadius*2/3,bodyRadius/3);
		glRotatef(90,1,0,0);
		glRotatef(45,0,1,0);
		glRotatef(-currArmSwing,1,0,0);//carry
		break;
	case THROW_SNOWBALL:
		glTranslatef(-bodyRadius/2,bodyRadius*2/3,bodyRadius/3);
		glRotatef(90,1,0,0);
		glRotatef(45,0,1,0);
		glRotatef(-currArmSwing,1,0,0);//carry + throw
		break;
	case RUN_FOR_LIFE:
		glTranslatef(0,bodyRadius,0);
		glRotatef(90,1,0,0);
		glRotatef(45,0,1,0);
		glRotatef(currArmSwing,0,1,0);
		break;
	case IDLE:
		glTranslatef(0,bodyRadius,0);
		glRotatef(90,1,0,0);
		glRotatef(45,0,1,0);
		break;
	}
	gluCylinder(circle,bodyRadius/3,bodyRadius/8,bodyRadius*2,10,10); //arms
	glPopMatrix();

	
	glPushMatrix();
	switch(currentState)
	{
	case MAKE_SNOWBALL:
		glTranslatef(bodyRadius/2,bodyRadius/3,bodyRadius/3);
		glRotatef(60,1,0,0);
		break;
	case CARRY_SNOWBALL:
		glTranslatef(bodyRadius/2,bodyRadius*2/3,bodyRadius/3);
		glRotatef(90,1,0,0);
		glRotatef(45,0,1,0);
		glRotatef(-currArmSwing,1,0,0);//carry
		break;

	case THROW_SNOWBALL:
		glTranslatef(bodyRadius/2,bodyRadius*2/3,bodyRadius/3);
		glRotatef(90,1,0,0);
		glRotatef(45,0,1,0);
		glRotatef(-currArmSwing,1,0,0);//carry + throw
		break;
	case RUN_FOR_LIFE:
		glTranslatef(0,bodyRadius,0);
		glRotatef(-90,1,0,0);
		glRotatef(-135,0,1,0);
		glRotatef(-currArmSwing,0,1,0);
		break;
	case IDLE:
		glTranslatef(0,bodyRadius,0);
		glRotatef(-90,1,0,0);
		glRotatef(-135,0,1,0);
		break;
	}
	gluCylinder(circle,bodyRadius/3,bodyRadius/8,bodyRadius*2,10,10); //arms
	glPopMatrix();

	//draw legs
	glPushMatrix();
	glTranslatef(-bodyRadius/3,-bodyRadius,0);
	glRotatef(90,1,0,0);
	if(currLegSwing)
		glRotatef(currLegAngle,1,0,0);
	gluCylinder(circle,bodyRadius/3,bodyRadius/6,bodyRadius,10,10); //legs
	glPopMatrix();

	//draw legs
	glPushMatrix();
	glTranslatef(bodyRadius/3,-bodyRadius,0);
	glRotatef(90,1,0,0);
	if(currLegSwing)
		glRotatef(-currLegAngle,1,0,0);
	gluCylinder(circle,bodyRadius/3,bodyRadius/6,bodyRadius,10,10); //legs
	glPopMatrix();

	//draw Head
	glPushMatrix();
	if(currentState==MAKE_SNOWBALL)	
		glTranslatef(0,0,bodyRadius*1.3);		
	else
		glTranslatef(0,bodyRadius*1.3,0);
	gluSphere(circle,bodyRadius/1.5,10,10);//head
	glPopMatrix();
	



	// **********************
	// ****** SNOWBALL ******
	// **********************
	
	switch (currentState)
	{	
		case MAKE_SNOWBALL:
			glPushMatrix();
			glColor4f(1,1,1,1);
			glBindTexture(GL_TEXTURE_2D,displayTxt);
			glTranslatef(0,-2*bodyRadius,1.25*bodyRadius);
			gluSphere(circle,(float)(snowballMakeStage +10)/(float)maxSnowBallMakeStage,snowRadius*3,snowRadius*3);
			glPopMatrix();			
			break;
		case THROW_SNOWBALL:

			break;
		case CARRY_SNOWBALL:
			glPushMatrix();
			glColor4f(1,1,1,1);
			glBindTexture(GL_TEXTURE_2D,displayTxt);
			glTranslatef(0,bodyRadius*2/3,2*bodyRadius);
			gluSphere(circle,snowRadius,snowRadius*3,snowRadius*3);
			glPopMatrix();
			break;
	}

	glPopMatrix();
	//update the motions of the character
	currLegAngle =currLegSwing; 	//persist the current State
	currArmAngle =currArmSwing;
	
}




//determine if legs should be moving
float Enemy::getAngleLegs(enum npcAction currState)
{
	float legSwing=0;
	switch(currState)
	{
	case MAKE_SNOWBALL:
	case DIE:
	case IDLE:
			legSwing=0;
			break;
	default:
		 incr = abs(currLegAngle)>angleLegSwing?-incr:incr;
		 legSwing =currLegAngle + incr;
		 break;
	}
	return legSwing;
}


GLfloat Enemy::getAngleArms(enum npcAction currState)
{
	float armSwing=0;
	if(aincr==0)
		aincr=1;
	switch(currState)
	{
	case CARRY_SNOWBALL:
		armSwing=75;
		break;
	case RUN_FOR_LIFE:
	case MAKE_SNOWBALL:
		aincr = abs(currArmAngle)>angleArmSwing?-aincr:aincr;
		armSwing =currArmAngle + aincr;
		break;
	case THROW_SNOWBALL:
		armSwing = 75.0 + snowballThrowStage*2;
		break;

	}
	return armSwing;
}



void 	Enemy::UpdateCurrentState()
{
	snowballThrowStage = (snowballThrowStage+1)%maxSnowBallThrowStage;

	//record the progress of our current animation - throwing snowballs
	if (currentState==THROW_SNOWBALL)
	{
		snowballThrowStage++; //the snowball stage
		if( snowballThrowStage>=maxSnowBallThrowStage)
			currentState=IDLE;
	}

	//record the progress of our current animation - making snowballs
	if (currentState==MAKE_SNOWBALL )
	{
		snowballMakeStage++; //the snowball makestage
		if( snowballMakeStage>maxSnowBallMakeStage)
			currentState=CARRY_SNOWBALL;
	}

	if(currentState==RUN_FOR_LIFE && !inDanger)
		currentState=IDLE;


	if(inDanger)
	{
		if(currentState==MAKE_SNOWBALL )
		{
			snowballMakeStage=0;
			currentState=RUN_FOR_LIFE;
		}
		if(currentState==CARRY_SNOWBALL && inRange)
		{
			currentState = THROW_SNOWBALL;
			snowballThrowStage=0;
			//turn to face vehicle
			//acquire target and resulting speed of snowball
		}else if(currentState==IDLE)
		{
			currentState=RUN_FOR_LIFE;
			inRange=FALSE;
		}
	}else
	{
		if( currentState==IDLE ||
			currentState==RUN_FOR_LIFE)
		{
			currentState=MAKE_SNOWBALL;
			snowballMakeStage=0;
			inRange=false;
		}

	}

	
}//end of function



void Enemy::setCurrentState(npcAction newState)
{
	currentState = newState;
}


npcAction Enemy::getCurrentState()
{
	return currentState;
}

void Enemy::setInDanger(bool newInDanger)
{
	inDanger= newInDanger;
}

bool Enemy::getInDanger()
{
	return inDanger;
}

void Enemy::setInRange(bool newInRange)
{
	inRange = newInRange;
}

bool Enemy::getInRange()
{
	return inRange;
}


void Enemy::setThrowRange(int newThrowRange)
{
	throwRange = newThrowRange;
}

int Enemy::getThrowRange()
{
	return throwRange;
}
