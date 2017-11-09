#include "speed-of-sound_test.h"

#include <chrono>

#include "environment.h"

TEST_F(EnvironmentTest, EnvironmentConstructorDefaultValue) {
  EXPECT_DOUBLE_EQ(environment_.temperature_,
                   speedofsound::theory::kStdTemperature);
  EXPECT_DOUBLE_EQ(environment_.humidity_, speedofsound::theory::kStdHumidity);
  EXPECT_DOUBLE_EQ(environment_.pressure_, speedofsound::theory::kStdPressure);
  EXPECT_DOUBLE_EQ(environment_.co2_mole_fraction_,
                   speedofsound::theory::kStdCO2MoleFraction);
}

TEST_F(EnvironmentTest, EnvironmentValidateTemperature) {
  EXPECT_TRUE(environment_.ValidateTemperature());
  environment_.temperature_ = speedofsound::theory::kMinTemperature - 1.0;
  EXPECT_FALSE(environment_.ValidateTemperature());
  ++environment_.temperature_;
  EXPECT_TRUE(environment_.ValidateTemperature());
  ++environment_.temperature_;
  EXPECT_TRUE(environment_.ValidateTemperature());

  environment_.temperature_ = speedofsound::theory::kMaxTemperature - 1.0;
  EXPECT_TRUE(environment_.ValidateTemperature());
  ++environment_.temperature_;
  EXPECT_TRUE(environment_.ValidateTemperature());
  ++environment_.temperature_;
  EXPECT_FALSE(environment_.ValidateTemperature());
}

TEST_F(EnvironmentTest, EnvironmentValidateHumidity) {
  const auto increment = 0.1;
  EXPECT_TRUE(environment_.ValidateHumidity());
  environment_.humidity_ = speedofsound::theory::kMinHumidity - increment;
  EXPECT_FALSE(environment_.ValidateHumidity());
  environment_.humidity_ += increment;
  EXPECT_TRUE(environment_.ValidateHumidity());
  environment_.humidity_ += increment;
  EXPECT_TRUE(environment_.ValidateHumidity());

  environment_.humidity_ = speedofsound::theory::kMaxHumidity - increment;
  EXPECT_TRUE(environment_.ValidateHumidity());
  environment_.humidity_ += increment;
  EXPECT_TRUE(environment_.ValidateHumidity());
  environment_.humidity_ += increment;
  EXPECT_FALSE(environment_.ValidateHumidity());
}

TEST_F(EnvironmentTest, EnvironmentValidatePressure) {
  EXPECT_TRUE(environment_.ValidatePressure());
  environment_.pressure_ = speedofsound::theory::kMinPressure - 1.0;
  EXPECT_FALSE(environment_.ValidatePressure());
  ++environment_.pressure_;
  EXPECT_TRUE(environment_.ValidatePressure());
  ++environment_.pressure_;
  EXPECT_TRUE(environment_.ValidatePressure());

  environment_.pressure_ = speedofsound::theory::kMaxPressure - 1.0;
  EXPECT_TRUE(environment_.ValidatePressure());
  ++environment_.pressure_;
  EXPECT_TRUE(environment_.ValidatePressure());
  ++environment_.pressure_;
  EXPECT_FALSE(environment_.ValidatePressure());
}

TEST_F(EnvironmentTest, EnvironmentValidateCO2MoleFraction) {
  const auto increment = 1e-3;
  EXPECT_TRUE(environment_.ValidateCO2MoleFraction());
  environment_.co2_mole_fraction_ =
      speedofsound::theory::kMinCO2MoleFraction - increment;
  EXPECT_FALSE(environment_.ValidateCO2MoleFraction());
  environment_.co2_mole_fraction_ = speedofsound::theory::kMinCO2MoleFraction;
  EXPECT_TRUE(environment_.ValidateCO2MoleFraction());
  environment_.co2_mole_fraction_ += increment;
  EXPECT_TRUE(environment_.ValidateCO2MoleFraction());

  environment_.co2_mole_fraction_ =
      speedofsound::theory::kMaxCO2MoleFraction - increment;
  EXPECT_TRUE(environment_.ValidateCO2MoleFraction());
  environment_.co2_mole_fraction_ = speedofsound::theory::kMaxCO2MoleFraction;
  EXPECT_TRUE(environment_.ValidateCO2MoleFraction());
  environment_.co2_mole_fraction_ += increment;
  EXPECT_FALSE(environment_.ValidateCO2MoleFraction());
}

