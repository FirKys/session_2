#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

//��������� ���������� ����
struct window
{
	unsigned int x = 800;
	unsigned int y = 500;
} windows;

//����� ������
class Player
{
public:
	RectangleShape rectangle;		//��� ����� (�������)
	VertexArray turret;				//����� ������
	int player;						//ID ������
	float angle;					//������ �����

	Player(int _player){
		angle = 0.0;
		player = _player;
		rectangle.setSize(Vector2f(20, 20));
		rectangle.setFillColor(Color::Green);
	};

};

//����� ����
class Bullet{
public:
	CircleShape shape;	//����
	int side;			//� ����� ������� �����: 1 - �����, 2 - ������
	int who;

	Bullet(Vector2f coord, int _side, int _who){
		who = _who;
		side = _side;
		shape.setPosition(coord);
		shape.setFillColor(Color::Red);
		shape.setRadius(5);
	}

	//��������� ����������
	void update(){
		Vector2f newcoord = { 1, 0 };

		if (side == 1){			//���� ����� �����
			shape.setPosition(shape.getPosition() - newcoord);
		}
		else if (side == 2) {	//���� ����� ������
			shape.setPosition(shape.getPosition() + newcoord);
		}
	}


};

//������� ��������
void Fire(vector<Bullet> &bullet, Player & p, int side){
	Vector2f coord = {0,0};
	coord = p.turret[1].position;
	bullet.push_back(Bullet(coord, side, p.player));
};

//�������� �����
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

//�������� �����
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
	short int player = 0;	// ID ������

	Player p1(++player);	//ID: 1 |����� �����|
	Player p2(++player);	//ID: 2 |������ �����|

	//cout << p1.player << " | " << p2.player << endl;

	player = 1; //����������, ������ ��� ����� ������� � �������� ����������� ����� ����� �����

	vector<Bullet> bullet;

	p1.rectangle.setPosition(Vector2f(50.f, windows.y - 100.f));												//������������� ������� ������� ������
	p2.rectangle.setPosition(Vector2f(windows.x - (p1.rectangle.getSize().x + 50.f), windows.y - 100.f));		//������������� ������� ������� ������

	CreateTurret(p1);	//������� ������ ������� ������
	CreateTurret(p2);	//������� ������ ������� ������

	RenderWindow window(VideoMode(windows.x, windows.y), "Artillery Game");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || event.key.code == Keyboard::Escape && event.type == Event::KeyPressed)
				window.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left || event.type == Event::KeyPressed && event.key.code == Keyboard::Right){
				//��� ���?
				if (player == 1)
					move(p1, event.key.code);
				else if (player == 2)
					move(p2, event.key.code);
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space){
				//��� ���?
				if (player == 1){
					Fire(bullet, p1, 2);	//���� ����� �� ������ p1 � ������ �������
					player = 2;				//����� ��������, ������ ��� ����� ������ �����
				}
				else if (player == 2){
					Fire(bullet, p2, 1);	//���� ����� �� ������ p2 � ����� �������
					player = 1;			//����� ��������, ������ ��� ����� ������ �����
				}

			}
		}

		//��������� ���������� ����
		for (vector<Bullet>::iterator it = bullet.begin(); it != bullet.end(); ++it)
			it->update();

		window.clear(Color::Black);		//������� �����

		window.draw(p1.rectangle);		//������ ������ p1
		window.draw(p2.rectangle);		//������ ������ p2

		window.draw(p1.turret);			//������ ������� ��� ������ p2
		window.draw(p2.turret);			//������ ������� ��� ������ p2

		//������ ���� ����
		for (vector<Bullet>::iterator it = bullet.begin(); it != bullet.end(); ++it){
			window.draw(it->shape);
		}

		for (vector<Bullet>::iterator it = bullet.begin(); it != bullet.end(); ){
			
			//������� ������ �� �����?
			if (it->shape.getPosition().x >= windows.x || it->shape.getPosition().x <= 0)
				it = bullet.erase(it);	//������� ���� ���� ������� �� �������
			else ++it;	//��������� � ����. ����

			//���� ������ �� �����?
			//if ()
		}

		window.display();
	}

	return 0;
}