#pragma once

#include "interfaces.h"

class Radio_Interface
{
public:
  Radio_Interface();
  void setup();
  void read(Radio_Data &radio_data);
};
