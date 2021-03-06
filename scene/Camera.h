#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>

#include "../lib/glm/glm/glm.hpp"
#include "../lib/glm/glm/gtc/matrix_transform.hpp"

class Camera {
private:
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;
public:
	Camera();

	void lookPoint(GLfloat x, GLfloat y, GLfloat z);
	void lookPoint(glm::vec3 v);

	void move(GLfloat x, GLfloat y, GLfloat z);
	void move(glm::vec3 v);

	void setX(GLfloat p);
	void setY(GLfloat p);
	void setZ(GLfloat p);
	void setPos(GLfloat x, GLfloat y, GLfloat z);
	void setPos(glm::vec3 v);

	void setUp(glm::vec3 u);

	// Calculates and returns the view matrix
	// used by the renderer for placing the camera
	// Should be called getViewMatrix...
	glm::mat4 getModelViewMatrix();

};

#endif