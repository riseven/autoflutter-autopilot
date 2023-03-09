#pragma once

#include "interfaces.h"

class Actuators_Interface
{
public:
  Actuators_Interface();
  void send(Actuators &actuators);
};
