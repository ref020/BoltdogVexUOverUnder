#include "main.h"

/*
FUNCTIONS
*/
extern double max(double a, double b);
extern double min(double a, double b);


/*
CONSTANTS
*/
      int joystickDeadZone;

/*
CONTROLLER
*/
    extern pros::Controller controller;

/*
MOTORS
*/

    //Drivetrain
        extern pros::Motor flDrive;
        extern pros::Motor mlDrive;
        extern pros::Motor blDrive;

        extern pros::Motor frDrive;
        extern pros::Motor mrDrive;
        extern pros::Motor brDrive;

        extern pros::Motor_Group leftDrive;
        extern pros::Motor_Group rightDrive;

        extern pros::ADIDigitalIn rightBumpSwitch;
        extern pros::ADIDigitalIn leftBumpSwitch;


    //Intake
        extern pros::Motor intakeMotor;

    //Lift
        extern pros::Motor liftMotor;

    //Shooter
        extern pros::Motor catapultMotor;

    //Wings
        extern pros::Motor wingMotor;

    //Climber