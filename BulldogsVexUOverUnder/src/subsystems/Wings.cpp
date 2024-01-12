#include "main.h"
#include <iostream>
using namespace std;

bool wingsOut = false;


void wingsPeriodic() {

	if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B) && !wingsOut) {
		flipWings(6000);
		wingsOut = true;
	}
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A) && wingsOut) {
		flipWings(0);
		wingsOut = false;
	}

    pros::lcd::set_text(2, "Wings Encoder: " + to_string(wingMotor.get_position()));

}

// Position-Controlled Wings
void flipWings(int position) {
	wingMotor.move_absolute(position, 600);
}

// Move Motor Directly (would be used for testing)
void manualOpenWings() {
	wingMotor.move(100);
}

// Move Motor Directly (would be used for testing)
void manualCloseWings() {
	wingMotor.move(-100);
}

// Stop Wing Movement
void stopWings() {
	wingMotor.brake();
}