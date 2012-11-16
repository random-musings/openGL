/*
*  Student 2997420
*  Name: Janie Jacobucci
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
bool processCollision(Obstacle &tmpObject);
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
Point vehicleOrigin(4,-23,-4);
Point currentOrigin=Point(0,-45,0);//used to track current position
Point translateToThirdPerson(-2,-50,-27);
Point tmpOrigin; //hold the temporary origin which searching for processCollisions
const float translateUpwardsIncrement=3;
const float translateUpwardsIncrementO=3;
float maxDamage=100;
const int strikeRange=20;
Vehicle vehicle(VehicleID,currentOrigin,Point(2,2,2),maxDamage,strikeRange,vehicleOrigin);


// ******************
// *** SNOWMAN *****
// *****************

//GLUquadric *snowman;
Point snowmanOrigin3(-20,-45,10);
Point snowmanOrigin2(-30,-45,30);
Point snowmanOrigin(30,-45,25);
GLfloat snowmanSize=10;
Snowman snowman;
Snowman snowman2;
Snowman snowman3;



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
		{10,0,-30 }
	},
	{
		{5,-20,10 },
		{ 5,36,5 },
		{ 5,36,-5 },
		{5,0,-30 }

	},
	{
		{5,0,10 },
		{ 5,36,5 },
		{ 5,36,-5 },
		{5,0,-30 }

	},
	{
		{ -10,-20,-10 },
		{ -10,-20,5 },
		{ -10,-20,-5 },
		{-10,-20,-30 }
	}
};


// ****************
// ** SNOWDRIFT #2
// *****************
Point caveSize2(20,40,20);
Point cavePosition2(-45,-30,0);
BezierPatch snowcave2(SNOWCAVEID2,cavePosition2);
float snowCavePoints2[4][4][3] = { 
	{
		{ 10,-30,10 },
		{ 10,-30,-5 },
		{ 10,-30,-5 },
		{10,-30,-30 }
	},
	{
		{5,-15,10 },
		{ 5,36,5 },
		{ 5,36,-5 },
		{5,0,-30 }
	},
	{
		{5,0,10 },
		{ 5,36,5 },
		{ 5,36,-5 },
		{5,0,-30 }

	},
	{
		{ -10,-15,-10 },
		{ -10,-15,5 },
		{ -10,-15,-5 },
		{-10,-15,-30 }
	}
};



// ********************
// *** POND
// *******************
Pond pond;
Point pondOrigin(0,-15,-30);
GLfloat pondRadius=7.0;
GLfloat pondHeight=30;


// *****************
// ** GIFTS
// *****************
const GLuint GIFT1ID=12;
const GLuint GIFT2ID=13;
const GLuint GIFT3ID=14;
const GLuint GIFT4ID=15;
const GLuint GIFT5ID=16;
Point giftOrigin1(-43,-44,38); //behind the fractal tree
Point giftOrigin2(45,-44,-20); //under the snow drift
Point giftOrigin3(0,-44,-20); //in the air rotating
Point giftOrigin5(30,-44,40); //corner behind bezier drift
Point giftOrigin4(-43,-44,-43); //on top of thesnowman
Point giftVelocity(-2,0,-2); //speed of rotating gift
float giftRadius=10;		//radius of rotating gift
float giftSize=1.1;
const int giftCount=5;
float giftAngle=0;
Gift gifts[giftCount];
float minDistance=25;


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
// **** ENEMY *********
// ********************
GLuint ENEMYID=21;
Point startOrigin(0,-43,0);
GLfloat bodyRadius=3;
GLfloat limbSwing=10;
GLfloat npcSpeed = 0.1;
Enemy npc(startOrigin,
			ENEMYID,
			bodyRadius,
			limbSwing);

// ************************
// **** MAP ***************
// ************************

Map currMap; //NPC Map
//Map currVehicleMap;

//point to collision function - used to assess the map for enemy obstacles
bool (*fp_processCollision)(Obstacle&);

PathController	controller;





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

	if(switchToThirdPersonView && !thirdPersonView)
	{
		//translate to ground level
		Point tmpOrigin = currentOrigin;
		GLint tmpAngle = vehicleAngle;
		Point tmpVelocity = velocity;
		glLoadIdentity();
		glTranslatef(thirdPersonCamera.x,thirdPersonCamera.y,thirdPersonCamera.z);

		glGetFloatv( GL_MODELVIEW_MATRIX, modelViewMatrix );  // save MY copy in modelViewMatrix
		thirdPersonView=true;			
		firstPersonView=false;
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
		advanceIncrement = calculateAdvanceIncrement(vehicle.getOrigin(),gifts[giftIx].getOrigin());

	if(gifts[giftIx].getDistanceFromObject(vehicle.getOrigin())> stopDistance)
	{
		glPushMatrix();
		//draw tractor beam from vehicle to gift
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_DEPTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //set teh alpha blending

		Point tractorBeam =vehicle.getOrigin();
		Point targetPoint = gifts[giftIx].getOrigin();
		Point targetSize =gifts[giftIx].getSpaceDimensions() + Point(3,3,3);
		glColor4f(0.0f,1.0f,0.0f,0.2f);                	// set color to red



		glPushMatrix();
		glTranslatef(targetPoint.x,targetPoint.y,targetPoint.z);
		GLUquadric *circle;
		circle = gluNewQuadric();
		gluSphere(circle,targetSize.x, 20,20);
		glPopMatrix();
 

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
	MENU_3RDPERSON,
	MENU_EXIT
};

int BuildPopupMenu (void)
{
  int menu = glutCreateMenu (SelectFromMenu);
  glutAddMenuEntry ("3rd Person View\t3", MENU_3RDPERSON);
  glutAddMenuEntry ("Exit Race\tEsc", MENU_EXIT);
  return menu;
}

void SelectFromMenu(int idCommand)
{
  switch (idCommand)
    {
	case MENU_3RDPERSON:
		switchToThirdPersonView=true;	
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
	glFrustum(0,worldX/8,-worldY/4, worldY/8, 6.0f, 8000.0f);
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
						float test_distance =gifts[i].getDistanceFromObject(vehicle.getOrigin());
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
	glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

	convertToView();

	glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf( modelViewMatrix );
	glColor4f(1,1,1,1);
	drawFloor(textures[FLOORID]);
	drawWalls(textures[WALLID]);


	//draw the items on the screen
    glRotatef(angle,0,1,0); //rotate the square

	//draw the snowman
	snowman.display();
	snowman2.display();
	snowman3.display();

	//draw the car

	vehicle.display(translateToThirdPerson,
					textures[SIRENID],
					textures[VEHICLEID],
					firstPersonView,
					overheadView);


	

//scoreboard
	sb.setMsg2(msgDamage);

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


	npc.display(textures[BUTTONID]);

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

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(8.5,-29.5,-8);
		glRotatef(degrees, x, y, z );
		glTranslatef( -8.5, 29.5, 8);
		glMultMatrixf( modelViewMatrix );
		glGetFloatv( GL_MODELVIEW_MATRIX, modelViewMatrix );

	//vehicleAngle =(GLint)(vehicleAngle+degrees) %360;
	//adjustVelocityDirection(vehicleAngle);	
	//vehicle.setFacingAngle( (int)(vehicle.getFacingAngle()+degrees)%360 );
	vehicle.adjustFacingAngle(degrees);
}


void 
update()
{
	
	Obstacle tmpObj = vehicle;
	tmpObj.moveObstacle();
	//MapNode *location =currMap.getNode(tmpObj.getOrigin());
	//MapNode *currLocation  =currMap.getNode(vehicle.getOrigin());


/*	if (processCollision(tmpObj)) //process collisions and damage taken
	{
		//make accomodations to ensure that 
 		vehicle.setSpeed(-0.001);
		vehicle.moveObstacle();
	}else
	{
		if(abs(vehicle.getVelocity().x)<0.01 && abs(vehicle.getVelocity().x)>0
			&& abs(vehicle.getVelocity().z)<0.01 && abs(vehicle.getVelocity().z)>0  )
		{
   			cout <<"next move "<<vehicle.getOrigin();
			cout <<" to "<<tmpObj.getOrigin()<<endl;
			vehicle.setSpeed(0);
		}
		vehicle.moveObstacle();
 		translate(0,0,vehicle.getSpeed());	
	}

*/
	vehicle.moveObstacle();
 	translate(0,0,vehicle.getSpeed());	

	if(activeBeam) //do not respond to events when beam is activated-drop vehicle velocity to zero
	{
        vehicle.setSpeed( -vehicle.getSpeed());
		return; 
	}

	//if (speed>0)
    if ( vehicle.getSpeed()>0 )
		vehicle.setSpeed(vehicle.getSpeed()-0.001f);
    else
		vehicle.setSpeed(0);

	//move the enemy player
	controller.advanceCharacter();
	display();
}

