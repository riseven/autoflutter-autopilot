#include "Autopilot.h"

// TODO: Refactor parameters away
const double H_HOLD = 1;
const double THROTTLE_TRIM_VALUE = 0.5;

Autopilot::Autopilot()
{
}

void Autopilot::setup()
{
}

void Autopilot::enable(State &state)
{
  if (!_is_enabled)
  {
    _is_enabled = true;
    _set_h = state.h;
    _set_airspeed = state.airspeed;
    _h_hold = H_HOLD;
    _set_chi = state.chi;
    // TODO: Any more things we need to set up
  }
}

void Autopilot::disable()
{
  if (_is_enabled)
  {
    _is_enabled = false;
    // TODO: Any more things we need to tear down
  }
}

void Autopilot::update(State &state, Actuators &actuators)
{
  // Lateral-directional Autopilot
  double commanded_phi;

  commanded_phi = _course_hold.calculate(_set_chi, state.chi);
  actuators.delta_a = _roll_attitude.calculate(commanded_phi, state.phi) -
                      _roll_rate_damping.calculate(state.p, 0.);

  // Longitudinal Autopilot
  bool is_in_descend = state.h > _set_h + _h_hold;
  bool is_in_ascend = state.h < _set_h - _h_hold;
  bool is_in_hold = !is_in_ascend && !is_in_descend;

  double commanded_pitch;

  if (is_in_descend)
  {
    actuators.thrust = 0.;
    commanded_pitch = _airspeed_hold_using_commanded_pitch.calculate(
        _set_airspeed,
        state.airspeed);
  }
  else if (is_in_hold)
  {
    actuators.thrust = THROTTLE_TRIM_VALUE +
                       _airspeed_hold_using_throttle.calculate(
                           _set_airspeed,
                           state.airspeed);
    commanded_pitch = _altitude_hold_using_commanded_pitch.calculate(
        _set_h,
        state.h);
  }
  else if (is_in_ascend)
  {
    actuators.thrust = 1.;
    commanded_pitch = _airspeed_hold_using_commanded_pitch.calculate(
        _set_airspeed,
        state.airspeed);
  }

  actuators.pitch = _pitch_attitude_hold.calculate(commanded_pitch, state.pitch);
}