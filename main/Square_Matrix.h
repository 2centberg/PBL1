#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "PBL.h"
#include "Irreversible.h"
#include "Square_Matrix.h"
#include "Out_Of_Memory.h"
#include "Invalid_Input.h"
#include "Invalid_Matrix.h"
#include "NonSquare_Matrix.h"
#include "Too_Large_Matrix.h"
template <typename T>
class Square_Matrix
{
	static constexpr bool &&Unit = 0;
protected:
	int Size;
	bool Reversible;
	T **Container;
public:
	Square_Matrix();
	Square_Matrix(const int &Size, const bool &flag = Unit);
	~Square_Matrix() noexcept;
	int &size() noexcept;
	void Init();
	void Display() noexcept;
	void Swap_Row(const int &Row_Index);
	void Reverse();
	Square_Matrix<T> &operator=(Square_Matrix<T> &&rhs) noexcept;
};

template<typename T>
inline Square_Matrix<T>::Square_Matrix() : Size{0}, Reversible{0}, Container{0} {}

template<typename T>
inline Square_Matrix<T>::Square_Matrix(const int &Size, const bool &flag) : Size{Size}, Reversible{0}
{
	if (Size > 1000)
	{
		throw Too_Large_Matrix();
	}
	try
	{
		Container = new T * [Size];
		if (flag)
		{
			for (int i{0}; i < Size; ++i)
			{
				Container[i] = new T[Size];
				{
					for (int j{0}; j < Size; ++j)
					{
						Container[i][j] = 0;
					}
					Container[i][i] = 1;
				}
			}
		}
		else
		{
			for (int i{0}; i < Size; ++i)
			{
				Container[i] = new T[Size];
			}
		}
	}
	catch (...)
	{
		throw Out_Of_Memory();
	}
}

template<typename T>
inline Square_Matrix<T>::~Square_Matrix() noexcept
{
	if (Container)
	{
		for (int &&i{0}; i < Size; ++i)
		{
			delete[] Container[i];
		}
		delete[] Container;
		Container = 0;
	}
	Size = 0;
}

template<typename T>
inline int &Square_Matrix<T>::size() noexcept
{
	return Size;
}

template<typename T>
void Square_Matrix<T>::Init()
{
	this->~Square_Matrix();
	if (PBL::Input_Selection == 1)
	{
		std::fstream INPUT_STREAM;
		INPUT_STREAM.open(PBL::Input_Path, std::ios::in);
		std::string element;
		while (std::getline(INPUT_STREAM, element))
		{
			if (element.length() == 0)
			{
				continue;
			}
			std::stringstream sstream;
			sstream.str(element);
			while (sstream >> element)
			{
				++Size;
			}
			INPUT_STREAM.close();
		}
		if (Size == 0)
		{
			throw Invalid_Matrix();
		}
		INPUT_STREAM.open(PBL::Input_Path, std::ios::in);
		int &&i{0}, &&j{0};
		this->operator=(Square_Matrix(Size));
		while (std::getline(INPUT_STREAM, element))
		{
			if (element.length() == 0)
			{
				continue;
			}
			if (i == Size)
			{
				throw NonSquare_Matrix();
			}
			std::stringstream sstream;
			sstream.str(element);
			while (sstream >> element)
			{
				try
				{
					Container[i][j] = stod(element);
					++j;
				}
				catch (...)
				{
					throw Invalid_Matrix();
				}
			}
			if (j != Size)
			{
				throw NonSquare_Matrix();
			}
			++i;
			j = 0;
		}
		if (i != Size)
		{
			throw NonSquare_Matrix();
		}
		INPUT_STREAM.close();
	}
	else
	{
		this->operator=(Square_Matrix(PBL::Matrix_Size));
		std::fstream RAND_STREAM;
		RAND_STREAM.open(PBL::Rand_Path, std::ios::out);
		RAND_STREAM.clear();
		for (int &&i{0}; i < Size; ++i)
		{
			for (int &&j{0}; j < Size; ++j)
			{
				Container[i][j] = Rand_Int();
				RAND_STREAM << Container[i][j] << ' ';
			}
			RAND_STREAM << '\n';
		}
		RAND_STREAM.close();
	}
}


template<typename T>
inline void Square_Matrix<T>::Display() noexcept
{
	if (PBL::Output_Selection == 1)
	{
		std::fstream OUTPUT_STREAM;
		OUTPUT_STREAM.open(PBL::Output_Path, std::ios::out);
		for (int &&i{0}; i < Size; ++i)
		{
			for (int &&j{0}; j < Size; ++j)
			{
				OUTPUT_STREAM << std::setprecision(9) << std::fixed << std::setw(12) << Container[i][j];
				if (j != Size - 1)
				{
					OUTPUT_STREAM << ' ';
				}
			}
			if (i != Size - 1)
			{
				OUTPUT_STREAM << std::endl;
			}
		}
		OUTPUT_STREAM.close();
	}
	else
	{
		for (int &&i{0}; i < Size; ++i)
		{
			
			for (int &&j{0}; j < Size; ++j)
			{
				std::cout << std::setprecision(3) << std::fixed << std::setw(9) << Container[i][j];
			}
			if (i != Size - 1)
			{
				std::cout << std::endl;
			}
		}
	}
}
template<typename T>
inline void Square_Matrix<T>::Swap_Row(const int &Row_Index)
{
	for (int i{Row_Index + 1}; i < Size; ++i)
	{
		if (Container[i][Row_Index] != 0)
		{
			std::swap(Container[i], Container[Row_Index]);
			return;
		}
	}
	throw Irreversible();
}

template<typename T>
inline void Square_Matrix<T>::Reverse()
{
	T Anchor_Point{0};
	Square_Matrix<T> Unit_Matrix(Size, 1);
	for (int Row_Index{0}; Row_Index < Size; ++Row_Index)
	{
		Anchor_Point = Container[Row_Index][Row_Index];
		if (Anchor_Point == 0)
		{
			this->Swap_Row(Row_Index);
			Anchor_Point = Container[Row_Index][Row_Index];
		}
		for (int Col_index{0}; Col_index < Size; ++Col_index)
		{
			Container[Row_Index][Col_index] /= Anchor_Point;
			Unit_Matrix.Container[Row_Index][Col_index] /= Anchor_Point;
		}

		for (int &&Another_Row{0}; Another_Row < Size; Another_Row++)
		{
			if (Another_Row != Row_Index)
			{
				Anchor_Point = -Container[Another_Row][Row_Index];
				for (int &&Col_index{0}; Col_index < Size; ++Col_index)
				{
					Container[Another_Row][Col_index] += Anchor_Point * Container[Row_Index][Col_index];
					Unit_Matrix.Container[Another_Row][Col_index] += Anchor_Point * Unit_Matrix.Container[Row_Index][Col_index];
				}
			}
		}
	}
	this->~Square_Matrix();
	this->Container = Unit_Matrix.Container;
	this->Size = Unit_Matrix.Size;
	Unit_Matrix.Container = 0;
	Unit_Matrix.Size = 0;
}

template<typename T>
inline Square_Matrix<T> &Square_Matrix<T>::operator=(Square_Matrix<T> &&rhs) noexcept
{
	this->Container = rhs.Container;
	this->Size = rhs.Size;
	rhs.Container = 0;
	rhs.Size = 0;
	return *this;
}