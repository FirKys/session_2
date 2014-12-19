#include <iostream>
#include <vector>

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
	setlocale(LC_ALL, "Russian");

	try{

		IntStack number;
		int a, b;
		string line, temp;

		line = "1 2 3 4 + * +";		// ввод данных через код
		//getline(cin, line);	// ввод данных через консоль

		//парсим
		for (int i = 0; i < (int)line.size(); i++){

			//это пробел?
			if (isspace(line[i])){
				if (0 != temp.size()) {
					number.push(atoi(temp.c_str()));
					temp.clear();
				}
			}

			//Это число?
			else if (isdigit(line[i])) temp += line[i];

			else if (ispunct(line[i])){
				//symbl.push_back(line[i]);
				if (2 > number.count())
				{
					cout << "Ne xvataet 4isel." << endl;
				}
				else {

					switch (line[i]){
					case '+':
						a = number.pop();
						b = number.pop();
						cout << a << " + " << b << " = " << a + b << endl;
						number.push(a + b);
						break;
					case '-':
						a = number.pop();
						b = number.pop();
						cout << a << " - " << b << " = " << a - b << endl;
						number.push(a - b);
						break;
					case '*':
						a = number.pop();
						b = number.pop();
						cout << a << " * " << b << " = " << a*b << endl;
						number.push(b*a);
						break;
					case '/':
						a = number.pop();
						b = number.pop();
						if (a == 0) break;
						cout << a << " / " << b << " = " << a / b << endl;
						number.push(a / b);
						break;
					default:
						break;
					};
				}
				//cout << "Это ЗНАК:" << line[i] << endl; 
			}

			else { cout << "Ошибка: " << line[i] << endl; }


		}

		cout << "Результат: " << number.pop() << endl;



	}
	catch (...) { cout << "Поймана ошибка." << endl; }
	
	cin.get();
	return 0;
}

