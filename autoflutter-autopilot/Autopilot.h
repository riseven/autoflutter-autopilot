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
  Radio_Interface _radio_interface;
  RadioData _radio_data;
};
