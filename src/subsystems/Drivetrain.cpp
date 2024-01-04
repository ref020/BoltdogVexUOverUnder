#include "main.h"

void drivetrainPeriodic(){
    //get joysticks for arcade
    int y1 = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int x2 = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

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
    left = max(-127, min(127, left));
    right = max(-127, min(127, right));
    //sets motor speeds
    leftDrive = left;
    rightDrive = right;
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
    if(!(leftBumpSwitch.get_value() && rightBumpSwitch.get_value())) {
        rightDrive = 127;
        leftDrive = 127;
    }
    else{
        if(leftBumpSwitch.get_value()) 
            rightDrive = 127;
        if(rightBumpSwitch.get_value()) 
            leftDrive = 127;
    }
}





