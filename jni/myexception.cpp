#include <exception>
#include <string>
#include <iostream>
#include "myexception.h"
class MyNativeException : public std::exception
{
    public:
         explicit MyNativeException(const char *msg) : message(msg) {}
         virtual ~MyNativeException() throw() {}
         virtual const char *what() const throw() { return message.c_str(); }
    protected:
         const std::string message;
};

int throw_my_exception()
{
   throw MyNativeException("FFmpeg native exception");
}
