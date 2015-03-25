#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include <iostream>

#include <SFML/Graphics.hpp>


#include "player.cpp"
#include "block.cpp"
#include "finish.cpp"

#define RUS setlocale(LC_ALL, "Russian")

using namespace std;
using namespace sf;

int n{ 20 }, m{ 20 }; float scale{ 30 };
int windowWidth{ (int)scale*n }, windowHeight{ (int)scale * m };

vector<Block>::iterator CheckBlock(Vector2f &coord, vector<Block> &block){
	vector<Block>::iterator it;

	for (it = block.begin(); it != block.end(); ++it)
	if (coord == it->rectangle.getPosition()){
		return it;
		break;
	}

	return it;
}

void KeyInput(int CodeInp, Player &player, vector<Block> &block){
	Vector2f CoordMove{ 0, 0 };
	Vector2f NextPos = player.rectangle.getPosition();
	Vector2f NextPos2;

	bool end = false;

	/* CRAZY MODE ON*/
	vector<Block>::iterator NextBlock;
	vector<Block>::iterator NextBlock2;
	/* CRAZY MODE OFF*/

	if (CodeInp == Keyboard::Up)
		CoordMove.y -= scale;
	else if (CodeInp == Keyboard::Down)
		CoordMove.y += scale;
	else if (CodeInp == Keyboard::Left)
		CoordMove.x -= scale;
	else if (CodeInp == Keyboard::Right)
		CoordMove.x += scale;
	else cout << "Fail move: " << CodeInp << endl;

	/* CRAZY MODE ON*/
	NextPos += CoordMove;
	NextPos2 = CoordMove + NextPos;

	for (vector<Block>::iterator it = block.begin(); it != block.end(); ++it)
	if (NextPos == it->rectangle.getPosition()){
		NextBlock = it;
		break;
	}

	for (vector<Block>::iterator it = block.begin(); it != block.end(); ++it)
	if (NextPos2 == it->rectangle.getPosition()){
		NextBlock2 = it;
		break;
	}
	/* CRAZY MODE OFF*/

	if (NextBlock._Ptr != 0 && NextBlock2._Ptr == 0 && NextBlock->type == 0){
		player.rectangle.move(CoordMove);
		NextBlock->rectangle.move(CoordMove);
	}
	else if (NextBlock._Ptr == 0){
		player.rectangle.move(CoordMove);
	}

}

void CreateMap(string _name, vector <Block> & block, vector <Finish> & finish, Player & player){
	ifstream map_name(_name);
	char buff;
	int x = 0, y = 0;

	if (!map_name.is_open())
		cout << "Fail loading map!" << endl;
	else{
		cout << "Open map: " << _name << endl;

		while (!map_name.eof()){
			buff = map_name.get();

			if (buff == '@')
				block.push_back(Block(Vector2f(x, y), 0, scale));
			else if (buff == '#')
				block.push_back(Block(Vector2f(x, y), 1, scale));
			else if (buff == 'O')
				finish.push_back(Finish(Vector2f(x, y), scale));
			else if (buff == 'X'){
				player.rectangle.setPosition(Vector2f(x*scale, y*scale));
			}

			x++;

			if (buff == '\n'){
				y++; x = 0;
			}

		}
	}
}

void FillLine(vector<Vertex> &line){

	for (float i = 0; i < windowWidth; i += scale){
		line.push_back(Vector2f(i, 0));
		line.push_back(Vector2f(i, (float)windowHeight));
	}
	for (float j = 0; j < windowHeight; j += scale){
		line.push_back(Vector2f(0, j));
		line.push_back(Vector2f((float)windowWidth, j));
	}

}

int main()
{
	ContextSettings setting;	//настройки
	vector <Block> block;		//блоки
	vector <Finish> finish;		//блоки
	Player player(scale);		//игрок
	vector <Vertex> line;		//поле

	int GameEnd = 0;
	bool draw_line = 0;

	//заполняем линиями
	FillLine(line);
	CreateMap("map.map", block, finish, player);

	RenderWindow window{ VideoMode(windowWidth, windowHeight), "Sokoban RPG :O", Style::Close };
	window.setFramerateLimit(60);


	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
				window.close();

			else if (Keyboard::isKeyPressed(Keyboard::Up) ||
				Keyboard::isKeyPressed(Keyboard::Down) ||
				Keyboard::isKeyPressed(Keyboard::Left) ||
				Keyboard::isKeyPressed(Keyboard::Right) &&
				event.type == Event::KeyPressed)
					KeyInput(event.key.code, player, block);

			else if (Keyboard::isKeyPressed(Keyboard::R) && event.type == Event::KeyPressed)
				draw_line = !draw_line;
		}

		for (vector<Finish>::iterator it = finish.begin(); it != finish.end(); ++it)
		for (vector<Block>::iterator it2 = block.begin(); it2 != block.end(); ++it2)
		if (it->shape.getPosition() == it2->rectangle.getPosition())
			GameEnd++;


		//Clear
		window.clear(Color::Color(255, 204, 153));

		//Draw::Поле(Линии)
		if (draw_line)
			window.draw(&line[0], line.size(), Lines);
		//Draw::Финиш
		for (auto it = finish.begin(); it < finish.end(); it++)
			window.draw(it->shape);
		//Draw::Блок
		for (auto it = block.begin(); it < block.end(); it++)
			window.draw(it->rectangle);
		//Draw::Игрок
		window.draw(player.rectangle);

		//Viev
		window.display();

		if (finish.size() != GameEnd)
			GameEnd = 0;
		else {block.clear(); finish.clear();  }



	}

	return 0;
}