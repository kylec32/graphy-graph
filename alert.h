/*
 *  alert.h
 *  
 *  Copyleft 2010 YottaPlex.
 *
 */

#ifndef ALERT_H
#define ALERT_H

#include <cstdlib>
#include <cmath>
#include "roundRect.h"
#include "button.h"



class alert : public roundRect
{
private:
	double Y1, Y2, red, green, blue;
	char *message;
	button *ok;
	
	void text_output(GLdouble x, GLdouble y, char *string);
	
	void drawRectangle(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
	
	void drawCircle(GLdouble x1, GLdouble y1, GLdouble radius);
public:
	
	alert(double x1, double y1, double x2, double y2, double r, char *message);
	
	alert(double x1, double y1, double x2, double y2, double r, double red, double green, double blue, char *message);
	
	void setText(char *message, double red, double green, double blue);
	
	void setColor(double red, double green, double blue);
	
	void draw();
	
	void changeSize(double x1, double y1, double x2, double y2);
	
	bool closeEdit(int x, int y);
	
	
};



#endif