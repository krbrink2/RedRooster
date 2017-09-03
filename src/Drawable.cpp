#include "Drawable.h"

Drawable::Drawable()
{}

Drawable::~Drawable()
{}

// Load a texture from file.
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

// Set sprite_ to use preloaded texture.
void Drawable::setTexture(const sf::Texture & texture)
{
  // @TODO clear texture_
  sprite_.setTexture(texture);
}

void Drawable::draw()
{  
  Gbl::game.drawSprite(sprite_);
}