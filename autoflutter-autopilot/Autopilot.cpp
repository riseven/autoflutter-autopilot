#include "Autopilot.h"

Autopilot::Autopilot()
{
}

void Autopilot::setup()
{
}

void Autopilot::update()
{
  // SensorData sensor_data;
  // Actuators actuators;

  _radio_interface.read(_radio_data);

  if (_radio_data.is_radio_on)
  {
    failsafe();
    return;
  }

  if (!_radio_data.is_auto_pilot_on)
  {
    fill_actuators_from_radio();
    // send_actuators(actuators);
    return;
  }

  // read_sensors(sensor_data);
  // process_state(state, sensor_data);
  // enable_autopilot(state);
  // _autopilot(state, autopilot_state, actuators);
  // send_actuators(actuators);
}

void Autopilot::failsafe()
{
  // TODO: Implement failsafe behaviour here
}

void Autopilot::fill_actuators_from_radio()
{
  // TODO: Fill in values for Actuators based on the signals from Radio (manual control)
}
