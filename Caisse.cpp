#include "Caisse.h"

#include <stdio.h>

#include "Utils/stb_image.h"

Caisse::Caisse(float taille, std::string const vertexShader, std::string const fragmentShader, std::string texture) : m_shader(vertexShader, fragmentShader), m_texturePath(texture), m_vao(0), m_vbo(0), m_tailleVertices(180 * sizeof(float)), m_texture(0)
{
  m_shader.charger();

  float verticesTmp[] = {
    -taille, -taille, -taille,  0.0f, 0.0f,
    taille, -taille, -taille,  1.0f, 0.0f,
    taille,  taille, -taille,  1.0f, 1.0f,
    taille,  taille, -taille,  1.0f, 1.0f,
    -taille,  taille, -taille,  0.0f, 1.0f,
    -taille, -taille, -taille,  0.0f, 0.0f,

    -taille, -taille,  taille,  0.0f, 0.0f,
    taille, -taille,  taille,  1.0f, 0.0f,
    taille,  taille,  taille,  1.0f, 1.0f,
    taille,  taille,  taille,  1.0f, 1.0f,
    -taille,  taille,  taille,  0.0f, 1.0f,
    -taille, -taille,  taille,  0.0f, 0.0f,

    -taille,  taille,  taille,  1.0f, 0.0f,
    -taille,  taille, -taille,  1.0f, 1.0f,
    -taille, -taille, -taille,  0.0f, 1.0f,
    -taille, -taille, -taille,  0.0f, 1.0f,
    -taille, -taille,  taille,  0.0f, 0.0f,
    -taille,  taille,  taille,  1.0f, 0.0f,

    taille,  taille,  taille,  1.0f, 0.0f,
    taille,  taille, -taille,  1.0f, 1.0f,
    taille, -taille, -taille,  0.0f, 1.0f,
    taille, -taille, -taille,  0.0f, 1.0f,
    taille, -taille,  taille,  0.0f, 0.0f,
    taille,  taille,  taille,  1.0f, 0.0f,

    -taille, -taille, -taille,  0.0f, 1.0f,
    taille, -taille, -taille,  1.0f, 1.0f,
    taille, -taille,  taille,  1.0f, 0.0f,
    taille, -taille,  taille,  1.0f, 0.0f,
    -taille, -taille,  taille,  0.0f, 0.0f,
    -taille, -taille, -taille,  0.0f, 1.0f,

    -taille,  taille, -taille,  0.0f, 1.0f,
    taille,  taille, -taille,  1.0f, 1.0f,
    taille,  taille,  taille,  1.0f, 0.0f,
    taille,  taille,  taille,  1.0f, 0.0f,
    -taille,  taille,  taille,  0.0f, 0.0f,
    -taille,  taille, -taille,  0.0f, 1.0f
  };

  for(int i = 0;i<180;i++)
  {
    m_vertices[i] = verticesTmp[i];
    std::cout << m_vertices[i] << " | ";
    if((i+1) % 5 == 0)
      std::cout << std::endl;
  }
}

Caisse::~Caisse()
{
  glDeleteBuffers(1, &m_vbo);
  glDeleteVertexArrays(1, &m_vao);
}

void Caisse::afficher(glm::mat4 &projection, glm::mat4 &model, glm::mat4 &view)
{
  m_shader.use();
  glBindTexture(GL_TEXTURE_2D, m_texture);

  m_shader.setMat4("projection", projection);
  m_shader.setMat4("model", model);
  m_shader.setMat4("view", view);

  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);

  glBindTexture(GL_TEXTURE_2D, 0);
  glUseProgram(0);
}

void Caisse::charger()
{

  if(glIsVertexArray(m_vao) == GL_TRUE)
       glDeleteVertexArrays(1, &m_vao);
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);

  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  unsigned char *data = stbi_load(m_texturePath.c_str(), &width, &height, &nrChannels, 0);
  if(data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    std::cout << "Erreur lors du chargement de la texture : " << m_texturePath << std::endl;
  }

  stbi_image_free(data);
}
