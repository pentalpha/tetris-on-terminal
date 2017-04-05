#include "beagleController.h"
#include <iostream>
using namespace std;

bool BeagleController::keepUpdating;
Queue BeagleController::cmds;

/*BeagleController::BeagleController(){
  startWatchers();
}

BeagleController::~BeagleController(){
  stopWatchers();
}*/

void BeagleController::init(){
  startWatchers();
}

void BeagleController::end(){
  stopWatchers();
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

float BeagleController::getNormalizedPort(int port){
  return ((float)readAnalog(port) / (float)MAX_POTENCIOMETER);
}

void BeagleController::startWatchers(){
  keepUpdating = true;
  thread t1 = thread(BeagleController::moveWatcher);
  t1.detach();
  thread t2 = thread(BeagleController::lightWatcher);
  t2.detach();
  thread t3 = thread(BeagleController::buttonWatcher);
  t3.detach();
}
void BeagleController::stopWatchers(){
  keepUpdating = false;
}

void BeagleController::moveWatcher(){
  float old_potenciometer;
  float potenciometer;
  old_potenciometer = potenciometer = getNormalizedPort(POTENCIOMETER_PORT);
  while(keepUpdating)
  {
    //std::this_thread::sleep_for(std::chrono::milliseconds{500});
    float p = getNormalizedPort(POTENCIOMETER_PORT);
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

void BeagleController::lightWatcher(){
  float old_lightFactor;
  float lightFactor;
  old_lightFactor = lightFactor = getNormalizedPort(LIGHT_PORT);
  while(keepUpdating)
  {
    //std::this_thread::sleep_for(std::chrono::milliseconds{500});
    float p = getNormalizedPort(LIGHT_PORT);
    lightFactor = p;
    if(old_lightFactor > lightFactor + LIGHT_TOLERANCE){
      old_lightFactor = lightFactor;
      int* v = new int;
      *v = BeagleController::shadow;
      cmds.push(v);
    }else{
      cout << lightFactor << endl;
    }
  }
}

void BeagleController::buttonWatcher(){
  bool old_buttonValue;
  bool buttonValue;
  while(keepUpdating){

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
