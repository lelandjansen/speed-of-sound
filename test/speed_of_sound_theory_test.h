// speed_of_sound_theory_test.h
#include <tuple>
#include <vector>
#include "test.h"

#ifndef TEST_SPEED_OF_SOUND_THEORY_TEST_H_
#define TEST_SPEED_OF_SOUND_THEORY_TEST_H_

class SpeedOfSoundTheoryTest : public ::testing::Test {
 public:
  SpeedOfSoundTheoryTest();

  speedofsound::Environment min_case, min_xw_case, std_case, max_case,
      max_xw_case;

  std::vector<std::pair<double, speedofsound::Environment> > test_cases;
  static constexpr double kTolerance = 1.0e-14;
};

#endif
