// speed_of_sound.cc
#include "speed_of_sound.h"

namespace speedofsound {
  Environment::Environment() {
    temperature_ = theory::kStdTemperature;
    humidity_ = theory::kStdHumidity;
    pressure_ = theory::kStdPressure;
    co2_mole_fraction_ = theory::kStdCO2MoleFraction;
  }

  bool Environment::ValidateTemperature() const {
    return theory::kMinTemperature <= temperature_ &&
      temperature_ <= theory::kMaxTemperature;
  }

  bool Environment::ValidateHumidity() const {
    return theory::kMinHumidity <= humidity_ &&
      humidity_ <= theory::kMaxHumidity;
  }

  bool Environment::ValidatePressure() const {
    return theory::kMinPressure <= pressure_ &&
      pressure_ <= theory::kMaxPressure;
  }

  bool Environment::ValidateCO2MoleFraction() const {
    return theory::kMinCO2MoleFraction <= co2_mole_fraction_ &&
      co2_mole_fraction_ <= theory::kMaxCO2MoleFraction;
  }

  bool Environment::ValidateEnvironment() const {
    return ValidateTemperature() &&
      ValidateHumidity() &&
      ValidatePressure() &&
      ValidateCO2MoleFraction();
  }


  EnvironmentRate::EnvironmentRate() {
    temperature_rate_ = 0.0;
    humidity_rate_ = 0.0;
    pressure_rate_ = 0.0;
    co2_mole_fraction_rate_ = 0.0;
  }


  SpeedOfSound::SpeedOfSound() {
    SpeedOfSound::Compute(init_environment);
  }


  SpeedOfSound::SpeedOfSound(Environment &ambient_conitions) {
    init_environment.temperature_ = ambient_conitions.temperature_;
    init_environment.humidity_ = ambient_conitions.humidity_;
    init_environment.pressure_ = ambient_conitions.pressure_;
    init_environment.co2_mole_fraction_ = ambient_conitions.co2_mole_fraction_;

    SpeedOfSound::Compute(init_environment);
  }

  Environment SpeedOfSound::GetInitEnvironment() const {
    return init_environment;
  }

  EnvironmentRate SpeedOfSound::GetInitEnvironmentRate() const {
    return init_environment_rate;
  }

  double SpeedOfSound::Compute(Environment &ambient_conitions) {
    double t, h, p, xc, T, F, Psv, Xw, C, dF_dt, dF_dp, dPsv_dt, dXw_dF, dC_dXw,
      dXw_dPsv, dXw_dp, dXw_dh, dC_dt, dC_dxc, dC_dp, dC_dh;

    t  = ambient_conitions.temperature_;
    h  = ambient_conitions.humidity_;
    p  = ambient_conitions.pressure_;
    xc = ambient_conitions.co2_mole_fraction_;

    T        = theory::T(t);
    F        = theory::F(p, t);
    Psv      = theory::Psv(T);
    Xw       = theory::Xw(h, F, Psv, p);
    C        = theory::C(t, p, Xw, xc);
    dF_dt    = theory::dF_dt(t);
    dF_dp    = theory::dF_dp();
    dPsv_dt  = theory::dPsv_dt(T);
    dXw_dF   = theory::dXw_dF(h, Psv, p);
    dXw_dPsv = theory::dXw_dPsv(h, F, p);
    dXw_dp   = theory::dXw_dp(h, F, Psv, p);
    dXw_dh   = theory::dXw_dh(F, Psv, p);
    dC_dt    = theory::dC_dt(t, p, Xw, xc, dXw_dF, dF_dt, dXw_dPsv, dPsv_dt);
    dC_dxc   = theory::dC_dxc(t, p, Xw, xc);
    dC_dp    = theory::dC_dp(t, p, Xw, xc, dXw_dp);
    dC_dXw   = theory::dC_dXw(t, p, Xw, xc);
    dC_dh    = theory::dC_dh(dC_dXw, dXw_dh);

    init_speed_of_sound_ = C;

    init_environment.temperature_ = t;
    init_environment.humidity_ = h;
    init_environment.pressure_ = p;
    init_environment.co2_mole_fraction_ = xc;

    init_environment_rate.temperature_rate_ = dC_dt;
    init_environment_rate.humidity_rate_ = dC_dh;
    init_environment_rate.pressure_rate_ = dC_dp;
    init_environment_rate.co2_mole_fraction_rate_ = dC_dxc;

    return init_speed_of_sound_;
  }


  double SpeedOfSound::QuickCompute(Environment &ambient_conitions) const {
    double t, h, p, xc, T, F, Psv, Xw;

    t  = ambient_conitions.temperature_;
    h  = ambient_conitions.humidity_;
    p  = ambient_conitions.pressure_;
    xc = ambient_conitions.co2_mole_fraction_;

    T   = theory::T(t);
    F   = theory::F(p, t);
    Psv = theory::Psv(T);
    Xw  = theory::Xw(h, F, Psv, p);

    return theory::C(t, p, Xw, xc);
  }


  double SpeedOfSound::Approximate(Environment &ambient_conitions) const {
    double approx_speed_of_sound, speed_of_sound_change;
    approx_speed_of_sound = init_speed_of_sound_;

    if (ambient_conitions.temperature_ != init_environment.temperature_) {
      speed_of_sound_change  = ambient_conitions.temperature_;
      speed_of_sound_change -= init_environment.temperature_;
      speed_of_sound_change *= init_environment_rate.temperature_rate_;
      approx_speed_of_sound += speed_of_sound_change;
    }
    if (ambient_conitions.humidity_ != init_environment.humidity_) {
      speed_of_sound_change  = ambient_conitions.humidity_;
      speed_of_sound_change -= init_environment.humidity_;
      speed_of_sound_change *= init_environment_rate.humidity_rate_;
      approx_speed_of_sound += speed_of_sound_change;
    }
    if (ambient_conitions.pressure_ != init_environment.pressure_) {
      speed_of_sound_change  = ambient_conitions.pressure_;
      speed_of_sound_change -= init_environment.pressure_;
      speed_of_sound_change *= init_environment_rate.pressure_rate_;
      approx_speed_of_sound += speed_of_sound_change;
    }
    if (ambient_conitions.co2_mole_fraction_ != init_environment.co2_mole_fraction_) {
      speed_of_sound_change  = ambient_conitions.co2_mole_fraction_;
      speed_of_sound_change -= init_environment.co2_mole_fraction_;
      speed_of_sound_change *= init_environment_rate.co2_mole_fraction_rate_;
      approx_speed_of_sound += speed_of_sound_change;
    }

    return approx_speed_of_sound;
  }
}
