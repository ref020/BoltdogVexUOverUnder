#include "main.h"

/*
FUNCTIONS
*/
extern double max(double a, double b);
extern double min(double a, double b);


/*
CONSTANTS
*/
 

/*
CONTROLLER
*/
    extern pros::Controller controller;

/*
MOTORS
*/

    //Drivetrain
        extern pros::Motor fLDrive;
        extern pros::Motor mLDrive;
        extern pros::Motor bLDrive;

        extern pros::Motor fRDrive;
        extern pros::Motor mRDrive;
        extern pros::Motor bRDrive;

        extern pros::Motor_Group leftDrive;
        extern pros::Motor_Group rightDrive;

        extern pros::ADIDigitalIn rightBumpSwitch;
        extern pros::ADIDigitalIn leftBumpSwitch;


    //Shooter
        extern pros::Motor catMotor;

    //Wings
        extern pros::Motor wingMotor;

    //Climber