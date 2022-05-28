#pragma once
#include "Node.h"
template <typename T>
class Stack
{
protected:
	int Size;
	std::shared_ptr<Node<T>> Front;
public:
	Stack() noexcept;
	~Stack() = default;
	void push(const T &element) noexcept;
	const int &front();
	const int &size();
	void pop();
};

template<typename T>
inline Stack<T>::Stack() noexcept : Size{0}
{
}

template<typename T>
inline void Stack<T>::push(const T &element) noexcept
{
	std::shared_ptr<Node<T>> ptr = std::make_shared<Node<T>>(element);
	if (Size != 0)
	{
		ptr->Right_Node = Front;
		Front = ptr;
	}
	else
	{
		Front = ptr;
	}
	++Size;
}

template<typename T>
inline const int &Stack<T>::front()
{
	return Front->Value;
}

template<typename T>
inline const int &Stack<T>::size()
{
	return Size;
}

template<typename T>
inline void Stack<T>::pop()
{
	if (Front)
	{
		Front = Front->Right_Node;
	}
	--Size;
}
