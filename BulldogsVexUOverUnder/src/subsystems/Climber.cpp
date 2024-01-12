#include "main.h"
#include <iostream>
using namespace std;

void climberInitialize() {
    leftClimbMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    rightClimbMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void climberPeriodic() {
        pros::lcd::set_text(3, "Climb Encoder: " + to_string(leftClimbMotor.get_position()));

}

void climberToPosition(int position) {
    climb.move_absolute(position, 600);
}

void manualRaiseClimber() {
    climb.move(50);
}

void mannualLowerClimb() {
    climb.move(-100);
}


