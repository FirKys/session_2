#include <SFML/Graphics.hpp>
#include "bullet.h"

//����������� [����]
Bullet::Bullet(sf::Vector2f & pos){
	life = true;
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(pos);
	shape.setRadius(5);
}
