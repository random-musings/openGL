/*
*  Student 2997420
*  Name: Janie Jacobucci
*  TMA #4
*
* Notes:
*  the following has been implemented
* 1) shadows
* 2) bezier curve
* 3) fractal tree
* 
* All three views are available
1) overhead view
2) 1st person
3) 3rd person
*
*
* There is a scoreboard that indicates 
1) the number of parcels that have been picked up (there are 5 in total)
2) the amount of damage currently taken.
*
* When maximum damage is taken or all packages have been picked up  game play will stop
* and the appropriate message will be displayed.
* "Mission Accomplished"  or "Mission Failed"
*
* Navigation
* Up arrow move you upwards
* Down arrow move you down
* left arrow turns  you left
* right arrow turns you right
* space bar advances you forward.
*
* a tractor beam has been implemented to pull in parcels
* it is a translucent sphere and triangle.
* to activate the tracor beam get within range of the package and 
* put the mouse cursor on the package and click the left mouse button.
*
There is debris flying through the air. 
It causes 5 damage on impact.
it turns your vehicle into a beater in the process.
the debris is implemented like a tornado funnel. 
All debris starts roughly in the centre of the board. 
They begin to spin in the centre of the board
like a funnel cloud/dust devil, etc with an every increasing radius. 
The Debris gains height as they spin.
If the debris comes in contact with the snow drifts or the vehicle, they reset themselves.
The start over again in the centre of the board. (After assigning a random height and starting radius.)
*
*
* 
* All objects are of type Obstacle
* they use or override the parent functions 
*		display
*		objectWithinBoundingBox
*
* the following objects have been create (and inherited the parent class Obstacle)
* Snowman
* Fractal Tree
* Particle (the debris objects flying through the air)
* Bezier Patch (the snow drifts)
* Gifts (the pyramid cubes that represents the packages you are searching for)
* Pond (the stone surface underneath the rotating gift)
*
* All objects implement a bounding box that determines the exterior regions.
* in the case of the snow drifts a bounding box is implemented over the line segments 
* so it is a very tight set of bounding boxes. 
*
*
* The following functions do the majority of the work
1) process_hits & hit_test  these implement the pick matrix 
	and determine is the packages are within range of the vehicle
2) display - this function implements the shadows and draws all objects on the stage
3) processCollision - this determines if the vehicle has hit any object and if
	debris has hit the vehicle
4) covertToView this converts to the 1st/3rd and overhead view
5) pullInObject()-- this implements the tractor beam
*
*
*
* What doesn't work perfectly. I would love to fix these but I have run out of time - be gentle :)
* shadows.. there are no shadows on the snow drifts
* flipping from overhead to first or third person view will drop you to the floor even if you were were at a high elevation
* everything else I tested worked beautifully so hopefully it will work for you too 
*
*
* want to know where the packages Are? 
*       A package is a solid triangle.
* if yes keep scrolling otherwise 
* play the game now!
* (one of the packages is really tough to get...like really tough....
* I have tested it and you must navigate up down and over till you get within range.
* It requires some manuevering! but it is always attainable..just make sure you get close enough.
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
* Where the packages are
1) under the snow drift (one snow drift you can get underneath , the other one you can't)
	this is under the snow drift on the same side as the snowman.
2) under the fractal tree (you will have to go as far down as possible)
3) in the snowman (his belly button)
4) circling above the stone pond. 
	You cannot reach it from the ground you will have to go into the air
5) in the top left corner (flip to the overhead view) you will see it. 
	package #5 is the toughest to reach. go over the snow drift to the wall 
	go down as far as possible rotate so that your view is split by the wall
	you will be able to reach it from this angle.
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################
*########################################################*
*/

#include "stdafx.h"

int W, H;
const GLfloat worldX = 100; // 4.5 feet x 12 inches per foot 
const GLfloat worldY = 100; // 9   feet x 12 inches per foot 
float angle=0;


//record angle of direction
GLfloat translateDirX=0;
GLfloat translateDirY=0;
GLfloat translateDirZ=0;
GLfloat shadowx=0;
GLfloat shadowy=0;
GLfloat shadowz=0;

GLfloat modelViewMatrix[16];


GLfloat courseCorrection=2;
GLfloat courseDepth=45;
GLfloat courseBuffer=0.98;
char floorFile[] = "SnowFloor.bmp";
//char wallFile[] = "snowdrift_test.bmp";
char wallFile[] = "sdtest.bmp";
char vehicleFile[] ="vehicle.bmp";
char sirenFile[] ="siren.bmp";
char carrotFile[] = "carrot.bmp";
char buttonFile[]="button.bmp";
char marbleFile[]="marble.bmp";
char waterFile[]="water.bmp";

const GLuint WALLID =0;
const GLuint FLOORID=1;
const GLuint VEHICLEID=2;
const GLuint SIRENID=3;
const GLuint CARROTID=4;
const GLuint BUTTONID=5;
const GLuint PARTICLEID=6;
const GLuint SNOWCAVEID=7;
const GLuint SNOWCAVEID2=8;
const GLuint SNOWMANID=9;
const GLuint PONDID=10;
const GLuint WATERID=11;



const int MAXTEXTURES=40;
GLuint textures[MAXTEXTURES];

bool gameInPlay =true;
GLfloat speed = 0.0f;

GLfloat mouseX=0;
GLfloat mouseY=0;

void translate( GLfloat x, GLfloat y, GLfloat z );
bool processCollision();
void rotate( GLfloat degrees, GLfloat x, GLfloat y, GLfloat z );
void reshape(int w, int h);
void adjustVelocityDirection(GLfloat adjDirection);
void display(void);




