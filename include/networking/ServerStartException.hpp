#ifndef SERVER_START_EXCEPTION_H
#define SERVER_START_EXCEPTION_H

#include <exception>
#include <string>

using exception = std::exception;
using string = std::string;

namespace networking {
  class ServerStartException : public exception {
    string reason;
  public:
    ServerStartException();
    ServerStartException(string);
    virtual const char* what() const throw();
  };
}

#endif