TEST_F(EnvironmentTest, EnvironmentValidateEnvironment) {
  EXPECT_TRUE(environment_.ValidateEnvironment());
  environment_.temperature_ = speedofsound::theory::kMinTemperature - 1.0;
  EXPECT_FALSE(environment_.ValidateEnvironment());
  environment_.pressure_ = speedofsound::theory::kMaxPressure + 1.0;
  environment_.humidity_ = speedofsound::theory::kMinTemperature - 0.1;
  EXPECT_FALSE(environment_.ValidateEnvironment());
  environment_.temperature_ += 10.0;
  EXPECT_FALSE(environment_.ValidateEnvironment());
  environment_.humidity_ = speedofsound::theory::kStdHumidity;
  EXPECT_FALSE(environment_.ValidateEnvironment());
  environment_.pressure_ -= 100.0;
  EXPECT_TRUE(environment_.ValidateEnvironment());
}

TEST_F(EnvironmentRateTest, EnvironmentRateConstructorDefaultValue) {
  EXPECT_DOUBLE_EQ(environment_rate_.temperature_rate_, 0.0);
  EXPECT_DOUBLE_EQ(environment_rate_.humidity_rate_, 0.0);
  EXPECT_DOUBLE_EQ(environment_rate_.pressure_rate_, 0.0);
  EXPECT_DOUBLE_EQ(environment_rate_.co2_mole_fraction_rate_, 0.0);
}

TEST_F(SpeedOfSoundTest, EnvironmentConstructorDefaultValues) {
  EXPECT_DOUBLE_EQ(speed_of_sound_.GetInitEnvironment().temperature_,
                   speedofsound::theory::kStdTemperature);
  EXPECT_DOUBLE_EQ(speed_of_sound_.GetInitEnvironment().humidity_,
                   speedofsound::theory::kStdHumidity);
  EXPECT_DOUBLE_EQ(speed_of_sound_.GetInitEnvironment().pressure_,
                   speedofsound::theory::kStdPressure);
  EXPECT_DOUBLE_EQ(speed_of_sound_.GetInitEnvironment().co2_mole_fraction_,
                   speedofsound::theory::kStdCO2MoleFraction);
}

TEST_F(SpeedOfSoundTest, EnvironmentOverloadConstructorValues) {
  speedofsound::Environment environment_;
  environment_.temperature_ = speedofsound::theory::kMinTemperature;
  environment_.humidity_ = speedofsound::theory::kMinHumidity;
  environment_.pressure_ = speedofsound::theory::kMinPressure;
  environment_.co2_mole_fraction_ = speedofsound::theory::kMinCO2MoleFraction;
  speedofsound::SpeedOfSound speed_of_sound(environment_);

  EXPECT_DOUBLE_EQ(speed_of_sound.GetInitEnvironment().temperature_,
                   speedofsound::theory::kMinTemperature);
  EXPECT_DOUBLE_EQ(speed_of_sound.GetInitEnvironment().humidity_,
                   speedofsound::theory::kMinHumidity);
  EXPECT_DOUBLE_EQ(speed_of_sound.GetInitEnvironment().pressure_,
                   speedofsound::theory::kMinPressure);
  EXPECT_DOUBLE_EQ(speed_of_sound.GetInitEnvironment().co2_mole_fraction_,
                   speedofsound::theory::kMinCO2MoleFraction);
}

