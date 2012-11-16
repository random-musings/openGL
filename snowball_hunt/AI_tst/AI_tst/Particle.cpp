#include "stdafx.h"

Particle::Particle():jitterIx(0),
			jitterRange(0),
			direction(0,1,0),
			startRange(0,0,0),
			endRange(1,1,1),
			angle(0),
			radius(0),
			radiusIncr(0),
			heightIncr(0),
			particle(0),
			particleInnerRadius(0),
			particleOuterRadius(0)
			{setVisibility(false);}

Particle::Particle(	GLuint newName,
				Point newDirection,
				Point newStartRange,
				Point newEndRange,
				float newSize,
				GLfloat newJitterRange,
				float newInnerRadius,
				float newOuterRadius):
				Obstacle(newName, 
					newStartRange,
					Point(newSize,newSize,newSize),
					Point(0,0,0),  //starting velocity
					false,
					0),//the new list ID				
					jitterRange(newJitterRange),
					jitterIx(0),
					size(newSize),
					startRange(newStartRange),
					endRange(newEndRange),
					direction(newDirection)	,
					angle(0),
					radius(0),
					radiusIncr(0),
					heightIncr(0),
					particle(0),
					particleInnerRadius(newInnerRadius),
					particleOuterRadius(newOuterRadius)

				{
				}

Particle::~Particle()
{
	gluDeleteQuadric(particle);
}

void Particle::advance()
{
	//reset the particle if it is out of bounds
	if ( abs(getOrigin().x)>abs(endRange.x)
		|| abs(getOrigin().y)>abs(endRange.y)
		|| abs(getOrigin().z)>abs(endRange.z))
		reset(false);
	//reset the particle if velocity==0
	if ( abs(getVelocity().x)<1 
		&& abs(getVelocity().y)<1
		&& abs(getVelocity().z)<1)
		reset(false);

	//expand the radius
	radius =radius+ 0.01;
	angle = ((int)angle +1)%360;
	Point newOrigin;

	//jitter its movement 
	//jitter  =(int)rand()%2==0? 0.05*radius:-0.05*radius;

	//newOrigin.x = (radius+jitter)*cos(angle*PI/180) +startRange.x ;
	//newOrigin.z = (radius+jitter)*sin(angle*PI/180) +startRange.z ;

	newOrigin.x = (radius)*cos(angle*PI/180) +startRange.x ;
	newOrigin.z = (radius)*sin(angle*PI/180) +startRange.z ;
	newOrigin.y =getOrigin().y +heightIncr;//angle==0?1:0;
	setOrigin(newOrigin);

}


void Particle::display(GLuint texture)
{
	if(getVisibility())
	{
		//glBindTexture(GL_TEXTURE_2D,texture);
		
		glColor4f(0,0,1,1);
		float red =0;
		//float inner_radius =0.2;
		//float outer_radius =0.5;
		float inner_radius =particleInnerRadius;
		float outer_radius =particleOuterRadius;
		glPushMatrix();
			glLoadName(getName());
			float z_translate =3;
			int max_rings =5;
			float incr =0.3;
			//glTranslatef(getOrigin().x,getOrigin().y,getOrigin().z);
			//glRotatef(90,1,0,0);
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			for(int i=0; i<max_rings;i++)
			{
				z_translate += incr;				
				glPushMatrix();
				glTranslatef(0,0,z_translate);
				glBegin(GL_POLYGON);
				glTexCoord3f(0,0,1);
				glVertex3f(getOrigin().x,getOrigin().y+outer_radius,getOrigin().z+z_translate);
				glTexCoord3f(0,1,0);
				glVertex3f(getOrigin().x+inner_radius,getOrigin().y,getOrigin().z+z_translate);
				glTexCoord3f(1,0,0);
				glVertex3f(getOrigin().x-inner_radius,getOrigin().y,getOrigin().z+z_translate);
				glEnd();
				glPopMatrix();
		
				inner_radius +=incr;
				outer_radius +=incr;
			}
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glPopMatrix();
	}
	glColor4f(1,1,1,1);

}



void Particle::reset(bool firstTimeThrough)
{

	float randn = rand();
	setOrigin(Point(startRange.x,
					startRange.y  + (firstTimeThrough?(int)randn%(int)endRange.y:(int)abs(getOrigin().y)%50),
					startRange.z));

	setVelocity(Point(1,1,1));

	radius=((int) rand()*10) %20;
	radiusIncr =((int) rand()*10) %5;
	heightIncr =((int) randn*10) %10 +0.01;
	angle =((int) rand()*100) %360;

	//set jitter
	jitter = getVelocity().y*particleOuterRadius
			+getVelocity().x*particleOuterRadius
			+getVelocity().z*(particleOuterRadius+particleInnerRadius);	
}




bool Particle::objectWithinRadius(Obstacle testObj)
{
	Point vehiclePt = testObj.getOrigin();
	Point particleObj = getOrigin();
   float actualDistance= getDistanceFromObject(testObj.getOrigin());
 	if( actualDistance < size )
		return true;
 
	return objectWithinBoundingBox(testObj);
}

 