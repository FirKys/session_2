#include <SFML/Graphics.hpp>
#include "enemy.h"

//Инцилизация [врага]
Enemy::Enemy(sf::Vector2f & pos){
	life = true;
	move = 0;
	rectangle.setSize(sf::Vector2f(40, 40));
	rectangle.setFillColor(sf::Color::Cyan);
	rectangle.setPosition(pos);
}
