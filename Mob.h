#ifndef MOB_H
#define MOB_H
#include "Globals.h"


class MobController;

class Mob{
public:
	Mob();
	Mob(char* fileName);
	~Mob();

	int loadTexture(char* fileName);
	void attachMobController(MobController* mobController);

	void takeInput(sf::Event event);
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
	// @TODO does the Mob own the MobController, or vise-versa?
	MobController* pAttachedMobController_;

};


#endif
