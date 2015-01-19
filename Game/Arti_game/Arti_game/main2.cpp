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

class radian{
public:
	int angle = 0;


	void setAngle(int _angle){
		angle += _angle;

		if (angle > 360) angle = 0;
		if (angle < 0)  angle = 360;

	};


};

//Класс игрока
class Player
{
public:
	RectangleShape rectangle;		//Сам игрок (квадрат)
	VertexArray turret;				//Пушка игрока
	radian test;
	int player;						//ID игрока

	Player(int player, float x, float y){
		// == Создание игрока ==
		rectangle.setPosition(Vector2f(x, y));		//Позиция игрока
		this->player = player;						//ID игрока
		rectangle.setSize(Vector2f(20, 20));		//Размер
		rectangle.setFillColor(Color::Green);		//Цвет

		// == Создание пушки ==
		Vector2f centerTank = { 0, 0 };
		centerTank.x = rectangle.getPosition().x + (rectangle.getSize().x / 2);	//Центр танка по x
		centerTank.y = rectangle.getPosition().y + (rectangle.getSize().y / 2);	//Центр танка по y

		turret.setPrimitiveType(LinesStrip);

		turret.append(centerTank);	//Начало пушки из танка
		centerTank.y -= 25;
		turret.append(centerTank);	//Смещение по y на 10
	};

};

//Класс пули
class Bullet{
public:
	CircleShape shape;	//круг

	int who;
	radian test;
	float time = 0;

	Bullet(Vector2f coord, int who, int test){
		this->test.angle = test;
		this->who = who;
		shape.setPosition(coord);
		shape.setFillColor(Color::Red);
		shape.setRadius(5);
	}

	//Обновляем координаты
	void update(){
		Vector2f step = {0,0};
		float testik = test.angle * 3.14159265358979323846 / 180;

		step.x = 0.32f * cos(testik);
		step.y = 0.32f * sin(testik);

		step.y += 0.0015f * time;
		shape.move(step);

		time += 0.1;
	}


};

//Функция выстрела
void Fire(vector<Bullet> &bullet, Player & p){
	Vector2f coordBullet = { 0, 0 };
	Vector2f coordTurret = p.turret[1].position;


	bullet.push_back(Bullet(coordTurret, p.player, p.test.angle));
};


//Смещение пушки
void move(Player & p, int code){
	float x = 0, y = 0;
	float r = 25;

	if (code == Keyboard::Left){
		p.test.setAngle(2);

		cout << "Left: "<< p.test.angle << endl;
		float testik = p.test.angle * 3.14159265358979323846 / 180;

		x = p.turret[0].position.x + r * cos(testik);
		y = p.turret[0].position.y + r * sin(testik);


		p.turret[1].position.x = x;
		p.turret[1].position.y = y;
	}

	else if (code == Keyboard::Right){
		p.test.setAngle(-2);

		cout << "Right: "<< p.test.angle << endl;
		float testik = p.test.angle * 3.14159265358979323846 / 180;

		x = p.turret[0].position.x + r * cos(testik);
		y = p.turret[0].position.y + r * sin(testik);


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

	Player p1(++player, 50.f, windows.y - 100.f);	//ID: 1 |левый игрок|
	Player p2(++player, (windows.x - (p1.rectangle.getSize().x + 50.f)) , (windows.y - 100.f) );	//ID: 2 |правый игрок|

	player = 1; //Сбрасываем, теперь это будет служить в качестве определения какой игрок ходит

	vector<Bullet> bullet;

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
					Fire(bullet, p1);	//Пуля летит от игрока p1 в правую сторону
					player = 2;				//после выстрела, делаем что ходит другой игрок
				}
				else if (player == 2){
					Fire(bullet, p2);	//Пуля летит от игрока p2 в левую сторону
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