#include <iostream>
#include <SFML/Graphics.hpp>

#include "player.h"	//����� �����
#include "enemy.h"	//����� �����
#include "bullet.h"	//����� ����

#define RUS setlocale(LC_ALL, "rus")	//���������

using namespace std;
using namespace sf;

struct Window
{
	int x = 600;
	int y = 800;
} windowsize;

//�����
void Fire(Player & player, std::vector<Bullet> & bullet){
	sf::Vector2f coord;

	coord.x = player.rectangle.getPosition().x;
	coord.y = player.rectangle.getPosition().y - 15;

	bullet.push_back(Bullet(coord));

	std::cout << "Fire! ������ � ���� ���������: " << bullet.size() << " ����."<<std::endl;
}

//������������ ������
void MoveToKey(int key, Player & player){
	sf::Vector2f MoveCoord{ 0, 0 };

	if (key == sf::Keyboard::Left)
		MoveCoord.x -= 20;
	else if (key == sf::Keyboard::Right)
		MoveCoord.x += 20;
	else std::cout << "Fail Key: " << key << std::endl;

	//���� ������ ��� ����� ��� ����. ��������
	MoveCoord += player.rectangle.getPosition();

	//�� ��������� ������� �� ������� ������
	if (MoveCoord.x > -1 && MoveCoord.x < windowsize.x)
		player.rectangle.setPosition(MoveCoord);
}

//������������ ����
void UpdateMoveBullet(std::vector<Bullet> & bullet){
	//����� ����
	for (std::vector<Bullet>::iterator it = bullet.begin(); it != bullet.end();){
		it->shape.move(0, -1);

		if (it->shape.getPosition().y <= -1)
			it = bullet.erase(it);
		else ++it;
	}
}

//������������ ����
void UpdateMoveEnemy(std::vector<Enemy> & enemy){

	for (std::vector<Enemy>::iterator it = enemy.begin(); it != enemy.end();){


		it->rectangle.move(0, 1);	//������� ����

		if (it->rectangle.getPosition().y >= windowsize.y){
			it = enemy.erase(it);
			std::cout << "GAME END! ��������� ���� ������ ���� ���!" << std::endl;
		}
		else ++it;
	}

}

//������������ ���� � �����
void Collision(std::vector<Bullet> & bullet, std::vector<Enemy> & enemy){

	for (std::vector<Bullet>::iterator itBullet = bullet.begin(); itBullet != bullet.end(); ++itBullet)
		for (std::vector<Enemy>::iterator itEnemy = enemy.begin(); itEnemy != enemy.end(); ++itEnemy)

			//���� ��������� �� �����?
			if (itBullet->shape.getPosition().x >= itEnemy->rectangle.getPosition().x 										  //x>
				&& (itEnemy->rectangle.getPosition().x + itEnemy->rectangle.getSize().x) >= itBullet->shape.getPosition().x   //x<
				&& itBullet->shape.getPosition().y >= itEnemy->rectangle.getPosition().y									  //y>
				&& (itEnemy->rectangle.getPosition().y + itEnemy->rectangle.getSize().y) >= itBullet->shape.getPosition().y	  //y<
				&& itBullet->life && itEnemy->life){

				itBullet->life = false;	//������ ��� ���� ��� �� "����"
				itEnemy->life = false;	//������ ��� ���� ��� �� "���"
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

//�������� ������ �� ����
void CreateEnemy(std::vector<Enemy> & enemy){
	for (int i = 0; i < 5; i++){
		enemy.push_back(Vector2f(i * 100, 70.0f));
	}

}

//����� ������ ���������
int main()
{
	srand(time(0));
	RUS;
	cout << "������� �� ������ \"R\" ����� ��������� ������!"<< endl;
	cout << "���������� � ������ ���������, � ������ ��������� ������-�����." << endl;

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


		UpdateMoveBullet(bullet);	//��������� (��������) ���������� ����
		UpdateMoveEnemy(enemy);		//��������� (��������) ���������� ������

		Collision(bullet, enemy);	//���������, ���� �� ������������ ���� � �����
		RemoveDead(bullet, enemy);	//������� ���� � ����� ���� ������������ ����

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