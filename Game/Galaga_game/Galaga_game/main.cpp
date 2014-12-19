#include <iostream>
#include <SFML/Graphics.hpp>

#include "player.h"	//файлы врага
#include "enemy.h"	//файлы врага
#include "bullet.h"	//файлы пули

#define RUS setlocale(LC_ALL, "rus")	//кодировка

using namespace std;
using namespace sf;

struct Window
{
	int x = 600;
	int y = 800;
} windowsize;

//огонь
void Fire(Player & player, std::vector<Bullet> & bullet){
	sf::Vector2f coord;

	coord.x = player.rectangle.getPosition().x;
	coord.y = player.rectangle.getPosition().y - 15;

	bullet.push_back(Bullet(coord));

	std::cout << "Fire! —ейчас в игре участвует: " << bullet.size() << " пуль."<<std::endl;
}

//передвижение игрока
void MoveToKey(int key, Player & player){
	sf::Vector2f MoveCoord{ 0, 0 };

	if (key == sf::Keyboard::Left)
		MoveCoord.x -= 20;
	else if (key == sf::Keyboard::Right)
		MoveCoord.x += 20;
	else std::cout << "Fail Key: " << key << std::endl;

	//куда попадЄт наш игрок при след. движении
	MoveCoord += player.rectangle.getPosition();

	//не позвол€ем уходить за границы экрана
	if (MoveCoord.x > -1 && MoveCoord.x < windowsize.x)
		player.rectangle.setPosition(MoveCoord);
}

//передвижение пули
void UpdateMoveBullet(std::vector<Bullet> & bullet){
	//полет пули
	for (std::vector<Bullet>::iterator it = bullet.begin(); it != bullet.end();){
		it->shape.move(0, -1);

		if (it->shape.getPosition().y <= -1)
			it = bullet.erase(it);
		else ++it;
	}
}

//передвижение пули
void UpdateMoveEnemy(std::vector<Enemy> & enemy){

	for (std::vector<Enemy>::iterator it = enemy.begin(); it != enemy.end();){


		it->rectangle.move(0, 1);	//двигаем вниз

		if (it->rectangle.getPosition().y >= windowsize.y){
			it = enemy.erase(it);
			std::cout << "GAME END! ѕротивник смог пройти мимо вас!" << std::endl;
		}
		else ++it;
	}

}

//столкновение пули и врага
void Collision(std::vector<Bullet> & bullet, std::vector<Enemy> & enemy){

	for (std::vector<Bullet>::iterator itBullet = bullet.begin(); itBullet != bullet.end(); ++itBullet)
		for (std::vector<Enemy>::iterator itEnemy = enemy.begin(); itEnemy != enemy.end(); ++itEnemy)

			//пул€ находитс€ во враге?
			if (itBullet->shape.getPosition().x >= itEnemy->rectangle.getPosition().x 										  //x>
				&& (itEnemy->rectangle.getPosition().x + itEnemy->rectangle.getSize().x) >= itBullet->shape.getPosition().x   //x<
				&& itBullet->shape.getPosition().y >= itEnemy->rectangle.getPosition().y									  //y>
				&& (itEnemy->rectangle.getPosition().y + itEnemy->rectangle.getSize().y) >= itBullet->shape.getPosition().y	  //y<
				&& itBullet->life && itEnemy->life){

				itBullet->life = false;	//ставим что пул€ уже не "жива"
				itEnemy->life = false;	//ставим что враг уже не "жив"
				break;
			}
}

void RemoveDead(std::vector<Bullet> & bullet, std::vector<Enemy> & enemy){
	for (std::vector<Bullet>::iterator itBullet = bullet.begin(); itBullet != bullet.end();){
		if (itBullet->life) { ++itBullet; }
		else { itBullet = bullet.erase(itBullet); }
	}

	for (std::vector<Enemy>::iterator itEnemy = enemy.begin(); itEnemy != enemy.end();){
		if (itEnemy->life) { ++itEnemy; }
		else { itEnemy = enemy.erase(itEnemy); }
	}
}

//создание врагов на поле
void CreateEnemy(std::vector<Enemy> & enemy){
	for (int i = 0; i < 5; i++){
		enemy.push_back(Vector2f(i * 100, 70.0f));
	}

}

//точка началы программы
int main()
{
	srand(time(0));
	RUS;
	cout << "Ќажмите на кнопку \"R\" „тобы выпустить врагов!"<< endl;
	cout << "”правление с помощь стрелочек, а пробел выпускает ћееега-лазер." << endl;

	RenderWindow window(VideoMode(windowsize.x, windowsize.y), "Galaga Game!");
	window.setFramerateLimit(60);

	Player player(windowsize.x, windowsize.y);
	vector<Bullet> bullet;
	vector<Enemy> enemy;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
				Fire(player, bullet);
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
				MoveToKey(event.key.code, player);
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right)
				MoveToKey(event.key.code, player);
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::R)
				CreateEnemy(enemy);
				//enemy.push_back(Vector2f(10 + rand() % 560, 70.f));
		}


		UpdateMoveBullet(bullet);	//обновл€ем (измен€ем) координаты пуль
		UpdateMoveEnemy(enemy);		//обновл€ем (измен€ем) координаты врагов

		Collision(bullet, enemy);	//провер€ем, было ли столкновение пули и врага
		RemoveDead(bullet, enemy);	//удал€ем пулю и врага если столкновение было

		window.clear(Color(255, 204, 153));

		if (!bullet.empty())
			for (vector<Bullet>::iterator it = bullet.begin(); it != bullet.end(); ++it)
				window.draw(it->shape);

		if (!enemy.empty())
			for (vector<Enemy>::iterator it = enemy.begin(); it != enemy.end(); ++it)
				window.draw(it->rectangle);

		window.draw(player.rectangle);

		window.display();
	}


	return 0;
}