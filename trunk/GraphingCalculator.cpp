// CS 2020 Graphing Calculator Starter Kit
// This code currently displays a mathematical expression which is hardcoded inside the function, MathExpression().
// Instead, prompt the user to enter a function of their choice.
// Use the expression parsing technique described in the Stack chapter of our book to draw the user's formula.
//
// For Extra Mile work, also provide a way for the user to change the domain and range (low_x, high_x, low_y, and high_y).
//
// Starter kit by Barton Stander
// Fall, 2004
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <time.h>
//#include "glut.h"
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#endif
#ifdef _WIN32
#include "glut.h"
#endif
#include <stack>
#include <string>
//#include "graphics.h"
#include "button.h"
#include "roundButton.h"



using namespace std;

// Global Variables
// Some colors you can use, or make your own and add them
// here and in graphics.h
GLfloat redMaterial[] = {0.7, 0.1, 0.2, 1.0};
GLfloat greenMaterial[] = {0.1, 0.7, 0.4, 1.0};
GLfloat brightGreenMaterial[] = {0.1, 0.9, 0.1, 1.0};
GLfloat blueMaterial[] = {0.1, 0.2, 0.7, 1.0};
GLfloat whiteMaterial[] = {1.0, 1.0, 1.0, 1.0};
GLfloat blackMaterial[] = {0.0, 0.0, 0.0, 0.0};

//float low_x = -350;
//float high_x = 350;//70
//float low_y = -250;
//float high_y = 250;//50

void reshape(int w, int h);

float vLeft=-350;
float vRight=350;
float vBottom=-250;
float vTop=250;

float disLo_x=-5;
float disHi_x=5;
float disLo_y=-5;
float disHi_y=5;

double dividerX=vRight/disHi_x;
double dividerY=vTop/disHi_y;

float screen_x = 700;
float screen_y = 500;

string equStr="x*x*x", hiXstr, loXstr, hiYstr, loYstr, postFix;

double roundiness = 5;
double bRed=.4, bGreen=.4, bBlue=.4;

double x1=vLeft*.95, ylow=vTop*.8, x2=vLeft*.75, y2=vTop*.95;
double cYlow=0, cx2=0;

button changeDimBut(x1, ylow, x2, y2, roundiness, bRed, bGreen, bBlue, "Edit");


//input buttons
button equInFil(x1, ylow, x2, y2, roundiness, 1, 1, 1, " ");
button hiXfil(x1, ylow, x2, y2, roundiness, 1, 1, 1, " ");
button loXfil(x1, ylow, x2, y2, roundiness, 1, 1, 1, " ");
button hiYfil(x1, ylow, x2, y2, roundiness, 1, 1, 1, " ");
button loYfil(x1, ylow, x2, y2, roundiness, 1, 1, 1, " ");

//clear input buttons
roundButton clEqu(x1, ylow, roundiness, 1, 0, 0, "CL");
roundButton clLoX(x1, ylow, roundiness, 1, 0, 0, "CL");
roundButton clHiX(x1, ylow, roundiness, 1, 0, 0, "CL");
roundButton clLoY(x1, ylow, roundiness, 1, 0, 0, "CL");
roundButton clHiY(x1, ylow, roundiness, 1, 0, 0, "CL");


//done button
 
button donEdit(vRight*.25, vBottom*.6, vRight*.55, vBottom*.5, roundiness, 0, 1, 0, "Done"); 


bool openEdit=false, closeEdit=false;
bool repeat = false;
bool edit = false;

bool eEqu=false, eHiX=false, eLoX=false, eHiY=false, eLoY=false;

int clickedX, clickedY;
int shiftX=0, shiftY=0;

int lastMouseX;
int lastMouseY;
float last_low_x=vLeft;
float last_high_x=vRight;
float last_low_y=vBottom;
float last_high_y=vTop;

string winTitle;
// 
// Functions that draw basic primitives
//

