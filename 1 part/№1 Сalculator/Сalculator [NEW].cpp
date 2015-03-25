#include <iostream>

#include <string>
#include <vector>
#include <deque> 

#include <sstream> 


#define RUS setlocale(LC_ALL, "Russian")

using namespace std;

class IntStackFullException {
};

class IntStackEmptyException {
};

class IntStack {
public:

	static const int DEFAULT_SIZE = 128;
	static const int MIN_SIZE = 16;

	IntStack(int size = DEFAULT_SIZE);
	virtual void push(int value) throw(IntStackFullException);
	virtual int pop() throw(IntStackEmptyException);
	virtual int count() const;
	virtual int size() const;
	virtual ~IntStack();
private:
	int * _data;
	int _size;
	int _count;
};

IntStack::IntStack(int size /* = DEFAULT_SIZE */) {
	_count = 0;
	_size = (size < MIN_SIZE) ? MIN_SIZE : size;
	_data = new int[_size];
}

void
IntStack::push(int value) throw(IntStackFullException) {
	if (_count == _size) {
		throw IntStackFullException();
	}
	_data[_count] = value;
	_count++;
}

int
IntStack::pop() throw(IntStackEmptyException) {
	if (0 == _count) {
		throw IntStackEmptyException();
	}
	_count--;
	return _data[_count];
}

int
IntStack::count() const {
	return _count;
}

int
IntStack::size() const {
	return _size;
}

IntStack::~IntStack() {
	delete[] _data;
}

int main(int argc, char* argv[])
{
	//Правило 1: Каждое число и знак должно быть разделено пробелами.
	//Правило 2: Если программа находит знак выч., то в стеке обязательно должно уже находиться два числа!
	RUS;

	IntStack number;
	string line;

	cout << "Пример ввода примера:  4 4 + 4 - " << endl;
	getline(cin, line);

	istringstream ss(line);

	while (!ss.eof()) {
		string str;
		ss >> str;
		if (str == "+") {
			if (number.count() >= 2){

				int x1 = number.pop();
				int x2 = number.pop();

				number.push(x2 + x1);
			}
			else cout << "Не хватает чисел для вычисления." << endl;
		}
		else if (str == "-") {
			if (number.count() >= 2){

				int x1 = number.pop();
				int x2 = number.pop();

				number.push(x2 - x1);
			}
			else cout << "Не хватает чисел для вычисления." << endl;
		}
		else if (str == "*") {
			if (number.count() >= 2){

				int x1 = number.pop();
				int x2 = number.pop();

				number.push(x2 * x1);
			}
			else cout << "Не хватает чисел для вычисления." << endl;
		}
		else if (str == "/") {
			if (number.count() >= 2){

				int x1 = number.pop();
				int x2 = number.pop();

				number.push(x2 / x1);
			}
			else cout << "Не хватает чисел для вычисления." << endl;
		}
		else {
			istringstream tmps(str);
			int d;
			tmps >> d;
			cout << "В стек добавлено новое число: " << d << endl;
			number.push(d);
		}
	}

	if (number.count() == 1)
		cout << "Результат: " << number.pop() << endl;
	else cout << "В стеке остались лишние числа, невозможно вывести результат." << endl;

	cin.get();
	return 0;
}

