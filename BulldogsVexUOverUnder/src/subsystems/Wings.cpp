#include "main.h"

void wingsPeriodic() {
 	if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
		manualOpenWings();
	}

	//Open Wings
	else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
		manualCloseWings();
	}

	else {
		wingMotor.brake();
	}
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