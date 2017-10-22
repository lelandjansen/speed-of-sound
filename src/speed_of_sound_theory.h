// speed_of_sound_theory.h
#include <cmath>

#ifndef SPEED_OF_SOUND_THEORY_H_
#define SPEED_OF_SOUND_THEORY_H_

namespace speedofsound {
namespace theory {
static constexpr double kStdTemperature = 20.0;
static constexpr double kStdHumidity = 0.5;
static constexpr double kStdPressure = 101325.0;
static constexpr double kStdCO2MoleFraction = 0.000314;

static constexpr double kMinTemperature = 0.0;
static constexpr double kMinHumidity = 0.0;
static constexpr double kMinPressure = 75000.0;
static constexpr double kMinXwPressure = 60000.0;
static constexpr double kMinCO2MoleFraction = 0.0;

static constexpr double kMaxTemperature = 30.0;
static constexpr double kMaxHumidity = 1.0;
static constexpr double kMaxPressure = 102000.0;
static constexpr double kMaxXwPressure = 110000.0;
static constexpr double kMaxCO2MoleFraction = 0.01;

double T(double t);
double dT_dt();

double F(double p, double t);
double dF_dp();
double dF_dt(double t);

double Psv(double T);
double dPsv_dt(double T);

double Xw(double h, double F, double Psv, double p);
double dXw_dh(double F, double Psv, double p);
double dXw_dF(double h, double Psv, double p);
double dXw_dPsv(double h, double F, double p);
double dXw_dp(double h, double F, double Psv, double p);

double C(double t, double p, double Xw, double xc);
double dC_dt(double t, double p, double Xw, double xc, double dXw_dF,
             double dF_dt, double dXw_dPsv, double dPsv_dt);
double dC_dXw(double t, double p, double Xw, double xc);
double dC_dxc(double t, double p, double Xw, double xc);
double dC_dp(double t, double p, double Xw, double xc, double dXw_dp);
double dC_dh(double dC_dXw, double dXw_dh);

static constexpr double k00 = 3.315024000e+02;
static constexpr double k01 = 6.030550000e-01;
static constexpr double k02 = -5.280000000e-04;
static constexpr double k03 = 5.147193500e+01;
static constexpr double k04 = 1.495874000e-01;
static constexpr double k05 = -7.820000000e-04;
static constexpr double k06 = -1.820000000e-07;
static constexpr double k07 = 3.730000000e-08;
static constexpr double k08 = -2.930000000e-10;
static constexpr double k09 = -8.520931000e+01;
static constexpr double k10 = -2.285250000e-01;
static constexpr double k11 = 5.910000000e-05;
static constexpr double k12 = -2.835149000e+00;
static constexpr double k13 = -2.150000000e-13;
static constexpr double k14 = 2.917976200e+01;
static constexpr double k15 = 4.860000000e-04;
static constexpr double k16 = 1.000620000e+00;
static constexpr double k17 = 3.140000000e-08;
static constexpr double k18 = 5.600000000e-07;
static constexpr double k19 = 1.281180500e-05;
static constexpr double k20 = -1.950987400e-02;
static constexpr double k21 = 3.404926034e+01;
static constexpr double k22 = -6.353631100e+03;
}  // namespace theory
}  // namespace speedofsound

#endif
