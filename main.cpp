#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "lib/glm/glm/glm.hpp"
#include "renderers/renderer.h"
#include "scene/Scene.h"
#include "scene/objects/cube.h"
#include "renderers/openglrenderer.h"

using namespace std;

/*
 Om det inte går att ladda in shaders och sådant:
 http://stackoverflow.com/questions/859501/learning-opengl-in-ubuntu
*/

Renderer *renderer = 0;
Scene *scene = 0;
Camera *camera = 0;
Cube *cube = 0;

void init() {
	renderer = new OpenGLRenderer();
	scene = new Scene(renderer);
	camera = new Camera();
	camera->move(0, 0, 3);
	cube = new Cube();
	scene->addObject(cube);
}

void display() {
	GLfloat t = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
	GLfloat b = t/1000;
	//cout << "display!" << endl;
	cube->setX( sin(b) );
	cube->setRotateX( t/70 );
	cube->setRotateY( t/70 );
	cube->setRotateZ( t/70 );

	cube->setScaleX( max(cos(b), 0.1f) );
	cube->setScaleY( max(sin(b), 0.1f) );
	cube->setScaleZ( max(cos(b), 0.1f) );

	renderer->render(scene, camera);
}

void OnTimer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(20, &OnTimer, value);

}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow ("3Dgame");
	init ();
	glutDisplayFunc(display); 
	//glutSetCursor(GLUT_CURSOR_NONE); 
	//glutKeyboardFunc(onKeyPressed); 
	//glutKeyboardUpFunc(onKeyUp); 
	//glutMouseFunc(onMouse);
	//glutPassiveMotionFunc(onMouseMove);
	
	glutTimerFunc(20, &OnTimer, 0);
	glutMainLoop();
}