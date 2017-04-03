#include "beagleController.h"

int readAnalog(int number){
   stringstream ss;
   ss << PATH_ADC << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}

bool getRotateControl(){
  return getGpioValue(PANIC_BUTTON_GPIO);
}

bool getMoveLeftControl();
bool getMoveRightControl();
float getLightFactorControl();

void startValuesUpdater();
void valuesUpdater();
