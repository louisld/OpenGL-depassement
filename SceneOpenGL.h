#ifndef DEF_SCENEOPENGL
#define DEF_SCENEOPENGL


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>

#include <SDL2/SDL.h>
#define GL3_PROTOTYPES 1
#include <GL/gl.h>

#include "Input.h"


// Classe

class SceneOpenGL
{
    public:

    SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    ~SceneOpenGL();

    bool initialiserFenetre();
    bool initGL();
    void bouclePrincipale();


    private:

    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;

    SDL_Window* m_fenetre;
    SDL_GLContext m_contexteOpenGL;
    SDL_Event m_evenements;

    Input m_input;

    bool handleEvent(float deltaTime);
};

#endif
