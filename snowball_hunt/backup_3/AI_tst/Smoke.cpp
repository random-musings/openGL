#include "stdafx.h"


Dust::Dust():origin(Point(0,0,0)),
				velocity(Point(0,0,0),
				size(1),
				isEnabled(false),
				color(0,0,0,1)
{}

Dust::Dust(Point newOrigin,
				Point newVelocity,
				GLfloat newSize,
				bool isEnabled,
				Color newColor)
				:origin(newOrigin),
				velocity(newVelocity),
				enabled(isEnabled),
				color(newColor)
{}


void Dust::advance()
{
    origin = origin+velocity;
}

void Dust::degradeVelocity(Point speedDegrade)
{
    velocity.x = velocity.x+ velocity.x * speedDegrade.x;
    velocity.y = velocity.y+ velocity.y * speedDegrade.y;
    velocity.z = velocity.z+ velocity.z * speedDegrade.z;
}

void Dust::display()
{
    glBegin(GL_POLYGON);
    glVertex3f(origin.x-size,origin.y+size,0);
    glVertex3f(origin.x,origin.y+sparcSize,0);
    glVertex3f(origin.x,origin.y-sparcSize,0);
    glVertex3f(origin.x-size,origin.y-size,0);
    glEnd();
}




Smoke::Smoke(void)
{
}

Smoke::~Smoke(void)
{
}


void Smoke::display()
{
	glPushMatrix();
	glTranslatef(origin.x,origin.y,origin.z);
       for(int i =0;i<maxParticles;i++)
        {
                    if( fire[i].velocity.y<0.1)
                    {
                                fire[i].velocity.y=rand() %10;
                                fire[i].velocity.x=rand() %5 -1;
			}

                    if( fire[i].origin.y>160)
                    {
                                fire[i].origin.y=0;
                                fire[i].origin.x=0;
                    }
                    if(fire[i].origin.x<-50 ||fire[i].origin.x>50)
                    {
                                fire[i].origin.x=0;
                    }
                    fire[i].advance();
                    fire[i].enabled=true;
                    fire[i].display();
                    fire[i].degradeSpeed(.8);
        }
 glPopMatrix();
}