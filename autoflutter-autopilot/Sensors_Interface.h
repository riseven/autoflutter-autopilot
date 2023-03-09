#pragma once

#include "interfaces.h"

class Sensors_Interface
{
public:
  Sensors_Interface();
  void setup();
  void read(Sensor_Data &sensor_data);
};
