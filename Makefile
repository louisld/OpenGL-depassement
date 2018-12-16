CXX=g++
CXXFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=-lSDL2 -lSDL2main -lGL -lGLEW
EXEC=depassement

all: $(EXEC)

depassement:SceneOpenGL.o Shader.o  depassement.o
	$(CXX) -o depassement SceneOpenGL.o depassement.o Shader.o $(LDFLAGS)

SceneOpenGL.o: SceneOpenGL.cpp Shader.h
	$(CXX) -o  SceneOpenGL.o -c SceneOpenGL.cpp $(CXXFLAGS)

Shader.o: Shader.cpp
	$(CXX) -o  Shader.o -c Shader.cpp $(CXXFLAGS)

depassement.o: depassement.cpp SceneOpenGL.h Shader.h
	$(CXX) -o depassement.o -c depassement.cpp $(CXXFLAGS)

clean:
	rm -rf *o
