/*
 *  roundRect.cpp
 *  Magic Tracker
 *
 *  Created by Kyle.
 *  Copyleft 2009 GNU.
 *
 */


#include <cstdlib>
#include "graphics.h"
#include "roundRect.h"
#include <cmath>
#include <time.h>



roundRect::roundRect(double x1, double y1, double x2, double y2, double r, double red, double green, double blue)
	{
		this->x1=x1;
		this->x2=x2;
		this->y1=y1;
		this->y2=y2;

		this->r=r;
		
		srand(time(0));
		rc=red;
		bc=blue;
		gc=green;

		radius=r;
		
		

		c1x=x1+r;
		c1y=y1+r;
		c2x=x1+r;
		c2y=y2-r;
		c3x=x2-r;
		c3y=y1+r;
		c4x=x2-r;
		c4y=y2-r;

		rtx1=x1+r;
		rty1=y2;
		rtx2=x2-r;
		rty2=y1;
		
		rlx1=x1;
		rly1=y1+r;
		rlx2=x2;
		rly2=y2-r;

	


		outline=false;

	}
roundRect::roundRect(double x1, double y1, double x2, double y2, double r, double red, double green, double blue, bool outline)
{
	this->x1=x1;
	this->x2=x2;
	this->y1=y1;
	this->y2=y2;
	
	this->r=r;
	
	srand(time(0));
	rc=red;
	bc=blue;
	gc=green;
	
	radius=r;
	

	
	c1x=x1+r;
	c1y=y1+r;
	c2x=x1+r;
	c2y=y2-r;
	c3x=x2-r;
	c3y=y1+r;
	c4x=x2-r;
	c4y=y2-r;
	
	rtx1=x1+r;
	rty1=y2;
	rtx2=x2-r;
	rty2=y1;
	
	rlx1=x1;
	rly1=y1+r;
	rlx2=x2;
	rly2=y2-r;
	

	
	this->outline=outline;
	borderR=0;
	borderG=0;
	borderB=0;
	borderThick=5;
	
}
roundRect::roundRect(double x1, double y1, double x2, double y2, double r, double red, double green, double blue, double borderRed, double borderGreen, double borderBlue, double borderThick)
{
	this->x1=x1;
	this->x2=x2;
	this->y1=y1;
	this->y2=y2;
	
	this->r=r;
	
	srand(time(0));
	rc=red;
	bc=blue;
	gc=green;
	
	radius=r;
	
	
	c1x=x1+r;
	c1y=y1+r;
	c2x=x1+r;
	c2y=y2-r;
	c3x=x2-r;
	c3y=y1+r;
	c4x=x2-r;
	c4y=y2-r;
	
	rtx1=x1+r;
	rty1=y2;
	rtx2=x2-r;
	rty2=y1;
	
	rlx1=x1;
	rly1=y1+r;
	rlx2=x2;
	rly2=y2-r;

	
	outline=true;
	borderR=borderRed;
	borderG=borderGreen;
	borderB=borderBlue;
	this->borderThick=borderThick;
	
}
void roundRect::changeSize(double x1, double y1, double x2, double y2)
{
	this->x1=x1;
	this->x2=x2;
	this->y1=y1;
	this->y2=y2;
	
	c1x=x1+r;
	c1y=y1+r;
	c2x=x1+r;
	c2y=y2-r;
	c3x=x2-r;
	c3y=y1+r;
	c4x=x2-r;
	c4y=y2-r;
	
	rtx1=x1+r;
	rty1=y2;
	rtx2=x2-r;
	rty2=y1;
	
	rlx1=x1;
	rly1=y1+r;
	rlx2=x2;
	rly2=y2-r;
	
}
void roundRect::drawCircle(GLdouble x1, GLdouble y1, GLdouble radius)
{
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void roundRect::drawRectangle(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(x1,y2);
	glEnd();
}

void roundRect::draw()
	{
		
		glColor3d(rc, gc, bc);
		if(!outline)
		{
	
			drawCircle(c1x, c1y, radius);
			drawCircle(c2x, c2y, radius);
			drawCircle(c3x, c3y, radius);
			drawCircle(c4x, c4y, radius);
			
			
			drawRectangle(rtx1, rty1, rtx2, rty2);
			drawRectangle(rlx1, rly1, rlx2, rly2);
			
		}
		else
		{
			
			glColor3d(borderR, borderG, borderB);

			drawRectangle(rtx1, rty1, rtx2, rty2);
			drawRectangle(rlx1, rly1, rlx2, rly2);
			
			
			
			drawCircle(c1x, c1y, radius);
			drawCircle(c2x, c2y, radius);
			drawCircle(c3x, c3y, radius);
			drawCircle(c4x, c4y, radius);
			
			
			glColor3d(rc, gc, bc);
			
			
			drawCircle(c1x+(borderThick/2), c1y+(borderThick/2), radius);
			drawCircle(c2x+(borderThick/2), c2y-(borderThick/2), radius);
			drawCircle(c3x-(borderThick/2), c3y+(borderThick/2), radius);
			drawCircle(c4x-(borderThick/2), c4y-(borderThick/2), radius);
			
			
			
			drawRectangle(rtx1+(borderThick/2), rty1-(borderThick/2), rtx2-(borderThick/2), rty2+(borderThick/2));
			drawRectangle(rlx1+(borderThick/2), rly1+(borderThick/2), rlx2-(borderThick/2), rly2-(borderThick/2));
			
			
			
		}
		
		
	}


void roundRect::randomColor()
{
	rc=(rand()%355)/355.0;
	bc=(rand()%355)/355.0;
	gc=(rand()%355)/355.0;
}