string InfixToPostfix(const string &infix)
{
	stack<char> operators;
	postFix.erase(0);

	bool clear=false;
	
	for(int i=0; i<infix.size(); i++)
	{
		if(infix[i] >= '0' && infix[i] <='9' || infix[i]=='x' || infix[i]=='X')
		{
			postFix+=infix[i];
		}
		else
		{
			if(infix[i]==')')
			{
				while(operators.top()!='(')
				{
					postFix+=operators.top();
					operators.pop();
				}
				operators.pop();
				clear =true;
			}

			while(!clear)
			{
	
				if(!operators.empty())
				{
					if((operators.top() == '*' || operators.top() == '/') && (infix[i]=='*' || infix[i]=='/' || infix[i] == '+' || infix[i] == '-'))
					   {
				
						   postFix+=operators.top();
						   operators.pop();
				
					   }
					   else if((operators.top() == '+' || operators.top()=='-') && (infix[i]=='+' || infix[i]=='-'))
					   {
				
						   postFix+=operators.top();
						   operators.pop();
				
					   }
					   else 
					   {
						   operators.push(infix[i]);
						   clear=true;
					   }
				}
					   else 
					   {
						   operators.push(infix[i]);
						   clear=true;
					   }
				   
					   }		   
			clear=false;
			
		}
		
		
	}
	while(!operators.empty())
	{
		postFix+=operators.top();
		operators.pop();
	}
	
	
	return postFix;
	
}


double indeX(double screen_xFrac)
{
	return screen_xFrac+vLeft;
}
double indeY(double screen_yFrac)
{
	return screen_yFrac+vBottom;
}

void DrawLine(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glEnd();
}


void DrawAxis()
{
	DrawLine(0, vBottom, 0, vTop);
	DrawLine(vLeft, 0, vRight, 0);
	for(int i=0; i<vRight; i+=dividerX)
	{
		DrawLine(i, 0, i, 10);
	}
	for(int i=0; i>vLeft; i-=dividerX)
	{
		DrawLine(i, 0, i, 10);
	}
	for(int i=0; i<vTop; i+=dividerY)
	{
		DrawLine(0, i, 10, i);
	}
	for(int i=0; i>vBottom; i-=dividerY)
	{
		DrawLine(0, i, 10, i);
	}
}

void DrawRectangle(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(x1,y2);
	glEnd();
}
float evalPostFix(float x)
{
	{
		stack<float> s;
		float rhs, lhs;
		
		//s.push(5); //puts 5 on stack
		//float rhs = s.top(); //gives you the last varible
		//s.pop();//gets rid of the top one    Does not return anything.
		//postFix = "2431--/2";
		for(unsigned int i=0; i<postFix.size(); i++)
		{
			if(postFix[i] >= '0' && postFix[i] <='9')
			{
				//s.push(atoi(gPostFix[i]));
				s.push(postFix[i]-'0');
			}
			else if(postFix[i]=='x' || postFix[i]=='X')
			{
				s.push(x);
			}
			else
			{
				float value;
				
				rhs = s.top();
				s.pop();
				lhs = s.top();
				s.pop();
				
				switch (postFix[i]) 
				{
					case '+':
						value = lhs + rhs;
						break;
					case '-':
						value = lhs - rhs;
						break;
					case '*':
						value = lhs * rhs;
						break;
					case '/':
						value = lhs / rhs;
						break;
					default:
						break;
				}
				s.push(value);
			}
		}
		
		float v = s.top();
		s.pop();
		//assert(s.empty());
		return v;//last item;
}
	
}
float MathExpression(float x) 
{
	//float y = .1*x*x*x;
	float y = evalPostFix(x);
	return y;
}

void DrawCurve()
{
	
	//float x = vLeft/dividerX;
	float x = disLo_x;

	float y = MathExpression(x);
	float increment = (vRight - vLeft)/(vRight-vLeft);
	glBegin(GL_LINE_STRIP);
	for(x=vLeft+increment; x<=vRight; x += increment)
	{
		
		if(x<=0)
		{
			y = MathExpression((x/dividerX)*disHi_x);
			glVertex2f(x*(disHi_x-disLo_x),(y*dividerY)*disHi_y);
		}
		else if(x>0)
		{
			y = MathExpression((x/dividerX)*disLo_x);
			glVertex2f(x*(disHi_x-disLo_x),(y*dividerY)*disLo_y);
		}
		
	}
	glEnd();
}
void text_output(GLdouble x, GLdouble y, char *string)
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
//
// GLUT callback functions
//

