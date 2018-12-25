#ifndef DEF_INPUT
#define DEF_INPUT

#include <SDL2/SDL.h>

class Input
{
public:
  Input();
  ~Input();
  void updateEvenements();
  bool terminer() const;
  bool getTouche(const SDL_Scancode touche) const;
  bool getMovSouris() const;
  int getX() const;
  int getY() const;
  int getXReal() const;
  int getYReal() const;
  void afficherPointeur(bool reponse) const;
  void capturerPointeur(bool reponse) const;

private:
  SDL_Event m_evenements;
  bool m_touches[SDL_NUM_SCANCODES];
  bool m_boutonSouris[8];

  int m_x;
  int m_y;
  int m_xReal;
  int m_yReal;

  bool m_terminer;

};

#endif