TEST_F(SpeedOfSoundTest, EnvironmentRateConstructorDefaultValues) {
  const auto t = speedofsound::theory::kStdTemperature;
  const auto h = speedofsound::theory::kStdHumidity;
  const auto p = speedofsound::theory::kStdPressure;
  const auto xc = speedofsound::theory::kStdCO2MoleFraction;
  const auto T = speedofsound::theory::T(t);
  const auto F = speedofsound::theory::F(p, t);
  const auto Psv = speedofsound::theory::Psv(T);
  const auto Xw = speedofsound::theory::Xw(h, F, Psv, p);
  const auto dF_dt = speedofsound::theory::dF_dt(t);
  const auto dPsv_dt = speedofsound::theory::dPsv_dt(T);
  const auto dXw_dh = speedofsound::theory::dXw_dh(F, Psv, p);
  const auto dXw_dF = speedofsound::theory::dXw_dF(h, Psv, p);
  const auto dXw_dPsv = speedofsound::theory::dXw_dPsv(h, F, p);
  const auto dXw_dp = speedofsound::theory::dXw_dp(h, F, Psv, p);
  const auto dC_dt = speedofsound::theory::dC_dt(t, p, Xw, xc, dXw_dF, dF_dt,
                                                 dXw_dPsv, dPsv_dt);
  const auto dC_dxc = speedofsound::theory::dC_dxc(t, p, Xw, xc);
  const auto dC_dp = speedofsound::theory::dC_dp(t, p, Xw, xc, dXw_dp);
  const auto dC_dXw = speedofsound::theory::dC_dXw(t, p, Xw, xc);
  const auto dC_dh = speedofsound::theory::dC_dh(dC_dXw, dXw_dh);
  EXPECT_DOUBLE_EQ(speed_of_sound_.GetInitEnvironmentRate().temperature_rate_,
                   dC_dt);
  EXPECT_DOUBLE_EQ(speed_of_sound_.GetInitEnvironmentRate().humidity_rate_,
                   dC_dh);
  EXPECT_DOUBLE_EQ(speed_of_sound_.GetInitEnvironmentRate().pressure_rate_,
                   dC_dp);
  EXPECT_DOUBLE_EQ(
      speed_of_sound_.GetInitEnvironmentRate().co2_mole_fraction_rate_, dC_dxc);
}

TEST_F(SpeedOfSoundTest, ComputeReturnsCorrectValue) {
  speedofsound::Environment environment_;
  for (auto t = kTMin; t <= kTMax; t += (kTMax - kTMin) * kIncrementFactor) {
    for (auto h = kHMin; h <= kHMax; h += (kHMax - kHMin) * kIncrementFactor) {
      for (auto p = kPMin; p <= kPMax;
           p += (kPMax - kPMin) * kIncrementFactor) {
        for (auto xc = kXcMin; xc <= kXcMax;
             xc += (kXcMax - kXcMin) * kIncrementFactor) {
          environment_.temperature_ = t;
          environment_.humidity_ = h;
          environment_.pressure_ = p;
          environment_.co2_mole_fraction_ = xc;
          const auto c = speed_of_sound_.Compute(environment_);
          const auto T = speedofsound::theory::T(t);
          const auto F = speedofsound::theory::F(p, t);
          const auto Psv = speedofsound::theory::Psv(T);
          const auto Xw = speedofsound::theory::Xw(h, F, Psv, p);
          const auto C = speedofsound::theory::C(t, p, Xw, xc);
          ASSERT_DOUBLE_EQ(C, c);
        }
      }
    }
  }
}

TEST_F(SpeedOfSoundTest, QuickComputeReturnsCorrectValue) {
  speedofsound::Environment environment_;
  for (auto t = kTMin; t <= kTMax; t += (kTMax - kTMin) * kIncrementFactor) {
    for (auto h = kHMin; h <= kHMax; h += (kHMax - kHMin) * kIncrementFactor) {
      for (auto p = kPMin; p <= kPMax;
           p += (kPMax - kPMin) * kIncrementFactor) {
        for (auto xc = kXcMin; xc <= kXcMax;
             xc += (kXcMax - kXcMin) * kIncrementFactor) {
          const auto T = speedofsound::theory::T(t);
          const auto F = speedofsound::theory::F(p, t);
          const auto Psv = speedofsound::theory::Psv(T);
          const auto Xw = speedofsound::theory::Xw(h, F, Psv, p);
          const auto C = speedofsound::theory::C(t, p, Xw, xc);
          environment_.temperature_ = t;
          environment_.humidity_ = h;
          environment_.pressure_ = p;
          environment_.co2_mole_fraction_ = xc;
          const auto c = speed_of_sound_.QuickCompute(environment_);
          ASSERT_DOUBLE_EQ(C, c);
        }
      }
    }
  }
}

TEST_F(SpeedOfSoundTest, ApproximationReturnsCorrectValue) {
  speedofsound::Environment environment_;
  speedofsound::Environment environment_higher, environment_lower;
  EXPECT_DOUBLE_EQ(speed_of_sound_.Compute(environment_),
                   speed_of_sound_.Approximate(environment_));
  environment_higher.temperature_ += 5.0;
  environment_higher.humidity_ += 0.2;
  environment_higher.pressure_ += 600;
  environment_higher.co2_mole_fraction_ += 0.003;
  EXPECT_DOUBLE_EQ(347.0974896038062,
                   speed_of_sound_.Approximate(environment_higher));

  environment_lower.temperature_ -= 12.0;
  environment_lower.humidity_ -= 0.3;
  environment_lower.pressure_ -= 2000;
  environment_lower.co2_mole_fraction_ -= 0.0001;
  EXPECT_DOUBLE_EQ(336.14277346708593,
                   speed_of_sound_.Approximate(environment_lower));
}