// ***************************************
// ************* VEHICLE *****************
// ***************************************
GLuint VehicleID = 30;
GLint vehicleAngle=0;
Point velocity(0,0,0);
Point lastMove(0,0,0);
Point vehicleOrigin(-27,5,-8);
Point overheadVehicle(-37,5,0);
Point currentOrigin=Point(0,0,0);//used to track current position
Point translateToThirdPerson(-2,-50,-27);
Point originInSpace=Point(0,-45,0);//used to track current position
Point tmpOrigin; //hold the temporary origin which searching for processCollisions
const float originInSpaceIncrement=1.5;
const float translateUpwardsIncrement=3;
const float translateUpwardsIncrementO=3;
float maxDamage=100;
Vehicle vehicle(VehicleID,currentOrigin,Point(2,2,2),maxDamage);


// ******************
// *** SNOWMAN *****
// *****************

//GLUquadric *snowman;
Point snowmanOrigin(30,-45,30);
GLfloat snowmanSize=10;
Snowman snowman;

// ********************
// **** Fractal Tree **
// ********************
GLuint fractalTreeID=50;
Point fractalTreePosition(-40,0,35);
int maxDepth=4;
GLfloat branchLength=50;
GLfloat trunkWidth=1;
float fractalMax =85;
float fractalMin =-60;
float fractalIncr = 0;

FractalTree ft(
	fractalTreePosition,
	fractalTreeID,
	4,
	branchLength,
	trunkWidth,
	0,
	0.6, //amount to reduce the trunk width and the branch length as levels are added.
	false,	//if true then the branches will be created via random angles
	0);

// *********************
// *** ParticleSystem***
// *********************
const int MAXPARTICLES=30;
Particle debris[MAXPARTICLES];
Point particleDirection(0,0,1);
Point particleStart(1,-45,1);
Point particleEnd (50,45,50);
GLfloat particleSize =5;
GLfloat particleJitter=20;
GLfloat particleDamage=5;
GLfloat particleInnerRadius=0.2;
GLfloat particleOuterRadius=0.5;

// **********************
// *** Snow Drift ********
// **********************
float driftBuffer=2.5;
Point caveSize(20,40,20);
Point cavePosition(40,-30,0);
BezierPatch snowcave(SNOWCAVEID,cavePosition);
float snowCavePoints[4][4][3] = { 
	{
		{ 10,0,10 },
		{ 10,0,-5 },
		{ 10,0,-5 },
		{10,0,-50 }
	},
	{
		{5,-20,10 },
		{ 5,36,5 },
		{ 5,36,-5 },
		{5,0,-50 }

	},
	{
		{5,0,10 },
		{ 5,36,5 },
		{ 5,36,-5 },
		{5,0,-50 }

	},
	{
		{ -10,-20,-10 },
		{ -10,-20,5 },
		{ -10,-20,-5 },
		{-10,-20,-50 }
	}
};


// ****************
// ** SNOWDRIFT #2
// *****************
Point caveSize2(20,40,20);
Point cavePosition2(-40,-30,0);
BezierPatch snowcave2(SNOWCAVEID2,cavePosition2);
float snowCavePoints2[4][4][3] = { 
	{
		{ 10,-20,10 },
		{ 10,-20,-5 },
		{ 10,-20,-5 },
		{10,-20,-50 }
	},
	{
		{5,-20,10 },
		{ 5,36,5 },
		{ 5,36,-5 },
		{5,0,-50 }
	},
	{
		{5,0,10 },
		{ 5,36,5 },
		{ 5,36,-5 },
		{5,0,-50 }

	},
	{
		{ -10,-20,-10 },
		{ -10,-20,5 },
		{ -10,-20,-5 },
		{-10,-20,-50 }
	}
};



// ********************
// *** POND
// *******************
Pond pond;
Point pondOrigin(0,-45,-30);
GLfloat pondRadius=7.0;



// *****************
// ** GIFTS
// *****************
const GLuint GIFT1ID=12;
const GLuint GIFT2ID=13;
const GLuint GIFT3ID=14;
const GLuint GIFT4ID=15;
const GLuint GIFT5ID=16;
Point giftOrigin1(-43,-43,38); //behind the fractal tree
Point giftOrigin2(45,-45,-20); //under the snow drift
Point giftOrigin3(0,-20,-30); //in the air rotating
Point giftOrigin4(30,-35,40); //on top of thesnowman
Point giftOrigin5(-49,-40,-49); //corner behind bezier drift
Point giftVelocity(-2,0,-2); //speed of rotating gift
float giftRadius=10;		//radius of rotating gift
float giftSize=1.1;
const int giftCount=5;
float giftAngle=0;
Gift gifts[giftCount];
float minDistance=25;

// ********************
// function to move gift
// ********************
void rotateGift(float &test_angle, float radius,Gift &gift)
{
	test_angle = ((int)test_angle +2)%360;
	gift.setOrigin(Point((radius)*cos(test_angle*PI/180) +gift.getOrigin().x ,
		gift.getOrigin().y,
		(radius)*sin(test_angle*PI/180) + gift.getOrigin().z ));
}

// ***************************
// ** Test if unobstructedView
// ****************************
bool objectUnobstructed(float distanceFromObject,int giftIx)
{
	if (distanceFromObject>minDistance)
		return false;

	//compare to CurrentOrigin
	//if this is GIFT5ID then 
	//currentOrigin.y> drift 2 height
	if(currentOrigin.y<snowcave2.getSpaceDimensions().y+snowcave2.getOrigin().y)
		return false;
	return true;
}

