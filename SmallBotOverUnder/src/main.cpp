#include "main.h"
#include <iostream>
using namespace std;

// Controller Setup
pros::Controller master(pros::E_CONTROLLER_MASTER);


// Motor Initialization
pros::Motor catapult(18);

pros::Motor frontLeftMotor(19, MOTOR_GEAR_BLUE, true, MOTOR_ENCODER_COUNTS);
pros::Motor frontRightMotor(12, MOTOR_GEAR_BLUE, false, MOTOR_ENCODER_COUNTS);
pros::Motor backLeftMotor(20, MOTOR_GEAR_BLUE, true, MOTOR_ENCODER_COUNTS);
pros::Motor backRightMotor(11, MOTOR_GEAR_BLUE, false, MOTOR_ENCODER_COUNTS);

pros::Motor_Group leftSideMotors({frontLeftMotor, backLeftMotor});
pros::Motor_Group rightSideMotors({frontRightMotor, backRightMotor});

pros::Motor leftLiftMotor(5, true);
pros::Motor rightLiftMotor(6);
pros::Motor_Group lift({leftLiftMotor, rightLiftMotor});

pros::Motor intake(1, true);

// Sensor Initialization
pros::ADIAnalogIn lineTracker('H');
pros::ADIUltrasonic ultrasonic('E', 'F');

// Globals
static bool skills = false;
static bool red = false;
static bool blue = false;


// User Drive Function
void drive() {
	int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
	
	leftSideMotors = power + turn;
	rightSideMotors = power - turn;
}

// Move x distance
void moveDistance(int distance, int speed) {
    double targetDistanceLeft = frontLeftMotor.get_position() + distance;
    double targetDistanceRight = frontRightMotor.get_position() + distance;

    // leftDrive.move_absolute(targetDistanceLeft, speed);
    // rightDrive.move_absolute(targetDistanceRight, speed);

    leftSideMotors.move_relative(distance, speed);
    rightSideMotors.move_relative(distance, speed);

    while (abs(abs(targetDistanceLeft) - abs(frontLeftMotor.get_position())) > 20) {
    }

	
    leftSideMotors.move_relative(0, speed);
    rightSideMotors.move_relative(0, speed);
    pros::delay(200);
}

// Target angle is relative to the robot's current heading, so a 90 will mean the robot will turn 90 degrees
void rotateToHeading(int angle, int speed) {
    // the distance the motor needs to travel in order to reach the desired rotation
    double distance = 2335 * ((angle - 5) / 360.0);

    // the actual target encoder value for the leftDrive
    double targetDistanceLeft = frontLeftMotor.get_position() + distance;
    double targetDistanceRight = frontRightMotor.get_position() - distance;

    // set the motors to move to the target positions. (This will move and stop the motors on its own [apparently])
    leftSideMotors.move_absolute(targetDistanceLeft, speed);
    rightSideMotors.move_absolute(targetDistanceRight, speed);

    while (abs(abs(targetDistanceLeft) - abs(frontLeftMotor.get_position())) > 50) {
    }
    
    pros::delay(200);
}

// Checks to see if a triball is loaded
bool triballLoaded() {
    return ultrasonic.get_value() < 50;
}

// Makes sure the catapult is in the proper position to fire
void primeCatapult() {
	int lineTrackerVal;
	lineTrackerVal = lineTracker.get_value();
	if (lineTrackerVal > 300) {
		catapult.move(100);
		while(lineTrackerVal > 300) {
			drive();
			lineTrackerVal = lineTracker.get_value();
			if (lineTrackerVal < 300) {
				catapult.move(0);
				catapult.set_brake_mode(MOTOR_BRAKE_HOLD);
			}
		}
	}
	else {
		catapult.move(0);
		catapult.set_brake_mode(MOTOR_BRAKE_HOLD);
	}
}

// Fires the triball
void launchTriball() {
	catapult.move(100);
	pros::delay(200);
	primeCatapult();
}

void launchTriballNoPrime() {
	catapult.move(100);
	pros::delay(200);
	}

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "Skills Run");
		skills = true;
	} else {
		pros::lcd::clear_line(2);
		skills = false;
	}
}

void on_right_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(3, "red auton selected");
		red = true;
		blue = false;
	} else {
		pros::lcd::set_text(3, "blue auton selected");
		blue = true;
		red = false;
	}
}

