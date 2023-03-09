#pragma once

#include "interfaces.h"
#include "Radio_Interface.h"
#include "Actuators_Interface.h"

class Autopilot
{
public:
  Autopilot();
  void setup();
  void update();

private:
  void failsafe();
  void fill_actuators_from_radio();

  Radio_Interface _radio_interface;
  Actuators_Interface _actuators_interface;

  Radio_Data _radio_data;
  Actuators _actuators;
};
