#pragma once

#include "interfaces.h"

class State_Processor
{
public:
  State_Processor();
  void setup();
  void update(State &state, Sensor_Data &sensor_data);
};