// ***********************
// ***** ScoreBoard ******
// ***********************
ScoreBoard sb(Point(0,-40,0),20,worldX,"Packages Found:",0);
Point sbOrigin(2,52,-8);
char missionAccomplished[] ="Mission Accomplished";
char msgDamage[25] ="Damage 0 out of 100";
char msgMissionFailed[] ="Mission Failed";
// ********************
// ** OverheadView ****
// ********************
Point thirdPersonCamera(9,25,-9);
Point firstPersonCamera(-5,0,5);
Point overheadCamera(-25,-50,10);
GLfloat overheadAngle =90;
float overheadSelectX=75;
float overheadSelectY=95;

bool switchToFirstPersonView=false;
bool switchToOverheadView=false;
bool switchToThirdPersonView=true;

bool overheadView=false;
bool thirdPersonView=false;
bool firstPersonView=false;

Point firstPersonRotate(3.9,-29.5,-4.1);


void convertToView()
{
	if (switchToOverheadView && !overheadView)
	{
		overheadView=true;
		thirdPersonView=false;			
		firstPersonView=false;
		Point tmpOrigin = currentOrigin;
		GLint tmpAngle = vehicleAngle;
		Point tmpVelocity = velocity;
		glLoadIdentity();
		glRotatef(90,1,0,0);
		glTranslatef(overheadCamera.x,overheadCamera.y,overheadCamera.z); //flip camera to look down
        glGetFloatv( GL_MODELVIEW_MATRIX, modelViewMatrix );  // save MY copy in modelViewMatrix
		reshape(W,H);
	}

	if(switchToThirdPersonView && !thirdPersonView)
	{
		//translate to ground level
		Point tmpOrigin = currentOrigin;
		GLint tmpAngle = vehicleAngle;
		Point tmpVelocity = velocity;
		if (overheadView)
		{
			glLoadIdentity();
			originInSpace.y = -45;
			glTranslatef(thirdPersonCamera.x,thirdPersonCamera.y,thirdPersonCamera.z);
			glTranslatef(-currentOrigin.x,0,-currentOrigin.z);
		}else if (firstPersonView)
		{
			translate(-firstPersonCamera.x,-firstPersonCamera.y,-firstPersonCamera.z);
		}else
		{
			glLoadIdentity();
			glTranslatef(thirdPersonCamera.x,thirdPersonCamera.y,thirdPersonCamera.z);
		}

		glGetFloatv( GL_MODELVIEW_MATRIX, modelViewMatrix );  // save MY copy in modelViewMatrix
		if (overheadView)
		{
			thirdPersonView=true;			
			firstPersonView=false;
			overheadView=false;
			rotate(tmpAngle,0,1,0);
			velocity = tmpVelocity;
			currentOrigin = tmpOrigin;
			vehicleAngle=tmpAngle;
		}
		thirdPersonView=true;			
		firstPersonView=false;
		overheadView=false;
		reshape(W,H);
	}
	if(switchToFirstPersonView & !firstPersonView)
	{
		if (thirdPersonView)
			translate(firstPersonCamera.x,firstPersonCamera.y,firstPersonCamera.z);
		if (overheadView)
		{
			Point tmpOrigin = currentOrigin;
			GLint tmpAngle = vehicleAngle;
			Point tmpVelocity = velocity;
			originInSpace.y = -45;
			glLoadIdentity();
			glTranslatef(-currentOrigin.x,0,-currentOrigin.z);
			glTranslatef(thirdPersonCamera.x,thirdPersonCamera.y,thirdPersonCamera.z);
			glTranslatef(firstPersonCamera.x,firstPersonCamera.y,firstPersonCamera.z);
			glGetFloatv( GL_MODELVIEW_MATRIX, modelViewMatrix );  // save MY copy in modelViewMatrix
			thirdPersonView=false;			
			overheadView=false;
			firstPersonView=true;
			rotate(tmpAngle,0,1,0);
			velocity = tmpVelocity;
			currentOrigin = tmpOrigin;
			vehicleAngle=tmpAngle;

		}
		thirdPersonView=false;			
		firstPersonView=true;
		overheadView=false;
		reshape(W,H);
	}
	switchToOverheadView=false;
	switchToFirstPersonView=false;
	switchToThirdPersonView=false;

}

// ******************
// **** TRACTOR BEAM
// ******************
bool activeBeam =false; //indicates tractor beam is activated (if yes all other commands deactivated
GLuint giftIx=-1;  //this is the id of the object currently being pulled in
int stopDistance=2;   //this is the distance at which to stop pulling the object closer
Point advanceIncrement(0,0,0); //the coordinates in whic to advance the object towards the vehicle
Point emptyPoint(0,0,0);

Point calculateAdvanceIncrement(Point destinationPoint, Point startPoint)
{

	float length = sqrt( (startPoint.x-destinationPoint.x) * (startPoint.x-destinationPoint.x) +
						(startPoint.y-destinationPoint.y) * (startPoint.y-destinationPoint.y) +
						(startPoint.z-destinationPoint.z) * (startPoint.z-destinationPoint.z) );
	return 	Point  ( (destinationPoint.x-startPoint.x)/length,
						 (destinationPoint.y-startPoint.y)/length,
						 (destinationPoint.z-startPoint.z)/length);
}

