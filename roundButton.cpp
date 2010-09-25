/*
 *  roundButton.cpp
 *  Magic Tracker
 *
 *  Created by Kyle.
 *  Copyleft 2009 GNU.
 *
 */


#include "roundButton.h"
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#endif
#ifdef _WIN32
#include "glut.h"
#endif
#include <stdio.h>
#include <string.h>
#include <math.h>


roundButton::roundButton(double x, double y,double r, double red, double green, double blue, char *label)
{
	this->label=label;
	
	this->red=1;
	this->green=1;
	this->blue=1;
	rc=red;
	gc=green;
	bc=blue;
	
	this->x=x;
	this->y=y;
	this->r=r;
	outline=false;
	
}

roundButton::roundButton(double x, double y,double r, double red, double green, double blue, char *label, bool outline)
{
	this->label=label;
	
	this->red=0;
	this->green=0;
	this->blue=0;
	rc=red;
	gc=green;
	bc=blue;
	
	this->x=x;
	this->y=y;
	this->r=r;
	this->outline=outline;
	borderThick=5;
	borderR=0;
	borderG=0;
	borderB=0;
	
}

roundButton::roundButton(double x, double y,double r, double red, double green, double blue, char *label, double borderRed, double borderGreen, double borderBlue, double borderThickness)
{
	this->label=label;
	
	this->red=0;
	this->green=0;
	this->blue=0;
	rc=red;
	gc=green;
	bc=blue;
	
	this->x=x;
	this->y=y;
	this->r=r;
	outline=true;
	borderThick=5;
	borderR=borderRed;
	borderG=borderGreen;
	borderB=borderBlue;
	
}

void roundButton::setText(char *label, double red, double green, double blue)
{
	this->label=label;
	this->green=green;
	this->red=red;
	this->blue=blue;
}


bool roundButton::inButton(double x1, double y1)
{
	if((sqrt((pow(x1-x,2)+pow(y1-y,2))))<=r)
		return true;
	else
		return false;
}

void roundButton::text_output(double x, double y, char * string)
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

void roundButton::draw()
{
	glColor3d(rc, gc, bc);
	if(!outline)
	{

		glBegin(GL_POLYGON);
		for(int i=0; i<32; i++)
		{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x1 = x + r * cos(theta);
		double y1= y + r * sin(theta);
		glVertex2d(x1, y1);
		}
		glEnd();
	
	}
	else
	{
		glColor3d(borderR, borderG, borderB);
		glBegin(GL_POLYGON);
		for(int i=0; i<32; i++)
		{
			double theta = (double)i/32.0 * 2.0 * 3.1415926;
			double x1 = x + r * cos(theta);
			double y1= y + r * sin(theta);
			glVertex2d(x1, y1);
		}
		glEnd();
		glColor3d(rc, gc, bc);
		glBegin(GL_POLYGON);
		for(int i=0; i<32; i++)
		{
			double theta = (double)i/32.0 * 2.0 * 3.1415926;
			double x1 = x + (r-borderThick) * cos(theta);
			double y1= y + (r-borderThick) * sin(theta);
			glVertex2d(x1, y1);
		}
		glEnd();
	}
	
		glColor3d(red, green, blue);
		int len;
		len = (int) strlen(label);
		text_output(x-(len*4.5), y, label);
	
	
}

void roundButton::setColor(double red, double green, double blue)
{
	this->rc=red;
	this->gc=green;
	this->bc=blue;
}

void roundButton::changeSize(double x, double y, double r)
{
	this->x=x;
	this->y=y;
	this->r=r;
}
