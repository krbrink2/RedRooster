#ifndef MOB_H
#define MOB_H
#include "Globals.h"
#include "Boundable.h"
#include "Drawable.h"
// Do NOT include MobController.h

class MobController;

class Mob
  : public Boundable
  , public Drawable
{
public:
	Mob();
	Mob(const std::string fileName);
	~Mob();

	void attachMobController(MobController* mobController);

	void takeInput(sf::Event event);
	void update();
	void draw();
	void step(double x, double y);
	void step(sf::Vector2f vector);
	void setPosition(double x, double y);
	void setPosition(sf::Vector2f pos);
	void setWidth(double w);
	void setHeight(double h);
	sf::Vector2f getPosition();

//private:
  double scale_            = 1;
  sf::Vector2f position_   = sf::Vector2f(0, 0);
	double width_            = 100;
	double height_           = 100;
	MobController* pAttachedMobController_; // DOES live here

};


#endif
