#pragma once
#include <exception>
class Irreversible :
    public std::exception
{
public:
    Irreversible() noexcept = default;
    ~Irreversible() = default;
    virtual const char *what() const noexcept override
    {
        return "Ma tran khong kha nghich!";
    }
};