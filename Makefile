CXX=g++
CXXFLAGS=-W -ansi #-pedantic -Wall
LDFLAGS=-lSDL2 -lSDL2main -lGL -lGLEW
EXEC=depassement

all: $(EXEC)

depassement:SceneOpenGL.o Shader.o  depassement.o Input.o
	$(CXX) -o depassement SceneOpenGL.o depassement.o Shader.o Input.o $(LDFLAGS)

SceneOpenGL.o: SceneOpenGL.cpp Shader.h
	$(CXX) -o  SceneOpenGL.o -c SceneOpenGL.cpp $(CXXFLAGS)

Shader.o: Shader.cpp
	$(CXX) -o  Shader.o -c Shader.cpp $(CXXFLAGS)

Input.o: Input.cpp
	$(CXX) -o Input.o -c Input.cpp $(CXXFLAGS)

depassement.o: depassement.cpp SceneOpenGL.h Shader.h Camera.h Input.h
	$(CXX) -o depassement.o -c depassement.cpp $(CXXFLAGS)

clean:
	rm -rf *o
