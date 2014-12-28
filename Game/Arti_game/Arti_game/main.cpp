#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct window
{
	unsigned int x = 800;
	unsigned int y = 500;
} window;

class Player
{
public:
	RectangleShape rectangle;
	VertexArray turret;
	int player;
	float angle;

	Player(int _player){
		angle = 0.0;
		player = _player;
		rectangle.setSize(Vector2f(20, 20));
		rectangle.setFillColor(Color::Green);
	};

private:
};

class Bullet{


};

void Fire(vector<Bullet> &bullet, Player & p){

};

//Создание пушки
void CreateTurret(Player & p){
	Vector2f pcoord = p.rectangle.getPosition();

	float x = 0, y = 0;
	float r = 35;

	p.turret.setPrimitiveType(LinesStrip);

	if (p.player == 1){
		pcoord.x += p.rectangle.getSize().x;

		x = p.rectangle.getPosition().x + r * cos(p.angle);
		y = p.rectangle.getPosition().y + r * sin(p.angle);

		p.turret.append(pcoord);
		p.turret.append(Vector2f(x, y));
	}
	else if (p.player == 2)
	{
		x = p.rectangle.getPosition().x + r * cos(p.angle);
		y = p.rectangle.getPosition().y + r * sin(p.angle);

		p.turret.append(pcoord);
		p.turret.append(Vector2f(x, y));
	}
}

//Смещение пушки
void move(Player & p, int code){
	float x = 0, y = 0;
	float r = 35;

	if (code == Keyboard::Left){
		p.angle -= 0.1f;

		cout << p.angle << endl;

		x = p.turret[0].position.x + r * cos(p.angle);
		y = p.turret[0].position.y + r * sin(p.angle);

		p.turret[1].position.x = x;
		p.turret[1].position.y = y;
	}

	else if (code == Keyboard::Right){
		p.angle += 0.1f;

		cout << p.angle << endl;

		x = p.turret[0].position.x + r * cos(p.angle);
		y = p.turret[0].position.y + r * sin(p.angle);

		p.turret[1].position.x = x;
		p.turret[1].position.y = y;
	}
}

int main()
{
	short int player = 0;	// ID игрока

	Player p1(++player);	//ID: 1 |левый игрок|
	Player p2(++player);	//ID: 2 |правый игрок|
	//cout << p1.player << " | " << p2.player << endl;

	player = 1; //Сбрасываем, теперь это будет служить в качестве определения какой игрок ходит

	vector<Bullet> bullet;

	p1.rectangle.setPosition(Vector2f(50.f, window.y - 100.f));												//Устанавливаем позицию первого игрока
	p2.rectangle.setPosition(Vector2f(window.x - (p1.rectangle.getSize().x + 50.f), window.y - 100.f));		//Устанавливаем позицию второго игрока

	CreateTurret(p1);	//Создаём турель первому игроку
	CreateTurret(p2);	//Создаем турель второму игроку

	RenderWindow window(VideoMode(window.x, window.y), "Artillery Game");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || event.key.code == Keyboard::Escape && event.type == Event::KeyPressed)
				window.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left || event.type == Event::KeyPressed && event.key.code == Keyboard::Right){
				//чей ход?
				if (player == 1)
					move(p1, event.key.code);
				else if (player == 2)
					move(p2, event.key.code);
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space){
				//чей ход?
				if (player == 1){
					Fire(bullet, p1);
					player = 2;			//после выстрела, делаем что ходит другой игрок
				}
				else if (player == 2){
					Fire(bullet, p2);
					player = 1;			//после выстрела, делаем что ходит другой игрок
				}

			}
		}

		window.clear(Color::Black);		//Очищаем экран

		window.draw(p1.rectangle);		//Рисуем игрока p1
		window.draw(p2.rectangle);		//Рисуем игрока p2

		window.draw(p1.turret);			//Рисуем туррель для игрока p2
		window.draw(p2.turret);			//Рисуем туррель для игрока p2

		//window.draw(convex);
		window.display();
	}

	return 0;
}