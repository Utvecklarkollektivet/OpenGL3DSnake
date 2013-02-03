#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H
#include <iostream>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "../lib/glm/glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../lib/glm/glm/gtc/type_ptr.hpp"
#include "../lib/GL_utilities.h"

#include "renderer.h"


class OpenGLRenderer : public Renderer{
private:
	GLuint program;	

	struct meshData {
		unsigned int id;
		unsigned int vertexArrayObjID;
		unsigned int vertexBufferObjID;
		unsigned int indexBufferObjID;
		unsigned int normalBufferObjID;
	};

	std::map<int, meshData*> meshes;
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	int addMesh(GLfloat vertices[], GLfloat normals[], GLfloat indices[]);
	int addMesh(SceneObject* so);
	void drawMesh(GLint index);

	void render(Scene *scene, Camera *camera);

};

#endif