#include "SceneObject.h"

SceneObject::SceneObject() {
	scaleX = scaleY = scaleZ = 0;
	rotX = rotY = rotZ = 0;

	pos = glm::vec3(0, 0, 0);

	vertices.num = 0;
	normals.num = 0;
	indices.num = 0;


	scaleX = 1.0f;
	scaleY = 1.0f;
	scaleZ = 1.0f;

	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
}

SceneObject::SceneObject(GLfloatCollection vertices, 
		GLfloatCollection normals, GLfloatCollection indices) {
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

void SceneObject::setRotateX(GLfloat r) {
	this->rotX = r;
}
void SceneObject::setRotateY(GLfloat r) {
	this->rotY = r;
}
void SceneObject::setRotateZ(GLfloat r) {
	this->rotZ = r;
}

void SceneObject::setScale(glm::vec3 s) {
	this->scaleX = s.x;
	this->scaleY = s.y;
	this->scaleZ = s.z;
}
void SceneObject::setScaleX(GLfloat s) {
	this->scaleX = s;
}
void SceneObject::setScaleY(GLfloat s) {
	this->scaleY = s;
}
void SceneObject::setScaleZ(GLfloat s) {
	this->scaleZ = s;
}



glm::mat4 SceneObject::getModelWorldMatrix() {
	glm::mat4 modelToWorld;
	modelToWorld = glm::translate(modelToWorld, this->pos);
	
	modelToWorld = glm::rotate(modelToWorld, this->rotX, glm::vec3(1.0f, 0, 0));
	modelToWorld = glm::rotate(modelToWorld, this->rotY, glm::vec3(0, 1.0f, 0));
	modelToWorld = glm::rotate(modelToWorld, this->rotZ, glm::vec3(0, 0, 1.0f));

	modelToWorld = glm::scale(modelToWorld, 
		glm::vec3(this->scaleX, this->scaleY, this->scaleZ));

	return modelToWorld;
}