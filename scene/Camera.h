#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>

#include "../lib/glm/glm/glm.hpp"
#include "../lib/glm/glm/gtc/matrix_transform.hpp"

class Camera {
private:
	glm::vec3 pos;
	glm::vec3 eye;
	glm::vec3 up;
public:
	Camera();

	void lookPoint(GLfloat x, GLfloat y, GLfloat z);
	void lookPoint(glm::vec3 v);

	void move(GLfloat x, GLfloat y, GLfloat z);
	void move(glm::vec3 v);

	// Calculates and returns the view matrix
	// used by the renderer for placing the camera
	glm::mat4 getModelViewMatrix();

};

#endif