#pragma once

#include "interfaces.h"
#include "PID.h"

class Autopilot
{
public:
  Autopilot();
  void setup();
  void enable(State &state);
  void disable();
  void update(State &state, Actuators &actuators);

private:
  PID _roll_attitude;
  PID _roll_rate_damping;
  PID _course_hold;

  PID _pitch_attitude_hold;
  PID _altitude_hold_using_commanded_pitch;
  PID _airspeed_hold_using_commanded_pitch;
  PID _airspeed_hold_using_throttle;

  bool _is_enabled = false;
  double _set_h;
  double _set_airspeed;
  double _h_hold;
  double _set_chi;
};
