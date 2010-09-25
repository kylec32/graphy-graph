/*
 *  button.cpp
 *  Magic Tracker
 *
 *  Created by Kyle.
 *  Copyleft 2009 GNU.
 *
 */



#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "button.h"
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#endif
#ifdef _WIN32
#include "glut.h"
#endif

button::button(double x1, double y1, double x2, double y2, double r, double red, double green, double blue, char *label):roundRect(x1, y1, x2, y2, r, red, green, blue)
{
	this->label=label;
	Y1=y1;
	Y2=y2;
	red=0;
	green=0;
	blue=0;
	outline=false;
}

button::button(double x1, double y1, double x2, double y2, double r, double red, double green, double blue, char *label, bool outline):roundRect(x1, y1, x2, y2, r, red, green, blue)
{
	this->label=label;
	Y1=y1;
	Y2=y2;
	red=0;
	green=0;
	blue=0;
	this->outline=outline;
	borderThick=5;
	borderR=0;
	borderG=0;
	borderB=0;
}

button::button(double x1, double y1, double x2, double y2, double r, double red, double green, double blue, char *label, double borderRed, double borderGreen, double borderBlue, double borderThick):roundRect(x1, y1, x2, y2, r, red, green, blue)
{
	this->label=label;
	Y1=y1;
	Y2=y2;
	red=0;
	green=0;
	blue=0;
	outline=true;
	this->borderThick=borderThick;
	borderR=borderRed;
	borderG=borderGreen;
	borderB=borderBlue;
}

void button::changeSize(double x1, double y1, double x2, double y2)
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

void button::setText(char *label, double red, double green, double blue)
	{
		this->label=label;
		this->green=green;
		this->red=red;
		this->blue=blue;
	}


bool button::inButton(double x, double y)
	{
		if(x>x1 && x< x2 && y<y2 && y>y1)
			return true;
		else
			return false;
	}

void button::draw()
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
		
			
			drawCircle(c1x, c1y, radius);
			drawCircle(c2x, c2y, radius);
			drawCircle(c3x, c3y, radius);
			drawCircle(c4x, c4y, radius);
			
			
			drawRectangle(rtx1, rty1, rtx2, rty2);
			drawRectangle(rlx1, rly1, rlx2, rly2);
			
			
			
			
			glColor3d(rc, gc, bc);
			
			
			drawCircle(c1x+(borderThick/2), c1y+(borderThick/2), radius);
			drawCircle(c2x+(borderThick/2), c2y-(borderThick/2), radius);
			drawCircle(c3x-(borderThick/2), c3y+(borderThick/2), radius);
			drawCircle(c4x-(borderThick/2), c4y-(borderThick/2), radius);
			
			
			
			drawRectangle(rtx1+(borderThick/2), rty1-(borderThick/2), rtx2-(borderThick/2), rty2+(borderThick/2));
			drawRectangle(rlx1+(borderThick/2), rly1+(borderThick/2), rlx2-(borderThick/2), rly2-(borderThick/2));
			
			
			
		}
		
		glColor3d(red, green, blue);
		glColor3d(1,1,1);
		int len;
		len = (int) strlen(label);
		text_output(((x1+x2)/2)-(len*4.5), (y1+y2)/2, label);
		//text_output(-4.6, 4.55, label);
		

	}

void button::setColor(double red, double green, double blue)
{
	this->rc=red;
	this->gc=green;
	this->bc=blue;
}

void button::text_output(GLdouble x, GLdouble y, char *string)
{
	void *font = GLUT_BITMAP_9_BY_15;
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	
	int len, i;
	glRasterPos2d(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(font, string[i]);
	}
	
    glDisable(GL_BLEND);
	
	
	
}

void button::drawRectangle(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(x1,y2);
	glEnd();
	
}

void button::drawCircle(GLdouble x1, GLdouble y1, GLdouble radius)
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

void button::setBordColor(double red, double green, double blue)
{
	borderR=red;
	borderG=green;
	borderB=blue;
}
