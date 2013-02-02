#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "lib/glm/glm/glm.hpp"
#include "openglrenderer.h"

using namespace std;

OpenGLRenderer renderer;

void init() {
	//renderer = new OpenGLRenderer();


}
int main(int argc, char *argv[])
{


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow ("3Dgame");
	//init ();
	//glutDisplayFunc(display); 
	//glutSetCursor(GLUT_CURSOR_NONE); 
	//glutKeyboardFunc(onKeyPressed); 
	//glutKeyboardUpFunc(onKeyUp); 
	//glutMouseFunc(onMouse);
	//glutPassiveMotionFunc(onMouseMove);
	
	//glutTimerFunc(20, &OnTimer, 0);
	glutMainLoop();
}