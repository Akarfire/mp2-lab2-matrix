// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem;

public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if (sz <= 0 || sz > MAX_VECTOR_SIZE)
			throw out_of_range("TDynamicVector size should be greater than zero");
		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}

	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		assert(arr != nullptr && "TDynamicVector requires non-nullptr arg");
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}

	TDynamicVector(const TDynamicVector& v): sz(v.sz)
	{
		pMem = new T[sz];
		std::copy(v.pMem, v.pMem + sz, pMem);
	}

	TDynamicVector(TDynamicVector&& v) noexcept
	{
		sz = v.sz;
		pMem = v.pMem;

		v.pMem = nullptr;
	}

	~TDynamicVector()
	{
		delete[] pMem;
	}

	TDynamicVector& operator=(const TDynamicVector& v)
	{

		if (v.sz != sz)
		{
			sz = v.sz;

			delete[] pMem;
			pMem = new T[sz];
		}

		std::copy(v.pMem, v.pMem + sz, pMem);

		return *this;
	}

	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		std::swap(sz, v.sz);
		std::swap(pMem, v.pMem);

		return *this;
	}

	size_t size() const noexcept { return sz; }


	// индексация
	T& operator[](size_t ind)
	{
		return pMem[ind];
	}

	const T& operator[](size_t ind) const
	{
		return pMem[ind];
	}


	// индексация с контролем
	T& at(size_t ind)
	{
		if (ind >= sz || ind < 0)
			throw(out_of_range("TDynamicVector[i]: i out of range"));

		return pMem[ind];
	}

	const T& at(size_t ind) const
	{
		if (ind >= sz || ind < 0)
			throw(out_of_range("TDynamicVector[i]: i out of range"));

		return pMem[ind];
	}


	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz)
			return false;

		bool Eq = true;
		for (int i = 0; i < sz; i++)
			if (pMem[i] != v[i])
			{
				Eq = false;
				break;
			}

		return Eq;
	}

	bool operator!=(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz)
			return true;

		bool Eq = true;
		for (int i = 0; i < sz; i++)
			if (pMem[i] != v[i])
			{
				Eq = false;
				break;
			}

		return !Eq;
	}


	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector<T> Result(sz);

		for (int i = 0; i < sz; i++)
			Result[i] = pMem[i] + val;

		return Result;
	}

	TDynamicVector operator-(T val)
	{
		TDynamicVector Result(sz);

		for (int i = 0; i < sz; i++)
			Result[i] = pMem[i] - val;

		return Result;
	}

	TDynamicVector operator*(T val)
	{
		TDynamicVector Result(sz);

		for (int i = 0; i < sz; i++)
			Result[i] = pMem[i] * val;

		return Result;
	}


	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw(exception("TDynamicVector: cannot add two vectors of non-equal size"));

		TDynamicVector Result(sz);

		for (int i = 0; i < sz; i++)
			Result[i] = pMem[i] + v[i];

		return Result;
	}

	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw(exception("TDynamicVector: cannot subtract two vectors of non-equal size"));

		TDynamicVector Result(sz);

		for (int i = 0; i < sz; i++)
			Result[i] = pMem[i] - v[i];

		return Result;
	}

	T operator*(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw(exception("TDynamicVector: cannot multiply two vectors of non-equal size"));

		T Result = T();
		for (int i = 0; i < sz; i++)
			Result += pMem[i] * v[i];

		return Result;
	}

	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}


	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}

	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;

public:
	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (s <= 0 || s > MAX_MATRIX_SIZE)
			throw(exception("TDynamicMatrix: matrix size must be positive"));

		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}

	using TDynamicVector<TDynamicVector<T>>::operator[];
	using TDynamicVector<TDynamicVector<T>>::at;
	using TDynamicVector<TDynamicVector<T>>::size;


	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		return TDynamicVector<TDynamicVector<T>>::operator==(m);
	}

	bool operator!=(const TDynamicMatrix& m) const noexcept
	{
		return TDynamicVector<TDynamicVector<T>>::operator!=(m);
	}


	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val)
	{
		TDynamicMatrix Result(sz);

		for (int i = 0; i < sz; i++)
			Result[i] = pMem[i] * val;

		return Result;
	}


	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		if (sz != v.sz)
			throw(exception("TDynamicMatrix: cannot multiply by TDynamicVector of non-equal size"));

		TDynamicVector<T> Result(sz);

		for (int i = 0; i < sz; i++)
			Result[i] = pMem[i] * v;

		return Result;
	}


	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
			throw(exception("TDynamicMatrix: cannot add matricies of non-equal size"));

		TDynamicMatrix Result(sz);

		for (int i = 0; i < sz; i++)
			Result[i] = pMem[i] + m[i];

		return Result;
	}

	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
			throw(exception("TDynamicMatrix: cannot subtract matricies of non-equal size"));

		TDynamicMatrix Result(sz);

		for (int i = 0; i < sz; i++)
			Result[i] = pMem[i] - m[i];

		return Result;
	}

	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
			throw(exception("TDynamicMatrix: cannot multiply matricies of non-equal size"));

		TDynamicMatrix Result(sz);

		for (int k = 0; k < sz; k++)
		{
			for (int i = 0; i < sz; i++)
				for (int j = 0; j < sz; j++)
					Result[i][j] += pMem[i][k] * m[k][j];
		}

		return Result;
	}


	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& m)
	{
		for (int i = 0; i < sz; i++)
			istr >> m[i];

		return istr;
	}

	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
	{
		ostr << endl;
		for (int i = 0; i < m.sz; i++)
			ostr << m[i] << endl;

		ostr << endl;

		return ostr;
	}
};

#endif
