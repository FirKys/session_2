#include <SFML/Graphics.hpp>
#include "player.h"

////����������� [������]
Player::Player(int & x, int & y){
	rectangle.setSize(sf::Vector2f(20, 20));
	rectangle.setFillColor(sf::Color::Green);
	rectangle.setPosition(x / 2.f, y - 50.f);
}
