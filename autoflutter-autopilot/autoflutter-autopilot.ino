#include "interfaces.h"
#include "PID.h"

// TODO: Refactor parameters away
const double H_HOLD = 1;
const double THROTTLE_TRIM_VALUE = 0.5;

State state;

// TODO: Pass the PID parameters
PID roll_attitude;
PID roll_rate_damping;
PID course_hold;

PID pitch_attitude_hold;
PID altitude_hold_using_commanded_pitch;
PID airspeed_hold_using_commanded_pitch;
PID airspeed_hold_using_throttle;

AutopilotState autopilot_state;

void read_radio(RadioData &radio_data)
{
}

void enable_autopilot(State &state)
{
  if (!autopilot_state.is_enabled)
  {
    autopilot_state.is_enabled = true;
    autopilot_state.set_h = state.h;
    autopilot_state.set_airspeed = state.airspeed;
    autopilot_state.h_hold = H_HOLD;
    autopilot_state.set_chi = state.chi;
    // TODO: Any more things we need to set up
  }
}

void disable_autopilot()
{
  if (autopilot_state.is_enabled)
  {
    autopilot_state.is_enabled = false;
    // TODO: Any more things we need to tear down
  }
}

void failsafe()
{
}

void actuators_from_radio(RadioData &radio_data, Actuators &actuators)
{
}

void read_sensors(SensorData &sensor_data)
{
}

void process_state(State &state, SensorData &sensor_data)
{
}

void autopilot(State &state, AutopilotState &autopilot_state, Actuators &actuators)
{
  // Lateral-directional Autopilot
  double commanded_phi;

  commanded_phi = course_hold.calculate(autopilot_state.set_chi, state.chi);
  actuators.delta_a = roll_attitude.calculate(commanded_phi, state.phi) -
                      roll_rate_damping.calculate(state.p, 0.);

  // Longitudinal Autopilot
  bool is_in_descend = state.h > autopilot_state.set_h + autopilot_state.h_hold;
  bool is_in_ascend = state.h < autopilot_state.set_h - autopilot_state.h_hold;
  bool is_in_hold = !is_in_ascend && !is_in_descend;

  double commanded_pitch;

  if (is_in_descend)
  {
    actuators.thrust = 0.;
    commanded_pitch = airspeed_hold_using_commanded_pitch.calculate(
        autopilot_state.set_airspeed,
        state.airspeed);
  }
  else if (is_in_hold)
  {
    actuators.thrust = THROTTLE_TRIM_VALUE +
                       airspeed_hold_using_throttle.calculate(
                           autopilot_state.set_airspeed,
                           state.airspeed);
    commanded_pitch = altitude_hold_using_commanded_pitch.calculate(
        autopilot_state.set_h,
        state.h);
  }
  else if (is_in_ascend)
  {
    actuators.thrust = 1.;
    commanded_pitch = airspeed_hold_using_commanded_pitch.calculate(
        autopilot_state.set_airspeed,
        state.airspeed);
  }

  actuators.pitch = pitch_attitude_hold.calculate(commanded_pitch, state.pitch);
}

void send_actuators(Actuators &actuators)
{
}

void setup()
{
  // put your setup code here, to run once:
}

void loop()
{
  RadioData radio_data;
  SensorData sensor_data;
  Actuators actuators;

  read_radio(radio_data);

  if (radio_data.is_radio_on)
  {
    failsafe();
    return;
  }

  if (!radio_data.is_auto_pilot_on)
  {
    actuators_from_radio(radio_data, actuators);
    send_actuators(actuators);
    return;
  }

  read_sensors(sensor_data);
  process_state(state, sensor_data);
  enable_autopilot(state);
  autopilot(state, autopilot_state, actuators);
  send_actuators(actuators);
}
