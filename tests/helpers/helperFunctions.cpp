#include <vector>

#include <gtest/gtest.h>
#include <helpers/helperFunctions.hpp>

TEST(StringToCharVectorTest, ShouldConvertAStringToCharVector) {
  std::string toTest = "Hello, World!";

  // "Hello, World!" in ASCII hexadecimal
  std::vector<unsigned char> expected({
    0x48,
    0x65,
    0x6c,
    0x6c,
    0x6f,
    0x2c,
    0x20,
    0x57,
    0x6f,
    0x72,
    0x6c,
    0x64,
    0x21
  });

  auto underTest = helpers::stringToCharVector(toTest);

  EXPECT_TRUE(
    std::equal(expected.begin(), expected.end(), underTest.begin())
  );
}
