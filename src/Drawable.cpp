#include "Drawable.h"

Drawable::Drawable()
{}

Drawable::~Drawable()
{}

int Drawable::loadTexture(const std::string fileName)
{
  if(!texture_.loadFromFile(fileName))
  {
    std::cout << "Load error in " << __PRETTY_FUNCTION__ << std::endl;
    return -1;
  }
  sprite_.setTexture(texture_);
  return 0;
}

void Drawable::draw()
{  
  Gbl::game.drawSprite(sprite_);
}