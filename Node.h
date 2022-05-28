#pragma once
#include <memory>
template<typename T>
class Node
{
public:
	T Value;
	std::shared_ptr<Node<T>> Left_Node;
	std::shared_ptr<Node<T>> Right_Node;
public:
	Node() noexcept;
	Node(const T &Value) noexcept;
	~Node() = default;
};

template<typename T>
inline Node<T>::Node() noexcept : Value{T()}
{
}

template<typename T>
inline Node<T>::Node(const T &Value) noexcept : Value{T(Value)}
{
};
