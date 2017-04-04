#ifndef _BEAGLE_CONTROLLER_
#define _BEAGLE_CONTROLLER_

#include <iostream>
#include <thread>

#define MAX_POTENCIOMETER 4095
#define MAX_LDR 4095
#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"
//The ports of the ADC hardware
#define POTENCIOMETER_PORT 1
#define LIGHT_PORT 3
//The GPIO id of the button
#define BUTTON_GPIO 47;
//A value smaller than the tolerance will be ignored
#define POTENCIOMETER_TOLERANCE 0.01
#define LIGHT_TOLERANCE 0.1

class BeagleController{
public:
  BeagleController();
  ~BeagleController();

  //returns the current command
  static int getCommand();
  //Values to interpret the return of getCommand():
  static int no_command = 0;
  //A movement to the right
  static int right = 1;
  //A movement to the left
  static int left = 2;
  //The light on the LDR decreased
  static int shadow = 3;
  //The button has been pressed
  static int button = 4;

private:
  //flag to continue the updating of the values
  bool keepUpdating;

  //The range of the following values is 0.0 <= x <= 1.0 (percentage)
  float old_potenciometer;
  float potenciometer;
  float old_lightFactor;
  float lightFactor;
  //
  bool old_buttonValue;
  bool buttonValue;

  //static instance of the controller to be used by getCommand
  static BeagleController* _instance = NULL;

  //true if the current values in...
  // ...old_button and button mean that the user pressed them
  bool getRotateControl();
  //...old_potenciometer and potenciometer mean that the user
  //turned the potenciometer to the left
  bool getMoveLeftControl();
  //...old_potenciometer and potenciometer mean that the user
  //turned the potenciometer to the right
  bool getMoveRightControl();
  //...old_lightFactor and lightFactor mean that the LDR sensor
  //was in the light, but now is under a shadow
  bool getLightFactorControl();

  //reads an analog port
  static int readAnalog(int number);

  //starts to update the values
  void startValuesUpdater();
  //callback to update the values
  void valuesUpdater();
  void stopValuesUpdater();
};

#endif
