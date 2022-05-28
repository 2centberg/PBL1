#pragma once
#include "Stack.h"
template<typename T>
class Head
{
public:
	int Head_Size;
	std::shared_ptr<Node<T>> First_Node;
	std::shared_ptr<Head> Left_Head;
	std::shared_ptr<Head> Right_Head;
public:
	Head() noexcept = default;
	Head(const int &Head_Size) noexcept;
	~Head() noexcept = default;
	std::shared_ptr<Node<T>> &At(int Index);
};

template<typename T>
inline Head<T>::Head(const int &Head_Size) noexcept : Head_Size{Head_Size}
{
	for (int i = 1; i <= Head_Size; ++i)
	{
		this->At(i) = std::make_shared<Node<T>>();
	}
}

template<typename T>
inline std::shared_ptr<Node<T>> &Head<T>::At(int Index)
{
	if (Index == 1)
	{
		return First_Node;
	}
	Stack<int> S;
	while (Index != 1)
	{
		S.push(Index);
		Index >>= 1;
	}
	std::shared_ptr<Node<T>> ptr{First_Node};
	while (S.size() != 1)
	{
		if (S.front() & 1)
		{
			ptr = ptr->Right_Node;
		}
		else
		{
			ptr = ptr->Left_Node;
		}
		S.pop();
	}
	if (S.front() & 1)
	{
		return ptr->Right_Node;
	}
	else
	{
		return ptr->Left_Node;
	}
}
