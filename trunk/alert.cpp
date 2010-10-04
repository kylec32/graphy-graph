/*
 *  alert.cpp
 *
 *  Copyleft 2010 YottaPlex.
 *
 */

#include "alert.h"

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

alert::alert(double x1, double y1, double x2, double y2, double r, char *message):roundRect(x1, y1, x2, y2, r, red, green, blue)
{
	this->message=message;
	Y1=y1;
	Y2=y2;
	ok=new button(((x1+x2)/2)-20, ((y1+y2)/2)-20, ((x1+x2)/2)+20, ((y1+y2)/2)+20, 10, 0.0, 0.0, 0.0, "OK"); 
	//ok=new button(x1, y1, x1+50, y1+50, 10, 1.0, 0.0, 0.0, "OK"); 
	//ok=new button(x1, ylow, x2, y2, roundiness, 1, 1, 1, " ");
	
}

alert::alert(double x1, double y1, double x2, double y2, double r, double red, double green, double blue, char *message):roundRect(x1, y1, x2, y2, r, red, green, blue)
{
	this->message=message;
	Y1=y1;
	Y2=y2;
	red=0;
	green=0;
	blue=0;
	ok=new button(((x1+x2)/2)-20, ((y1+y2)*.47)-30, ((x1+x2)/2)+20, ((y1+y2)*.47), 10, 0.0, 0.0, 0.0, "OK"); 
}

void alert::changeSize(double x1, double y1, double x2, double y2)
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

void alert::setText(char *message, double red, double green, double blue)
{
	this->message=message;
	this->green=green;
	this->red=red;
	this->blue=blue;
}


void alert::draw()
{
	
	glColor3d(rc, gc, bc);
		
		drawCircle(c1x, c1y, radius);
		drawCircle(c2x, c2y, radius);
		drawCircle(c3x, c3y, radius);
		drawCircle(c4x, c4y, radius);
		
		
		drawRectangle(rtx1, rty1, rtx2, rty2);
		drawRectangle(rlx1, rly1, rlx2, rly2);

	
	glColor3d(red, green, blue);
	glColor3d(1,1,1);
	int len;
	len = (int) strlen(message);
	text_output(((x1+x2)/2)-(len*4.5), (y1+y2)*.6, message);

	ok->draw();
	
}

void alert::setColor(double red, double green, double blue)
{
	this->rc=red;
	this->gc=green;
	this->bc=blue;
}

void alert::text_output(GLdouble x, GLdouble y, char *string)
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

void alert::drawRectangle(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(x1,y2);
	glEnd();
	
}

void alert::drawCircle(GLdouble x1, GLdouble y1, GLdouble radius)
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

bool alert::closeEdit(int x, int y)
{
	return ok->inButton(x,y);
}
