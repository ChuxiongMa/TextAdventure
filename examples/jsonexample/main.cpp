#include <iostream>

#include <json/json.hpp>

using json = nlohmann::json;

int main() {
  json foo = {
    {"something", 3.1415926}
  };
  std::cout << foo.dump() << std::endl;
  return 0;
}
