#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <string>
#include "../renderers/renderer.h"
#include "SceneObject.h"

//Forward declare renderer since we got a circulat dependency
class Renderer;

class Scene {
private:
	Renderer *renderer;

	std::map<std::string, SceneObject*> mObjects;
public:
	Scene(Renderer &renderer);
	~Scene();

	void addObject(SceneObject &so);
	const std::map<std::string, SceneObject*>& getObjects();


};

#endif
/*
Scene *scene = new Scene(renderer);
SceneObject* s = new SceneObject(...);
//int id = renderer.addMesh(s);

Scene.addObject(s); // denna funktion kallar på renderer.addMesh(...);

renderer.render(scene, camera);
*/