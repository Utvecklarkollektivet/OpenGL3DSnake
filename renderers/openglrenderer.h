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
#include "../lib/glm/glm/gtc/matrix_access.hpp"
#include "../lib/GL_utilities.h"
#include "../lib/loadobj.h"
#include "../lib/LoadTGA.h"

#include "renderer.h"


class OpenGLRenderer : public Renderer{
private:
	GLuint program;	

	struct meshData {
		unsigned int id;
		unsigned int useIndices;
		unsigned int vertexArrayObjID;
		unsigned int vertexBufferObjID;
		unsigned int indexBufferObjID;
		unsigned int normalBufferObjID;
		unsigned int texCoordBufferObjID;

		unsigned int numVertices;
		unsigned int numIndices;
		unsigned int numNormals;
	};

	std::map<int, meshData*> meshes;

	meshData skyBoxMesh;
	GLuint skyBoxTexture;
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	int addMesh(GLfloatCollection *vertices, GLfloatCollection *normals, GLfloatCollection *indices);
	int addMesh(SceneObject* so);
	void drawMesh(GLint index);

	void render(Scene *scene, Camera *camera);

	void onResizeScreen();

};

#endif