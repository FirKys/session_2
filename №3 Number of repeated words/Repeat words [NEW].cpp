// Программа получает некоторое количество слов из файла.
// Должна сохранить в память.
// Подсчитать повторы слов и вывести их в сорт. порядке по значению, точнее числу повторов.
// Обязательное использование map

// !Проблема: Невозможно сортировать по значению, поэтому придётся создавать дополнительный контейнер.
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#define dictionary "word.txt"			//название файла
#define RUS setlocale(LC_ALL, "Russian")	//локаль |кодировка консоли|

using namespace std;

//для сортировки
bool check(const pair< string, int > &a, const pair< string, int > &b)
{
	return a.second > b.second;
}

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
		string buffer;						//временное хранение слова из файла
		is >> buffer;						//забираем слово из файла

		word[buffer]++;						//заносим в map или прибавляем +1 если найден повтор
		cout << "Добавлено слово: " << buffer << endl;
	}

	//создаем вектор из map'a
	vector<pair<string,int> > vec(word.begin(), word.end());
	// сортируем этот вектор по значению, т.е числу повторов
	sort(vec.begin(), vec.end(), check);

	//выводим из вектора наши повторы :)
	cout << "=========================== " << endl;
	cout << "Найденные совпадения: " << endl;
	for (vector<pair<string, int> >::iterator i = vec.begin(); i != vec.end(); i++) {
		if (i->second >= 2) //Выводить если найдено больше двух значений
			cout << "Слово: " << i->first << " \tСовпадений: " << i->second << endl;
	}

	return 0;
}
