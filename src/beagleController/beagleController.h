#ifndef _BEAGLE_CONTROLLER_
#define _BEAGLE_CONTROLLER_

#include <iostream>
#include <thread>

#define POTENCIOMETER_PORT 1
#define POTENCIOMETER_PORT 3
#define MAX_POTENCIOMETER 4095
#define MAX_LDR 4095
#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"
#define PANIC_BUTTON_GPIO 47;

int potenciometer_value;

bool getRotateControl();
bool getMoveLeftControl();
bool getMoveRightControl();
float getLightFactorControl();

int readAnalog(int number);

void startValuesUpdater();
void valuesUpdater();
#endif
