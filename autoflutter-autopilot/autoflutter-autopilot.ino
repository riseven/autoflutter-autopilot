#include "Avionics.h"

Avionics avionics;

void setup()
{
  avionics.setup();
}

void loop()
{
  avionics.update();
}
