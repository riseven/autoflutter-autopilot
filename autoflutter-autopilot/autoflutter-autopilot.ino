#include "interfaces.h"
#include "PID.h"

State state;
PID pid_altitude;
PID pid_pitch;
AutopilotState autopilot_state;

void read_radio(RadioData &radio_data)
{
}

void enable_autopilot(SensorData &sensor_data)
{
  if (!autopilot_state.is_enabled)
  {
    autopilot_state.is_enabled = true;
    autopilot_state.set_h = sensor_data.h;
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

void autopilot(State &state, Actuators &actuators)
{
  double theta_c = pid_altitude.calculate(autopilot_state.set_h, state.h);
  double delta_e = pid_pitch.calculate(theta_c, state.theta);

  actuators.delta_e = delta_e;
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

  enable_autopilot(sensor_data);
  read_sensors(sensor_data);
  process_state(state, sensor_data);
  autopilot(state, actuators);
  send_actuators(actuators);
}
