#include "environment.h"

#include "speed-of-sound-theory.h"

namespace speedofsound {

Environment::Environment()
    : temperature_(theory::kStdTemperature),
      humidity_(theory::kStdHumidity),
      pressure_(theory::kStdPressure),
      co2_mole_fraction_(theory::kStdCO2MoleFraction) {}

auto Environment::ValidateTemperature() const -> bool {
  return theory::kMinTemperature <= temperature_ &&
         temperature_ <= theory::kMaxTemperature;
}

auto Environment::ValidateHumidity() const -> bool {
  return theory::kMinHumidity <= humidity_ && humidity_ <= theory::kMaxHumidity;
}

auto Environment::ValidatePressure() const -> bool {
  return theory::kMinPressure <= pressure_ && pressure_ <= theory::kMaxPressure;
}

auto Environment::ValidateCO2MoleFraction() const -> bool {
  return theory::kMinCO2MoleFraction <= co2_mole_fraction_ &&
         co2_mole_fraction_ <= theory::kMaxCO2MoleFraction;
}

auto Environment::ValidateEnvironment() const -> bool {
  return ValidateTemperature() && ValidateHumidity() && ValidatePressure() &&
         ValidateCO2MoleFraction();
}

EnvironmentRate::EnvironmentRate()
    : temperature_rate_(0.0),
      humidity_rate_(0.0),
      pressure_rate_(0.0),
      co2_mole_fraction_rate_(0.0) {}

}  // namespace speedofsound
