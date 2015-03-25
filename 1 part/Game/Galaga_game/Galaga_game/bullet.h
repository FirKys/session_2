#pragma once
#include <SFML/Graphics.hpp>

//пуля
class Bullet{
public:
	sf::CircleShape shape;
	bool life;
	Bullet(sf::Vector2f & pos);
};