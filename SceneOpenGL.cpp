#include "SceneOpenGL.h"
#include "Shader.h"

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre), m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0)
{

}

SceneOpenGL::~SceneOpenGL()
{
  SDL_GL_DeleteContext(m_contexteOpenGL);
  SDL_DestroyWindow(m_fenetre);
  SDL_Quit();
}

bool SceneOpenGL::initialiserFenetre()
{
  // Initialisation de la SDL

  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
    SDL_Quit();

    return false;
  }


  // Version d'OpenGL

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


  // Double Buffer

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


  // Création de la fenêtre

  m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  if(m_fenetre == 0)
  {
    std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
    SDL_Quit();

    return false;
  }


  // Création du contexte OpenGL

  m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

  if(m_contexteOpenGL == 0)
  {
    std::cout << SDL_GetError() << std::endl;
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();

    return false;
  }

  return true;
}

bool SceneOpenGL::initGL()
{
  //#ifdef WIN32

  // On initialise GLEW

  glewExperimental = GL_TRUE;

  GLenum initialisationGLEW( glewInit() );


  // Si l'initialisation a échoué :

  if(initialisationGLEW != GLEW_OK)
  {
    // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

    std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;


    // On quitte la SDL

    SDL_GL_DeleteContext(m_contexteOpenGL);
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();

    return false;
  }

  //#endif


  // Tout s'est bien passé, on retourne true

  return true;
}

void SceneOpenGL::bouclePrincipale()
{
  // Variables

  bool terminer(false);

  //Variables
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
  };
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  Shader shader = Shader("Shaders/1.vert", "Shaders/1.frag");
  shader.charger();
  int shaderProgram = shader.getProgramID();

  // Boucle principale


  while(!terminer)
  {
    // Gestion des évènements

    SDL_WaitEvent(&m_evenements);

    if(m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
    terminer = true;

    // Nettoyage de l'écran
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Actualisation de la fenêtre
    SDL_GL_SwapWindow(m_fenetre);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}
