// speed_of_sound_test.cc
#include "speed_of_sound_test.h"

TEST_F(EnvironmentTest, EnvironmentConstructorDefaultValue) {
  EXPECT_DOUBLE_EQ(environment.temperature_,
                   speedofsound::theory::kStdTemperature);
  EXPECT_DOUBLE_EQ(environment.humidity_, speedofsound::theory::kStdHumidity);
  EXPECT_DOUBLE_EQ(environment.pressure_, speedofsound::theory::kStdPressure);
  EXPECT_DOUBLE_EQ(environment.co2_mole_fraction_,
                   speedofsound::theory::kStdCO2MoleFraction);
}

TEST_F(EnvironmentTest, EnvironmentValidateTemperature) {
  EXPECT_TRUE(environment.ValidateTemperature());
  environment.temperature_ = speedofsound::theory::kMinTemperature - 1.0;
  EXPECT_FALSE(environment.ValidateTemperature());
  ++environment.temperature_;
  EXPECT_TRUE(environment.ValidateTemperature());
  ++environment.temperature_;
  EXPECT_TRUE(environment.ValidateTemperature());

  environment.temperature_ = speedofsound::theory::kMaxTemperature - 1.0;
  EXPECT_TRUE(environment.ValidateTemperature());
  ++environment.temperature_;
  EXPECT_TRUE(environment.ValidateTemperature());
  ++environment.temperature_;
  EXPECT_FALSE(environment.ValidateTemperature());
}

TEST_F(EnvironmentTest, EnvironmentValidateHumidity) {
  double increment = 0.1;
  EXPECT_TRUE(environment.ValidateHumidity());
  environment.humidity_ = speedofsound::theory::kMinHumidity - increment;
  EXPECT_FALSE(environment.ValidateHumidity());
  environment.humidity_ += increment;
  EXPECT_TRUE(environment.ValidateHumidity());
  environment.humidity_ += increment;
  EXPECT_TRUE(environment.ValidateHumidity());

  environment.humidity_ = speedofsound::theory::kMaxHumidity - increment;
  EXPECT_TRUE(environment.ValidateHumidity());
  environment.humidity_ += increment;
  EXPECT_TRUE(environment.ValidateHumidity());
  environment.humidity_ += increment;
  EXPECT_FALSE(environment.ValidateHumidity());
}

TEST_F(EnvironmentTest, EnvironmentValidatePressure) {
  EXPECT_TRUE(environment.ValidatePressure());
  environment.pressure_ = speedofsound::theory::kMinPressure - 1.0;
  EXPECT_FALSE(environment.ValidatePressure());
  ++environment.pressure_;
  EXPECT_TRUE(environment.ValidatePressure());
  ++environment.pressure_;
  EXPECT_TRUE(environment.ValidatePressure());

  environment.pressure_ = speedofsound::theory::kMaxPressure - 1.0;
  EXPECT_TRUE(environment.ValidatePressure());
  ++environment.pressure_;
  EXPECT_TRUE(environment.ValidatePressure());
  ++environment.pressure_;
  EXPECT_FALSE(environment.ValidatePressure());
}

TEST_F(EnvironmentTest, EnvironmentValidateCO2MoleFraction) {
  double increment = 1e-3;
  EXPECT_TRUE(environment.ValidateCO2MoleFraction());
  environment.co2_mole_fraction_ =
      speedofsound::theory::kMinCO2MoleFraction - increment;
  EXPECT_FALSE(environment.ValidateCO2MoleFraction());
  environment.co2_mole_fraction_ = speedofsound::theory::kMinCO2MoleFraction;
  EXPECT_TRUE(environment.ValidateCO2MoleFraction());
  environment.co2_mole_fraction_ += increment;
  EXPECT_TRUE(environment.ValidateCO2MoleFraction());

  environment.co2_mole_fraction_ =
      speedofsound::theory::kMaxCO2MoleFraction - increment;
  EXPECT_TRUE(environment.ValidateCO2MoleFraction());
  environment.co2_mole_fraction_ = speedofsound::theory::kMaxCO2MoleFraction;
  EXPECT_TRUE(environment.ValidateCO2MoleFraction());
  environment.co2_mole_fraction_ += increment;
  EXPECT_FALSE(environment.ValidateCO2MoleFraction());
}

