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
#include "lib/glm/glm/gtc/matrix_access.hpp"
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
const GLfloat UPDATE_RATE = 100; // ms

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
bool isOutsideBoundaries(glm::vec3 p) {
	if ( p.x <= 0 || p.x >= BOARD_WIDTH*2 || 
		p.z <= 0 || p.z >= BOARD_HEIGHT*2) {
		return true;
	} else {
		return false;
	}
}

// colliding with the tail?
bool isOnTail(glm::vec3 p) {
	for (auto it = tail.begin(); it != tail.end(); ++it) {
		if (p.x == (*it)->getX() && 
			p.z == (*it)->getZ()) {
			return true;
		}
	}
	return false;
}

void placeCandy() {
	GLint rndX = rand() % (BOARD_WIDTH-1);
	GLint rndZ = rand() % (BOARD_HEIGHT-1);
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
			//cout << "A" << prev <<endl;
			tail[i]->setX( tail[prev]->getX());
			tail[i]->setZ( tail[prev]->getZ());
		} else {
			//cout << "B" << endl;
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

void start() {
	// Snake head placement
	if (cube == 0) {
		cube = new Cube();
		scene->addObject(cube);
	}
	cube->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
	cube->setX(2);
	cube->setY(2);
	cube->setZ(BOARD_HEIGHT*2-2);
	

	// Candy placement
	if (candy == 0) {
		candy = new Cube();
		scene->addObject(candy);
	}
	candy->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
	candy->setY(2);
	placeCandy();

	// If the snake got a tail, delete it!
	if (tail.size() > 0) {
		for (auto it = tail.begin(); it != tail.end(); ++it) {
			// Delete it from the scene
			scene->removeObject(*it);
			// Free allocated memory
			delete *it;
		}
		// Clear the list
		tail.clear();
	}
}

void init() {

	srand(time(NULL));


	renderer = new OpenGLRenderer();
	scene = new Scene(renderer);
	camera = new Camera();
	
	// Camera right forward
	camera->move(10.0f, 10.0f, 60.0f);
	camera->lookPoint(glm::vec3(10.0f, 0, 10.0f));

	// Camera looking left
	//camera->move(10.0f, 10.0f, 60.0f);
	//camera->lookPoint(glm::vec3(-10.0f, 0, 1.0f));
	
	/*
	//	Camera above
	camera->move(10.0f, 60.0f, -10.0f);
	camera->lookPoint(10.0f, 0, 0);
	camera->setUp(glm::vec3(0, 0, -1.0f));
	*/
	// Start the game!
	start();


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

		// temp
		camera->setPos( cube->getPos() - snakeForward*glm::vec3(4));
		camera->setY(5);
		camera->lookPoint(cube->getPos() );

			// Check collisions on snake itself and boundaries
		// ...
		/*if (isOutsideBoundaries( cube->getPos() + snakeForward)) {
			// Collided border
			cout << "Outside of boundries" << endl;
			start();
		}
		*/
		if (isOnTail(cube->getPos() + snakeForward)) {
			cout << "Collided with tail" << endl;
		}
		if (isOnCandy()) {
			//cout << "Candycollision" << endl;
			addTail();
			placeCandy();
		}

		moveTail();
		cube->move(snakeForward);
		//cout << "Snake pos " << cube->getX() << "<->" << cube->getZ() << endl;

		lastUpdate = t;
	}
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
	glm::mat4 view = camera->getModelViewMatrix();
	glm::vec3 rightVector = glm::vec3(view[0][0], view[1][0], view[2][0]);

	if (k == 'w' && snakeForward.z != 2.0f) {
		snakeForward = glm::vec3(0.0f, 0.0f, -2.0f);
	} else if (k == 's' && snakeForward.z != -2.0f) {
		snakeForward = glm::vec3(0.0f, 0.0f, 2.0f);
	} else if (k == 'a'  && snakeForward.x != 2.0f) {
		//snakeForward = glm::vec3(-2.0f, 0.0f, 0.0f);
		snakeForward = glm::vec3(-1.0f, -1.0f, -1.0f) * rightVector;
	} else if (k == 'd' && snakeForward.x != -2.0f) {
		//snakeForward = glm::vec3(2.0f, 0.0f, 0.0f);
		snakeForward = rightVector;
	} else if (k == 'r') {
		start();
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