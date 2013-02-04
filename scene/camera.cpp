 #include "Camera.h"

Camera::Camera() {
	this->eye = glm::vec3(0.0f);
	this->center = glm::vec3(0.0f);
	this->up = glm::vec3(0, 1.0f, 0);
}

void Camera::lookPoint(GLfloat x, GLfloat y, GLfloat z) {
	this->center = glm::vec3(x, y, z);
}

void Camera::lookPoint(glm::vec3 v) {
	this->lookPoint(v.x, v.y, v.z);
}

void Camera::move(GLfloat x, GLfloat y, GLfloat z) {
	this->eye = glm::vec3(this->eye.x + x, this->eye.y + y, this->eye.z + z);
}
void Camera::move(glm::vec3 v) {
	this->move(v.x, v.y, v.z);
}

void Camera::setX(GLfloat p) {
	this->eye.x = p;
}
void Camera::setY(GLfloat p) {
	this->eye.y = p;
}
void Camera::setZ(GLfloat p) {
	this->eye.z = p;
}
void Camera::setPos(GLfloat x, GLfloat y, GLfloat z) {
	this->eye = glm::vec3(x, y, z);
}
void Camera::setPos(glm::vec3 v) {
	this->eye = v;
}
void Camera::setUp(glm::vec3 u) {
	this->up = u;
}

glm::mat4 Camera::getModelViewMatrix() {
	return glm::lookAt(this->eye, this->center, this->up);
}