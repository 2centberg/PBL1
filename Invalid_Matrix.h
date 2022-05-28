#pragma once
#include <exception>
class Invalid_Matrix :
    public std::exception
{
public:
    Invalid_Matrix() noexcept = default;
    ~Invalid_Matrix() = default;
    const char *what() const override
    {
        return "Ma tran khong hop le";
    }
};