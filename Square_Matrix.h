#pragma once
#include <fstream>
#include <iostream>
#include "Head.h"
#include "Stack.h"
#include "Irreversible.h"
#include "PBL.h"
template <typename T>
class Square_Matrix
{
protected: 
	int Size;
	bool Reversible;
	std::shared_ptr<Head<T>> First_Head;
public:
	Square_Matrix() noexcept;
	Square_Matrix(const int &Size) noexcept;
	~Square_Matrix() noexcept = default;
	void Init();
	void Display();
	void Reverse();
	std::shared_ptr<Head<T>> &At(int Index);
};

template<typename T>
inline Square_Matrix<T>::Square_Matrix() noexcept : Size{0}, Reversible{false}
{
}

template<typename T>
inline Square_Matrix<T>::Square_Matrix(const int &Size) noexcept : Size{Size}, Reversible{false}
{
	for (int i = 1; i <= Size; i++)
	{
		this->At(i) = std::make_shared<Head<T>>(Size);
		this->At(i)->At(i)->Value = 1; // Identity Matrix
	}
}

template<typename T>
inline void Square_Matrix<T>::Init()
{
	std::fstream INPUT_STREAM;
	//std::cout << "input selection : " << Get_Input_Selection();
	//if (Get_Input_Selection() == 1)
	//{
	//	INPUT_STREAM.open(Get_Input_Path(), std::ios::in);
	//	
	//}
	//else
	//{
	//	INPUT_STREAM.open(Get_Rand_Path(), std::ios::in);
	//}
	INPUT_STREAM.close();
}

template<typename T>
inline void Square_Matrix<T>::Display()
{
	//std::cout << "output selection : " << Get_Output_Selection();
	if (1)//Get_Output_Selection() == 1)
	{
		//std::fstream OUTPUT_STREAM;
		//OUTPUT_STREAM.open(Get_Output_Path(), std::ios::out);
		//OUTPUT_STREAM.close();
	}
	else
	{
		for (int i = 1; i <= Size; ++i)
		{
			for (int j = 1; j <= Size; ++j)
			{
				std::cout << this->At(i)->At(j)->Value << ' ';
			}
			std::cout << std::endl;
		}
	}
}

template<typename T>
inline void Square_Matrix<T>::Reverse()
{
	//throw Irreversible();
}
//done
template<typename T>
inline std::shared_ptr<Head<T>> &Square_Matrix<T>::At(int Index)
{
	if (Index == 1)
	{
		return First_Head;
	}
	Stack<int> S;
	while (Index != 1)
	{
		S.push(Index);
		Index >>= 1;
	}
	std::shared_ptr<Head<T>> ptr{First_Head};
	while (S.size() != 1)
	{
		if (S.front() & 1)
		{
			ptr = ptr->Right_Head;
		}
		else
		{
			ptr = ptr->Left_Head;
		}
		S.pop();
	}
	if (S.front() & 1)
	{
		return ptr->Right_Head;
	}
	else
	{
		return ptr->Left_Head;
	}
}