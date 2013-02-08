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
	glm::mat4 projMatrix = glm::perspective(90.0f, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100.f);

	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_FALSE, glm::value_ptr(projMatrix));
	// Note: This should be recalculated when the screen is being resized.


	// This is temporary, should be moved

	Model* skybox = LoadModel("resources/skybox.obj");
	LoadTGATextureSimple("resources/SkyBox512.tga", &this->skyBoxTexture);
	glBindTexture(GL_TEXTURE_2D, skyBoxTexture);
	

	glGenVertexArrays(1, &skyBoxMesh.vertexArrayObjID);
	glGenBuffers(1, &skyBoxMesh.vertexBufferObjID);
	glGenBuffers(1, &skyBoxMesh.indexBufferObjID);
	glGenBuffers(1, &skyBoxMesh.normalBufferObjID);
	glGenBuffers(1, &skyBoxMesh.texCoordBufferObjID);
	

	// Bind buffers to this VAO
	glBindVertexArray(skyBoxMesh.vertexArrayObjID);

	glBindBuffer(GL_ARRAY_BUFFER, skyBoxMesh.vertexBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, skybox->numVertices*3*sizeof(GLfloat), skybox->vertexArray, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));

	glBindBuffer(GL_ARRAY_BUFFER, skyBoxMesh.normalBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, skybox->numVertices*3*sizeof(GLfloat), skybox->normalArray, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Normal"));
	
	glBindBuffer(GL_ARRAY_BUFFER, skyBoxMesh.texCoordBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, skybox->numVertices*2*sizeof(GLfloat), skybox->texCoordArray, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_TexCoord"), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_TexCoord"));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyBoxMesh.indexBufferObjID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, skybox->numIndices*sizeof(GLfloat), skybox->indexArray, GL_STATIC_DRAW);

	skyBoxMesh.numIndices = skybox->numIndices;

}

OpenGLRenderer::~OpenGLRenderer() {
	// Free memory
	for (auto it = this->meshes.begin(); it != this->meshes.end(); it++) {
		delete it->second;
	}
}

int OpenGLRenderer::addMesh(GLfloatCollection *vertices, GLfloatCollection *normals, GLfloatCollection *indices) {
	meshData *d = new meshData();

	//std::cout << "hejsan hoppsan: " << vertices->data[2] <<  std::endl;

	// Generate buffers
	glGenVertexArrays(1, &d->vertexArrayObjID);
	glGenBuffers(1, &d->vertexBufferObjID);
	glGenBuffers(1, &d->indexBufferObjID);
	glGenBuffers(1, &d->normalBufferObjID);

	// Bind buffers to this VAO
	glBindVertexArray(d->vertexArrayObjID);

	if ( vertices->num != 0) {
	    // VBO for vertex data
	    glBindBuffer(GL_ARRAY_BUFFER, d->vertexBufferObjID);
	    //glBufferData(GL_ARRAY_BUFFER, s->m->numVertices*3*sizeof(GLfloat), s->m->vertexArray, GL_STATIC_DRAW);
		//glBufferData(GL_ARRAY_BUFFER, 36*3*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, vertices->num*sizeof(GLfloat), &vertices->data[0], GL_STATIC_DRAW);
		glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
		glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));

		d->numVertices = vertices->num;
	}
	
	if ( normals != NULL && normals->num != 0) {
		// VBO for vertex normal data
	    glBindBuffer(GL_ARRAY_BUFFER, d->normalBufferObjID);
	    glBufferData(GL_ARRAY_BUFFER, normals->num*sizeof(GLfloat), &normals->data[0], GL_STATIC_DRAW);
		glVertexAttribPointer(glGetAttribLocation(program, "in_Normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(glGetAttribLocation(program, "in_Normal"));

		d->numNormals = normals->num;

	}

	if (indices != NULL && indices->num != 0) {
		// Index data
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, d->indexBufferObjID);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->num*sizeof(GLfloat), &indices->data[0], GL_STATIC_DRAW);
		
		d->numIndices = indices->num;

		// When rendering, use indices!
		d->useIndices = 1;
	} else {
		// When rendering, don't use indices!
		d->useIndices = 0;
	}
    GLint id = rand() % 10000 + 1;
    d->id = id;

    //this->meshes.push_back(d);
    this->meshes.insert(std::pair<int, meshData*>(id, d));
    return id;
}

int OpenGLRenderer::addMesh(SceneObject* so) {
	//return this->addMesh(&so->vertices[0], &so->normals[0], &so->indices[0]);
	return this->addMesh(&so->vertices, &so->normals, &so->indices);
}
/**
 * Render the scene by calculating modelToWorld matrix for each model and worldToView matrix
 * for all models.
 *
 */
void OpenGLRenderer::render(Scene *scene, Camera *camera) {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw skybox
	glm::mat4 skyboxView = camera->getModelViewMatrix();
	/*
	skyboxView[0][3] = 0;
	skyboxView[1][3] = 0;
	skyboxView[2][3] = 0;
	*/
	// Viewmatrix is transposed
	skyboxView[3][0] = 0;
	skyboxView[3][1] = 0;
	skyboxView[3][2] = 0;
	

	glDisable(GL_DEPTH_TEST);

	glUniform1i(glGetUniformLocation(program, "texUnit"), 0); // Texture unit 0
	glBindVertexArray(this->skyBoxMesh.vertexArrayObjID);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_FALSE, glm::value_ptr(skyboxView));
	glDrawElements(GL_TRIANGLES, this->skyBoxMesh.numIndices, GL_UNSIGNED_INT, 0L);

	glEnable(GL_DEPTH_TEST);
	

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
			if (d->useIndices) {
				glDrawElements(GL_TRIANGLES, d->numIndices, GL_UNSIGNED_INT, 0L);
			} else {
				//GL_TRIANGLES
				glDrawArrays(GL_LINES, 0, d->numVertices);
			}
		    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0L);
		    
		} else {
			// TODO: Handle this error, caused when the ID wasn't found
			std::cout << "THIS IS BAD!" << std::endl;
		}
		
	}
	
	glutSwapBuffers();
}

void OpenGLRenderer::onResizeScreen() {
	//std::cout << "width: " << glutGet(GLUT_WINDOW_WIDTH) << " height: " << glutGet(GLUT_WINDOW_HEIGHT) << std::endl;
	GLint width = glutGet(GLUT_WINDOW_WIDTH);
	GLint height = glutGet(GLUT_WINDOW_HEIGHT);
	
	GLfloat aspect = (GLfloat)width/height;

	glm::mat4 projMatrix = glm::perspective(90.0f, aspect, 0.1f, 100.f);

	glViewport(0, 0, width, height); // Set the viewport size to fill the window 
	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_FALSE, glm::value_ptr(projMatrix));
}