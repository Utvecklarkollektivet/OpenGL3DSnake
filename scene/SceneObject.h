#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <iostream>
#include <vector>
#include <GL/gl.h>
#include "../lib/glm/glm/glm.hpp"
#include "../lib/glm/glm/gtc/matrix_transform.hpp"

class SceneObject {
protected:

	
	GLfloat scaleX;
	GLfloat scaleY;
	GLfloat scaleZ;

	GLfloat rotX;
	GLfloat rotY;
	GLfloat rotZ;

	glm::vec3 pos;
public:
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> indices;
	/*
	GLfloat vertices[];
	GLfloat normals[];
	GLfloat texCoords[];
	GLfloat indices[];
	*/
	SceneObject();
	SceneObject(std::vector<GLfloat> vertices, 
		std::vector<GLfloat> normals, std::vector<GLfloat> indices);

	void move(GLfloat x, GLfloat y, GLfloat z);
	void move(glm::vec3 v);

	void setX(GLfloat x);
	void setY(GLfloat y);
	void setZ(GLfloat z);

	void setPos(glm::vec3 p);

	void setRotateX(GLfloat r);
	void setRotateY(GLfloat r);
	void setRotateZ(GLfloat r);

	void setScale(glm::vec3 s);
	void setScaleX(GLfloat s);
	void setScaleY(GLfloat s);
	void setScaleZ(GLfloat s);


	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();
	glm::vec3 getPos();

	// Calculates and returns the world matrix for the model
	// used by the renderer for placing the object
	glm::mat4 getModelWorldMatrix();

};

#endif