TEST_F(EnvironmentTest, EnvironmentValidateEnvironment) {
  EXPECT_TRUE(environment.ValidateEnvironment());
  environment.temperature_ = speedofsound::theory::kMinTemperature - 1.0;
  EXPECT_FALSE(environment.ValidateEnvironment());
  environment.pressure_ = speedofsound::theory::kMaxPressure + 1.0;
  environment.humidity_ = speedofsound::theory::kMinTemperature - 0.1;
  EXPECT_FALSE(environment.ValidateEnvironment());
  environment.temperature_ += 10.0;
  EXPECT_FALSE(environment.ValidateEnvironment());
  environment.humidity_ = speedofsound::theory::kStdHumidity;
  EXPECT_FALSE(environment.ValidateEnvironment());
  environment.pressure_ -= 100.0;
  EXPECT_TRUE(environment.ValidateEnvironment());
}

TEST_F(EnvironmentRateTest, EnvironmentRateConstructorDefaultValue) {
  EXPECT_DOUBLE_EQ(environment_rate.temperature_rate_, 0.0);
  EXPECT_DOUBLE_EQ(environment_rate.humidity_rate_, 0.0);
  EXPECT_DOUBLE_EQ(environment_rate.pressure_rate_, 0.0);
  EXPECT_DOUBLE_EQ(environment_rate.co2_mole_fraction_rate_, 0.0);
}

TEST_F(SpeedOfSoundTest, EnvironmentConstructorDefaultValues) {
  EXPECT_DOUBLE_EQ(speed_of_sound.GetInitEnvironment().temperature_,
                   speedofsound::theory::kStdTemperature);
  EXPECT_DOUBLE_EQ(speed_of_sound.GetInitEnvironment().humidity_,
                   speedofsound::theory::kStdHumidity);
  EXPECT_DOUBLE_EQ(speed_of_sound.GetInitEnvironment().pressure_,
                   speedofsound::theory::kStdPressure);
  EXPECT_DOUBLE_EQ(speed_of_sound.GetInitEnvironment().co2_mole_fraction_,
                   speedofsound::theory::kStdCO2MoleFraction);
}

TEST_F(SpeedOfSoundTest, EnvironmentOverloadConstructorValues) {
  speedofsound::Environment environment;
  environment.temperature_ = speedofsound::theory::kMinTemperature;
  environment.humidity_ = speedofsound::theory::kMinHumidity;
  environment.pressure_ = speedofsound::theory::kMinPressure;
  environment.co2_mole_fraction_ = speedofsound::theory::kMinCO2MoleFraction;
  speedofsound::SpeedOfSound speed_of_sound(environment);

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
  double t, h, p, xc, T, F, Psv, Xw, dF_dt, dPsv_dt, dXw_dh, dXw_dF, dXw_dPsv,
      dXw_dp, dC_dt, dC_dh, dC_dp, dC_dXw, dC_dxc;

  t = speedofsound::theory::kStdTemperature;
  h = speedofsound::theory::kStdHumidity;
  p = speedofsound::theory::kStdPressure;
  xc = speedofsound::theory::kStdCO2MoleFraction;

  T = speedofsound::theory::T(t);
  F = speedofsound::theory::F(p, t);
  Psv = speedofsound::theory::Psv(T);
  Xw = speedofsound::theory::Xw(h, F, Psv, p);
  dF_dt = speedofsound::theory::dF_dt(t);
  dPsv_dt = speedofsound::theory::dPsv_dt(T);
  dXw_dh = speedofsound::theory::dXw_dh(F, Psv, p);
  dXw_dF = speedofsound::theory::dXw_dF(h, Psv, p);
  dXw_dPsv = speedofsound::theory::dXw_dPsv(h, F, p);
  dXw_dp = speedofsound::theory::dXw_dp(h, F, Psv, p);
  dC_dt = speedofsound::theory::dC_dt(t, p, Xw, xc, dXw_dF, dF_dt, dXw_dPsv,
                                      dPsv_dt);
  dC_dxc = speedofsound::theory::dC_dxc(t, p, Xw, xc);
  dC_dp = speedofsound::theory::dC_dp(t, p, Xw, xc, dXw_dp);
  dC_dXw = speedofsound::theory::dC_dXw(t, p, Xw, xc);
  dC_dh = speedofsound::theory::dC_dh(dC_dXw, dXw_dh);

  EXPECT_DOUBLE_EQ(speed_of_sound.GetInitEnvironmentRate().temperature_rate_,
                   dC_dt);
  EXPECT_DOUBLE_EQ(speed_of_sound.GetInitEnvironmentRate().humidity_rate_,
                   dC_dh);
  EXPECT_DOUBLE_EQ(speed_of_sound.GetInitEnvironmentRate().pressure_rate_,
                   dC_dp);
  EXPECT_DOUBLE_EQ(
      speed_of_sound.GetInitEnvironmentRate().co2_mole_fraction_rate_, dC_dxc);
}

