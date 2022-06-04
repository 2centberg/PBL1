#pragma once
#include <exception>
class Invalid_Input :
    public std::exception
{
public:
    Invalid_Input() noexcept = default;
    ~Invalid_Input() = default;
    virtual const char *what() const noexcept override
    {
        return "Gia tri khong hop le!";
    }
};