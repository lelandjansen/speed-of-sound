# Speed of Sound
[![CircleCI](https://circleci.com/gh/lelandjansen/speed-of-sound.svg?style=svg)](https://circleci.com/gh/lelandjansen/speed-of-sound)
[![Coverage Status](https://coveralls.io/repos/github/lelandjansen/speed-of-sound/badge.svg)](https://coveralls.io/github/lelandjansen/speed-of-sound)

**Speed of Sound** is a library to efficiently compute the speed of sound in air. It is intended for use in embedded systems that require a high-precision computation of the speed of sound in air based a variety of ambient conditions.


## Contents
- [Quick facts](#quick-facts)
- [Environmental parameters](#environmental-parameters)
- [Usage](#usage)
 - [Example](#example)
- [Notes on notation](#notes-on-notation)
- [Testing](#testing)
- [Attributions](#attributions)


## Quick facts
- Computes the speed of sound in air based on temperature, relative humidity, pressure, and carbon dioxide mole fraction.
- Runtime of subsequent speed of sound computations reduced by 67.7% through the use of calculus linear approximations ([reference](https://github.com/lelandjansen/speed-of-sound/blob/master/test/speed_of_sound_test.cc#L312)).
- Approximation maintains precision of at least 0.05% with environmental factors varying up to 20% ([reference](https://github.com/lelandjansen/speed-of-sound/blob/master/test/speed_of_sound_test.cc#L275)).


## Environmental parameters
The speed of sound computation takes on the following parameters and is only valid in within the following range.

| Variable (units)                             | Minimum     | Default  | Maximum     |
| -------------------------------------------- | ----------- | -------- | ----------- |
| temperature (°C)                             | 0.0         | 20.0     | 30.0        |
| relative humidity (dimensionless)            | 0.0         | 0.5      | 1.0         |
| pressure (Pa)                                | 75000.0     | 101325.0 | 102000.0    |
| Carbon dioxide mole fraction (dimensionless) | 0.0         | 0.000314 | 0.01        |

**Note:** This library is intended for use with embedded systems and therefore does **not** throw an exception if passed an invalid quantity. Instead, methods are provided to validate that values are within the given constraints (see [Usage](#usage)).


## Usage
```C++
#include "speed_of_sound.h"
```

Create `Environment` object to hold ambient conditions (initializes values to default).
```C++
speedofsound::Environment ambient_conditions;
```

Access `Environment` object members.
```C++
ambient_conditions.temperature_;
ambient_conditions.humidity_;
ambient_conditions.pressure_;
ambient_conditions.co2_mole_fraction_;
```

Adjust environment variables.
```C++
ambient_conditions.temperature_ = 25.0;
...
```

Check if environmental parameters are within specified constraints (see Constraints for details).
```C++
bool is_valid;

// Validate individual parameters
is_valid = ambient_conditions.ValidateTemperature();
is_valid = ambient_conditions.ValidateHumidity();
is_valid = ambient_conditions.ValidatePressure();
is_valid = ambient_conditions.ValidateCO2MoleFraction();

// Validate all parameters
is_valid = ambient_conditions.ValidateEnvironment();
```

Create `SpeedOfSound` object and set initial conditions.
```C++
speedofsound::SpeedOfSound speed_of_sound(ambient_conditions);

speedofsound::SpeedOfSound speed_of_sound(); // Default Environment values
```

Compute speed of sound.
```C++
double sound_speed;

// Full computation, reset initial conditions
sound_speed = speed_of_sound.Compute(ambient_conditions);

// Full computation, do not reset initial conditions
sound_speed = speed_of_sound.QuickCompute(ambient_conditions);

// Linear approximation, do not reset initial conditions
sound_speed = speed_of_sound.Approximate(ambient_conditions);
```


### Example
```C++
#include <iostream>
#include "speed_of_sound.h"
#include "some_sensor.h"

int main() {
  speedofsound::Environment ambient_conditions;
  ambient_conditions.temperature_ = sensor::MeasureTemperature();

  // Initial "full" computation
  speedofsound::SpeedOfSound speed_of_sound(ambient_conditions);

  double sound_speed;
  const double distance = 100.0; // meters
  while (true) {
    ambient_conditions.temperature_ = sensor::MeasureTemperature();
    if (!ambient_conditions.ValidateTemperature()) break;

    sound_speed = speed_of_sound.Approximate(ambient_conditions);

    std::cout << "It would take a sound wave approximately " << \
                 distance/sound_speed << " seconds to travel " << \
                 distance << " meters." << std::endl;
  }

  return 0;
}
```


## Notes on notation
The following abbreviations are used in theory-related computations.

Lower-case variables (`t`, `h`, etc.) represent measured environmental parameters. Variables starting with an uppercase character (`C`, `Psv`, etc.) represent computed values.

| Variable          | Meaning                          | Units                    |
| ----------------- | -------------------------------- | ------------------------ |
| `C`               | speed of sound                   | meters per second (m/s)  |
| `t`               | temperature                      | Celsius (°C)             |
| `T`               | thermodynamic temperature        | Kelvin (K)               |
| `h`               | relative humidity                | fraction (dimensionless) |
| `xc`              | Carbon dioxide mole fraction     | fraction (dimensionless) |
| `p`               | pressure                         | Pascals (Pa)             |
| `Xw`              | mole fraction of water in air    | fraction (dimensionless) |
| `Psv`             | saturation vapor pressure        | Pascals (Pa)             |
| `F`               | Enhancement factor for moist air | dimensionless            |
| `k00`, `k01`, ... | experimental constants           | various                  |

`dy_dx` denotes the partial derivative of `y` with respect to `x`.


## Testing
Tests are written using [GoogleTest](https://github.com/google/googletest).

Run all tests:
```
$ test/test
```

## Attributions
The equation for computing the speed of sound in air uses Owen Cramer's research.

*J. Acoust. Soc. Am. 93, 2510 (1993); http://dx.doi.org/10.1121/1.405827*