TEST_F(SpeedOfSoundTest, ComputeReturnsCorrectValue) {
  double t, h, p, xc, c, T, F, Psv, Xw, C;
  speedofsound::Environment environment;

  for (t = kTMin; t <= kTMax; t += (kTMax - kTMin) * kIncrementFactor) {
    for (h = kHMin; h <= kHMax; h += (kHMax - kHMin) * kIncrementFactor) {
      for (p = kPMin; p <= kPMax; p += (kPMax - kPMin) * kIncrementFactor) {
        for (xc = kXcMin; xc <= kXcMax;
             xc += (kXcMax - kXcMin) * kIncrementFactor) {
          environment.temperature_ = t;
          environment.humidity_ = h;
          environment.pressure_ = p;
          environment.co2_mole_fraction_ = xc;
          c = speed_of_sound.Compute(environment);

          T = speedofsound::theory::T(t);
          F = speedofsound::theory::F(p, t);
          Psv = speedofsound::theory::Psv(T);
          Xw = speedofsound::theory::Xw(h, F, Psv, p);
          C = speedofsound::theory::C(t, p, Xw, xc);

          ASSERT_DOUBLE_EQ(C, c);
        }
      }
    }
  }
}

TEST_F(SpeedOfSoundTest, QuickComputeReturnsCorrectValue) {
  double t, h, p, xc, c, T, F, Psv, Xw, C;
  speedofsound::Environment environment;

  for (t = kTMin; t <= kTMax; t += (kTMax - kTMin) * kIncrementFactor) {
    for (h = kHMin; h <= kHMax; h += (kHMax - kHMin) * kIncrementFactor) {
      for (p = kPMin; p <= kPMax; p += (kPMax - kPMin) * kIncrementFactor) {
        for (xc = kXcMin; xc <= kXcMax;
             xc += (kXcMax - kXcMin) * kIncrementFactor) {
          T = speedofsound::theory::T(t);
          F = speedofsound::theory::F(p, t);
          Psv = speedofsound::theory::Psv(T);
          Xw = speedofsound::theory::Xw(h, F, Psv, p);
          C = speedofsound::theory::C(t, p, Xw, xc);

          environment.temperature_ = t;
          environment.humidity_ = h;
          environment.pressure_ = p;
          environment.co2_mole_fraction_ = xc;
          c = speed_of_sound.QuickCompute(environment);

          ASSERT_DOUBLE_EQ(C, c);
        }
      }
    }
  }
}

TEST_F(SpeedOfSoundTest, ApproximationReturnsCorrectValue) {
  speedofsound::Environment environment, environment_higher, environment_lower;
  EXPECT_DOUBLE_EQ(speed_of_sound.Compute(environment),
                   speed_of_sound.Approximate(environment));

  environment_higher.temperature_ += 5.0;
  environment_higher.humidity_ += 0.2;
  environment_higher.pressure_ += 600;
  environment_higher.co2_mole_fraction_ += 0.003;
  EXPECT_DOUBLE_EQ(347.0974896038062,
                   speed_of_sound.Approximate(environment_higher));

  environment_lower.temperature_ -= 12.0;
  environment_lower.humidity_ -= 0.3;
  environment_lower.pressure_ -= 2000;
  environment_lower.co2_mole_fraction_ -= 0.0001;
  EXPECT_DOUBLE_EQ(336.14277346708593,
                   speed_of_sound.Approximate(environment_lower));
}

