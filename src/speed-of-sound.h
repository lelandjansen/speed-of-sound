#ifndef SPEED_OF_SOUND_H_
#define SPEED_OF_SOUND_H_

#include "speed-of-sound-theory.h"

#include "environment.h"

namespace speedofsound {

class SpeedOfSound {
 public:
  SpeedOfSound();
  SpeedOfSound(const Environment& ambient_conitions);
  auto GetInitEnvironment() const -> Environment;
  auto GetInitEnvironmentRate() const -> EnvironmentRate;
  auto Compute(const Environment& ambient_conitions) -> double;
  auto QuickCompute(const Environment& ambient_conitions) const -> double;
  auto Approximate(const Environment& ambient_conitions) const -> double;

 private:
  double init_speed_of_sound_;
  Environment init_environment_;
  EnvironmentRate init_environment_rate_;
};

}  // namespace speedofsound

#endif  // SPEED_OF_SOUND_H_