void specialChar( int key, int x, int y )
{
	if (activeBeam) //do not respond to events when tractor beam is puling in objects
		return;
	if(!gameInPlay)
		return;

	switch( key )  {

/*	Obstacle tmpObj=(Obstacle)vehicle;
    switch( key )  {
        case GLUT_KEY_UP:
			tmpObj.setOrigin(currentOrigin+originInSpace);
			tmpObj.setOrigin(tmpObj.getOrigin()+Point(0,originInSpaceIncrement,0));
			if(!processCollision(tmpObj ))
			{
				translate(0,-translateUpwardsIncrement,0);			
				originInSpace.y+=originInSpaceIncrement;
			}
            break;
        case GLUT_KEY_DOWN:
			tmpObj.setOrigin(currentOrigin+originInSpace);
			tmpObj.setOrigin(tmpObj.getOrigin()-Point(0,originInSpaceIncrement,0));
			if(!processCollision(tmpObj ) )
			{
				translate(0,translateUpwardsIncrement,0);			
				originInSpace.y-=originInSpaceIncrement;
			}
            break;
*/
        case GLUT_KEY_DOWN:
			vehicle.setSpeed(0);
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
				vehicle.setSpeed(vehicle.getSpeed() + 0.06f);
				break;
		case 0:
				vehicle.setSpeed(-vehicle.getSpeed());
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
		case 'p':
			//currMap.printState();
			currMap.printState();
			break;
    }
	vehicle.shadowX=shadowx;
	vehicle.shadowY=shadowy;
	vehicle.shadowZ=shadowz;
	//cout <<" firstPersonRotate = "<<firstPersonRotate.x<<","<<firstPersonRotate.y<<","<<firstPersonRotate.z<<endl;
	//cout <<"Shadow "<<shadowx<<" ,"<<shadowy<<","<<shadowz<<endl;
	//translateToThirdPerson.x += shadowx;
	//translateToThirdPerson.y +=shadowy;
	translateToThirdPerson.y +=shadowz;;
    display();
}


