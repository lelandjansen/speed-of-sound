#include <chrono>
#include "gtest/gtest.h"
#include "speed-of-sound-theory.h"
#include "speed-of-sound.h"

auto main(int argc, char* argv[]) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
