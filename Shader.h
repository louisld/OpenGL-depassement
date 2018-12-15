#ifndef DEF_SHADER
#define DEF_SHADER

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include <SDL2/SDL.h>
#define GL3_PROTOTYPES 1
#include <GL/gl.h>


// Classe Shader

class Shader
{
    public:

    Shader();
    Shader(Shader const &shaderACopier);
    Shader(std::string vertexSource, std::string fragmentSource);
    ~Shader();

    Shader& operator=(Shader const &shaderACopier);

    bool charger();
    bool compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource);
    GLuint getProgramID() const;


    private:

    GLuint m_vertexShader;
    GLuint m_fragmentShader;
    GLuint m_programShader;

    std::string m_vertexSource;
    std::string m_fragmentSource;
};

#endif
