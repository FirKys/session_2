#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

//Настройки разрешения окна
struct window
{
	unsigned int x = 800;
	unsigned int y = 500;
} windows;

//Класс игрока
class Player
{
public:
	RectangleShape rectangle;		//Сам игрок (квадрат)
	VertexArray turret;				//Пушка игрока
	int player;						//ID игрока
	float angle;					//Градус пушки

	Player(int _player){
		angle = 0.0;
		player = _player;
		rectangle.setSize(Vector2f(20, 20));
		rectangle.setFillColor(Color::Green);
	};

};

//Класс пули
class Bullet{
public:
	CircleShape shape;	//круг
	int side;			//В какую сторону летит: 1 - влево, 2 - вправо
	int who;

	Bullet(Vector2f coord, int _side, int _who){
		who = _who;
		side = _side;
		shape.setPosition(coord);
		shape.setFillColor(Color::Red);
		shape.setRadius(5);
	}

	//Обновляем координаты
	void update(){
		Vector2f newcoord = { 1, 0 };

		if (side == 1){			//Пуля летит влево
			shape.setPosition(shape.getPosition() - newcoord);
		}
		else if (side == 2) {	//Пуля летит вправо
			shape.setPosition(shape.getPosition() + newcoord);
		}
	}


};

//Функция выстрела
void Fire(vector<Bullet> &bullet, Player & p, int side){
	Vector2f coord = { 0, 0 };
	coord = p.turret[1].position;
	bullet.push_back(Bullet(coord, side, p.player));
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
		p.angle = 3.1f;
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

//Точка входит в квадрат?
bool Check(RectangleShape rect, CircleShape shape){
	Vector2f coordrect = rect.getPosition();
	Vector2f coordshape = shape.getPosition();

	if (coordrect.x <= coordshape.x &&
		coordrect.y <= coordshape.y &&
		coordrect.x + rect.getSize().x >= coordshape.x &&
		coordrect.y + rect.getSize().y >= coordshape.y)
	{
		return true;
	}
	else { return false; }
}


int main()
{
	short int player = 0;	// ID игрока

	Player p1(++player);	//ID: 1 |левый игрок|
	Player p2(++player);	//ID: 2 |правый игрок|

	//cout << p1.player << " | " << p2.player << endl;

	player = 1; //Сбрасываем, теперь это будет служить в качестве определения какой игрок ходит

	vector<Bullet> bullet;

	p1.rectangle.setPosition(Vector2f(50.f, windows.y - 100.f));												//Устанавливаем позицию первого игрока
	p2.rectangle.setPosition(Vector2f(windows.x - (p1.rectangle.getSize().x + 50.f), windows.y - 100.f));		//Устанавливаем позицию второго игрока

	CreateTurret(p1);	//Создаём турель первому игроку
	CreateTurret(p2);	//Создаем турель второму игроку

	RenderWindow window(VideoMode(windows.x, windows.y), "Artillery Game");

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
					Fire(bullet, p1, 2);	//Пуля летит от игрока p1 в правую сторону
					player = 2;				//после выстрела, делаем что ходит другой игрок
				}
				else if (player == 2){
					Fire(bullet, p2, 1);	//Пуля летит от игрока p2 в левую сторону
					player = 1;			//после выстрела, делаем что ходит другой игрок
				}

			}
		}

		//Обновляем координаты пули
		for (vector<Bullet>::iterator it = bullet.begin(); it != bullet.end(); ++it)
			it->update();

		window.clear(Color::Black);		//Очищаем экран

		window.draw(p1.rectangle);		//Рисуем игрока p1
		window.draw(p2.rectangle);		//Рисуем игрока p2

		window.draw(p1.turret);			//Рисуем туррель для игрока p2
		window.draw(p2.turret);			//Рисуем туррель для игрока p2

		//рисуем наши пули
		for (vector<Bullet>::iterator it = bullet.begin(); it != bullet.end(); ++it){
			window.draw(it->shape);
		}

		for (vector<Bullet>::iterator it = bullet.begin(); it != bullet.end();){
			
			//В игрока 1 попали пули?
			if (Check(p1.rectangle, it->shape)){
				cout << "In the p1 hit by a bullet" << endl;
				it = bullet.erase(it);	//удаляем пулю
				break;
			}

			//В игрока 2 попали пули?
			if (Check(p2.rectangle, it->shape)){
				cout << "In the p2 hit by a bullet" << endl;
				it = bullet.erase(it);	//удаляем пулю
				break;
			}

			//улетела пулька за экран?
			if (it->shape.getPosition().x >= windows.x || it->shape.getPosition().x <= 0){
				it = bullet.erase(it);	//удаляем пули если улетела за границу
				break;
			}

			++it; //переходим к след. пуле.


		}

		window.display();
	}

	return 0;
}