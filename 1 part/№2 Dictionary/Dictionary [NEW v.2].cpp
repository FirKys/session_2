//#include "stdafx.h"
#include <iostream>		//
#include <stdio.h>		//
#include <iterator>		//
#include <string>		// type: string
#include <vector>		// type: vector
#include <stdlib.h> 	// rand(), srand()
#include <ctime>		// time()
#include <fstream>		// <ifstream> - файловый ввод и <ofstream>  - файловый вывод.

#define file_open "dictionary.txt"	// Какое файл открываем
#define file_save "out.txt"		// В какой сохраняем
#define RUS setlocale(LC_ALL, "Russian")

using namespace std;


//структура для словаря
struct word{
	string key;
	string value;
};

//Протатипы функций
word parser_text(string text);								//Разделение строки на две части
void sort(vector<word>& target);							//Сортировка вектора
int binarySearch(vector<word> source, string target);		//Бинарный поиск


int main()
{
	RUS;

	cout << "Словарь. 0.1v" << endl;

	vector<word> box;							//создаем вектор структур box
	word temp_word;


	//=============================================
	//чтение файла
	cout << "Открытие файла " << file_open << "." << endl;
	ifstream F(file_open);							//поток со строками
	int line_n = 0;								//Счетчик для подсчета строк
	string buff;								//буфер > getline

	//если открытие файла прошло корректно, то
	if (F.is_open())
	{
		//цикл для чтения значений из файла; выполнение цикла прервется,
		//когда достигнем конца файла, в этом случае F.eof() вернет истину.
		while (!F.eof())
		{
			getline(F, buff);					// считали строку из файла
			box.push_back(parser_text(buff));	// string >> word >> vector <word>
			line_n++;
		}

		F.close();								//закрытие потока
		cout << "\nКоличество строк загружено в память = " << line_n << '\n' << endl;
	}
	else {
		cout << "Файл " << file_open << " не существует. " << endl;
		return 1;
	}
	//конец чтения файла
	//=============================================


	//=============================================
	//добавление слова в вектор
	cout << "Введите значение и описание, чтобы добавить слово в словарь." << endl;
	cout << "Для остановки ввода слова, оставьте поле пустым и нажмите ENTER!" << endl;
	string part1; //строка для ввода данных
	string part2; //строка для ввода данных
	while (true){

		cout << "Значение: ";
		getline(cin, part1);				//Записываем значение в строку
		temp_word.key = part1;			//Записываем из строки в структуру

		if (part1.size() == 0) break;	//пустая строка, выходим из цикла

		cout << "Описание: ";
		getline(cin, part2);				//Записываем значение в строку
		temp_word.value = part2;		//Записываем из строки в структуру

		if (part2.size() == 0) break;	//пустая строка, выходим из цикла

		box.push_back(temp_word);		//записываем нашу структуру с данными в конец вектора
		cout << '\n';					//переход на новую строку
	}
	cout << "Ввод данных закончен!\n" << endl;


	//===============	Соритировка	===============
	sort(box);


	//==============	Вывод данных	===========
	cout << "\nВыводим сорт. данные из памяти:" << endl;
	for (vector<word>::iterator it = box.begin(); it < box.end(); it++)
		cout << it->key << "\t" << it->value << endl;


	//==============	Бинарный поиск	===========
	string key;
	cout << "\nНапишите первые три буквы или слово целиком для поиска: " << endl;

	getline(cin, key);

	//Слово введено?
	if (key.size() > 0){

		cout << "Возможные совпадения:" << endl;
		int result = binarySearch(box, key);

		if (result < 0)
			cout << "Совпадений не найдено." << endl;
		else {
			while (strncmp(key.data(), box[result].key.data(), key.size()) == 0){
				cout << box[result].key << endl;
				result++;
				if (result > (int)box.size()) break;	//чтобы не уйти за границу контейнера
			}
		}
	}




	//=============================================
	//Сохранение данных из памяти в файл
	//Связываем объект с файлом, при этом файл открываем в режиме записи, предварительно удаляя все данные из него
	ofstream fout(file_save, ios_base::out | ios_base::trunc);

	if (!fout.is_open()) // если файл небыл открыт
	{
		cout << "Файл не может быть открыт или создан для сохранения данных."; // напечатать соответствующее сообщение
		return 1; // выполнить выход из программы
	}
	else{
		for (vector<word>::iterator it = box.begin(); it < box.end(); it++){
			fout << it->key << ":" << it->value << endl;
		}
		cout << "\nВсе данные успешно сохранены в " << file_save << "." << endl;
	}
	fout.close();	// программа больше не использует файл, поэтому его нужно закрыть


	return 0;
}

//Сортировка
void sort(vector<word>& target){
	for (int i = 0; i < (int)target.size() - 1; i++)
		for (int j = i + 1; j < (int)target.size(); j++)
			if (strcmp(target[i].key.data(), target[j].key.data()) > 0)
				swap(target[i], target[j]);
}


//Бинарный поиск (Возращает либо id крайнего значения, либо -1 в случае неудачи.)
int binarySearch(vector<word> source, string target)
{
	int size = source.size();
	int targetSize = target.size();

	//Проверки
	if (size == 0)
		return -1;
	else if (strncmp(target.data(), source[0].key.data(), targetSize) < 0){				//искомый элемент меньше всех в массиве
		cout << "! Искомый элемент меньше всех в массиве" << endl;
		return -1;
	}
	else if (strncmp(target.data(), source[size - 1].key.data(), targetSize) > 0){ 		//искомый элемент больше всех в массиве
		cout << "! Искомый элемент больше всех в массиве" << endl;
		return -1;
	}

	//инициализация
	int first = 0;
	int last = size;

	while (first < last)
	{
		int mid = first + (last - first) / 2;

		if ((int)source[mid].key.size() < targetSize){
			first = mid + 1;
			continue;
		}

		if (strncmp(target.c_str(), source[mid].key.data(), targetSize) <= 0)
			last = mid;
		else
			first = mid + 1;
	}

	if (strncmp(source[last].key.data(), target.c_str(), targetSize) == 0)
		return last;
	else
		return -1;

}

//Разделение строки на две части и копирование в word
word parser_text(string text){

	word temp;
	char delimeters = ':'; //разделитель

	int n = 0;
	for (string::iterator iter = text.begin(); iter < text.end(); iter++){

		char symb = (char)*iter;

		//Нашли разделитель?
		if (delimeters == symb) {
			//cout << "Разделитель (" << delimeters <<") найден." << endl;
			temp.key = text.substr(0, n);
			n++;
			temp.value = text.substr(n, text.size());
			//cout << "\nЗначение: " << temp.key << " Описание: " << temp.value << endl;
			break;
		}
		n++;
	}

	return temp;
};
