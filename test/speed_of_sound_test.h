// speed_of_sound_test.h
#include "test.h"

#ifndef TEST_SPEED_OF_SOUND_TEST_H_
#define TEST_SPEED_OF_SOUND_TEST_H_

class EnvironmentTest : public ::testing::Test {
 public:
  speedofsound::Environment environment;
};

class EnvironmentRateTest : public ::testing::Test {
 public:
  speedofsound::EnvironmentRate environment_rate;
};

class SpeedOfSoundTest : public ::testing::Test {
 public:
  speedofsound::SpeedOfSound speed_of_sound;

  static constexpr double kIncrementFactor = 2.0 / 100.0;
  static constexpr double kTMin = speedofsound::theory::kMinTemperature;
  static constexpr double kTMax = speedofsound::theory::kMaxTemperature;
  static constexpr double kHMin = speedofsound::theory::kMinHumidity;
  static constexpr double kHMax = speedofsound::theory::kMaxHumidity;
  static constexpr double kPMin = speedofsound::theory::kMinPressure;
  static constexpr double kPMax = speedofsound::theory::kMaxPressure;
  static constexpr double kXcMin = speedofsound::theory::kMinCO2MoleFraction;
  static constexpr double kXcMax = speedofsound::theory::kMaxCO2MoleFraction;
};

#endif
