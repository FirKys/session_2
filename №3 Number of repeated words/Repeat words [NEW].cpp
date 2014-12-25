// Программа получает некоторое количество слов из файла.
// Должна сохранить в память.
// Подсчитать повторы слов и вывести их.
//
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>

#define dictionary "word.txt"			//название файла
#define RUS setlocale(LC_ALL, "Russian")	//локаль |кодировка консоли|

using namespace std;


int main() {
	RUS;

	cout << "Open: " << dictionary << endl;
	map<string, int> word;					//Контейнер map


	ifstream is(dictionary);				//Пытаемся загрузить файл в поток
	if (!is.is_open()){
		cout << "Файл не может быть открыт!" << endl;
		return 1;
	}

	//записываем слова в map
	while (!is.eof()) {
		string buffer;
		is >> buffer;

		//word.insert(pair<string, int>(buffer, 1));
		word[buffer]++;
		cout << "Добавлено слово: " << buffer << endl;
	}


	//выводим
	cout << "=========================== " << endl;
	cout << "Найденные совпадения: " << endl;
	for (map<string, int>::iterator i = word.begin(); i != word.end(); i++) {
		if (i->second >= 2) //Выводить если найдено больше двух значений
			cout << "Слово: " << i->first << " \tСовпадений: " << i->second << endl;
	}

	return 0;
}
