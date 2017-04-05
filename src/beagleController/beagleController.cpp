#include "beagleController.h"
#include <iostream>
using namespace std;
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

void BeagleController::startValuesUpdater(){
  old_potenciometer = potenciometer = readAnalog(POTENCIOMETER_PORT) / (float)MAX_POTENCIOMETER;
  keepUpdating = true;
  thread t = thread(&BeagleController::valuesUpdater, this);
  t.detach();
}
void BeagleController::stopValuesUpdater(){
  keepUpdating = false;
}

void BeagleController::valuesUpdater(){
  while(keepUpdating)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
    float p = readAnalog(POTENCIOMETER_PORT) / (float)MAX_POTENCIOMETER;
    potenciometer = p;
    if((potenciometer - old_potenciometer) > POTENCIOMETER_TOLERANCE){
      old_potenciometer = potenciometer;
      int* v = new int;
      *v = BeagleController::left;
      cmds.push(v);
    }else if((old_potenciometer - potenciometer) > POTENCIOMETER_TOLERANCE){
      old_potenciometer = potenciometer;
      int* v = new int;
      *v = BeagleController::right;
      cmds.push(v);
    }else{
      cout << potenciometer << endl;
    }
  }
}

int BeagleController::getCommand(){
  //if(_instance == NULL){
  //  _instance = new BeagleController();
  //}

  /*if(getRotateControl()){
    return BeagleController::button;
  }else if (getMoveLeftControl()){
    return BeagleController::left;
  }else if (getMoveRightControl()){
    return BeagleController::right;
  }else if (getLightFactorControl()){
    return BeagleController::shadow;
  }else{
    return BeagleController::no_command;
  }*/
  int* cmd = cmds.pop();
  if(cmd != NULL){
    return *cmd;
  }else{
    return BeagleController::no_command;
  }
}