//display tractor beam and move object towards vehicle
void pullInObject()
{
	if (!activeBeam || giftIx<0)
		return;
	if(emptyPoint==advanceIncrement)
		advanceIncrement = calculateAdvanceIncrement(currentOrigin+ originInSpace,gifts[giftIx].getOrigin());

	if(gifts[giftIx].getDistanceFromObject(currentOrigin +originInSpace)> stopDistance)
	{
		glPushMatrix();
		//draw tractor beam from vehicle to gift
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_DEPTH);
		glEnable(GL_BLEND);

		Point tractorBeam =currentOrigin+originInSpace;
		Point targetPoint = gifts[giftIx].getOrigin();
		Point targetSize =gifts[giftIx].getSpaceDimensions() + Point(3,3,3);
		glColor4f(0.0f,1.0f,0.0f,0.2f);                	// set color to red



		glPushMatrix();
		glTranslatef(targetPoint.x,targetPoint.y,targetPoint.z);
		GLUquadric *circle;
		circle = gluNewQuadric();
		gluSphere(circle,targetSize.x, 20,20);
		glPopMatrix();
 
 			glBegin(GL_TRIANGLES);
			glVertex3f(  tractorBeam.x, tractorBeam.y, tractorBeam.z);
			glVertex3f(targetPoint.x-targetSize.x,  targetPoint.y+targetSize.y, targetPoint.z-targetSize.z);
			glVertex3f(targetPoint.x+targetSize.x,  targetPoint.y+targetSize.y, targetPoint.z+targetSize.z);
			glEnd();

			glDisable(GL_COLOR_MATERIAL);
			glDisable(GL_DEPTH);
			glDisable(GL_BLEND);

		glPopMatrix();

		//pull gift closer to vehicle
		Point newPoint = advanceIncrement+gifts[giftIx].getOrigin();
		gifts[giftIx].setOrigin(newPoint);
		glutPostRedisplay();
	}else
	{
		gifts[giftIx].setFound(true);
		giftIx=-1;
		activeBeam=false;
		advanceIncrement=emptyPoint;
		sb.incrementPackagesFound();
		for(int i=0;i<giftCount;i++)
		{
			if(!gifts[i].isFound())
				return;
		}
		gameInPlay=false;
		sb.setMessage(missionAccomplished);
		sb.setDisplayScore(false);
	}


}


// ******************************************
// **************** MENU ********************
// ******************************************
void SelectFromMenu(int idCommand);
enum {
	MENU_LIGHTING = 1,
	MENU_1STPERSON,
	MENU_3RDPERSON,
	MENU_OVERHEADVIEW,
	MENU_EXIT
};

int BuildPopupMenu (void)
{
  int menu = glutCreateMenu (SelectFromMenu);
  glutAddMenuEntry ("Toggle Day/Night Mode\tn", MENU_LIGHTING);
  glutAddMenuEntry ("1st Person View\t1", MENU_1STPERSON);
  glutAddMenuEntry ("3rd Person View\t3", MENU_3RDPERSON);
  glutAddMenuEntry ("Overhead View\to", MENU_OVERHEADVIEW);
  glutAddMenuEntry ("Exit Race\tEsc", MENU_EXIT);
  return menu;
}

void SelectFromMenu(int idCommand)
{
  switch (idCommand)
    {
	case MENU_1STPERSON:
		switchToFirstPersonView=true;	
		break;
	case MENU_3RDPERSON:
		switchToThirdPersonView=true;	
		break;
	case MENU_OVERHEADVIEW:
		switchToOverheadView=true;
		break;
    case MENU_EXIT:
      exit (0);
      break;
    }
  glutPostRedisplay();
}

void reshape(int w, int h)
{
    W = w;
    H = h;
    glViewport(0, 0, w, h);
    cout << "w = " << w << ", h = " << h << endl;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	// ***** OVERHEAD *****
	if(!overheadView)
		glFrustum(0,worldX/8,-worldY/4, worldY/8, 6.0f, 8000.0f);
	else
	    glFrustum(-worldX/4,worldX/8,-worldY/4, worldY/8, 20.0f, 8000.0f);
	glMatrixMode(GL_MODELVIEW);
}



// ***********************************
// *********PICK MATRIX **************
// ***********************************
GLfloat pickMatrixX =-5;
GLfloat pickMatrixY = -5;
GLfloat pickMatrixWidth  = 10;
GLfloat pickMatrixHeight = 10;

const GLuint HITBUFSIZE=512;
void hit_test();


void process_Hits( GLint hits, GLuint buffer[] )
{
	bool hitSomething = false;
	GLuint *ptr = (GLuint*)buffer;
	for (GLint i = 0; i < hits; i++) 
	{
		std::cerr << "hits: " << hits << "\n";
		GLuint names = *ptr;
		std::cerr << "number of names for this hit = "<<*ptr<<"   names=" << names << "\n";
		ptr++;
		//std::cerr << "              z1: " <<"  "<<*ptr<<"  "<<(*ptr/0x7fffffff);
		ptr++;
		//std::cerr << "               z2: " <<"  "<<*ptr<<"  "<< (*ptr/0x7fffffff);
		ptr++;
		//std::cerr << "\nnames: ";
		for( GLuint j = 0; j < names; j++)
		{			
			hitSomething=true;
				float closest_distance=100;
				for(int i=0;i<giftCount;i++)
				{
					if(*ptr==gifts[i].getName())
					{
						float test_distance =gifts[i].getDistanceFromObject(currentOrigin+originInSpace);
						if(  test_distance<closest_distance 
							&& objectUnobstructed(test_distance,i)
							&& !gifts[giftIx].getVisibility())
						{ //find the package closest to the car
							std::cerr << (*ptr) << " "<<endl;
							activeBeam=true;
							giftIx=i;
							closest_distance =test_distance;
						//	return;
						}//end of test distance
					}//end of getname
				}//end of for
			std::cerr <<"*** hit object**** --> "<<*ptr<<"  "<<"settings: ("<<pickMatrixX<<","<<pickMatrixY<<") to w="<< pickMatrixWidth<<" h="<<pickMatrixHeight;
			std::cerr << (*ptr) << " "<<endl;
			ptr++;
		}//end of for names
	}//end of for ptr
}//PROCESS_hits


