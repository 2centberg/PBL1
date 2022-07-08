#pragma once
#include <memory>
template<typename T>
class Node
{
public:
	Node() noexcept = default;
	Node(const T &Value) noexcept;
	Node(const T &&Value) noexcept;
	~Node() noexcept = default;

public:
	std::shared_ptr<Node> Next;
	T Value;
};
template<typename T>
inline Node<T>::Node(const T &Value) noexcept  : Value{Value}
{
}

template<typename T>
inline Node<T>::Node(const T &&Value) noexcept  : Value{Value}
{
}