#ifndef MOB_H
#define MOB_H
#include <vector>
#include <SFML/Graphics.hpp>


class MobController;

class Mob{
public:
	Mob();
	Mob(char[] fileName);
	~Mob();

	void loadTexture(char[] fileName);
	void clear();

	void draw();
	void step(double x, double y);
	void reposition(double x, double y);

	sf::Texture texture_;
	sf::Sprite sprite_;
	double scale_;
	double x_;
	double y_;
	// @TODO does the Mob own the MobController, or vise-versa?
	MobController* pAttachedMobController_;

}







#endif