TEST_F(SpeedOfSoundTest, LinearApproximationResultWithinTolerance) {
  double t, h, p, xc, c, c_approx;
  static constexpr double environment_variance = 20.0 / 100.0;
  static constexpr double tolerance = 0.05 / 100.0;
  speedofsound::Environment e, e_init;

  for (t = kTMin; t <= kTMax; t += (kTMax - kTMin) * kIncrementFactor) {
    for (h = kHMin; h <= kHMax; h += (kHMax - kHMin) * kIncrementFactor) {
      for (p = kPMin; p <= kPMax; p += (kPMax - kPMin) * kIncrementFactor) {
        for (xc = kXcMin; xc <= kXcMax;
             xc += (kXcMax - kXcMin) * kIncrementFactor) {
          e_init.temperature_ = t;
          e_init.humidity_ = h;
          e_init.pressure_ = p;
          e_init.co2_mole_fraction_ = xc;
          c = speed_of_sound.Compute(e_init);

          e.temperature_ = (1.0 - environment_variance) * t;
          e.humidity_ = (1.0 - environment_variance) * h;
          e.pressure_ = (1.0 - environment_variance) * p;
          e.co2_mole_fraction_ = (1.0 - environment_variance) * xc;
          c = speed_of_sound.QuickCompute(e);
          c_approx = speed_of_sound.Approximate(e);
          ASSERT_NEAR(c, c_approx, c * tolerance);

          e.temperature_ = (1.0 + environment_variance) * t;
          e.humidity_ = (1.0 + environment_variance) * h;
          e.pressure_ = (1.0 + environment_variance) * p;
          e.co2_mole_fraction_ = (1.0 + environment_variance) * xc;
          c = speed_of_sound.QuickCompute(e);
          c_approx = speed_of_sound.Approximate(e);
          ASSERT_NEAR(c, c_approx, c * tolerance);
        }
      }
    }
  }
}

TEST_F(SpeedOfSoundTest, ApproximationFasterThanQuickCompute) {
  double t, h, p, xc, c;
  static constexpr double runtime_ratio = 1.0 / 3.0;
  static constexpr int attempts = 3;
  speedofsound::Environment environment;
  std::chrono::duration<double> quick_compute_time, approximation_time;

  for (int i = 0; i < attempts; ++i) {
    auto quick_compute_timer_start = std::chrono::high_resolution_clock::now();
    for (t = kTMin; t <= kTMax; t += (kTMax - kTMin) * kIncrementFactor) {
      for (h = kHMin; h <= kHMax; h += (kHMax - kHMin) * kIncrementFactor) {
        for (p = kPMin; p <= kPMax; p += (kPMax - kPMin) * kIncrementFactor) {
          for (xc = kXcMin; xc <= kXcMax;
               xc += (kXcMax - kXcMin) * kIncrementFactor) {
            environment.temperature_ = t;
            environment.humidity_ = h;
            environment.pressure_ = p;
            environment.co2_mole_fraction_ = xc;
            speed_of_sound.QuickCompute(environment);
          }
        }
      }
    }
    auto quick_compute_timer_end = std::chrono::high_resolution_clock::now();
    quick_compute_time = quick_compute_timer_end - quick_compute_timer_start;

    auto approximation_timer_start = std::chrono::high_resolution_clock::now();
    for (t = kTMin; t <= kTMax; t += (kTMax - kTMin) * kIncrementFactor) {
      for (h = kHMin; h <= kHMax; h += (kHMax - kHMin) * kIncrementFactor) {
        for (p = kPMin; p <= kPMax; p += (kPMax - kPMin) * kIncrementFactor) {
          for (xc = kXcMin; xc <= kXcMax;
               xc += (kXcMax - kXcMin) * kIncrementFactor) {
            environment.temperature_ = t;
            environment.humidity_ = h;
            environment.pressure_ = p;
            environment.co2_mole_fraction_ = xc;
            speed_of_sound.Approximate(environment);
          }
        }
      }
    }
    auto approximation_timer_end = std::chrono::high_resolution_clock::now();
    approximation_time = approximation_timer_end - approximation_timer_start;

    if (approximation_time.count() <=
        quick_compute_time.count() * runtime_ratio)
      break;
  }

  EXPECT_LE(approximation_time.count(),
            quick_compute_time.count() * runtime_ratio);
}
