// speed_of_sound.h
#include "speed_of_sound_theory.h"

#ifndef SPEED_OF_SOUND_H_
#define SPEED_OF_SOUND_H_

namespace speedofsound {
  class Environment {
    public:
      Environment();
      bool ValidateTemperature() const;
      bool ValidateHumidity() const;
      bool ValidatePressure() const;
      bool ValidateCO2MoleFraction() const;
      bool ValidateEnvironment() const;
      double temperature_, humidity_, pressure_, co2_mole_fraction_;
  };
  class EnvironmentRate {
    public:
      EnvironmentRate();
      double temperature_rate_, humidity_rate_, pressure_rate_, co2_mole_fraction_rate_;
  };


  class SpeedOfSound {
    public:
      SpeedOfSound();
      SpeedOfSound(Environment ambient_conitions);
      Environment GetInitEnvironment() const;
      EnvironmentRate GetInitEnvironmentRate() const;
      double Compute(Environment ambient_conitions);
      double QuickCompute(Environment ambient_conitions) const;
      double Approximate(Environment ambient_conitions) const;

    private:
      double init_speed_of_sound_;
      Environment init_environment;
      EnvironmentRate init_environment_rate;
  };
}

#endif
