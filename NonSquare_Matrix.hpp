#pragma once
#include <exception>
class NonSquare_Matrix : std::exception
{
public:
	NonSquare_Matrix() noexcept = default;
	~NonSquare_Matrix() = default;
	virtual const char *what() const noexcept override
	{
		return "Ma tran khong vuong!";
	}
};