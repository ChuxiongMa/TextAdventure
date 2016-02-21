#include <vector>
#include <functional>

#include <uv.h>
#include <uvpp/Loop.hpp>

namespace textadventure {
  namespace bcrypt {
    void generateSalt(
      int workfactor,
      std::function<void (std::string)>
    );
    void generateSalt(
      uvpp::Loop& loop,
      int workfactor,
      std::function<void (std::string)>
    );
    void performHash(
      std::string plaintext,
      std::string salt,
      std::function<void (std::string)>
    );
    void performHash(
      uvpp::Loop& loop,
      std::string plaintext,
      std::string salt,
      std::function<void (std::string)>
    );
    void performSaltAndHash(
      int workfactor,
      std::string plaintext,
      std::function<void (std::string)>
    );
    void performSaltAndHash(
      uvpp::Loop& loop,
      int workfactor,
      std::string plaintext,
      std::function<void (std::string)>
    );
    void verify(
      std::string plaintext,
      std::string hash,
      std::function<void (bool)>
    );
    void verify(
      uvpp::Loop& loop,
      std::string plaintext,
      std::string hash,
      std::function<void (bool)>
    );
  }
}
