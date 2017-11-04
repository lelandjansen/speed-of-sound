#ifndef TEST_SPEED_OF_SOUND_TEST_H_
#define TEST_SPEED_OF_SOUND_TEST_H_

#include "gtest/gtest.h"
#include "speed-of-sound.h"

class EnvironmentTest : public ::testing::Test {
 public:
  speedofsound::Environment environment_;
};

class EnvironmentRateTest : public ::testing::Test {
 public:
  speedofsound::EnvironmentRate environment_rate_;
};

class SpeedOfSoundTest : public ::testing::Test {
 public:
  speedofsound::SpeedOfSound speed_of_sound_;
  const double kIncrementFactor = 2.0 / 100.0;
  const double kTMin = speedofsound::theory::kMinTemperature;
  const double kTMax = speedofsound::theory::kMaxTemperature;
  const double kHMin = speedofsound::theory::kMinHumidity;
  const double kHMax = speedofsound::theory::kMaxHumidity;
  const double kPMin = speedofsound::theory::kMinPressure;
  const double kPMax = speedofsound::theory::kMaxPressure;
  const double kXcMin = speedofsound::theory::kMinCO2MoleFraction;
  const double kXcMax = speedofsound::theory::kMaxCO2MoleFraction;
};

#endif  // TEST_SPEED_OF_SOUND_TEST_H_
