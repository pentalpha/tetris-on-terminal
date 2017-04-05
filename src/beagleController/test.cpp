#include <iostream>
#include "beagleController.h"

using namespace std;

int main(int argc, char const *argv[]) {
  BeagleController::init();
  int bgCmd = 0;
  BeagleController controller;
  do{
    bgCmd = BeagleController::getCommand();
    if(bgCmd != BeagleController::no_command){
      if(bgCmd == BeagleController::shadow)
              cout << "Force fall\n";
      if (bgCmd == BeagleController::left)
              cout << "Move left\n";
      if (bgCmd == BeagleController::right)
              cout << "Move right\n";
      if (bgCmd == BeagleController::button)
              cout << "Rotate\n";
    }
  }while(true);
  BeagleController::end();
  return 0;
}
