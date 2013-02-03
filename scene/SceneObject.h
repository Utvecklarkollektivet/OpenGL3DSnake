#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <GL/gl.h>
#include "../lib/glm/glm/glm.hpp"

class SceneObject {
private:
	GLfloat vertices;
	GLfloat normals;
	GLfloat texCoords;
	
	GLint scaleX;
	GLint scaleY;
	GLint scaleZ;

	glm::vec3 pos;

public:

	void move(GLint x, GLint y, GLint z);
	void move(glm::vec3 v);

	void setX(GLfloat x);
	void setY(GLfloat y);
	void setZ(GLfloat z);

	void setPos(glm::vec3 p);

	GLint getX();
	GLint getY();
	GLint getZ();
	glm::vec3 getPos();

	// Calculates and returns the world matrix for the model
	// used by the renderer for placing the object
	glm::mat4 getModelWorldMatrix();

};

#endif