#include "main.h"

void catapultPeriodic()
{
  // Prime the cata
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    primeCatapult();
  }
  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    launchCatapult();
  }
  else {
    stopCatapult();
  }
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
