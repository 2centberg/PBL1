#pragma once
#include <exception>
class Out_Of_Memory 
	: public std::exception
{
public:
	Out_Of_Memory() noexcept = default;
	~Out_Of_Memory() = default;
	virtual const char *what() const noexcept override
	{
		return "Khong du bo nho cap phat!";
	}
};