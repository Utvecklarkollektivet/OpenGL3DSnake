#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
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

const GLint BOARD_WIDTH = 10;
const GLint BOARD_HEIGHT = 10;
const GLfloat UPDATE_RATE = 200; // ms

GLfloat lastUpdate = 0;
glm::vec3 snakeForward;

Cube *candy = 0;

Renderer *renderer = 0;
Scene *scene = 0;
Camera *camera = 0;
Cube *cube = 0;

//std::vector<Cube> plane;
std::vector<Cube*> tail;

bool isOnCandy() {
	GLfloat headX;
	GLfloat headZ;
	GLfloat candyX;
	GLfloat candyZ;

	headX = cube->getX();
	headZ = cube->getZ();

	candyX = candy->getX();
	candyZ = candy->getZ();
	
	return (headX == candyX && headZ == candyZ);
}
// outside the boundaries?
bool isOutsideBoundaries() {

}

// colliding with the tail?
bool isOnTail() {

}

void placeCandy() {
	GLint rndX = rand() % BOARD_WIDTH;
	GLint rndZ = rand() % BOARD_HEIGHT;
	rndX *= 2;
	rndZ *= 2;

	candy->setX(rndX);
	candy->setZ(rndZ);
	cout << "Placed candy on " << rndX << " <-> " << rndZ << endl;
	//candy->setZ(17*2);
}

void addTail() {
	Cube *t = new Cube();
	
	t->setY(2);
	t->setScale(glm::vec3(2.0f,2.0f,2.0f));

	if (tail.size() == 0) {
		t->setX(cube->getX());
		t->setZ(cube->getZ());
	} else {
		Cube *lastTail = tail.back();
		t->setX(lastTail->getX());
		t->setZ(lastTail->getZ());
	}

	tail.push_back(t);
	scene->addObject(t);
}

void moveTail() {
	for (GLint i = tail.size() - 1; i >= 0; --i) {
		GLint prev = i-1;
		//Cube *frontTail = tail[i-1];
		if ( prev >= 0) {
			cout << "A" << prev <<endl;
			tail[i]->setX( tail[prev]->getX());
			tail[i]->setZ( tail[prev]->getZ());
		} else {
			cout << "B" << endl;
			tail[i]->setX(cube->getX());
			tail[i]->setZ(cube->getZ());
		}
	}
	/*for (auto it = tail.end(); it != tail.begin(); --it) {
		//Cube *frontTail = (it - 1);
		if (frontTail != tail.begin()) {
			(*it)->setX(frontTail->getX());
			(*it)->setZ(frontTail->getZ());
		} else {
			(*it)->setX(cube->getX());
			(*it)->setZ(cube->getZ());
		}
	}
	*/
}

void init() {

	srand(time(NULL));


	renderer = new OpenGLRenderer();
	scene = new Scene(renderer);
	camera = new Camera();
	camera->move(10.0f, 10.0f, 60.0f);
	cube = new Cube();
	cube->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
	cube->setY(2);
	cube->setZ(19*2);
	scene->addObject(cube);

	// Candy placement
	candy = new Cube();
	scene->addObject(candy);
	candy->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
	candy->setY(2);
	placeCandy();

	// The board
	/*
	for(auto i = 0; i <= BOARD_WIDTH; ++i) {
		for (auto j = 0; j <= BOARD_HEIGHT; ++j) {
			Cube *c = new Cube();
			c->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
			c->setX(i*2);
			c->setZ(j*2);
			scene->addObject(c);
		}
	}*/
}

void cleanup() {
	delete renderer;
	delete scene;
	delete camera;
	delete cube;
}

void display() {
	GLfloat t = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
	GLfloat diff = t - lastUpdate;
	
	GLfloat b = t/1000;
	


	if (diff >= UPDATE_RATE) {

			// Check collisions on snake itself and boundaries
		// ...
		if (isOnCandy()) {
			//cout << "Candycollision" << endl;
			addTail();
			placeCandy();
		}

		moveTail();
		cube->move(snakeForward);
		cout << "Snake pos " << cube->getX() << "<->" << cube->getZ() << endl;
		/*
		// Set all the tail the front tail position
		for (auto it = tail.end(); it != tail.begin(); --it) {

		}*/

		lastUpdate = t;
	}
	//cout << "display!" << endl;
	/*
	cube->setX( sin(b) );
	cube->setRotateX( t/70 );
	cube->setRotateY( t/70 );
	cube->setRotateZ( t/70 );

	cube->setScaleX( max(cos(b), 0.1f) );
	cube->setScaleY( max(sin(b), 0.1f) );
	cube->setScaleZ( max(cos(b), 0.1f) );
	
	camera->setPos( sin(b) * 5, 0, cos(b) * 5);
	*/
	renderer->render(scene, camera);
}



void reshape(GLint newWidth, GLint newHeight) {
	//std::cout << "!!! width: " << newWidth << " height: " << newHeight << std::endl;
	renderer->onResizeScreen();
	glutPostRedisplay();
}

void OnTimer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(20, &OnTimer, value);

}

void onKeyPressed(unsigned char k, int x, int y) {
	if (k == 'w') {
		snakeForward = glm::vec3(0.0f, 0.0f, -2.0f);
	} else if (k == 's') {
		snakeForward = glm::vec3(0.0f, 0.0f, 2.0f);
	} else if (k == 'a') {
		snakeForward = glm::vec3(-2.0f, 0.0f, 0.0f);
	} else if (k == 'd') {
		snakeForward = glm::vec3(2.0f, 0.0f, 0.0f);
	}
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
	glutReshapeFunc(reshape);
	//glutSetCursor(GLUT_CURSOR_NONE); 
	glutKeyboardFunc(onKeyPressed); 
	//glutKeyboardUpFunc(onKeyUp); 
	//glutMouseFunc(onMouse);
	//glutPassiveMotionFunc(onMouseMove);
	
	glutTimerFunc(20, &OnTimer, 0);
	atexit(cleanup);
	glutMainLoop();
}