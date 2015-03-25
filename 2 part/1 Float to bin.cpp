//http://www.binaryconvert.com/result_float.html?decimal=050051046048053
#include <iostream>

using namespace std;

//Вариант 2
union FloatStruct
{
	float value;
	struct
	{
		unsigned  mantissa : 23;
		unsigned  exp : 8;
		unsigned  sign : 1;
	};
};

//Вариант 1
union MyFloat
{
	float asFloat;
	int asInteger;
};

/*
int number  - Число которое "уйдет" в формат bin
bool reves  - Перевенуть значение
*/
string DecToBin2(int number, bool reves = false)
{
	string result = "";

	do
	{
		if ((number & 1) == 0)
			result += "0";
		else
			result += "1";

		number >>= 1;
	} while (number);

	if (reves) reverse(result.begin(), result.end());
	return result;
}

int main(){
	setlocale(LC_ALL, "Russian");

	cout << "Размер Float: " << sizeof(float) << endl; // 4 байта или 32 бита (8 байт = 1 бит)
							// 1 бит - под знак | 8 бит - целая часть | 23 бит - дробная часть 
	MyFloat testFloat;
	testFloat.asFloat = 23.05f;

	int znak = testFloat.asInteger >> 31;
	int poryadok = (testFloat.asInteger >> 23) & 0xFF;
	int mantissa = testFloat.asInteger & 0x7FFFFF;
	
	string poryadokT = DecToBin2(poryadok, true);
	string mantissaT = DecToBin2(mantissa);

	cout << "Знак: " << znak << endl;
	cout << "Порядок: " << poryadok << "\t\tПорядок BIN: " << poryadokT.c_str() << endl;
	cout << "Мантисса: " << mantissa << "\tМантисса BIN: " << mantissaT.c_str() << endl;


	return 0;
}