#pragma once
#include <exception>
class Invalid_Matrix :
    public std::exception
{
public:
    Invalid_Matrix() noexcept = default;
    ~Invalid_Matrix() = default;
    virtual const char *what() const noexcept override
    {
        return "Ma tran khong hop le!";
    }
};