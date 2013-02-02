#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include "lib/glm/glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "lib/glm/glm/gtc/type_ptr.hpp"
#include "GL_utilities.h"


class OpenGLRenderer {
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

};

#endif