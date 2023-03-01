#pragma once

class RadioData
{
public:
  bool is_radio_on;
  bool is_auto_pilot_on;
  // And the rest of signals from radio
  // ...
};

class SensorData
{
public:
  double h;
  // Whatever it is that we have sensors for
};

class State
{
public:
  // Whatever
  double h;
  double pitch;
  double airspeed;
};

class Actuators
{
public:
  // Whatever
  double delta_e;
  double thrust;
  double pitch;
};

class AutopilotState
{
public:
  bool is_enabled = false;
  double set_h;
  double set_airspeed;
  double h_hold;
};