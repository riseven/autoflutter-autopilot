#pragma once

#include "interfaces.h"
#include "Radio_Interface.h"

class Autopilot
{
public:
  Autopilot();
  void setup();
  void update();

private:
  void failsafe();

  Radio_Interface _radio_interface;
  Radio_Data _radio_data;
};
