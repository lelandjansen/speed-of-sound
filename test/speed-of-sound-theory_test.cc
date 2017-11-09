#include "speed-of-sound-theory_test.h"

SpeedOfSoundTheoryTest::SpeedOfSoundTheoryTest() {
  min_case.temperature_ = speedofsound::theory::kMinTemperature;
  min_case.humidity_ = speedofsound::theory::kMinHumidity;
  min_case.pressure_ = speedofsound::theory::kMinPressure;
  min_case.co2_mole_fraction_ = speedofsound::theory::kMinCO2MoleFraction;

  min_xw_case.temperature_ = speedofsound::theory::kMinTemperature;
  min_xw_case.humidity_ = speedofsound::theory::kMinHumidity;
  min_xw_case.pressure_ = speedofsound::theory::kMinXwPressure;
  min_xw_case.co2_mole_fraction_ = speedofsound::theory::kMinCO2MoleFraction;

  max_case.temperature_ = speedofsound::theory::kMaxTemperature,
  max_case.humidity_ = speedofsound::theory::kMaxHumidity,
  max_case.pressure_ = speedofsound::theory::kMaxPressure,
  max_case.co2_mole_fraction_ = speedofsound::theory::kMaxCO2MoleFraction;

  max_xw_case.temperature_ = speedofsound::theory::kMaxTemperature,
  max_xw_case.humidity_ = speedofsound::theory::kMaxHumidity,
  max_xw_case.pressure_ = speedofsound::theory::kMaxXwPressure,
  max_xw_case.co2_mole_fraction_ = speedofsound::theory::kMaxCO2MoleFraction;
}

TEST_F(SpeedOfSoundTheoryTest, T) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 18.284148638241625;
  test_cases = {{273.15, min_case},
                {291.4341486382416, random_case},
                {293.15, std_case},
                {303.15, max_case}};
  double t, T;
  for (auto test_case : test_cases) {
    t = test_case.second.temperature_;
    T = speedofsound::theory::T(t);
    EXPECT_DOUBLE_EQ(test_case.first, T);
  }
}

TEST_F(SpeedOfSoundTheoryTest, dT_dt) {
  EXPECT_DOUBLE_EQ(1.0, speedofsound::theory::dT_dt());
}

TEST_F(SpeedOfSoundTheoryTest, F) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 27.844468454693093;
  random_case.pressure_ = 89656.35925586602;
  test_cases = {{1.002504, min_xw_case},
                {1.0038693857578078, random_case},
                {1.004025605, std_case},
                {1.0045780000000002, max_xw_case}};
  double p, t, F;
  for (auto test_case : test_cases) {
    p = test_case.second.pressure_;
    t = test_case.second.temperature_;
    F = speedofsound::theory::F(p, t);
    EXPECT_DOUBLE_EQ(test_case.first, F);
  }
}

TEST_F(SpeedOfSoundTheoryTest, dF_dp) {
  EXPECT_DOUBLE_EQ(3.14e-8, speedofsound::theory::dF_dp());
}

TEST_F(SpeedOfSoundTheoryTest, dF_dt) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 12.294236473063911;
  test_cases = {{0.0, min_xw_case},
                {0.00001376954484983158, random_case},
                {0.000022399999999999996, std_case},
                {0.0000336, max_xw_case}};
  double t, dF_dt;
  for (auto test_case : test_cases) {
    t = test_case.second.temperature_;
    dF_dt = speedofsound::theory::dF_dt(t);
    EXPECT_DOUBLE_EQ(test_case.first, dF_dt);
  }
}

TEST_F(SpeedOfSoundTheoryTest, Psv) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 2.1984818036360068;
  test_cases = {{611.2129344513172, min_xw_case},
                {716.0310817057355, random_case},
                {2338.5721154062803, std_case},
                {4245.190531747869, max_xw_case}};
  double T, Psv;
  for (auto test_case : test_cases) {
    T = speedofsound::theory::T(test_case.second.temperature_);
    Psv = speedofsound::theory::Psv(T);
    EXPECT_NEAR(test_case.first, Psv, test_case.first * kTolerance);
  }
}

