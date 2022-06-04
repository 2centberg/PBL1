#pragma once
#include "exception"
class Too_Large_Matrix :
    public std::exception
{
public:
    Too_Large_Matrix() noexcept = default;
    ~Too_Large_Matrix() = default;
    virtual const char *what() const override
    {
        return "Ma tran qua lon!";
    }
};

