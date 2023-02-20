#include "interfaces.h"

State state;

void read_radio(RadioData &radio_data)
{
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
  }

  read_sensors(sensor_data);
  process_state(state, sensor_data);
  autopilot(state, actuators);
  send_actuators(actuators);
}
