#ifdef __APPLE__
#include <GLUT/GLUT.h>
#endif
#ifdef _WIN32
#include "glut.h"
#endif

void DrawLine(double x1, double y1, double x2, double y2);

// "Prototypes" of some color variables defined in graphics.cpp
extern GLdouble redMaterial[];
extern GLdouble greenMaterial[];
extern GLdouble brightGreenMaterial[];
extern GLdouble blueMaterial[];
extern GLdouble whiteMaterial[];