TEST_F(SpeedOfSoundTheoryTest, dPsv_dt) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 8.105720408347487;
  test_cases = {{44.40221431628648, min_xw_case},
                {73.4960648857937, random_case},
                {144.84027310567882, std_case},
                {243.64989811537197, max_xw_case}};
  double T, dPsv_dt;
  for (auto test_case : test_cases) {
    T = speedofsound::theory::T(test_case.second.temperature_);
    dPsv_dt = speedofsound::theory::dPsv_dt(T);
    EXPECT_NEAR(test_case.first, dPsv_dt, test_case.first * kTolerance);
  }
}

TEST_F(SpeedOfSoundTheoryTest, Xw) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 11.998297271608877;
  random_case.humidity_ = 0.34202164822956593;
  random_case.pressure_ = 67874.61330893353;
  test_cases = {{0.0, min_xw_case},
                {0.007086640331164677, random_case},
                {0.011586411463147895, std_case},
                {0.03876931830911101, max_xw_case}};
  double t, h, p, F, Psv, Xw;
  for (auto test_case : test_cases) {
    t = test_case.second.temperature_;
    h = test_case.second.humidity_;
    p = test_case.second.pressure_;
    F = speedofsound::theory::F(p, t);
    Psv = speedofsound::theory::Psv(speedofsound::theory::T(t));
    Xw = speedofsound::theory::Xw(h, F, Psv, p);
    EXPECT_NEAR(test_case.first, Xw, test_case.first * kTolerance);
  }
}

TEST_F(SpeedOfSoundTheoryTest, dXw_dh) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 23.807213428100113;
  random_case.pressure_ = 90725.80279070066;
  test_cases = {{0.01021239019398639, min_xw_case},
                {0.03264236679363074, random_case},
                {0.02317282292629579, std_case},
                {0.03876931830911101, max_xw_case}};
  double t, p, F, Psv, dXw_dh;
  for (auto test_case : test_cases) {
    t = test_case.second.temperature_;
    p = test_case.second.pressure_;
    F = speedofsound::theory::F(p, t);
    Psv = speedofsound::theory::Psv(speedofsound::theory::T(t));
    dXw_dh = speedofsound::theory::dXw_dh(F, Psv, p);
    EXPECT_NEAR(test_case.first, dXw_dh, test_case.first * kTolerance);
  }
}

TEST_F(SpeedOfSoundTheoryTest, dXw_dF) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 12.347891354488652;
  random_case.humidity_ = 0.1629359256607068;
  random_case.pressure_ = 90930.00940507354;
  test_cases = {{0.0, min_xw_case},
                {0.002571419561273468, random_case},
                {0.011539956157938715, std_case},
                {0.038592641197707896, max_xw_case}};
  double t, h, p, Psv, dXw_dF;
  for (auto test_case : test_cases) {
    t = test_case.second.temperature_;
    h = test_case.second.humidity_;
    p = test_case.second.pressure_;
    Psv = speedofsound::theory::Psv(speedofsound::theory::T(t));
    dXw_dF = speedofsound::theory::dXw_dF(h, Psv, p);
  }
}

TEST_F(SpeedOfSoundTheoryTest, dXw_dPsv) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 4.848721185763054;
  random_case.humidity_ = 0.8556806268369959;
  random_case.pressure_ = 62674.21872949686;
  test_cases = {{0.0, min_xw_case},
                {0.000013688345639018303, random_case},
                {4.954481149765606e-6, std_case},
                {9.132527272727275e-6, max_xw_case}};
  double t, h, p, F, dXw_dPsv;
  for (auto test_case : test_cases) {
    t = test_case.second.temperature_;
    h = test_case.second.humidity_;
    p = test_case.second.pressure_;
    F = speedofsound::theory::F(p, t);
    dXw_dPsv = speedofsound::theory::dXw_dPsv(h, F, p);
    EXPECT_NEAR(test_case.first, dXw_dPsv, test_case.first * kTolerance);
  }
}

