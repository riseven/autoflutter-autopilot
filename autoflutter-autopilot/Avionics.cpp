#include "Avionics.h"

Avionics::Avionics()
{
}

void Avionics::setup()
{
  _radio_interface.setup();
  _actuators_interface.setup();
  _sensors_interface.setup();
  _state_processor.setup();
  _autopilot.setup();
}

void Avionics::update()
{
  _radio_interface.read(_radio_data);

  if (!_radio_data.is_radio_on)
  {
    failsafe();
    return;
  }

  if (!_radio_data.is_auto_pilot_on)
  {
    _autopilot.disable();
    fill_actuators_from_radio();
  }
  else
  {
    _sensors_interface.read(_sensor_data);
    _state_processor.update(_state, _sensor_data);
    _autopilot.enable(_state);
    _autopilot.update(_state, _actuators);
  }

  _actuators_interface.send(_actuators);
}

void Avionics::failsafe()
{
  // TODO: Implement failsafe behaviour here
}

void Avionics::fill_actuators_from_radio()
{
  // TODO: Fill in values for Actuators based on the signals from Radio (manual control)
}
