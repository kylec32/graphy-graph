/*
 * button.h
 *  Magic Tracker
 *
 *  Created by Kyle.
 *  Copyleft 2009 GNU.
 *
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <cstdlib>
#include <cmath>
#include "roundRect.h"



class button : public roundRect
{
private:
	double Y1, Y2, red, green, blue;
	char *label;
	bool outline;
	double borderThick, borderR, borderG, borderB;
	
	void text_output(GLdouble x, GLdouble y, char *string);
	
	void drawRectangle(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
	
	void drawCircle(GLdouble x1, GLdouble y1, GLdouble radius);
	
public:

	button(double x1, double y1, double x2, double y2, double r, double red, double green, double blue, char *label);

	button(double x1, double y1, double x2, double y2, double r, double red, double green, double blue, char *label, bool outline);
	
	button(double x1, double y1, double x2, double y2, double r, double red, double green, double blue, char *label, double borderRed, double borderGreen, double borderBlue, double borderThick);
	
	void setText(char *label, double red, double green, double blue);
	
	void setColor(double red, double green, double blue);
	
	void setBordColor(double red, double green, double blue);

	bool inButton(double x, double y);

	void draw();

	void changeSize(double x1, double y1, double x2, double y2);


};



#endif