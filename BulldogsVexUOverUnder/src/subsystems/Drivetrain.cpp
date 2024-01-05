#include "main.h"

void drivetrainPeriodic() {
    //get joysticks for arcade
    int y1 = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int x2 = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    //add a dead zone
    if(abs(y1) < 10) 
        y1 = 0;
    if(abs(x2) < 10) 
        x2 = 0;
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

// Target angle is relative to the robot's current heading, so a 90 will mean the robot will turn 90 degrees
void rotateToHeading(int angle) {
    // the distance the motor needs to travel in order to reach the desired rotation
    int distance = oneRotationEncoderCount * (angle / 360);

    // the actual target encoder value for the leftDrive
    int targetDistanceLeft = fLDrive.get_position() + distance;
    int targetDistanceRight = fRDrive.get_position() - distance;

    // set the motors to move to the target positions. (This will move and stop the motors on its own [apparently])
    leftDrive.move_absolute(targetDistanceLeft, 1000);
    rightDrive.move_absolute(targetDistanceRight, 1000);
}

// Same goal as the previous method but uses voltage control and a p-controller
// to move the drivebase, instead of the built in position controllers
void rotateToHeadingVoltage(int angle) {
    int kP = 10;

    // the distance the motor needs to travel in order to reach the desired rotation
    int distance = oneRotationEncoderCount * (angle / 360);

    // the actual target encoder value
    int targetDistance = fLDrive.get_position() + distance;

    int error = targetDistance - fLDrive.get_position();

    while (abs(error) < 100) {
		int motorVal = error * kP;
		leftDrive.move(motorVal);
		rightDrive.move(-motorVal);
	    int error = targetDistance - fLDrive.get_position();
	}

    leftDrive.move(0);
	rightDrive.move(0);

}