GLuint loadtextures (const char *filename, float width, float height) {
  GLuint texture;

  unsigned char *data;
  FILE *file;

  file = fopen( filename, "rb" );
  if ( file == NULL ) return 0;

  data = (unsigned char *)malloc( width * height * 3 );
  fread( data, width * height * 3, 1, file );

  fclose( file );
  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D,3,GL_RGBA8,width,height,0,GL_BGR,GL_UNSIGNED_BYTE,data);
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
   glEnable(GL_TEXTURE_2D);

  data = NULL;

  return texture;
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


	snowman2 = Snowman(snowmanOrigin2,
		SNOWMANID,
		snowmanSize,
		textures[FLOORID],
		textures[CARROTID], 
		textures[BUTTONID]);

	snowman3 = Snowman(snowmanOrigin3,
		SNOWMANID,
		snowmanSize,
		textures[FLOORID],
		textures[CARROTID], 
		textures[BUTTONID]);

	//Pond 
	pond = Pond(pondOrigin,PONDID,pondRadius,pondHeight);
	pond.setSpaceDimensions(Point(10,10,10));
	pond.setBoundingBox(pondOrigin.x-10,pondOrigin.x+10,-50,pondOrigin.y+5,pondOrigin.z-10,pondOrigin.z+10);

	//Gifts
	gifts[0] = Gift(giftOrigin1,GIFT1ID,giftSize);
	gifts[1] = Gift(giftOrigin2,GIFT2ID,giftSize);
	gifts[2] = Gift(giftOrigin3,GIFT3ID,giftSize);
	gifts[3] = Gift(giftOrigin4,GIFT4ID,giftSize);
	gifts[4] = Gift(giftOrigin5,GIFT5ID,giftSize);

	//enemy 
	npc.setSpeed(npcSpeed);
	npc.setSpaceDimensions(Point(bodyRadius/2,bodyRadius/2,bodyRadius/2));

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

	//this is defined 
	//bool (*fp_processCollision)(Obstacle);
	fp_processCollision = &processCollision;

