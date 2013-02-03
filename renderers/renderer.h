#ifndef RENDERER_H
#define RENDERER_H

#include "../scene/Scene.h"
#include "../scene/Camera.h"


class Renderer{
private:

public:
	//Renderer();
	virtual ~Renderer() = 0;
	
	//virtual void addMesh() = 0;
	virtual void render(const Scene &scene, const Camera &camera) = 0;

};

#endif