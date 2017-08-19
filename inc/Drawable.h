#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Globals.h"


class Drawable
{
public:
  Drawable();
  virtual ~Drawable();

  int loadTexture(const std::string fileName);
  virtual void draw();


//protected:
  sf::Texture texture_;
  sf::Sprite sprite_;
}

#endif