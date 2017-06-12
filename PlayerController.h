#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include <SFML/System.hpp>


class PlayerController: public MobController
{
public:
	PlayerController();

	void takeInput(sf::Event event);
}


#endif