//scroll through our hit buffer and see what we picked with the mouse
void hit_test()
{


//convert to third person view and execute a hit_test
	GLint viewport[4];
	glGetIntegerv (GL_VIEWPORT, viewport);
	GLuint selectBuf[HITBUFSIZE];
	glSelectBuffer (HITBUFSIZE, selectBuf);


	glRenderMode (GL_SELECT);
	glInitNames();
	glPushName(0);

	if(overheadView)
	{
		pickMatrixX = pickMatrixX/20;
		pickMatrixY = (H-pickMatrixY)/3;

		glMatrixMode (GL_PROJECTION);
		glPushMatrix ();
		glLoadIdentity ();
		gluPickMatrix ( pickMatrixX,
						pickMatrixY,
						pickMatrixWidth+10,
						pickMatrixHeight+20,  viewport);
//		glRotatef(shadowx,1,0,0);
//		glRotatef(shadowy,0,1,0);
//		glRotatef(shadowz,0,0,1);
		//glRotatef(10,0,0,1);
	    //glFrustum(-worldX/4,worldX/8,-worldY/4, worldY/8, 20.0f, 8000.0f);
		//glFrustum(1,worldX-25+shadowx,-26 +shadowz, worldY-4+shadowy, 2.0f, 8000.0f);
		//glFrustum(0,overheadSelectX,shadowy,overheadSelectY, 2.0f, 8000.0f);
		//glFrustum(1,75+shadowx,-25+shadowz, 100+shadowy, 2.0f, 8000.0f);
		//glFrustum(-20,worldX-25+shadowx,-26 +shadowz, worldY-4+shadowy, 20.0f, 8000.0f);
		glFrustum(pickMatrixX-28,worldX-25,-25, worldY-4, 20.0f, 8000.0f);
	}else
	{//third and first person view)
		pickMatrixX = pickMatrixX*8/(worldX);
		pickMatrixY = (H-pickMatrixY)/3;

		glMatrixMode (GL_PROJECTION);
		glPushMatrix ();
		glLoadIdentity ();
		gluPickMatrix (pickMatrixX,
						pickMatrixY,
						pickMatrixWidth-shadowz,
						pickMatrixHeight-shadowz,  viewport);
		glFrustum( 1,worldX,-26, worldY, 5.0f, 40.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	display();
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();
	glFlush();
	GLint hits = glRenderMode (GL_RENDER);
	process_Hits (hits, selectBuf);


	glutPostRedisplay();
}

void idleMouse(int x, int y)
{
	//static int idlecnt= 0;
	//	hit_test();
	//	idlecnt=0;
	//idlecnt++;
}



// ********************
// *** Display ********
// ********************


void 
display(void)
{
	glClearStencil(0);
	glClearDepth(1.0f);
	//glClearColor(0.1,0.3,0.55,1);
	glClearColor(1,1,1,1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

	convertToView();

	glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf( modelViewMatrix );
	glPushMatrix();

	//Stencil Routines
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); //disable the color mask
    glDepthMask(GL_FALSE); //disable the depth mask
    glEnable(GL_STENCIL_TEST); //enable the stencil testing
    glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); //set the stencil buffer to replace our next lot of data
		//what the shadows will be drawn on
		drawWalls(textures[WALLID]);
		drawFloor(textures[FLOORID]);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); //enable   the color mask
    glDepthMask(GL_TRUE); //enable the depth mask
    glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //set the stencil buffer to keep our next lot of data
    glDisable(GL_TEXTURE_2D); //disable texturing of the shadow
    glDisable(GL_DEPTH_TEST); //disable depth testing of the shadow
    glPushMatrix();
    glScalef(1.0f, -1.0f, 1.0f); //flip the shadow vertically
 	glTranslatef(0,2,0); //translate the shadow onto our drawing plane
    glRotatef(angle,0,1,0); //rotate the shadow accordingly
    glColor4f(0,0,0,1); //color the shadow black

	//draw shadows

		//snowman shadow
		glPushMatrix();
		glTranslatef(60,78,-17);
		glRotatef(90,1,0,0);
		glRotatef(180,0,0,1);
		snowman.display();
		glPopMatrix();

		glPushMatrix();
		glRotatef(-90,1,0,0);
		glScalef(3,3,3);
		glTranslatef(-5,57,64);
		for(int i=0;i<MAXPARTICLES;i++)
		{
			debris[i].display(textures[SIRENID]);
		}
		glPopMatrix();

	//fractalTree shadow
		glPushMatrix();
		glScalef(1.0f, 0.2f, 1.2f); //flip the shadow vertically
		glTranslatef(-70,165,-12);
		glRotatef(270,1,0,0);
		glRotatef(90,0,1,0);
		ft.display();
		glPopMatrix();

	//pond shadow
		glPushMatrix();
		glTranslatef(0,100,10);
		glScalef(1.1f, 1.0f, 1.5f); 
		pond.display(textures[PONDID],textures[WATERID]);
		glPopMatrix();

	//gifts
	//glPushMatrix();
	//glRotatef(90,1,0,0);
	//for (int i=0; i<giftCount;i++)
	//{
	//	switch(giftIx)
	//	{
	//		case 0:	glTranslatef(shadowx,shadowy,shadowz);break;
	//		case 1:	glTranslatef(shadowx,shadowy,shadowz);break;
	//		case 2:	glTranslatef(shadowx,shadowy,shadowz);break;
	//		case 3:	glTranslatef(shadowx,shadowy,shadowz);break;
	//		case 4:	glTranslatef(shadowx,shadowy,shadowz);break;
	//	}
	//	gifts[i].display();
	//}
	//glPopMatrix();


	glColor4f(1,1,1,0.8); //FREAKING DON't TOUCH THIS 
    glPopMatrix();
    glEnable(GL_DEPTH_TEST); //enable depth testing
    glEnable(GL_TEXTURE_2D); //enable texturing
    glDisable(GL_STENCIL_TEST); //disable the stencil testing //end

    glEnable(GL_BLEND); //enable alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //set teh alpha blending

	//draw the actual textures with shadows blended into them
		drawWalls(textures[WALLID]);
		drawFloor(textures[FLOORID]);

    glDisable(GL_BLEND); //disable alpha blending


	glColor4f(1,1,1,0.1);


	//draw the items on the screen
    glRotatef(angle,0,1,0); //rotate the square

	//draw the snowman
	snowman.display();

	//draw the car
	Point tmpOrigin = vehicle.getOrigin();
	if(overheadView)
	{
		Point tO2 =Point(0,50,0) +originInSpace;
		tO2 = tO2 + vehicle.getOrigin();
		tO2.x += currentOrigin.x;
		tO2.z += currentOrigin.z;
		vehicle.setOrigin(tO2);
	}
//	vehicle.setCollision(true);
	vehicle.display(translateToThirdPerson,
					textures[SIRENID],
					textures[VEHICLEID],
					firstPersonView,
					overheadView);
	if(overheadView)
		vehicle.setOrigin(tmpOrigin);


	//fractal tree
	ft.setTextureId(textures[VEHICLEID]);
	ft.display();
	ft.setFixedAngle(66);
	//ft.adjustAngles(fractalMax,fractalMin,fractalIncr);
	

//scoreboard
	sb.setMsg2(msgDamage);

	//draw the particles
	for(int i=0;i<MAXPARTICLES;i++)
	{
		debris[i].display(textures[SIRENID]);
		debris[i].advance();
	}

	//draw the Snowdift
	snowcave.display(textures[FLOORID]);
	snowcave2.display(textures[FLOORID]);

	//pond display
	pond.display(textures[PONDID],textures[WATERID]);

	//gifts
	//for (int i=0; i<giftCount;i++)
	//	gifts[i].display();
	glPushMatrix();
	for (int i=0; i<giftCount;i++)
		gifts[i].display();
	glPopMatrix();

	// Tractor Beam Function
	pullInObject();

	glPopMatrix();


	//ScoreBoard()
	glPushMatrix();
	glLoadIdentity();
	if(!overheadView)
		glTranslatef(sbOrigin.x,sbOrigin.y,sbOrigin.z);
	else
		glTranslatef(0,0,-40);

	sb.display(overheadView);
	glPopMatrix();

	drawCieling();
	glFlush();
    glutSwapBuffers();
}



