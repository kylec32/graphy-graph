/*
 *  roundButton.h
 *  Magic Tracker
 *
 *  Created by Kyle.
 *  Copyleft 2009 GNU.
 *
 */

#ifndef ROUNDBUTTON_H
#define ROUNDBUTTON_H



#include <cstdlib>

class roundButton
	{
	private:
		double red, green, blue, rc, gc, bc;
		double borderThick, borderR, borderG, borderB;
		double x, y, r;
		char *label;
		bool outline;
	public:

		
		roundButton(double x, double y,double r, double red, double green, double blue, char *label);
		
		roundButton(double x, double y,double r, double red, double green, double blue, char *label, bool outline);
		
		roundButton(double x, double y,double r, double red, double green, double blue, char *label, double borderRed, double borderGreen, double borderBlue, double borderThickness);
		
		void setText(char *label, double red, double green, double blue);
		
		void setColor(double red, double green, double blue);
		
		bool inButton(double x, double y);
		
		void draw();
		
		void text_output(double x, double y, char * string);
		
		void changeSize(double x, double y, double r);
		
	};

#endif 