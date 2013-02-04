#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <string>
#include "../renderers/renderer.h"
#include "SceneObject.h"

//Forward declare renderer since we got a circular dependency
class Renderer;

class Scene {
private:
	Renderer *renderer;

	std::map<int, SceneObject*> mObjects;
public:
	Scene(Renderer *renderer);
	//~Scene();

	void addObject(SceneObject *so);
	void removeObject(SceneObject *so);
	const std::map<int, SceneObject*>& getObjects();


};

#endif
/*
Scene *scene = new Scene(renderer);
SceneObject* s = new SceneObject(...);
//int id = renderer.addMesh(s);

Scene.addObject(s); // denna funktion kallar på renderer.addMesh(...);

renderer.render(scene, camera);
*/