void translate(GLfloat x, GLfloat y, GLfloat z )
{
	if(!overheadView)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef( x, y, z );
		glMultMatrixf( modelViewMatrix );
		glGetFloatv( GL_MODELVIEW_MATRIX, modelViewMatrix );
	}
}


void adjustVelocityMagnitude(GLfloat adjVelocity)
{

	velocity.z =adjVelocity<0.01?0:-1*(cos(vehicleAngle*PI/180) * adjVelocity);
	velocity.x =adjVelocity<0.01?0:sin(vehicleAngle*PI/180) * adjVelocity;
}

void adjustVelocityDirection(GLfloat adjDirection)
{
	velocity.z +=cos(adjDirection*PI/180);
	velocity.x +=sin(adjDirection*PI/180);
}


// we really want to rotate at a point other than the viewpoint - namely closer to the wheels...
void rotate(GLfloat degrees, GLfloat x, GLfloat y, GLfloat z )
{
	if (degrees==0)
		return;

	if(!overheadView)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		if(thirdPersonView || overheadView)
			glTranslatef(8.5,-29.5,-8);
		if(firstPersonView)
			glTranslatef(firstPersonRotate.x,firstPersonRotate.y,firstPersonRotate.z);

		glRotatef(degrees, x, y, z );
		if(thirdPersonView  || overheadView)
			glTranslatef( -8.5, 29.5, 8);
		if(firstPersonView)
			glTranslatef(-firstPersonRotate.x,-firstPersonRotate.y,-firstPersonRotate.z);
		glMultMatrixf( modelViewMatrix );
		glGetFloatv( GL_MODELVIEW_MATRIX, modelViewMatrix );
	}		

	vehicleAngle =(GLint)(vehicleAngle+degrees) %360;
	adjustVelocityDirection(vehicleAngle);	

}


void 
update()
{

	(void)processCollision(); //process collisions and damage taken

	if(activeBeam) //do not respond to events when beam is activated-drop vehicle velocity to zero
	{
        speed = -speed;
		adjustVelocityMagnitude(speed);
		return; 
	}

    if ( speed > 0 )
	{
        speed -=0.001f;
		adjustVelocityMagnitude(speed);
	}
    else
	{
		adjustVelocityMagnitude(speed);
        speed = 0;
	}


	//move object/view
	translate(0,0,speed);

	//calculate new Position
	lastMove = currentOrigin;
	currentOrigin.x += velocity.x;
	currentOrigin.z += velocity.z;

	//move the gift - unless it has already been picked up or is
	//in the process of being picked up
	if (gifts[2].getVisibility() && giftIx!=2)
	{
		gifts[2].setOrigin(giftOrigin3);
		rotateGift(giftAngle, giftRadius,gifts[2]);
	}

	display();
}

