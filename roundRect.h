/*
 *  roundRect.h
 *  Magic Tracker
 *
 *  Created by Kyle.
 *  Copyleft 2009 GNU.
 *
 */




#ifndef ROUNDRECT_H
#define ROUNDRECT_H

//#include "graphics.h"
//#include <GLUT/GLUT.h>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#endif
#ifdef _WIN32
#include "glut.h"
#endif


class roundRect
{
protected:
	double c1x, c1y, c2x, c2y, c3x, c3y, c4x, c4y;
	double rtx1, rtx2, rty1, rty2;
	double rlx1, rlx2, rly1, rly2;
	double radius;
	double mainRx1, mainRy1, mainRx2, mainRy2;
	double rc, gc, bc;
	double x1, x2, y1, y2;
	double r;
	
	bool outline;
	
	double borderThick, borderR, borderG, borderB;
	void drawCircle(GLdouble x1, GLdouble y1, GLdouble radius);
	void drawRectangle(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
	void randomColor();

public:
	roundRect(double x1, double y1, double x2, double y2, double r, double red, double green, double blue);
	roundRect(double x1, double y1, double x2, double y2, double r, double red, double green, double blue, bool outline);
	roundRect(double x1, double y1, double x2, double y2, double r, double red, double green, double blue, double borderRed, double borderGreen, double borderBlue, double borderThick);
	void draw();
	
	bool inRect(double x, double y);
	

	void changeSize(double x1, double y1, double x2, double y2);


};

#endif