TEST_F(SpeedOfSoundTheoryTest, dXw_dp) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 2.8967257386015532;
  random_case.humidity_ = 0.5169528442922398;
  random_case.pressure_ = 106192.0489382949;
  test_cases = {{0.0, min_xw_case},
                {-3.451789197083466e-8, random_case},
                {-1.1398663588389851e-7, std_case},
                {-3.512365393310375e-7, max_xw_case}};
  double t, h, p, F, Psv, dXw_dp;
  for (auto test_case : test_cases) {
    t = test_case.second.temperature_;
    h = test_case.second.humidity_;
    p = test_case.second.pressure_;
    F = speedofsound::theory::F(p, t);
    Psv = speedofsound::theory::Psv(speedofsound::theory::T(t));
    dXw_dp = speedofsound::theory::dXw_dp(h, F, Psv, p);
    EXPECT_NEAR(test_case.first, dXw_dp, -1.0 * test_case.first * kTolerance);
  }
}

TEST_F(SpeedOfSoundTheoryTest, C) {
  speedofsound::Environment random_case_1, random_case_2;
  random_case_1.temperature_ = 4.788305455529283;
  random_case_1.humidity_ = 0.8483903127928138;
  random_case_1.pressure_ = 99341.02580103357;
  random_case_1.co2_mole_fraction_ = 0.007868880851415702;
  random_case_2.temperature_ = 11.220446605723424;
  random_case_2.humidity_ = 0.0326086454966481;
  random_case_2.pressure_ = 96000.82892784919;
  random_case_2.co2_mole_fraction_ = 0.0030235205198150903;
  test_cases = {{331.48754062500007, min_case},
                {334.08459414185165, random_case_1},
                {337.9787163164935, random_case_2},
                {343.9943970603679, std_case},
                {350.593524548772, max_case}};
  double t, h, p, xc, F, Psv, Xw, C;
  for (auto test_case : test_cases) {
    t = test_case.second.temperature_;
    h = test_case.second.humidity_;
    p = test_case.second.pressure_;
    xc = test_case.second.co2_mole_fraction_;
    F = speedofsound::theory::F(p, t);
    Psv = speedofsound::theory::Psv(speedofsound::theory::T(t));
    Xw = speedofsound::theory::Xw(h, F, Psv, p);
    C = speedofsound::theory::C(t, p, Xw, xc);
    EXPECT_NEAR(test_case.first, C, test_case.first * kTolerance);
  }
}

TEST_F(SpeedOfSoundTheoryTest, dC_dt) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 8.335426774441274;
  random_case.humidity_ = 0.04306573258518309;
  random_case.pressure_ = 100339.02623320109;
  random_case.co2_mole_fraction_ = 0.001142713269765925;
  test_cases = {{0.6058525, min_case},
                {0.5990025466394929, random_case},
                {0.6246637009346002, std_case},
                {0.7086882617549803, max_case}};
  double t, h, p, xc, F, Psv, Xw, dXw_dF, dF_dt, dXw_dPsv, dPsv_dt, dC_dt;
  for (auto test_case : test_cases) {
    t = test_case.second.temperature_;
    h = test_case.second.humidity_;
    p = test_case.second.pressure_;
    xc = test_case.second.co2_mole_fraction_;
    F = speedofsound::theory::F(p, t);
    Psv = speedofsound::theory::Psv(speedofsound::theory::T(t));
    Xw = speedofsound::theory::Xw(h, F, Psv, p);
    dXw_dF = speedofsound::theory::dXw_dF(h, Psv, p);
    dF_dt = speedofsound::theory::dF_dt(t);
    dXw_dPsv = speedofsound::theory::dXw_dPsv(h, F, p);
    dPsv_dt = speedofsound::theory::dPsv_dt(speedofsound::theory::T(t));
    dC_dt = speedofsound::theory::dC_dt(t, p, Xw, xc, dXw_dF, dF_dt, dXw_dPsv,
                                        dPsv_dt);
    EXPECT_NEAR(test_case.first, dC_dt, test_case.first * kTolerance);
  }
}

TEST_F(SpeedOfSoundTheoryTest, dC_dXw) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 26.30665373526002;
  random_case.humidity_ = 0.3356317205048449;
  random_case.pressure_ = 91021.06631986011;
  random_case.co2_mole_fraction_ = 0.001022633303459329;
  test_cases = {{51.471935, min_case},
                {54.83927112325779, random_case},
                {54.10064719455334, std_case},
                {55.514460843843075, max_case}};
  double t, h, p, xc, F, Psv, Xw, dC_dXw;
  for (auto test_case : test_cases) {
    t = test_case.second.temperature_;
    h = test_case.second.humidity_;
    p = test_case.second.pressure_;
    xc = test_case.second.co2_mole_fraction_;
    F = speedofsound::theory::F(p, t);
    Psv = speedofsound::theory::Psv(speedofsound::theory::T(t));
    Xw = speedofsound::theory::Xw(h, F, Psv, p);
    dC_dXw = speedofsound::theory::dC_dXw(t, p, Xw, xc);
    EXPECT_NEAR(test_case.first, dC_dXw, test_case.first * kTolerance);
  }
}

