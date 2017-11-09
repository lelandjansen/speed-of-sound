#include "speed-of-sound-theory.h"

#include <cmath>

namespace speedofsound {

namespace theory {

namespace {

const double k00 = 3.315024000e+02;
const double k01 = 6.030550000e-01;
const double k02 = -5.280000000e-04;
const double k03 = 5.147193500e+01;
const double k04 = 1.495874000e-01;
const double k05 = -7.820000000e-04;
const double k06 = -1.820000000e-07;
const double k07 = 3.730000000e-08;
const double k08 = -2.930000000e-10;
const double k09 = -8.520931000e+01;
const double k10 = -2.285250000e-01;
const double k11 = 5.910000000e-05;
const double k12 = -2.835149000e+00;
const double k13 = -2.150000000e-13;
const double k14 = 2.917976200e+01;
const double k15 = 4.860000000e-04;
const double k16 = 1.000620000e+00;
const double k17 = 3.140000000e-08;
const double k18 = 5.600000000e-07;
const double k19 = 1.281180500e-05;
const double k20 = -1.950987400e-02;
const double k21 = 3.404926034e+01;
const double k22 = -6.353631100e+03;

}  // namespace

auto T(const double t) -> double { return t + 273.15; }

auto dT_dt() -> double { return 1.0; }

auto F(const double p, const double t) -> double {
  return k16 + k17 * p + k18 * t * t;
}

auto dF_dp() -> double { return k17; }

auto dF_dt(const double t) -> double { return 2.0 * k18 * t; }

auto Psv(const double T) -> double {
  auto Psv = k19 * T * T;
  Psv += k20 * T;
  Psv += k21;
  Psv += k22 / T;
  return exp(Psv);
}

auto dPsv_dt(const double T) -> double {
  auto dPsv_dt = 2.0 * k19 * T + k20 - k22 / (T * T);
  dPsv_dt *= Psv(T);
  dPsv_dt *= dT_dt();
  return dPsv_dt;
}

auto Xw(const double h, const double F, const double Psv, const double p)
    -> double {
  return h * F * Psv / p;
}

auto dXw_dh(const double F, const double Psv, const double p) -> double {
  return F * Psv / p;
}

auto dXw_dF(const double h, const double Psv, const double p) -> double {
  return h * Psv / p;
}

auto dXw_dPsv(const double h, const double F, const double p) -> double {
  return h * F / p;
}

auto dXw_dp(const double h, const double F, const double Psv, const double p)
    -> double {
  auto dXw_dp = -h * F * Psv / (p * p);
  dXw_dp += h * dF_dp() * Psv / p;
  return dXw_dp;
}

auto C(const double t, const double p, const double Xw, const double xc)
    -> double {
  auto C = k00 + k01 * t + k02 * t * t;
  C += (k03 + k04 * t + k05 * t * t) * Xw;
  C += (k06 + k07 * t + k08 * t * t) * p;
  C += (k09 + k10 * t + k11 * t * t) * xc;
  C += k12 * Xw * Xw;
  C += k13 * p * p;
  C += k14 * xc * xc;
  C += k15 * Xw * p * xc;
  return C;
}

auto dC_dt(const double t, const double p, const double Xw, const double xc,
           const double dXw_dF, const double dF_dt, const double dXw_dPsv,
           const double dPsv_dt) -> double {
  auto dC_dt = k01 + 2.0 * k02 * t;
  dC_dt += (k04 + 2.0 * k05 * t) * Xw;
  dC_dt += (k03 + k04 * t + k05 * t * t) * dXw_dPsv * dPsv_dt;
  dC_dt += (k03 + k04 * t + k05 * t * t) * dXw_dF * dF_dt;
  dC_dt += (k07 + 2.0 * k08 * t) * p;
  dC_dt += (k10 + 2.0 * k11 * t) * xc;
  dC_dt += 2.0 * k12 * Xw * dXw_dPsv * dPsv_dt;
  dC_dt += 2.0 * k12 * Xw * dXw_dF * dF_dt;
  dC_dt += k15 * p * xc * dXw_dPsv * dPsv_dt;
  dC_dt += k15 * p * xc * dXw_dF * dF_dt;
  return dC_dt;
}

auto dC_dXw(const double t, const double p, const double Xw, const double xc)
    -> double {
  auto dC_dXw = k03 + k04 * t + k05 * t * t;
  dC_dXw += 2.0 * k12 * Xw;
  dC_dXw += k15 * xc * p;
  return dC_dXw;
}

auto dC_dp(const double t, const double p, const double Xw, const double xc,
           const double dXw_dp) -> double {
  auto dC_dp = (k03 + k04 * t + k05 * t * t) * dXw_dp;
  dC_dp += k06 + k07 * t + k08 * t * t;
  dC_dp += 2.0 * k12 * Xw * dXw_dp;
  dC_dp += 2.0 * k13 * p;
  dC_dp += k15 * dXw_dp * p * xc;
  dC_dp += k15 * Xw * xc;
  return dC_dp;
}

auto dC_dxc(const double t, const double p, const double Xw, const double xc)
    -> double {
  auto dC_dxc = k09 + k10 * t + k11 * t * t;
  dC_dxc += 2.0 * k14 * xc;
  dC_dxc += k15 * p * Xw;
  return dC_dxc;
}

auto dC_dh(const double dC_dXw, const double dXw_dh) -> double {
  return dC_dXw * dXw_dh;
}

}  // namespace theory

}  // namespace speedofsound
