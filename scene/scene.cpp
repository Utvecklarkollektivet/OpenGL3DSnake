#include "Scene.h"

Scene::Scene(Renderer *renderer) {
	this->renderer = renderer;
}

void Scene::addObject(SceneObject *so) {
	int id = this->renderer->addMesh(so);
	so->id = id;
	this->mObjects.insert(std::pair<int, SceneObject*>(id, so));
}

void Scene::removeObject(SceneObject *so) {
	auto it = this->mObjects.find(so->id);
	this->mObjects.erase(it);
}

const std::map<int, SceneObject*>& Scene::getObjects() {
	return this->mObjects;
}