TEST_F(SpeedOfSoundTest, LinearApproximationResultWithinTolerance) {
  const auto environment_variance = 20.0 / 100.0;
  const auto tolerance = 0.05 / 100.0;
  speedofsound::Environment e_init;
  speedofsound::Environment e;
  for (auto t = kTMin; t <= kTMax; t += (kTMax - kTMin) * kIncrementFactor) {
    for (auto h = kHMin; h <= kHMax; h += (kHMax - kHMin) * kIncrementFactor) {
      for (auto p = kPMin; p <= kPMax;
           p += (kPMax - kPMin) * kIncrementFactor) {
        for (auto xc = kXcMin; xc <= kXcMax;
             xc += (kXcMax - kXcMin) * kIncrementFactor) {
          e_init.temperature_ = t;
          e_init.humidity_ = h;
          e_init.pressure_ = p;
          e_init.co2_mole_fraction_ = xc;
          auto c = speed_of_sound_.Compute(e_init);

          e.temperature_ = (1.0 - environment_variance) * t;
          e.humidity_ = (1.0 - environment_variance) * h;
          e.pressure_ = (1.0 - environment_variance) * p;
          e.co2_mole_fraction_ = (1.0 - environment_variance) * xc;
          c = speed_of_sound_.QuickCompute(e);
          auto c_approx = speed_of_sound_.Approximate(e);
          ASSERT_NEAR(c, c_approx, c * tolerance);

          e.temperature_ = (1.0 + environment_variance) * t;
          e.humidity_ = (1.0 + environment_variance) * h;
          e.pressure_ = (1.0 + environment_variance) * p;
          e.co2_mole_fraction_ = (1.0 + environment_variance) * xc;
          c = speed_of_sound_.QuickCompute(e);
          c_approx = speed_of_sound_.Approximate(e);
          ASSERT_NEAR(c, c_approx, c * tolerance);
        }
      }
    }
  }
}

TEST_F(SpeedOfSoundTest, ApproximationFasterThanQuickCompute) {
  const auto runtime_ratio = 1.0 / 3.0;
  speedofsound::Environment environment_;
  auto quick_compute_timer_start = std::chrono::high_resolution_clock::now();
  for (auto t = kTMin; t <= kTMax; t += (kTMax - kTMin) * kIncrementFactor) {
    for (auto h = kHMin; h <= kHMax; h += (kHMax - kHMin) * kIncrementFactor) {
      for (auto p = kPMin; p <= kPMax;
           p += (kPMax - kPMin) * kIncrementFactor) {
        for (auto xc = kXcMin; xc <= kXcMax;
             xc += (kXcMax - kXcMin) * kIncrementFactor) {
          environment_.temperature_ = t;
          environment_.humidity_ = h;
          environment_.pressure_ = p;
          environment_.co2_mole_fraction_ = xc;
          speed_of_sound_.QuickCompute(environment_);
        }
      }
    }
  }
  const auto quick_compute_timer_end =
      std::chrono::high_resolution_clock::now();
  const auto quick_compute_time =
      quick_compute_timer_end - quick_compute_timer_start;
  auto approximation_timer_start = std::chrono::high_resolution_clock::now();
  for (auto t = kTMin; t <= kTMax; t += (kTMax - kTMin) * kIncrementFactor) {
    for (auto h = kHMin; h <= kHMax; h += (kHMax - kHMin) * kIncrementFactor) {
      for (auto p = kPMin; p <= kPMax;
           p += (kPMax - kPMin) * kIncrementFactor) {
        for (auto xc = kXcMin; xc <= kXcMax;
             xc += (kXcMax - kXcMin) * kIncrementFactor) {
          environment_.temperature_ = t;
          environment_.humidity_ = h;
          environment_.pressure_ = p;
          environment_.co2_mole_fraction_ = xc;
          speed_of_sound_.Approximate(environment_);
        }
      }
    }
  }
  const auto approximation_timer_end =
      std::chrono::high_resolution_clock::now();
  const auto approximation_time =
      approximation_timer_end - approximation_timer_start;
  EXPECT_LE(approximation_time.count(),
            quick_compute_time.count() * runtime_ratio);
}
