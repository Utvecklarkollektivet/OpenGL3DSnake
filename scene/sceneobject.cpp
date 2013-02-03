#include "SceneObject.h"

SceneObject::SceneObject() {
	scaleX = scaleY = scaleZ = 0;
	rotX = rotY = rotZ = 0;

	pos = glm::vec3(0, 0, 0);
}

SceneObject::SceneObject(std::vector<GLfloat> vertices, 
		std::vector<GLfloat> normals, std::vector<GLfloat> indices) {
	this->vertices = vertices;
	this->normals = normals;
	this->indices = indices;
}

void SceneObject::move(GLfloat x, GLfloat y, GLfloat z) {
	this->pos = glm::vec3(this->pos.x + x, 
		this->pos.y + y, 
		this->pos.z + z);
}

void SceneObject::move(glm::vec3 v) {
	this->move(v.x, v.y, v.z);
}

void SceneObject::setX(GLfloat x) {
	this->pos.x = x;
}
void SceneObject::setY(GLfloat y) {
	this->pos.y = y;
}
void SceneObject::setZ(GLfloat z) {
	this->pos.z = z;
}
void SceneObject::setPos(glm::vec3 p) {
	this->pos = p;
}



glm::mat4 SceneObject::getModelWorldMatrix() {
	glm::mat4 modelToWorld;
	modelToWorld = glm::translate(modelToWorld, this->pos);
	

	return modelToWorld;
}