#pragma once

class PID
{
  PID(double dt, double max, double min, double Kp, double Kd, double Ki);
  double calculate(double setpoint, double pv);

private:
  double dt;
  double max;
  double min;
  double Kp;
  double Kd;
  double Ki;
  double integral;
  double pre_error;
};
