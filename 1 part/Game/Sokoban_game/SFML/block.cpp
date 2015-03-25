#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct Block{
	// 0 - можно двигать, 1 - нельзя двигать
	sf::RectangleShape rectangle;
	int type;

	Block(sf::Vector2f pos, int _type, float scale){
		type = _type;

		if (type == 0)
			rectangle.setFillColor(sf::Color::Transparent);
		else
			rectangle.setFillColor(sf::Color::Black);

		rectangle.setPosition(pos.x*scale, pos.y*scale);
		rectangle.setSize(sf::Vector2f(scale, scale));

		std::cout << "Create: " << rectangle.getPosition().x << "," << rectangle.getPosition().x  << "type: " << type << std::endl;

	};

};