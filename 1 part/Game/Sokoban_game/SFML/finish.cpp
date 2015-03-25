#pragma once
#include <SFML/Graphics.hpp>

struct Finish{
	// 0 - можно двигать, 1 - нельзя двигать
	sf::CircleShape shape;

	Finish(sf::Vector2f pos, float scale){
		shape.setFillColor(sf::Color::Magenta);
		shape.setPosition(pos.x*scale, pos.y*scale);
		shape.setRadius(scale / 2);

	};

};
