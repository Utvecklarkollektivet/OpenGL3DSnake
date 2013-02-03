#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>

#include "../lib/glm/glm/glm.hpp"

class Camera {
private:
	glm::vec3 pos;
public:

	void lookPoint(GLint x, GLint y, GLint z);
	void lookPoint(glm::vec3 v);

	void move(GLint x, GLint y, GLint z);
	void move(glm::vec3 v);

	// Calculates and returns the view matrix
	// used by the renderer for placing the camera
	glm::mat4 getModelViewMatrix();

};

#endif