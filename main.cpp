#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "lib/glm/glm/glm.hpp"
#include "renderers/renderer.h"
#include "scene/Scene.h"
#include "renderers/openglrenderer.h"

using namespace std;

/*
 Om det inte går att ladda in shaders och sådant:
 http://stackoverflow.com/questions/859501/learning-opengl-in-ubuntu
*/

Renderer *renderer = 0;

void init() {
	renderer = new OpenGLRenderer();


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