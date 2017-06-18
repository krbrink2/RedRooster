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
	void reposition(double x, double y);

	double getX();
	double getY();

	sf::Texture texture_;
	sf::Sprite sprite_;
	double scale_;
	double x_;
	double y_;
	sf::CircleShape shape_;
	MobController* pAttachedMobController_; // DOES live here

};


#endif
