#ifndef MOB_H
#define MOB_H
#include "Globals.h"
// Do NOT include MobController.h


class MobController;

class Mob{
public:
	Mob();
	Mob(const std::string fileName);
	~Mob();

	int loadTexture(const std::string fileName);
	void attachMobController(MobController* mobController);

	void takeInput(sf::Event event);
	void update();
	void draw();
	void step(double x, double y);
	void step(sf::Vector2f vector);
	void setPosition(double x, double y);
	sf::Vector2f getPosition();

	sf::Texture texture_;
	sf::Sprite sprite_;
	double scale_ = 1;
	sf::Vector2f position_ = sf::Vector2f(0, 0);
	MobController* pAttachedMobController_; // DOES live here

};


#endif
