#include <helpers/helperFunctions.hpp>

namespace helpers {
  std::vector<unsigned char> stringToCharVector(const std::string& str) {
    std::vector<unsigned char> output(str.size());
    std::copy(str.begin(), str.end(), output.begin());
    return output;
  }
}
