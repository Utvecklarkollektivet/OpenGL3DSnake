 #include "openglrenderer.h"


//#include <GL/freeglut.h>
//#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glut.h>
//#include <GL/glu.h>
//#include <GL/glext.h>

OpenGLRenderer::OpenGLRenderer() {

	// GL inits
	glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);

	program = loadShaders("main.vert", "main.frag");

	// Perspective matrix
	glm::mat4 projMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);

	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_FALSE, glm::value_ptr(projMatrix));
}

OpenGLRenderer::~OpenGLRenderer() {

}

int OpenGLRenderer::addMesh(GLfloat vertices[], GLfloat normals[], GLfloat indices[]) {
	meshData *d = new meshData();

	// Generate buffers
	glGenVertexArrays(1, &d->vertexArrayObjID);
	glGenBuffers(1, &d->vertexBufferObjID);
	glGenBuffers(1, &d->indexBufferObjID);
	glGenBuffers(1, &d->normalBufferObjID);

	// Bind buffers to this VAO
	glBindVertexArray(d->vertexArrayObjID);


    // VBO for vertex data
    glBindBuffer(GL_ARRAY_BUFFER, d->vertexBufferObjID);
    //glBufferData(GL_ARRAY_BUFFER, s->m->numVertices*3*sizeof(GLfloat), s->m->vertexArray, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));

	// VBO for vertex normal data
    glBindBuffer(GL_ARRAY_BUFFER, d->normalBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Normal"));

	// Index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, d->indexBufferObjID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    this->meshes.push_back(d);
    return (this->meshes.size() -1);
}