TEST_F(SpeedOfSoundTheoryTest, dC_dxc) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 21.706163749674275;
  random_case.humidity_ = 0.45418417642349995;
  random_case.pressure_ = 76777.7224873716;
  random_case.co2_mole_fraction_ = 0.0019591670521459936;
  test_cases = {{-85.20931, min_case},
                {-89.45230237346945, random_case},
                {-89.16728444269332, std_case},
                {-89.35618526963965, max_case}};
  double t, h, p, xc, F, Psv, Xw, dC_dxc;
  for (auto test_case : test_cases) {
    t = test_case.second.temperature_;
    h = test_case.second.humidity_;
    p = test_case.second.pressure_;
    xc = test_case.second.co2_mole_fraction_;
    F = speedofsound::theory::F(p, t);
    Psv = speedofsound::theory::Psv(speedofsound::theory::T(t));
    Xw = speedofsound::theory::Xw(h, F, Psv, p);
    dC_dxc = speedofsound::theory::dC_dxc(t, p, Xw, xc);
    EXPECT_NEAR(test_case.first, dC_dxc, -1.0 * test_case.first * kTolerance);
  }
}

TEST_F(SpeedOfSoundTheoryTest, dC_dp) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 23.060057075564643;
  random_case.humidity_ = 0.8929583480896977;
  random_case.pressure_ = 78994.74831236238;
  random_case.co2_mole_fraction_ = 0.003932372141783944;
  test_cases = {{-2.1425e-7, min_case},
                {-0.00002145591319831367, random_case},
                {-5.761752390113884e-6, std_case},
                {-0.00002184468771493967, max_case}};
  double t, h, p, xc, F, Psv, Xw, dXw_dp, dC_dp;
  for (auto test_case : test_cases) {
    t = test_case.second.temperature_;
    h = test_case.second.humidity_;
    p = test_case.second.pressure_;
    xc = test_case.second.co2_mole_fraction_;
    F = speedofsound::theory::F(p, t);
    Psv = speedofsound::theory::Psv(speedofsound::theory::T(t));
    Xw = speedofsound::theory::Xw(h, F, Psv, p);
    dXw_dp = speedofsound::theory::dXw_dp(h, F, Psv, p);
    dC_dp = speedofsound::theory::dC_dp(t, p, Xw, xc, dXw_dp);
    EXPECT_NEAR(test_case.first, dC_dp, -1.0 * test_case.first * kTolerance);
  }
}

TEST_F(SpeedOfSoundTheoryTest, dC_dh) {
  speedofsound::Environment random_case;
  random_case.temperature_ = 23.019582399896642;
  random_case.humidity_ = 0.0928206714768458;
  random_case.pressure_ = 99919.41775510696;
  random_case.co2_mole_fraction_ = 0.0013816954173898905;
  test_cases = {{0.42071875816968457, min_case},
                {1.5422750283964233, random_case},
                {1.2536647176373856, std_case},
                {2.3204819429829007, max_case}};
  double t, h, p, xc, F, Psv, Xw, dC_dXw, dXw_dh, dC_dh;
  for (auto test_case : test_cases) {
    t = test_case.second.temperature_;
    h = test_case.second.humidity_;
    p = test_case.second.pressure_;
    xc = test_case.second.co2_mole_fraction_;
    F = speedofsound::theory::F(p, t);
    Psv = speedofsound::theory::Psv(speedofsound::theory::T(t));
    Xw = speedofsound::theory::Xw(h, F, Psv, p);
    dC_dXw = speedofsound::theory::dC_dXw(t, p, Xw, xc);
    dXw_dh = speedofsound::theory::dXw_dh(F, Psv, p);
    dC_dh = speedofsound::theory::dC_dh(dC_dXw, dXw_dh);
    EXPECT_NEAR(test_case.first, dC_dh, test_case.first * kTolerance);
  }
}
