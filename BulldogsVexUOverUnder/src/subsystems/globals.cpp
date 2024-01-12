#include "main.h"

/*
FUNCTIONS
*/
//min and max //idk why they wouldnt work other wise
double max(double a, double b){
    return (a > b)? a: b;
}

double min(double a, double b){
    return (a < b)? a: b;
}

/*
CONSTANTS
*/
    // Drive
    const int oneRotationEncoderCount = 3000;


/*
CONTROLLER
*/
    pros::Controller controller(pros::E_CONTROLLER_MASTER);

/*
MOTORS
*/
        //TODO: figure out gears
//Drivetrain
    pros::Motor fRDrive(11, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor mRDrive(12, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor bRDrive(13, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_COUNTS);

    pros::Motor fLDrive(18, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor mLDrive(19, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor bLDrive(20, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_COUNTS);

    pros::Motor_Group leftDrive({fLDrive, mLDrive, bLDrive});
    pros::Motor_Group rightDrive({fRDrive, mRDrive, bRDrive});

    pros::ADIDigitalIn leftBumpSwitch('a');
    pros::ADIDigitalIn rightBumpSwitch('b');
    
//Shooter
    pros::Motor catMotor(4, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_COUNTS);

//Wings
    pros::Motor wingMotor(15, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_COUNTS);

//Climber
    pros::Motor leftClimbMotor(1, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor rightClimbMotor(2, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_COUNTS);

    pros::Motor_Group climb({leftClimbMotor, rightClimbMotor});

