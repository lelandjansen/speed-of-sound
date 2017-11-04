#ifndef SPEED_OF_SOUND_THEORY_H_
#define SPEED_OF_SOUND_THEORY_H_

namespace speedofsound {

namespace theory {

const double kStdTemperature = 20.0;
const double kStdHumidity = 0.5;
const double kStdPressure = 101325.0;
const double kStdCO2MoleFraction = 0.000314;

const double kMinTemperature = 0.0;
const double kMinHumidity = 0.0;
const double kMinPressure = 75000.0;
const double kMinXwPressure = 60000.0;
const double kMinCO2MoleFraction = 0.0;

const double kMaxTemperature = 30.0;
const double kMaxHumidity = 1.0;
const double kMaxPressure = 102000.0;
const double kMaxXwPressure = 110000.0;
const double kMaxCO2MoleFraction = 0.01;

auto T(const double t) -> double;
auto dT_dt() -> double;

auto F(const double p, const double t) -> double;
auto dF_dp() -> double;
auto dF_dt(const double t) -> double;

auto Psv(const double T) -> double;
auto dPsv_dt(const double T) -> double;

auto Xw(const double h, const double F, const double Psv, const double p)
    -> double;
auto dXw_dh(const double F, const double Psv, const double p) -> double;
auto dXw_dF(const double h, const double Psv, const double p) -> double;
auto dXw_dPsv(const double h, const double F, const double p) -> double;
auto dXw_dp(const double h, const double F, const double Psv, const double p)
    -> double;

auto C(const double t, const double p, const double Xw, const double xc)
    -> double;
auto dC_dt(const double t, const double p, const double Xw, const double xc,
           const double dXw_dF, const double dF_dt, const double dXw_dPsv,
           const double dPsv_dt) -> double;
auto dC_dXw(const double t, const double p, const double Xw, const double xc)
    -> double;
auto dC_dxc(const double t, const double p, const double Xw, const double xc)
    -> double;
auto dC_dp(const double t, const double p, const double Xw, const double xc,
           const double dXw_dp) -> double;
auto dC_dh(const double dC_dXw, const double dXw_dh) -> double;

}  // namespace theory

}  // namespace speedofsound

#endif  // SPEED_OF_SOUND_THEORY_H_
