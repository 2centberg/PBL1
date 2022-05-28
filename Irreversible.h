#pragma once
#include <exception>
class Irreversible :
    public std::exception
{
public:
    Irreversible() noexcept = default;
    ~Irreversible() = default;
    const char *what() const override
    {
        return "Ma tran khong kha nghich";
    }
};