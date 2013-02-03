#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H
#include <vector>
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
		unsigned int vertexArrayObjID;
		unsigned int vertexBufferObjID;
		unsigned int indexBufferObjID;
		unsigned int normalBufferObjID;
	};

	std::vector<meshData*> meshes;
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	int addMesh(GLfloat vertices[], GLfloat normals[], GLfloat texCoords[]);
	int addMesh(SceneObject& so);
	void drawMesh(GLint index);

	void render(const Scene &scene, const Camera &camera);

};

#endif