//	vehicle.setSpaceDimensions(Point(3,5,5));
//	currVehicleMap.createMap(Point(-45,-45,-45), 
//					Point(45,45,45), 
//					vehicle, 
//					gifts, 
//					giftCount, 
//					fp_processCollision);
//	vehicle.setSpaceDimensions(Point(2,2,2));

	//Map Creation assessment
	currMap.createMap(Point(-46,-46,-46), 
					Point(46,46,46), 
					npc, 
					gifts, 
					giftCount, 
					fp_processCollision
					);
	currMap.printState();

	//setup the controller
	controller = PathController(&currMap,&npc,&vehicle);
	controller.setNextTarget(); //set the target


	
}


bool	processCollision(Obstacle &tmpObject)
{
	if (!gameInPlay)
		return false;

	Point pointOnField = tmpObject.getOrigin() +tmpObject.getVelocity();
	tmpObject.setOrigin(pointOnField);

	//Point pointOnField = currentOrigin +velocity;
	//Point currentVehicleOrigin = vehicle.getOrigin();
	//pointOnField = pointOnField + originInSpace;
	//vehicle.setOrigin(pointOnField);

	//collision with Wall/Floor
	if ( abs(pointOnField.x) > courseDepth 
		||abs(pointOnField.z) > courseDepth 
		||abs(pointOnField.y) > courseDepth )
	{
		//velocity=Point(0,0,0);
		//speed=0;
		tmpObject.setSpeed(0);

		//adjust the course Velocity so we don't get stuck in a wall
		if ( tmpObject.getOrigin().x > courseDepth)
			tmpObject.setOrigin(Point( courseDepth,tmpObject.getOrigin().y,tmpObject.getOrigin().z));
		if ( tmpObject.getOrigin().x < -courseDepth)
			tmpObject.setOrigin(Point( -courseDepth,tmpObject.getOrigin().y,tmpObject.getOrigin().z));
		if ( tmpObject.getOrigin().z > courseDepth)
			tmpObject.setOrigin(Point(tmpObject.getOrigin().x,tmpObject.getOrigin().y, courseDepth));
		if ( tmpObject.getOrigin().z < -courseDepth)
			tmpObject.setOrigin(Point(tmpObject.getOrigin().x,tmpObject.getOrigin().y, -courseDepth));
		if ( tmpObject.getOrigin().y > courseDepth)
			tmpObject.setOrigin(Point(tmpObject.getOrigin().x, courseDepth,tmpObject.getOrigin().z));
		if ( tmpObject.getOrigin().y < -courseDepth)
			tmpObject.setOrigin(Point(tmpObject.getOrigin().x, -courseDepth,tmpObject.getOrigin().z));
		cout <<"Collision with Wall "<<pointOnField  <<"  x> depth("<<courseDepth<<endl;
		return true;
	}

	//collision vehicle With Pond
	if(pond.objectWithinBoundingBox(tmpObject))
	{
		tmpObject.setSpeed(0);
		cout << "collision with pond  vehicle at "<<pointOnField<<endl;
		return true;
	}

	//collision with snowdrift 2;
	if(snowcave2.objectWithinBoundingBox(tmpObject))
	{
  		velocity = Point(0,0,0);
		tmpObject.setSpeed(0);
		cout << "collision with   snowcave2 at "<<pointOnField<<endl;
		return true;
	}

	if(snowcave.objectWithinBoundingBox(tmpObject))
	{
  		velocity = Point(0,0,0);
		tmpObject.setSpeed(0);
		cout << "collision with   snowcave at "<<pointOnField<<endl;
		return true;
	}

	//collision with snowman
	if(snowman.objectWithinBoundingBox(tmpObject)
		|| snowman2.objectWithinBoundingBox(tmpObject)
		|| snowman3.objectWithinBoundingBox(tmpObject))
	{
		tmpObject.setSpeed(0);
		cout << "collision with   snowman at "<<pointOnField<<endl;
		return true;
	}

	//put back the vehicleOrigin()
	//vehicle.setOrigin(currentVehicleOrigin);
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



