#include "test_Raffinamento.hpp"
#include "test_Segment.hpp"
#include "test_Triangle.hpp"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
