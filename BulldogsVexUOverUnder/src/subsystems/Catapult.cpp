#include "main.h"
#include <iostream>
using namespace std;

void catapultPeriodic() {
  // Prime the cata
  // if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
  //   manualPrimeCatapult();
  // }
  // else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
  //   manualLaunchCatapult();
  // }
  // else {
  //   stopCatapult();
// }

  // pros::lcd::set_text(1, "Catapult Encoder: " + to_string(catMotor.get_position()));

}

// Prime the cata
void primeCatapult() {
  catMotor.move_absolute(60, 100);
}

// Launch the cata
// AKA Send that thang to the shadow realm
void launchCatapult() {
  catMotor.move_absolute(110, 100);
}

void stopCatapult() {
  catMotor.brake();
}

void manualPrimeCatapult() {
  catMotor.move(50);
}

void manualLaunchCatapult() {
  catMotor.move(-50);
}
