#include "main.h"

void flipWings(int position) {
	// int kP = 0; // tune later
	// wings.get_encoder_units();
	wingMotor.move_absolute(position, 600);
}