void specialChar( int key, int x, int y )
{
	if (activeBeam) //do not respond to events when tractor beam is puling in objects
		return;
	if(!gameInPlay)
		return;

    switch( key )  {
        case GLUT_KEY_UP:
			tmpOrigin =originInSpace;
			originInSpace = originInSpace + Point(0,originInSpaceIncrement,0); //add the ascent
			if(!processCollision( ))
			{
				if(!overheadView)
					translate(0,-translateUpwardsIncrement,0);			
				else
					translate(0,-translateUpwardsIncrementO,0);			
				originInSpace.y+=originInSpaceIncrement;
			}else
				originInSpace  = tmpOrigin;
            break;
        case GLUT_KEY_DOWN:
			tmpOrigin =originInSpace;
			originInSpace = originInSpace + Point(0,-originInSpaceIncrement,0); //add the ascent
			if(!processCollision( ) )
			{
				if(!overheadView)
					translate(0,translateUpwardsIncrement,0);			
				else
					translate(0,translateUpwardsIncrementO,0);			
				originInSpace.y-=originInSpaceIncrement;
			}else
				originInSpace  = tmpOrigin;
            break;
        case GLUT_KEY_RIGHT:
			rotate( 3, 0, 1, 0 );
            break;
        case GLUT_KEY_LEFT:
	        rotate( -3, 0, 1, 0 );
            break;
    }
    display();
}


void keyBoard( unsigned char key, int x, int y )
{
	static int angle =0;
	 
	if(!gameInPlay)
		return;
    switch( key )  {
		case ' ':
				speed +=0.1f;
				adjustVelocityMagnitude(speed);
				break;
		case 0:
				adjustVelocityMagnitude(-speed);
				speed =-speed;
				break;

        case 'i':
			firstPersonRotate.x+=0.2;
			break;
        case 'I':
			firstPersonRotate.x-=0.2;
            break;
        case 'w':
			firstPersonRotate.z+=0.2;
            break;
        case 'W':
			firstPersonRotate.z-=0.2;
            break;
        case 'a':
            translate(1,0,0);
            break;
        case 'd':
            translate(-1,0,0);
            break;
        case 's':
            translate(0,-1,0);
            break;
        case 'S':
            translate(0,1,0);
            break;
		case 'x':
			shadowx++;
			//translate(1,0,0);
			break;
		case 'X':
			shadowx--;
			//translate(1,0,0);
			break;
		case 'z':
			//translate(0,0,1);
			shadowz++;
			break;
		case 'Z':
			//translate(0,0,1);
			shadowz--;
			break;
		case 'y':
			//translate(0,0,1);
			shadowy++;
			break;
		case 'Y':
			//translate(0,0,1);
			shadowy--;
			break;
		case '1':
			 SelectFromMenu(MENU_1STPERSON);
			 break;
		case '3':
			 SelectFromMenu(MENU_3RDPERSON);
			 break;
		case 'o':
			 SelectFromMenu(MENU_OVERHEADVIEW);
			 break;

    }

	//cout <<" firstPersonRotate = "<<firstPersonRotate.x<<","<<firstPersonRotate.y<<","<<firstPersonRotate.z<<endl;
	cout <<"Shadow "<<shadowx<<" ,"<<shadowy<<","<<shadowz<<endl;
	//translateToThirdPerson.x += shadowx;
	//translateToThirdPerson.y +=shadowy;
	translateToThirdPerson.y +=shadowz;;
    display();
}


void initializeGraphics()
{
	//Build Pop Up Menu
	BuildPopupMenu();
	glutAttachMenu (GLUT_RIGHT_BUTTON);

	//inittextures
	for(int i=0;i<MAXTEXTURES;i++)
		textures[i]=0;
	
	
	// disable Lighting
    glDisable( GL_LIGHTING );

    glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

    glEnable( GL_DEPTH_TEST );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv( GL_MODELVIEW_MATRIX, modelViewMatrix );  // save MY copy in modelViewMatrix

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//Load Textures
	textures[SIRENID] = loadtextures(sirenFile, 52,45);
	textures[VEHICLEID] = loadtextures(vehicleFile, 207,177);
	textures[WALLID] = loadtextures(wallFile, 512,512);
	textures[FLOORID] = loadtextures(floorFile, 512,512);
	textures[CARROTID] = loadtextures(carrotFile, 52,45);
	textures[BUTTONID] = loadtextures(buttonFile, 52,45);
	textures[PARTICLEID]=textures[VEHICLEID];
	textures[PONDID] = loadtextures(marbleFile,225,225);
	textures[WATERID] = loadtextures(waterFile,393,385);
	
	//snow drifts
	snowcave.resetPoints(snowCavePoints);
	snowcave.setBoundingBoxes(driftBuffer);

	snowcave2.resetPoints(snowCavePoints2);
//	snowcave2.setBoundingBox(-50,-27, //min max X
//							-50,-30, //min max Y
//							-50,10); //min max z
	snowcave2.setBoundingBoxes(driftBuffer);
	//snowman
	snowman = Snowman(snowmanOrigin,
		SNOWMANID,
		snowmanSize,
		textures[FLOORID],
		textures[CARROTID], 
		textures[BUTTONID]);
	snowman.setBoundingBox(20,40,-50,-10, 17,42);

	//Init ParticleSystem
	for(int i=0;i<MAXPARTICLES;i++)
	{
		debris[i] =Particle(PARTICLEID,
								particleDirection,
								particleStart,
								particleEnd,
								particleSize,
								particleJitter,
								particleInnerRadius,
								particleOuterRadius);
		debris[i].setVisibility(true);
		debris[i].reset(true);
	}

	//Pond 
	pond = Pond(pondOrigin,PONDID,pondRadius);
	pond.setSpaceDimensions(Point(10,10,10));
	pond.setBoundingBox(pondOrigin.x-10,pondOrigin.x+10,-50,pondOrigin.y+5,pondOrigin.z-10,pondOrigin.z+10);

	//fractal tree bounding box
	ft.setBoundingBox(-50,-15,-40,-10,12,50);

	//Gifts
	gifts[0] = Gift(giftOrigin1,GIFT1ID,giftSize);
	gifts[1] = Gift(giftOrigin2,GIFT2ID,giftSize);
	gifts[2] = Gift(giftOrigin3,GIFT3ID,giftSize);
	gifts[3] = Gift(giftOrigin4,GIFT4ID,giftSize);
	gifts[4] = Gift(giftOrigin5,GIFT5ID,giftSize);



	//vehicle
	vehicle.setDamage(0);
	vehicle.setMaxDamage(100);
	vehicle.setIsAlive(true);

	//init shadow paramteres
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);    
    glShadeModel (GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}



