#include "speed-of-sound.h"

namespace speedofsound {

SpeedOfSound::SpeedOfSound() { SpeedOfSound::Compute(init_environment_); }

SpeedOfSound::SpeedOfSound(const Environment& ambient_conitions)
    : init_environment_(ambient_conitions),
      init_speed_of_sound_(Compute(ambient_conitions)) {}

auto SpeedOfSound::GetInitEnvironment() const -> Environment {
  return init_environment_;
}

auto SpeedOfSound::GetInitEnvironmentRate() const -> EnvironmentRate {
  return init_environment_rate_;
}

auto SpeedOfSound::Compute(const Environment& ambient_conitions) -> double {
  const auto t = ambient_conitions.temperature_;
  const auto h = ambient_conitions.humidity_;
  const auto p = ambient_conitions.pressure_;
  const auto xc = ambient_conitions.co2_mole_fraction_;
  const auto T = theory::T(t);
  const auto F = theory::F(p, t);
  const auto Psv = theory::Psv(T);
  const auto Xw = theory::Xw(h, F, Psv, p);
  const auto C = theory::C(t, p, Xw, xc);
  const auto dF_dt = theory::dF_dt(t);
  const auto dPsv_dt = theory::dPsv_dt(T);
  const auto dXw_dF = theory::dXw_dF(h, Psv, p);
  const auto dXw_dPsv = theory::dXw_dPsv(h, F, p);
  const auto dXw_dp = theory::dXw_dp(h, F, Psv, p);
  const auto dXw_dh = theory::dXw_dh(F, Psv, p);
  const auto dC_dt =
      theory::dC_dt(t, p, Xw, xc, dXw_dF, dF_dt, dXw_dPsv, dPsv_dt);
  const auto dC_dxc = theory::dC_dxc(t, p, Xw, xc);
  const auto dC_dp = theory::dC_dp(t, p, Xw, xc, dXw_dp);
  const auto dC_dXw = theory::dC_dXw(t, p, Xw, xc);
  const auto dC_dh = theory::dC_dh(dC_dXw, dXw_dh);
  init_speed_of_sound_ = C;
  init_environment_.temperature_ = t;
  init_environment_.humidity_ = h;
  init_environment_.pressure_ = p;
  init_environment_.co2_mole_fraction_ = xc;
  init_environment_rate_.temperature_rate_ = dC_dt;
  init_environment_rate_.humidity_rate_ = dC_dh;
  init_environment_rate_.pressure_rate_ = dC_dp;
  init_environment_rate_.co2_mole_fraction_rate_ = dC_dxc;
  return init_speed_of_sound_;
}

auto SpeedOfSound::QuickCompute(const Environment& ambient_conitions) const
    -> double {
  const auto t = ambient_conitions.temperature_;
  const auto h = ambient_conitions.humidity_;
  const auto p = ambient_conitions.pressure_;
  const auto xc = ambient_conitions.co2_mole_fraction_;
  const auto T = theory::T(t);
  const auto F = theory::F(p, t);
  const auto Psv = theory::Psv(T);
  const auto Xw = theory::Xw(h, F, Psv, p);
  return theory::C(t, p, Xw, xc);
}

auto SpeedOfSound::Approximate(const Environment& ambient_conitions) const
    -> double {
  auto approx_speed_of_sound = init_speed_of_sound_;
  auto speed_of_sound_change = 0.0;
  if (ambient_conitions.temperature_ != init_environment_.temperature_) {
    speed_of_sound_change = ambient_conitions.temperature_;
    speed_of_sound_change -= init_environment_.temperature_;
    speed_of_sound_change *= init_environment_rate_.temperature_rate_;
    approx_speed_of_sound += speed_of_sound_change;
  }
  if (ambient_conitions.humidity_ != init_environment_.humidity_) {
    speed_of_sound_change = ambient_conitions.humidity_;
    speed_of_sound_change -= init_environment_.humidity_;
    speed_of_sound_change *= init_environment_rate_.humidity_rate_;
    approx_speed_of_sound += speed_of_sound_change;
  }
  if (ambient_conitions.pressure_ != init_environment_.pressure_) {
    speed_of_sound_change = ambient_conitions.pressure_;
    speed_of_sound_change -= init_environment_.pressure_;
    speed_of_sound_change *= init_environment_rate_.pressure_rate_;
    approx_speed_of_sound += speed_of_sound_change;
  }
  if (ambient_conitions.co2_mole_fraction_ !=
      init_environment_.co2_mole_fraction_) {
    speed_of_sound_change = ambient_conitions.co2_mole_fraction_;
    speed_of_sound_change -= init_environment_.co2_mole_fraction_;
    speed_of_sound_change *= init_environment_rate_.co2_mole_fraction_rate_;
    approx_speed_of_sound += speed_of_sound_change;
  }
  return approx_speed_of_sound;
}

}  // namespace speedofsound