void fixEvery()
{
		char buffer[200];
	
	if(!edit && !openEdit && !closeEdit)
	{
		
		
	double x1=indeX(screen_x*.01), ylow=indeY(screen_y*.85), x2=indeX(screen_x*.15), y2=indeY(screen_y*.98);
	changeDimBut.changeSize(x1, ylow, x2, y2);
		
		sprintf(buffer, "%f", vRight/dividerX);
		hiXstr=buffer;
		sprintf(buffer, "%f", vLeft/dividerX);
		loXstr=buffer;
		sprintf(buffer, "%f", vTop/dividerY);
		hiYstr=buffer;
		sprintf(buffer, "%f", vBottom/dividerY);
		loYstr=buffer;
		
	}
	
	double dividerX=vRight/disHi_x;
	double dividerY=vTop/disHi_y;
		
}

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	
	fixEvery();
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3fv(redMaterial);
	DrawAxis();

	glColor3fv(whiteMaterial);
	DrawCurve();
	
	
	
	
	changeDimBut.draw();
	
	if(edit)
	{
		glColor3fv(whiteMaterial);
		
		char buffer[100];
		char *tempP;
		
	
		
		text_output(indeX(screen_x*.25), indeY(screen_y*.9), "Equation Input:");
		equInFil.changeSize(indeX(screen_x*.47), indeY(screen_y*.87), indeX(screen_x*.75), indeY(screen_y*.92));
		clEqu.changeSize(indeX(screen_x*.78), indeY(screen_y*.9), roundiness*2.5);
		if(eEqu)
			equInFil.setColor(0,1,1);
		else 
			equInFil.setColor(1,1,1);

		equInFil.draw();
		clEqu.draw();
		
			
		
		
	
		
		text_output(indeX(screen_x*.35), indeY(screen_y*.78), "High X:");
		hiXfil.changeSize(indeX(screen_x*.47), indeY(screen_y*.75), indeX(screen_x*.75), indeY(screen_y*.8));
		clHiX.changeSize(indeX(screen_x*.78), indeY(screen_y*.78), roundiness*2.5);
		if(eHiX)
			hiXfil.setColor(0,1,1);
		else
			hiXfil.setColor(1,1,1);
		
		hiXfil.draw();
		clHiX.draw();	
		
		sprintf(buffer, "%f", vRight/dividerX);
		text_output(indeX(screen_x*.8), indeY(screen_y*.78), buffer);
		
		text_output(indeX(screen_x*.36), indeY(screen_y*.69), "Low X:");
		loXfil.changeSize(indeX(screen_x*.47), indeY(screen_y*.66), indeX(screen_x*.75), indeY(screen_y*.71));
		clLoX.changeSize(indeX(screen_x*.78), indeY(screen_y*.69), roundiness*2.5);
		if(eLoX)
			loXfil.setColor(0,1,1);
		else
			loXfil.setColor(1,1,1);
		
		loXfil.draw();
		clLoX.draw();
		
		sprintf(buffer, "%f", vLeft/dividerX);
		text_output(indeX(screen_x*.8), indeY(screen_y*.69), buffer);
		
		text_output(indeX(screen_x*.35), indeY(screen_y*.5), "High Y:");
		hiYfil.changeSize(indeX(screen_x*.47), indeY(screen_y*.47), indeX(screen_x*.75), indeY(screen_y*.52));
		clHiY.changeSize(indeX(screen_x*.78), indeY(screen_y*.5), roundiness*2.5);
		if(eHiY)
			hiYfil.setColor(0,1,1);
		else
			hiYfil.setColor(1,1,1);
		
		hiYfil.draw();
		clHiY.draw();
		
		sprintf(buffer, "%f", vTop/dividerY);
		text_output(indeX(screen_x*.8), indeY(screen_y*.5), buffer);
		
		text_output(indeX(screen_x*.36), indeY(screen_y*.4), "Low Y:");
		loYfil.changeSize(indeX(screen_x*.47), indeY(screen_y*.37), indeX(screen_x*.75), indeY(screen_y*.42));
		clLoY.changeSize(indeX(screen_x*.78), indeY(screen_y*.4), roundiness*2.5);
		if(eLoY)
			loYfil.setColor(0,1,1);
		else
			loYfil.setColor(1,1,1);
		
		loYfil.draw();
		clLoY.draw();
		
		sprintf(buffer, "%f", vBottom/dividerY);
		text_output(indeX(screen_x*.8), indeY(screen_y*.4), buffer);
		
		donEdit.changeSize(indeX(screen_x*.7), indeY(screen_y*.15), indeX(screen_x*.9), indeY(screen_y*.25));
		donEdit.draw();
		
		glColor3fv(blackMaterial);
		tempP=new char[equStr.size()+1];
		strcpy(tempP,equStr.c_str());
		text_output(indeX(screen_x*.5), indeY(screen_y*.89), tempP);
		delete []tempP;
		tempP=new char[hiXstr.size()+1];
		strcpy(tempP,hiXstr.c_str());
		text_output(indeX(screen_x*.5), indeY(screen_y*.77), tempP);
		delete []tempP;
		tempP=new char[loXstr.size()+1];
		strcpy(tempP,loXstr.c_str());
		text_output(indeX(screen_x*.5), indeY(screen_y*.68), tempP);
		delete []tempP;
		tempP=new char[hiYstr.size()+1];
		strcpy(tempP,hiYstr.c_str());
		text_output(indeX(screen_x*.5), indeY(screen_y*.49), tempP);
		delete []tempP;
		tempP=new char[loYstr.size()+1];
		strcpy(tempP,loYstr.c_str());
		text_output(indeX(screen_x*.5), indeY(screen_y*.39), tempP);
		delete []tempP;
		
		
		glutSwapBuffers();
		glutPostRedisplay();
	}
	

	
	if(repeat)
	{
		changeDimBut.setText(" ", bRed, bGreen, bBlue);
		
		if(openEdit)
		
		{
			double x1=indeX(screen_x*.01), ylow=indeY(screen_y*.85)+cYlow, x2=indeX(screen_x*.15)+cx2, y2=indeY(screen_y*.98);
			if(ylow>=indeY(screen_y*.11))
			{
				cYlow-=1;
				cx2+=1.48;
				//double x1=indeX(screen_x*.01), ylow=indeY(screen_y*.85)+cYlow, x2=indeX(screen_x*.15)+cx2, y2=indeY(screen_y*.98);
				changeDimBut.changeSize(x1, ylow, x2, y2);
			}
			else 
			{
				repeat=false;
				openEdit=false;
				edit=true;
			}
		}
		else if(closeEdit)
		{
			if(ylow+cYlow<=indeY(screen_y*.85))
			{
				cYlow+=1;
				cx2-=1.48;
				double x1=indeX(screen_x*.01), ylow=indeY(screen_y*.85)+cYlow, x2=indeX(screen_x*.15)+cx2, y2=indeY(screen_y*.98);
				changeDimBut.changeSize(x1, ylow, x2, y2);
			}
			else
			{
				changeDimBut.setText("Edit", bRed, bGreen, bBlue);
				repeat=false;
				closeEdit=false;
				cYlow=0;
				cx2=0;
			}
		}

		glutPostRedisplay();
	}
	glutSwapBuffers();
	
}
void keyboard(unsigned char c, int x, int y)
{
	
	if(edit && c!=27)
	{
		if(eEqu)
			equStr+=c;
		else if(eHiX)
			hiXstr+=c;
		else if(eLoX)
			loXstr+=c;
		else if(eHiY)
			hiYstr+=c;
		else if(eLoY)
			loYstr+=c;
		
	}
	else 
	{

	switch (c) 
	{
		case 27: // escape character means to quit the program
			
				exit(0);
			break;
		case 'c':
			dividerX;
			dividerY;
			disLo_x;
			disHi_x;
			disLo_y;
			disHi_y;
			eEqu;
			eHiX;
			eLoX;
			eHiY;
			eLoY;
			
			break;
		case 'e':
			evalPostFix(2.0f);
			break;
		case 't':
			InfixToPostfix("Blah");
			break;

		default:
			return; // if we don't care, return without glutPostRedisplay()
	}
	}
	
	glutPostRedisplay();
}
void mouse(int mouse_button, int state, int x, int y)
{
	y=screen_y-y+vBottom;
	x=x+vLeft;
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		clickedX=x;
		clickedY=y;
		if(!edit)
		{
			if(changeDimBut.inButton(x, y))
			{
				repeat=true;
				openEdit=true;
			}
			cout<<hiXstr;
		}
		
		else if(edit)
		{
			if(donEdit.inButton(x, y))
			{
				edit=false;
				closeEdit=true;
				openEdit=false;
				repeat=true;
				eEqu=false;
				eHiX=false;
				eLoX=false;
				eHiY=false;
				eLoY=false;
				InfixToPostfix(equStr);
				disHi_x=atoi(hiXstr.c_str());
				cout<<disHi_x;
				disLo_x=atoi(loXstr.c_str());
				disHi_y=atoi(hiYstr.c_str());
				disLo_y=atoi(loYstr.c_str());
				winTitle = "Graphing Calculator - "+equStr;
				glutSetWindowTitle(winTitle.c_str());
				
				vLeft=dividerX*disLo_x;
				vRight=dividerX*disHi_x;
				vTop=dividerY*disHi_y;
				vBottom=dividerY*disLo_y;

				reshape(screen_x, screen_y);

				
			}
			else if(equInFil.inButton(x,y))
			{
				eEqu=true;
				eHiX=false;
				eLoX=false;
				eHiY=false;
				eLoY=false;
			}	
			else if(hiXfil.inButton(x,y))
			{
				eEqu=false;
				eHiX=true;
				eLoX=false;
				eHiY=false;
				eLoY=false;
			}
			else if(loXfil.inButton(x,y))
			{
				eEqu=false;
				eHiX=false;
				eLoX=true;
				eHiY=false;
				eLoY=false;
			}
			else if(hiYfil.inButton(x,y))
			{
				eEqu=false;
				eHiX=false;
				eLoX=false;
				eHiY=true;
				eLoY=false;
			}
			else if(loYfil.inButton(x,y))
			{
				eEqu=false;
				eHiX=false;
				eLoX=false;
				eHiY=false;
				eLoY=true;
			}
			else if(clEqu.inButton(x,y))
			{
				equStr.erase(0);
			}
			else if(clLoX.inButton(x,y))
			{
				loXstr.erase(0);
			}
			else if(clHiX.inButton(x,y))
			{
				hiXstr.erase(0);
			}
			else if(clLoY.inButton(x,y))
			{
				loYstr.erase(0);
			}
			else if(clHiY.inButton(x,y))
			{
				hiYstr.erase(0);
			}
			
						
		}
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		lastMouseX=x;
		lastMouseY=y;
		//last_low_x=low_x;
		last_low_x=vLeft;
		 //last_high_x=high_x;
		last_high_x=vRight;
		 //last_low_y=low_y;
		last_low_y=vBottom;
		//last_high_y=high_y;
		last_high_y=vTop;
		//if(clickedX<0 && x<0)
//		{
//		shiftX= shiftX+(clickedX-x);
//		shiftY= shiftY+(clickedY-y);
//		}
//		else
//		{
//			shiftX= shiftX+(clickedX+x);
//			shiftY= shiftY+(clickedY+y);	
//		}
		if(clickedX>x)
		{
				shiftX= shiftX+(clickedX-x);
		}
		else {
			shiftX = shiftX + (x-clickedX);
		}
		if(clickedY>y)
			shiftY=shiftY+(clickedY-y);
		else {
			shiftY=shiftY+(y-clickedY);
		}


	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
	}
	glutPostRedisplay();
}

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0,0,w,h);

	// go into 2D mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the world coordinates.
	gluOrtho2D(vLeft, vRight, vBottom, vTop);
	glMatrixMode(GL_MODELVIEW);

}
void motion(int x, int y)
{
	
	
	
	y=screen_y-y+vBottom;
	x=x+vLeft;
	//y=screen_y-y+vBottom;
	//x=x+vLeft;
		
	
	vLeft=last_low_x + (clickedX - x);
	vRight=last_high_x + (clickedX -x);
	vTop=last_high_y + (clickedY - y);
	vBottom=last_low_y + (clickedY -y);
	
	reshape(screen_x, screen_y);
	glutPostRedisplay();
	
	
	
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	postFix=InfixToPostfix(equStr);
	
	//string infix;
//	cout<<"Enter Expression: ";
//	cin>>infix;
//	postFix=InfixToPostfix(infix);
	
	winTitle = "Graphing Calculator - " + equStr;
	glutCreateWindow(winTitle.c_str());

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	
	glClearColor(0, 0, 0, 0);
	
	glutMainLoop();

	return 0;
}
