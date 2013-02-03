#include "Scene.h"

Scene::Scene(Renderer *renderer) {
	this->renderer = renderer;
}

void Scene::addObject(SceneObject *so) {
	int id = this->renderer->addMesh(so);
	this->mObjects.insert(std::pair<int, SceneObject*>(id, so));
}

const std::map<int, SceneObject*>& Scene::getObjects() {
	return this->mObjects;
}