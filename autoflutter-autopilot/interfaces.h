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
};

class State
{
public:
  double h;
  double pitch;
  double airspeed;
  double phi;
  double p;
  double chi;
};

class Actuators
{
public:
  double delta_e;
  double thrust;
  double pitch;
  double delta_a;
};

class AutopilotState
{
public:
  bool is_enabled = false;
  double set_h;
  double set_airspeed;
  double h_hold;
  double set_chi;
};