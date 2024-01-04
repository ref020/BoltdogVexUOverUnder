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
    class dtConstants{
    private:
        /* data */
    public:
      int joystickDeadZone = 10;
    };


/*
CONTROLLER
*/
    pros::Controller controller(pros::E_CONTROLLER_MASTER);


/*
MOTORS
*/
        //TODO: figure out gears
//Drivetrain
    pros::Motor flDrive(1, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor mlDrive(2, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor blDrive(3, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_COUNTS);

    pros::Motor frDrive(11, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor mrDrive(12, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor brDrive(13, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_COUNTS);

    pros::Motor_Group leftDrive({flDrive, mlDrive, blDrive});
    pros::Motor_Group rightDrive({frDrive, mrDrive, brDrive});

    pros::ADIDigitalIn leftBumpSwitch('a');
    pros::ADIDigitalIn rightBumpSwitch('b');
    

//Intake
    pros::Motor intakeMotor(7, pros::E_MOTOR_GEAR_200, false, pros::E_MOTOR_ENCODER_COUNTS);

//Lift
    pros::Motor liftMotor(8, pros::E_MOTOR_GEAR_100, false, pros::E_MOTOR_ENCODER_COUNTS);

//Shooter
    pros::Motor catapultMotor(9, pros::E_MOTOR_GEAR_100, false, pros::E_MOTOR_ENCODER_COUNTS);

//Wings
    pros::Motor wingMotor(10, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_COUNTS);

//Climber