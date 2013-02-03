#ifndef RENDERER_H
#define RENDERER_H

#include "../scene/Scene.h"
#include "../scene/Camera.h"
#include "../scene/SceneObject.h"

// Forward declaration
class Scene;

class Renderer{
private:

public:
	//Renderer();
	virtual ~Renderer() = 0;
	
	virtual int addMesh(GLfloat vertices[], GLfloat normals[], GLfloat indices[]) = 0;
	virtual int addMesh(SceneObject* so) = 0;
	//virtual void addMesh() = 0;
	virtual void render(Scene *scene, Camera *camera) = 0;

};

#endif