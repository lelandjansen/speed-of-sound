// speed_of_sound_theory.cc
#include "speed_of_sound_theory.h"

namespace speedofsound {
namespace theory {
double T(double t) { return t + 273.15; }

double dT_dt() { return 1.0; }

double F(double p, double t) { return k16 + k17 * p + k18 * t * t; }

double dF_dp() { return k17; }

double dF_dt(double t) { return 2 * k18 * t; }

double Psv(double T) {
  double Psv;
  Psv = k19 * T * T;
  Psv += k20 * T;
  Psv += k21;
  Psv += k22 / T;
  Psv = exp(Psv);
  return Psv;
}

double dPsv_dt(double T) {
  double dPsv_dt;
  dPsv_dt = 2 * k19 * T + k20 - k22 / (T * T);
  dPsv_dt *= Psv(T);
  dPsv_dt *= dT_dt();
  return dPsv_dt;
}

double Xw(double h, double F, double Psv, double p) { return h * F * Psv / p; }

double dXw_dh(double F, double Psv, double p) { return F * Psv / p; }

double dXw_dF(double h, double Psv, double p) { return h * Psv / p; }

double dXw_dPsv(double h, double F, double p) { return h * F / p; }

double dXw_dp(double h, double F, double Psv, double p) {
  double dXw_dp;
  dXw_dp = -h * F * Psv / (p * p);
  dXw_dp += h * dF_dp() * Psv / p;
  return dXw_dp;
}

double C(double t, double p, double Xw, double xc) {
  double C;
  C = k00 + k01 * t + k02 * t * t;
  C += (k03 + k04 * t + k05 * t * t) * Xw;
  C += (k06 + k07 * t + k08 * t * t) * p;
  C += (k09 + k10 * t + k11 * t * t) * xc;
  C += k12 * Xw * Xw;
  C += k13 * p * p;
  C += k14 * xc * xc;
  C += k15 * Xw * p * xc;
  return C;
}

double dC_dt(double t, double p, double Xw, double xc, double dXw_dF,
             double dF_dt, double dXw_dPsv, double dPsv_dt) {
  double dC_dt;
  dC_dt = k01 + 2 * k02 * t;
  dC_dt += (k04 + 2 * k05 * t) * Xw;
  dC_dt += (k03 + k04 * t + k05 * t * t) * dXw_dPsv * dPsv_dt;
  dC_dt += (k03 + k04 * t + k05 * t * t) * dXw_dF * dF_dt;
  dC_dt += (k07 + 2 * k08 * t) * p;
  dC_dt += (k10 + 2 * k11 * t) * xc;
  dC_dt += 2 * k12 * Xw * dXw_dPsv * dPsv_dt;
  dC_dt += 2 * k12 * Xw * dXw_dF * dF_dt;
  dC_dt += k15 * p * xc * dXw_dPsv * dPsv_dt;
  dC_dt += k15 * p * xc * dXw_dF * dF_dt;
  return dC_dt;
}

double dC_dXw(double t, double p, double Xw, double xc) {
  double dC_dXw;
  dC_dXw = k03 + k04 * t + k05 * t * t;
  dC_dXw += 2 * k12 * Xw;
  dC_dXw += k15 * xc * p;
  return dC_dXw;
}

double dC_dp(double t, double p, double Xw, double xc, double dXw_dp) {
  double dC_dp;
  dC_dp = (k03 + k04 * t + k05 * t * t) * dXw_dp;
  dC_dp += k06 + k07 * t + k08 * t * t;
  dC_dp += 2 * k12 * Xw * dXw_dp;
  dC_dp += 2 * k13 * p;
  dC_dp += k15 * dXw_dp * p * xc;
  dC_dp += k15 * Xw * xc;
  return dC_dp;
}

double dC_dxc(double t, double p, double Xw, double xc) {
  double dC_dxc;
  dC_dxc = k09 + k10 * t + k11 * t * t;
  dC_dxc += 2 * k14 * xc;
  dC_dxc += k15 * p * Xw;
  return dC_dxc;
}

double dC_dh(double dC_dXw, double dXw_dh) { return dC_dXw * dXw_dh; }
}  // namespace theory
}  // namespace speedofsound
