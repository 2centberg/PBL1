#pragma once
#include <exception>
class Invalid_Input :
    public std::exception
{
public:
    Invalid_Input() noexcept = default;
    ~Invalid_Input() = default;
    const char *what() const override
    {
        return "Invalid input";
    }
};

