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

//прототип
//string rand_text();
word parser_text(string text);


int main()
{
	RUS;

	cout << "Словарь. 0.1v" << endl;

	vector<word> box;							//создаем вектор структур box
	word temp_word;


	//=============================================
	//чтение файла
	cout << "Открытие файла "<< file_open << "."<<endl;
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
			getline(F,buff);					// считали строку из файла
			box.push_back(parser_text(buff));	// string >> word >> vector <word>
			line_n++;
		}

		F.close();								//закрытие потока
		cout << "\nКоличество строк загружено в память = " <<  line_n << '\n'<<endl;
	}
	else {
		cout << "Файл "<< file_open << " не существует. "<<endl;
		return 1;
	}
	//конец чтения файла
	//=============================================


	//=============================================
	//добавление слова в вектор
	cout << "Введите значение и описание, чтобы добавить слово в словарь."<< endl;
	cout << "Для остановки ввода слова, оставьте поле пустым и нажмите ENTER!"<< endl;
	string part1; //строка для ввода данных
	string part2; //строка для ввода данных
	while(true){

		cout << "Значение: ";
		getline(cin,part1);				//Записываем значение в строку
		temp_word.key = part1;			//Записываем из строки в структуру

		if (part1.size() == 0) break;	//пустая строка, выходим из цикла

		cout << "Описание: ";
		getline(cin,part2);				//Записываем значение в строку
		temp_word.value = part2;		//Записываем из строки в структуру

		if (part2.size() == 0) break;	//пустая строка, выходим из цикла

		box.push_back(temp_word);		//записываем нашу структуру с данными в конец вектора
		cout << '\n';					//переход на новую строку
	}
	cout << "Ввод данных закончен!\n"<< endl;
	//Конец добавления слова в словарь
	//=============================================

	//=============================================
	//MINI-NANO сортировка
	for(int i = 0; i <  (int)box.size() - 1; i++)
		for(int j = i + 1; j < (int)box.size(); j++)
			if(strcmp(box[i].key.data(), box[j].key.data()) > 0)
				swap(box[i],box[j]);
	//Конец MINI-NANO сортировка
	//=============================================

	//=============================================
	//Вывод данных 
	cout << "\nВыводим данные из памяти:" << endl;
	for (vector<word>::iterator it = box.begin(); it < box.end(); it++){
		cout << it->key << "\t" << it->value << endl;
	}
	//Конец вывода данных
	//============================================= 

	//=============================================
	//Поиск слова по первым буквам
	string key;
	cout << "\nНапишите первые три буквы или слово целиком для поиска: " << endl;

	getline(cin, key);

	int mid = 0;				// переменная для хранения индекса среднего элемента массива
	int l = 0;				// индекс первого элемента в массиве
	int r = box.size();	// индекс последнего элемента в массиве

	cout << "Возможные совпадения:" << endl;
	while (l <= r)
	{
		mid = (r - l) / 2;
		
		if (strncmp(key.data(), box[mid].key.data(), key.size()) == 0){ cout << box[mid].key << endl; break; }
		if (strncmp(key.data(), box[mid].key.data(), key.size()) == 1){ r = --mid; continue; }
		if (strncmp(key.data(), box[mid].key.data(), key.size()) == -1){ l = ++mid; continue; }

	}

	int i = mid + 1;
	while (strncmp(key.data(), box[i].key.data(), key.size()) == 0){
		cout << box[i].key << endl;
		++i;
		if (i > (int)box.size()){ break; }	//не уходим за границу контейнера
	}

	int j = mid - 1;
	while (strncmp(key.data(), box[j].key.data(), key.size()) == 0){
		cout << box[j].key << endl;
		--j;
		if (j < 0){ break; }	//не уходим за границу контейнера
	}
	//Конец поиска
	//=============================================



	//=============================================
	//Сохранение данных из памяти в файл
	//Связываем объект с файлом, при этом файл открываем в режиме записи, предварительно удаляя все данные из него
	ofstream fout( file_save, ios_base::out | ios_base::trunc);

	if (!fout.is_open()) // если файл небыл открыт
	{
		cout << "Файл не может быть открыт или создан для сохранения данных."; // напечатать соответствующее сообщение
		return 1; // выполнить выход из программы
	}else{
		for(vector<word>::iterator it = box.begin(); it < box.end();it++){
			fout << it->key << ":"<< it->value << endl;
		}	
			cout << "\nВсе данные успешно сохранены в "<< file_save << "."<<endl;
	}
	fout.close();	// программа больше не использует файл, поэтому его нужно закрыть
	//Конец сохранения данных из памяти в файл
	//=============================================
	return 0;
}


//Парсинг
word parser_text(string text){

	word temp;
	char delimeters = ':'; //разделитель

	int n = 0;
	for(string::iterator iter = text.begin(); iter < text.end();iter++){

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
