#include "main.h"

void drivetrainPeriodic() {
    //get joysticks for arcade
    int y1 = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int x2 = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    //add a dead zone
    // if(abs(y1) < 10) 
    //     y1 = 0;
    // if(abs(x2) < 10) 
    //     x2 = 0;
    //arcade drive
    arcadeDrive(y1, x2);
}

//bad
void tankDrive(int left, int right) {
    //brings any numbers out side of range into range
    // left = max(-127, min(127, left));
    // right = max(-127, min(127, right));
    //sets motor speeds
    leftDrive.move(left);
    rightDrive.move(right);
}

//good
void arcadeDrive(int moveValue, int rotateValue) {
    //mixes the numbers
    int leftMotorSpeed = moveValue - rotateValue;
    int rightMotorSpeed = moveValue + rotateValue;
    //determines which is higher
    int mx = max(abs(leftMotorSpeed), abs(rightMotorSpeed));
    //scales both sides evenly based on if max > 127
    if (mx > 127) {
        leftMotorSpeed = (leftMotorSpeed / mx) * 127;
        rightMotorSpeed = (rightMotorSpeed / mx) * 127;
    }
    tankDrive(leftMotorSpeed, rightMotorSpeed);
}

/*
Autonomous Commands
*/

void evenBotWithBeam(){


}



void driveStraightDistance(int distance) {
	int kP = .1;
	int error = distance - fLDrive.get_position();

	while (abs(error) < 100) {
		int motorVal = error * kP;
		leftDrive.move(motorVal);
		rightDrive.move(motorVal);
	    error = distance - fLDrive.get_position();
	}

	leftDrive.move(0);
	rightDrive.move(0);
}

// void rotateToHeading(int angle) {
// 	int kP = .1; // TEST FOR LATER
// 	int error = angle - ((std::fmod(gyro.get_value(), 3600) / 10));

// 	while (abs(error) < 1) {
// 		int motorVal = error * kP;
// 		leftDrive.move(motorVal);
// 		rightDrive.move(motorVal * -1);
// 	    error = angle - ((std::fmod(gyro.get_value(), 3600) / 10));
// 	}

// 	leftDrive.move(0);
// 	rightDrive.move(0);
// }





