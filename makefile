
#g++ -Wall -std=c99 -o main -lm -lX11 -lGL -lGLU -lglut -DGL_GLEXT_PROTOTYPES main.cpp

BUILD_PATH = build/
OBJS = main.cpp renderers/renderer.cpp renderers/openglrenderer.cpp scene/camera.cpp scene/scene.cpp scene/sceneobject.cpp scene/objects/cube.cpp lib/GL_utilities.c lib/loadobj.c lib/LoadTGA.c
OBJ_NAME = 3dgame

all : $(OBJS)
	#g++ -Wall -std=c++98 $(OBJS) -I/usr/local/include -I/opt/X11/include -L/usr/local/lib -I/opt/X11/lib $(pkg-config --cflags --libs gl) -lglut -o $(OBJ_NAME)

	g++ -Wall -std=c++0x $(OBJS) -lGLEW -lX11 -lGL -lGLU -lm -lglut -o $(BUILD_PATH)$(OBJ_NAME)

clean :
	rm main
