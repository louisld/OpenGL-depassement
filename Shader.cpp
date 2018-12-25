#include "Shader.h"

// Constructeurs et Destructeur

Shader::Shader() : m_vertexShader(0), m_fragmentShader(0), m_programShader(0), m_vertexSource(), m_fragmentSource()
{
}


Shader::Shader(Shader const &shaderACopier)
{
    // Copie des fichiers sources

    m_vertexSource = shaderACopier.m_vertexSource;
    m_fragmentSource = shaderACopier.m_fragmentSource;


    // Chargement du nouveau shader

    charger();
}


Shader::Shader(std::string vertexSource, std::string fragmentSource) : m_vertexShader(0), m_fragmentShader(0), m_programShader(0),
                                                                       m_vertexSource(vertexSource), m_fragmentSource(fragmentSource)
{
}


Shader::~Shader()
{
    // Destruction du shader

    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
    glDeleteProgram(m_programShader);
}


// M�thodes

Shader& Shader::operator=(Shader const &shaderACopier)
{
    // Copie des fichiers sources

    m_vertexSource = shaderACopier.m_vertexSource;
    m_fragmentSource = shaderACopier.m_fragmentSource;


    // Chargement du nouveau shader

    charger();


    // Retour du pointeur this

    return *this;
}


bool Shader::charger()
{
    // Destruction d'un éventuel ancien Shader

    if(glIsShader(m_vertexShader) == GL_TRUE)
        glDeleteShader(m_vertexShader);

    if(glIsShader(m_fragmentShader) == GL_TRUE)
        glDeleteShader(m_fragmentShader);

    if(glIsProgram(m_programShader) == GL_TRUE)
        glDeleteProgram(m_programShader);


    if(!compilerShader(m_vertexShader, GL_VERTEX_SHADER, m_vertexSource))
        return false;

    if(!compilerShader(m_fragmentShader, GL_FRAGMENT_SHADER, m_fragmentSource))
        return false;

    m_programShader = glCreateProgram();
    glAttachShader(m_programShader, m_vertexShader);
    glAttachShader(m_programShader, m_fragmentShader);
    glLinkProgram(m_programShader);
    checkCompileErrors(m_programShader, "PROGRAM");
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);

    return true;
}


bool Shader::compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource)
{
    // Création du shader

    shader = glCreateShader(type);


    // Vérification du shader

    if(shader == 0)
    {
        std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
        return false;
    }


    // Flux de lecture

    std::ifstream fichier(fichierSource.c_str());


    // Test d'ouverture

    if(!fichier)
    {
        std::cout << "Erreur le fichier " << fichierSource << " est introuvable" << std::endl;
        glDeleteShader(shader);

        return false;
    }


    // Strings permettant de lire le code source

    std::string ligne;
    std::string codeSource;


    // Lecture

    while(getline(fichier, ligne))
        codeSource += ligne + '\n';

    fichier.close();

    const GLchar* chaineCodeSource = codeSource.c_str();

    //Compilation

    glShaderSource(shader, 1, &chaineCodeSource, NULL);
    glCompileShader(shader);
    //std::cout << glGetError() << std::endl;
    if(type == GL_FRAGMENT_SHADER)
      checkCompileErrors(shader, "FRAGMENT");
    else
      checkCompileErrors(shader, "VERTEX");

    return true;
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
  int success;
  char infoLog[1024];
  if(type != "PROGRAM")
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "Error::Shader::" << type << "::Compilation_Failed" << infoLog << std::endl;
    }
  }else{
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "Error::Shader::Program::Linking_Failed" << infoLog << std::endl;
    }
  }
}

void Shader::use()
{
  glUseProgram(m_programShader);
}

// Getter

GLuint Shader::getProgramID() const
{
    return m_programShader;
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
  glUniformMatrix4fv(glGetUniformLocation(m_programShader, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
