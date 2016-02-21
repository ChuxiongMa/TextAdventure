#include <string>

#include <networking/ServerStartException.hpp>

using string = std::string;

networking::ServerStartException::ServerStartException() {}

networking::ServerStartException::ServerStartException(string reason) {
  this->reason = reason;
}

const char* networking::ServerStartException::what() const throw() {
  return "Error starting server";
}
