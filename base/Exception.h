#pragma once

#include <exception>
#include <string>

namespace cppl
{
    class Exception : public std::exception
    {
    public:
        explicit Exception(const std::string &what);
        ~Exception() noexcept override = default;

        const char *what() const noexcept override
        {
            return message_.c_str();
        }

        const char *stackTrace() const noexcept
        {
            return stack_.c_str();
        }

    private:
        std::string message_;
        std::string stack_;
    };
}