 #include "openglrenderer.h"


//#include <GL/freeglut.h>
//#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glut.h>
//#include <GL/glu.h>
//#include <GL/glext.h>

OpenGLRenderer::OpenGLRenderer() {

	// init rand
	srand(time(NULL));


	GLenum err = glewInit();
	// TODO: Check err here
	// i.e: http://gamedev.stackexchange.com/questions/22785/glcreateshader-causes-segmentation-fault

	// GL inits
	glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);

	// Loads and links the shaders
	program = loadShaders("shaders/main.vert", "shaders/main.frag");

	// Perspective matrix
	glm::mat4 projMatrix = glm::perspective(45.0f, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100.f);

	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_FALSE, glm::value_ptr(projMatrix));
	// Note: This should be recalculated when the screen is being resized.
}

OpenGLRenderer::~OpenGLRenderer() {

}

int OpenGLRenderer::addMesh(GLfloat vertices[], GLfloat normals[], GLfloat indices[]) {
	meshData *d = new meshData();

	std::cout << "hejsan hoppsan: " << vertices[2] <<  std::endl;

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
	glBufferData(GL_ARRAY_BUFFER, 36*3*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));
	/*
	// VBO for vertex normal data
    glBindBuffer(GL_ARRAY_BUFFER, d->normalBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, 6*3*sizeof(GLfloat), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Normal"));

	// Index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, d->indexBufferObjID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLfloat), indices, GL_STATIC_DRAW);
	*/
    GLint id = rand() % 10000 + 1;
    d->id = id;

    //this->meshes.push_back(d);
    this->meshes.insert(std::pair<int, meshData*>(id, d));
    return id;
}

int OpenGLRenderer::addMesh(SceneObject* so) {
	return this->addMesh(&so->vertices[0], &so->normals[0], &so->indices[0]);
}
/**
 * Render the scene by calculating modelToWorld matrix for each model and worldToView matrix
 * for all models.
 *
 */
void OpenGLRenderer::render(Scene *scene, Camera *camera) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	// Get the modelToView matrix
	glm::mat4 modelToView = camera->getModelViewMatrix();
	//glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_FALSE, glm::value_ptr(modelToView));

	std::map<int, SceneObject*> objects = scene->getObjects();


	for (auto it = objects.begin(); it != objects.end(); it++) {
		auto it_2 = this->meshes.find(it->first);
		if (it_2 != this->meshes.end()) {
			meshData *d = it_2->second;

			// Get modelToWorld matrix
			glm::mat4 modelToWorld = it->second->getModelWorldMatrix();
			glm::mat4 modelMatrix = modelToView * modelToWorld;
			glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

			// Bind it!
			glBindVertexArray(d->vertexArrayObjID);    // Select VAO
										// 6 is the number of indices
		    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0L);
		    glDrawArrays(GL_TRIANGLES, 0, 36*3);
		} else {
			std::cout << "THIS IS BAD!" << std::endl;
		}
		
	}
	
	glutSwapBuffers();
}