#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

namespace speedofsound {

class Environment {
 public:
  Environment();
  auto ValidateTemperature() const -> bool;
  auto ValidateHumidity() const -> bool;
  auto ValidatePressure() const -> bool;
  auto ValidateCO2MoleFraction() const -> bool;
  auto ValidateEnvironment() const -> bool;
  double temperature_;
  double humidity_;
  double pressure_;
  double co2_mole_fraction_;
};

class EnvironmentRate {
 public:
  EnvironmentRate();
  double temperature_rate_;
  double humidity_rate_;
  double pressure_rate_;
  double co2_mole_fraction_rate_;
};

}  // namespace speedofsound

#endif  // ENVIRONMENT_H_
