#pragma once
#include <SFML/Graphics.hpp>

struct  Player{
	sf::RectangleShape rectangle;

	Player(float scale){
		rectangle.setPosition(0, 0);
		rectangle.setSize(sf::Vector2f(scale, scale));
		rectangle.setFillColor(sf::Color::Red);
	}

};