bool	processCollision()
{
	if (!gameInPlay)
		return false;
	Point currentVehicleOrigin = vehicle.getOrigin();
	Point pointOnField = currentOrigin +velocity;
	pointOnField = pointOnField + originInSpace;
	vehicle.setOrigin(pointOnField);

	//collision with Wall/Floor
	if ( abs(pointOnField.x) > courseDepth 
		||abs(pointOnField.z) > courseDepth 
		||abs(pointOnField.y) > courseDepth )
	{
		velocity=Point(0,0,0);
		speed=0;
		//adjust the course Velocity so we don't get stuck in a wall
		if ( currentOrigin.x > courseDepth)
			currentOrigin.x = courseDepth-0.1;
		if ( currentOrigin.x < -courseDepth)
			currentOrigin.x = -courseDepth+0.1;
		if ( currentOrigin.z > courseDepth)
			currentOrigin.z = courseDepth;
		if ( currentOrigin.z < -courseDepth)
			currentOrigin.z = -courseDepth;
		if ( currentOrigin.y > courseDepth)
			currentOrigin.y = courseDepth;
		if ( currentOrigin.y < -courseDepth)
			currentOrigin.y = -courseDepth;
		cout <<"Collision with Wall "<<pointOnField  <<"  x> depth("<<courseDepth<<endl;
		vehicle.setOrigin(currentVehicleOrigin);
		return true;
	}

	//collision vehicle With Pond
	if(pond.objectWithinBoundingBox(vehicle))
	{
  		velocity = Point(0,0,0);
		speed=0;
		vehicle.setOrigin(currentVehicleOrigin);
		cout << "collision with pond  vehicle at "<<pointOnField<<endl;
		return true;
	}

	//collision with snowdrift 2;
	if(snowcave2.objectWithinBoundingBox(vehicle))
	{
  		velocity = Point(0,0,0);
		speed=0;
		vehicle.setOrigin(currentVehicleOrigin);
		cout << "collision with   snowcave2 at "<<pointOnField<<endl;
		return true;
	}

	if(snowcave.objectWithinBoundingBox(vehicle))
	{
  		velocity = Point(0,0,0);
		speed=0;
		vehicle.setOrigin(currentVehicleOrigin);
		cout << "collision with   snowcave at "<<pointOnField<<endl;
		return true;
	}

	//collision with snowman
	if(snowman.objectWithinBoundingBox(vehicle))
	{
  		velocity = Point(0,0,0);
		speed=0;
		vehicle.setOrigin(currentVehicleOrigin);
		cout << "collision with   snowman at "<<pointOnField<<endl;
		return true;
	}


	if(ft.objectWithinBoundingBox(vehicle))
	{
		speed=0;
		vehicle.setOrigin(currentVehicleOrigin);
		return true;
	}

	//process Collisions with Particles
	vehicle.setOrigin(vehicle.getOrigin()+ Point(0,0,-8));
	for(int i=0;i<MAXPARTICLES;i++)
	{
		Point vehiclePt = vehicle.getOrigin();
		Point particleObj  = debris[i].getOrigin();
		if(debris[i].objectWithinRadius(vehicle))
		{
			//decrement health of Vehicle
 			vehicle.applyDamage(particleDamage);
			vehicle.setCollision(true);
			
			//reset particle
			debris[i].reset(false);

			//
			sprintf_s(msgDamage,"Damage %d out of %d",vehicle.getDamage(),vehicle.getMaxDamage());
			sb.setMsg2(msgDamage);
			if(!vehicle.getIsAlive())
			{
				gameInPlay=false;
				sb.setMessage(msgMissionFailed);
				sb.setDisplayScore(false);
			}
		}
		if(snowcave.objectWithinBoundingBox(debris[i])
			|| snowcave2.objectWithinBoundingBox(debris[i]))
		{
			debris[i].reset(false);			//reset the particle
		}
	}

	//put back the vehicleOrigin()
	vehicle.setOrigin(currentVehicleOrigin);
	return false;

}//end of processCollision





void mouseFunc(int button, int state, int x, int y)
{
	switch(state)
	{
		case GLUT_UP:
			mouseX= x;
			mouseY= y;
			break;
		case GLUT_DOWN:
			pickMatrixX = x;
			pickMatrixY=y;
			hit_test();

			break;
	}

}




void  cleanup()
{

	int textureCount=0;
	for(int i=0;i<MAXTEXTURES;i++)
	{
		if(textures[i]!=0)
			textureCount++;
	}
	if(textureCount!=0)
		glDeleteTextures(textureCount, textures);

}

void main(int argc, char** argv)
{
    W = 800; H = 800;

    int windowHandle = glutCreateWindow("Program 2");
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glEnable(GLUT_RGBA);
    glutSetWindow(windowHandle);
    glutPositionWindow ( 100, 10 );
    glutReshapeWindow( W, H );
    initializeGraphics();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(update);
    glutSpecialFunc( specialChar );
    glutKeyboardFunc( keyBoard );
	glutMouseFunc( mouseFunc );
	glutPassiveMotionFunc(idleMouse);
    glutMainLoop();
	//cleanup();
}



