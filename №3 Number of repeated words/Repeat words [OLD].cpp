/* в идеале прога должна считывать слова из текста, подсчитывая повторы этих слов и чтоб в конце выводила список наиболее повторяющихся слов */

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

#define dictionary "dictionary.txt"
#define RUS setlocale(LC_ALL, "Russian")

using namespace std;

struct rating{
	string word;
	int value;
};

int main() {
	RUS;

	cout << "Start: " << dictionary << endl;
	ifstream is(dictionary);

	if (!is.is_open()){ 
		cout << "Файл не может быть открыт!" << endl; 
		return 1;
	}

	string buffer;
	rating buftest;
	vector<rating> text;

	//записываем слова в вектор
	while (!is.eof()) {
		is >> buffer;
		cout << "Сожрал слово: " << buffer << endl;

		buftest.word = buffer;
		buftest.value = 0;


		for (vector<rating>::iterator i = text.begin(); i < text.end() ;i++)	
			if (i->word == buftest.word){
				i->value++;
				break;
			}	 

		text.push_back(buftest);
	}


	//выводим
	cout << "=========================== " << endl;
	cout << "Найденые совпадения: " << endl;
	for (vector<rating>::iterator i = text.begin(); i < text.end() ;i++) {
		if ( i->value > 0)
			cout << "Слово: " << i->word << " \tСовпадений: " << i->value << endl;
	}

	return 0;
}
