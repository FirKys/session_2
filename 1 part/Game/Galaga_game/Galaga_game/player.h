#pragma once
#include <SFML/Graphics.hpp>

class Player{
public:
	sf::RectangleShape rectangle;

	Player(int & x, int & y);
};