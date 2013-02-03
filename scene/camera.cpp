 #include "Camera.h"

Camera::Camera() {
	this->pos = glm::vec3(0.0f);
	this->eye = glm::vec3(0.0f);
	this->up = glm::vec3(0, 1.0f, 0);
}

void Camera::lookPoint(GLfloat x, GLfloat y, GLfloat z) {
	this->eye = glm::vec3(x, y, z);
}

void Camera::lookPoint(glm::vec3 v) {
	this->lookPoint(v.x, v.y, v.z);
}

void Camera::move(GLfloat x, GLfloat y, GLfloat z) {
	this->pos = glm::vec3(this->pos.x + x, this->pos.y + y, this->pos.z + z);
}
void Camera::move(glm::vec3 v) {
	this->move(v.x, v.y, v.z);
}

glm::mat4 Camera::getModelViewMatrix() {
	return glm::lookAt(this->pos, this->eye, this->up);
}