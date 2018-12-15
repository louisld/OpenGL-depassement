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
    int success;
    char infoLog[512];
    glGetProgramiv(m_programShader, GL_LINK_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(m_programShader, 512, NULL, infoLog);
      std::cout << "Error::Shader::Program::Linking_Failed" << infoLog << std::endl;
      glDeleteProgram(m_programShader);
      return false;
    }
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);

    return true;
}


bool Shader::compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource)
{
    // Cr�ation du shader

    shader = glCreateShader(type);


    // V�rification du shader

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
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(m_vertexShader, 512, NULL, infoLog);
      std::cout << "Error::Shader::" << type << "::Compilation_Failed" << infoLog << std::endl;
      glDeleteShader(shader);
      return false;
    }

    else
        return true;
}


// Getter

GLuint Shader::getProgramID() const
{
    return m_programShader;
}
