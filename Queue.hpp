#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "Node.hpp"
#include "Out_Of_Memory.hpp"
template <typename T>
class Queue
{
public:
	Queue() noexcept ;
	~Queue() noexcept = default;
	void Push(const T &rhs);
	void Pop() noexcept;
	T Top();
	const int &Size() noexcept;
	void Display();
private:
	std::shared_ptr<Node<T>> Front;
	std::shared_ptr<Node<T>> Back;
	int Qsize;
};

template<typename T>
inline Queue<T>::Queue() noexcept  : Qsize{0}
{
}

template<typename T>
inline void Queue<T>::Push(const T &rhs)
{
	try
	{
		if (Front)
		{
			Back->Next = std::make_shared<Node<T>>(rhs);
			Back = Back->Next;
		}
		else
		{
			Front = Back = std::make_shared<Node<T>>(rhs);
		}
	}
	catch (...)
	{
		throw Out_Of_Memory();
	}
	++Qsize;
}

template<typename T>
inline void Queue<T>::Pop() noexcept
{
	if (Front)
	{
		Front = Front->Next;
	}
	--Qsize;
}

template<typename T>
inline T Queue<T>::Top()
{
	if (Front)
	{
		return Front->Value;
	}
	return T{0};
}

template<typename T>
inline const int &Queue<T>::Size() noexcept
{
	return Qsize;
}

template<typename T>
inline void Queue<T>::Display()
{
	std::shared_ptr<Node<T>> Ptr = Front;
	while (Ptr)
	{
		std::cout << Ptr->Value << std::endl;
		Ptr = Ptr->Next;
	}
}
