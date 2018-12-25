#ifndef DEF_CAISSE
#define DEF_CAISSE

#include <string>

#include <GL/glew.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/gl.h>

#include "Shader.h"

class Caisse
{
public:
  Caisse(float taille, std::string const vertexShader, std::string const fragmentShader, std::string texture);
  ~Caisse();
  void afficher(glm::mat4 &projection, glm::mat4 &model, glm::mat4 &view);
  void charger();
private:
  Shader m_shader;
  float m_vertices[180];
  float m_couleurs[180];
  std::string m_texturePath;
  unsigned int m_texture;
  unsigned int m_vao;
  unsigned int m_vbo;
  int m_tailleVertices;
};

#endif
