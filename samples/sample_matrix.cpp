// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include <string>
#include "tmatrix.h"
//---------------------------------------------------------------------------

// Получает bool от пользователя
bool InputBool();

// Получает size_t от пользователя
size_t InputSize(size_t MaxSize);

// Получает int от пользователя
int InputInt(int Min, int Max);

// Получает double от пользователя
double InputDouble();

// Получает матрицу от пользователя
TDynamicMatrix<double> InputMatrix(size_t sz);

// Получает вектор от пользователя
TDynamicVector<double> InputVector(size_t sz);

// Отчищает cin после ввода
void ClearCin();

//---------------------------------------------------------------------------
/*
	Операции над матрицами:
		1. Умножение на число;
		2. Добавление числа;
		3. Вычитание числа;
		4. Умножение на вектор;
		5. Умножение на матрицу;
		6. Сложение матриц;
		7. Вычитание матриц;
*/
//---------------------------------------------------------------------------
int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Введите размер матриц/векторов: ";
	size_t Size = InputSize(MAX_MATRIX_SIZE);

	cout << "Матрица A: " << endl;
	TDynamicMatrix<double> A = InputMatrix(Size);

	cout << endl << "Выберете операцию над матрицей A:" << endl <<
		"1. Умножение на число;" << endl <<
		"2. Добавление числа;" << endl <<
		"3. Вычитание числа;" << endl <<
		"4. Умножение на вектор;" << endl <<
		"5. Умножение на матрицу;" << endl <<
		"6. Сложение матриц;" << endl <<
		"7. Вычитание матриц;" << endl <<
		"Ваш выбор: ";
	int Mode = InputInt(1, 7);

	switch (Mode)
	{
	case 1:
	{
		cout << endl << "Введите число c: ";
		double c = InputDouble();

		TDynamicMatrix<double> R = A * c;
		cout << endl << "Результат операции " << "A * c: " << endl << R;
		break;
	}

	case 2:
	{
		cout << endl << "Введите число c: ";
		double c = InputDouble();

		TDynamicMatrix<double> R = A + c;
		cout << endl << "Результат операции " << "A + c: " << endl << R;
		break;
	}

	case 3:
	{
		cout << endl << "Введите число c: ";
		double c = InputDouble();

		TDynamicMatrix<double> R = A - c;
		cout << endl << "Результат операции " << "A - c: " << endl << R;
		break;
	}

	case 4:
	{
		cout << endl << "Введите вектор v: ";
		TDynamicVector<double> v = InputVector(Size);

		TDynamicVector<double> R = A * v;
		cout << endl << "Результат операции " << "A * v: " << endl << R;
		break;
	}

	case 5:
	{
		cout << endl << "Введите матрицу B: ";
		TDynamicMatrix<double> B = InputMatrix(Size);

		TDynamicMatrix<double> R = A * B;
		cout << endl << "Результат операции " << "A * B: " << endl << R;
		break;
	}

	case 6:
	{
		cout << endl << "Введите матрицу B: ";
		TDynamicMatrix<double> B = InputMatrix(Size);

		TDynamicMatrix<double> R = A + B;
		cout << endl << "Результат операции " << "A + B: " << endl << R;
		break;
	}

	case 7:
	{
		cout << endl << "Введите матрицу B: ";
		TDynamicMatrix<double> B = InputMatrix(Size);

		TDynamicMatrix<double> R = A - B;
		cout << endl << "Результат операции " << "A - B: " << endl << R;
		break;
	}

	default: break;
	}

	system("pause");
	return 0;
}
//---------------------------------------------------------------------------

bool InputBool()
{
	bool Failed = false;
	while (true)
	{
		if (Failed)
			cout << endl << "Недоступная опция, попробуйте снова:";

		string Inp;
		cin >> Inp;
		ClearCin();

		if (Inp == "Y")
			return true;

		else if (Inp == "N")
			return false;

		Failed = true;
	}
}

size_t InputSize(size_t MaxSize)
{
	bool Failed = false;
	while (true)
	{
		if (Failed)
			cout << endl << "Недоступное значение, попробуйте снова:";

		string Inp;
		cin >> Inp;
		ClearCin();

		int Value = 0;

		Failed = false;
		try
		{
			Value = stoi(Inp);
		}

		catch (std::invalid_argument exception)
		{
			Failed = true;
		}

		catch (std::out_of_range exception)
		{
			Failed = true;
		}

		if (!Failed && Value > 0 && Value <= MaxSize)
			return Value;

		Failed = true;
	}
}

int InputInt(int Min, int Max)
{
	bool Failed = false;
	while (true)
	{
		if (Failed)
			cout << endl << "Недоступное значение, попробуйте снова:";

		string Inp;
		cin >> Inp;
		ClearCin();

		int Value = 0;

		Failed = false;
		try
		{
			Value = stoi(Inp);
		}

		catch (std::invalid_argument exception)
		{
			Failed = true;
		}

		catch (std::out_of_range exception)
		{
			Failed = true;
		}

		if (!Failed && Value >= Min && Value <= Max)
			return Value;

		Failed = true;
	}
}

double InputDouble()
{
	bool Failed = false;
	while (true)
	{
		if (Failed)
			cout << endl << "Недоступное значение, попробуйте снова:";

		string Inp;
		cin >> Inp;
		ClearCin();

		double Value = 0;

		Failed == false;
		try
		{
			Value = stod(Inp);
		}

		catch (std::invalid_argument exception)
		{
			Failed = true;
		}

		catch (std::out_of_range exception)
		{
			Failed = true;
		}

		if (!Failed)
			return Value;

		Failed = true;
	}
}

TDynamicVector<double> InputVector(size_t sz)
{
	TDynamicVector<double> Vector(sz);

	bool InputConfirmed = false;
	do
	{
		cout << endl << "Введите элементы вектора размера " << sz << " в одну строку : " << endl;

		cin >> Vector;
		ClearCin();

		cout << endl << "Подтвердите корректность вектора:" << endl;
		cout << Vector;

		cout << endl << "Введите Y (верно) или N (неверно): ";

		InputConfirmed = InputBool();

	} while (!InputConfirmed);

	return Vector;
}

TDynamicMatrix<double> InputMatrix(size_t sz)
{
	TDynamicMatrix<double> Matrix(sz);

	bool InputConfirmed = false;
	do
	{
		cout << endl << "Введите элементы матрицы " << sz << "x" << sz << " в одну строку (в порядке строк):" << endl;

		cin >> Matrix;
		ClearCin();

		cout << endl << "Подтвердите корректность матрицы:" << endl;
		cout << Matrix;

		cout << "Введите Y (верно) или N (неверно): ";

		InputConfirmed = InputBool();

	} while (!InputConfirmed);

	return Matrix;
}

void ClearCin()
{
	if (cin.fail())
		cin.clear();

	cin.ignore(INT_MAX, '\n');
}