void on_left_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(3, "blue auton selected");
		blue = true;
		red = false;
	} else {
		pros::lcd::set_text(3, "red auton selected");
		red = true;
		blue = false;
	}
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Running Match Code");

	pros::lcd::register_btn1_cb(on_center_button);
	pros::lcd::register_btn0_cb(on_right_button);
	pros::lcd::register_btn2_cb(on_left_button);

	frontLeftMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	frontRightMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	backLeftMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	backRightMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);

	leftLiftMotor.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
	lift.set_brake_modes(MOTOR_BRAKE_HOLD);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	pros::lcd::set_text(1, "Running Match Code");

	pros::lcd::register_btn1_cb(on_center_button);
	pros::lcd::register_btn0_cb(on_right_button);
	pros::lcd::register_btn2_cb(on_left_button);
	}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	//lift up dor shooting
	lift.move(127);
	pros::delay(300);
	lift.move(0);
	//rotate to fire onto opponent side
	rotateToHeading(-55, 100);
	//shoot and reset
	// launchTriballNoPrime();
	// primeCatapult();
	launchTriball();
	//spin to drive to other side
	rotateToHeading(230, 200);
	//start intake wheels
	intake.move(40);
	lift.move(-127);
	pros::delay(50);
	lift.move(0);
	moveDistance(-4200, 300);
	lift.move(-127);
	pros::delay(50);
	lift.move(0);
	rotateToHeading(-45, 100);
	moveDistance(-1400, 300);
	rotateToHeading(-45, 100);
	// lift.move(127);
	// pros::delay(300);
	// lift.move(0);
	intake.move(-127);
	moveDistance(400, 300);
	lift.move(-127);
	pros::delay(1000);
	lift.move(0);
	moveDistance(-500, 600);
	moveDistance(500, 300);
	intake.move(0);
	lift.move(127);
	pros::delay(500);
	lift.move(0);
	rotateToHeading(-135, 200);
	moveDistance(-500, 200);
	rotateToHeading(-90, 200);
	moveDistance(-300, 200);
	intake.move(70);
	lift.move(-127);
	moveDistance(-300, 200);
	pros::delay(200);
	lift.move(0);
	moveDistance(600, 200);
	intake.move(0);
	rotateToHeading(-90, 200);
	moveDistance(-600, 200);
	rotateToHeading(-40, 200);
	lift.move(127);
	pros::delay(500);
	lift.move(0);
	moveDistance(-200, 200);
	moveDistance(500, 200);
	lift.move(-127);
	pros::delay(500);
	lift.move(0);
	moveDistance(-700, 400);
	moveDistance(500, 200);
	rotateToHeading(-135, 250);
	moveDistance(-1200, 250);
	rotateToHeading(55, 250);
	moveDistance(-4000, 250);

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {

	float liftPos;
	primeCatapult();
	leftLiftMotor.tare_position();

	while (true) {
		if (master.get_digital(DIGITAL_A)) {
			lift.move_absolute(.642222222222, 200);
		}
		
		pros::lcd::set_text(0, "Drivetrain Left Encoder: " + to_string(frontLeftMotor.get_position()));

		liftPos = leftLiftMotor.get_position();
		pros::lcd::print(2, "%f", liftPos);

		//Split Arcade control code
		drive();

		// This block launches the triball when the correct buttons is pressed
		if (master.get_digital(DIGITAL_R2) && triballLoaded()) {
			launchTriball();
		}

		// This block lifts the lift and intake up and down
		if (master.get_digital(DIGITAL_L1)) {
			if (liftPos < 2 || master.get_digital(DIGITAL_B)) {
				lift.move(127);
			}
			else {
				lift.move(0);
			}
		}
		else if (master.get_digital(DIGITAL_L2)) {
			if (liftPos > 0) {
				lift.move(-127);
				intake.move(127);
			}
			else {
				lift.move(0);
			}
		}
		else {
			lift.move(0);
		}

		if (master.get_digital(DIGITAL_UP)){
			intake.move(127);
		} else if (master.get_digital(DIGITAL_DOWN)){
			intake.move(-127);
		} else {
			intake.move(0);
		}

		if (master.get_digital(DIGITAL_X)){
			autonomous();
		}

		pros::delay(20);
	}
}	

