#include "beagleController.h"

BeagleController::BeagleController(){
  startValuesUpdater();
}

BeagleController::~BeagleController(){
  stopValuesUpdater();
}

int BeagleController::readAnalog(int number){
   stringstream ss;
   ss << PATH_ADC << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}

bool BeagleController::getRotateControl();
bool BeagleController::getMoveLeftControl();
bool BeagleController::getMoveRightControl();
bool BeagleController::getLightFactorControl();

void BeagleController::startValuesUpdater(){
  keepUpdating = true;
  //TODO
}
void BeagleController::stopValuesUpdater(){
  keepUpdating = false;
}

void BeagleController::valuesUpdater(){
  while(keepUpdating)
  {
    //TODO
    //std::this_thread::sleep_for(std::chrono::milliseconds{100});
  }
}

int BeagleController::getCommand(){
  if(_instance == NULL){
    _instance = new BeagleController();
  }

  if(_instance.getRotateControl()){
    return BeagleController::button;
  }else if (_instance.getMoveLeftControl()){
    return BeagleController::left;
  }else if (_instance.getMoveRightControl()){
    return BeagleController::right;
  }else if (_instance.getLightFactorControl()){
    return BeagleController::shadow;
  }else{
    return BeagleController::no_command;
  }
}
