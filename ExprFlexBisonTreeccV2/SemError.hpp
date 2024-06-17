#ifndef __SEM_ERROR_HPP__
#define __SEM_ERROR_HPP__

#include <string>

class SemError
{
public:
    SemError(const std::string& _msg)
      : msg (_msg)
    {}

    std::string message() const
    { return msg; }

private:
    std::string msg;
};

#endif
