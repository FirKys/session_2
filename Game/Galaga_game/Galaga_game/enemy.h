#pragma once
#include <SFML/Graphics.hpp>

//����
class Enemy{
public:
	sf::RectangleShape rectangle;
	bool life;
	int move;

	Enemy(sf::Vector2f & pos);
};