#include "SceneOpenGL.h"
#include "Shader.h"
#include "Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Utils/stb_image.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre), m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0), m_input()
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

  //Variables


  float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };


  float couleurs[] = {
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  glEnable(GL_DEPTH_TEST);
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  //glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  Shader shader = Shader("Shaders/1.vert", "Shaders/1.frag");
  shader.charger();
  int shaderProgram = shader.getProgramID();

  //Chargement de l'image
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  unsigned char *data = stbi_load("Textures/container.jpg", &width, &height, &nrChannels, 0);
  if(data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    std::cout << "Erreur lors du chargement de la texture" << std::endl;
  }

  stbi_image_free(data);

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  int frames = 0;
  float deltaTime;
  float lastFrame;

  m_input.afficherPointeur(false);
  m_input.capturerPointeur(true);

  while(!m_input.terminer())
  {

    float currentFrame = SDL_GetTicks();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if(handleEvent(deltaTime))
      break;

    // Nettoyage de l'écran
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture);

    glm::mat4 model(1.0f);
    model = glm::rotate(model, (float) SDL_GetTicks() * glm::radians(2.0f) / 50.0f, glm::vec3(0.5f, 1.0f, 0.2f));

    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float) m_largeurFenetre / (float) m_hauteurFenetre, 0.1f, 100.0f);

    glm::mat4 view = camera.GetViewMatrix();

    shader.use();
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindVertexArray(VAO);

    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    //std::cout << "Frame n°" << frames << " : " <<  glGetError() << std::endl;frames++;

    // Actualisation de la fenêtre
    SDL_GL_SwapWindow(m_fenetre);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

bool SceneOpenGL::handleEvent(float deltaTime)
{
  m_input.updateEvenements();
  if(m_input.getTouche(SDL_SCANCODE_W))
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if(m_input.getTouche(SDL_SCANCODE_S))
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if(m_input.getTouche(SDL_SCANCODE_A))
    camera.ProcessKeyboard(LEFT, deltaTime);
  if(m_input.getTouche(SDL_SCANCODE_D))
    camera.ProcessKeyboard(RIGHT, deltaTime);
  if(m_input.getMovSouris())
    camera.ProcessMouseMovement(m_input.getXReal(), -m_input.getYReal());
  if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
    return 1;
  else
    return 0;
}
