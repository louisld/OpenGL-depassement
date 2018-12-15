#include "SceneOpenGL.h"

int main()
{
  SceneOpenGL scene("Dépassement", 800, 600);
  if(scene.initialiserFenetre() == false)
    return -1;
  if(scene.initGL() == false)
    return -1;

    // Boucle Principale

  scene.bouclePrincipale();

  return 0;
}
