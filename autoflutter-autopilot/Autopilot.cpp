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

  // if (radio_data.is_radio_on)
  // {
  //   failsafe();
  //   return;
  // }

  // if (!radio_data.is_auto_pilot_on)
  // {
  //   actuators_from_radio(radio_data, actuators);
  //   send_actuators(actuators);
  //   return;
  // }

  // read_sensors(sensor_data);
  // process_state(state, sensor_data);
  // enable_autopilot(state);
  // _autopilot(state, autopilot_state, actuators);
  // send_actuators(actuators);
}
