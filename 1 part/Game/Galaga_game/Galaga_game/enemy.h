#pragma once
#include <SFML/Graphics.hpp>

//Враг
class Enemy{
public:
	sf::RectangleShape rectangle;
	bool life;
	int move;

	Enemy(sf::Vector2f & pos);
};