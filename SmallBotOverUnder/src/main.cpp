#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor frontLeft(19);
pros::Motor frontRight(12, true);
pros::Motor cata(18);
pros::Motor backLeft(20);
pros::Motor backRight(11, true);
pros::Motor_Group left({frontLeft, backLeft});
pros::Motor_Group right({frontRight, backRight});
pros::Motor leftLift(5, true);
pros::Motor rightLift(6);
pros::Motor_Group lift({leftLift, rightLift});
pros::Motor intake(1, true);
pros::ADIDigitalIn limitSwitch (8);
pros::ADIDigitalIn sonarIN (std::uint8_t F);
pros::ADIDigitalIn sonarOut (std::uint8_t G);

/*
Subroutines:
Below are the subroutines used in the opcontrol section
The following subroutines are used:
-move distance (feet)
-launch triball
-prime catapult
*/

void movement() {

	left.move(master.get_analog(ANALOG_LEFT_Y)*-1);
	right.move(master.get_analog(ANALOG_RIGHT_Y)*-1);
}

void primeCatapult() {

	while (limitSwitch.get_value() == 0){
		cata.move(50);
	}

}

void launchTriball() {

	cata.move(100);
	pros::delay(20);
	primeCatapult();
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
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
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
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
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
void competition_initialize() {}

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
void autonomous() {}

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
	
	primeCatapult();

	while (true) {

		//Tank control code
		movement();
        
		//Catapult code
		//R1 = Fire Cata
		
        if (master.get_digital(DIGITAL_R1)) {

        	launchTriball(); 
			
		} else {
		
		    cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			cata.brake();

		}
		
		//Lift Controls
		//UP = Raise Lift Arm
		//DOWN = Lower Lift Arm/Raise Robot
		if (master.get_digital(DIGITAL_UP)) {

			lift.move_velocity(100);

			movement();

		} else if (master.get_digital(DIGITAL_DOWN)) {

			lift.move_velocity(-100);

			movement();

		} else {

			lift.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
			lift.brake();
			
		}


		//Intake code
		//L1 = Intake
		//L2 = Output
		if (master.get_digital(DIGITAL_L1)) {

			intake.move_velocity(100);
		
		} else if (master.get_digital(DIGITAL_L2)){

			intake.move_velocity(-100);

		} else{

			intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			intake.brake();

		}
		pros::delay(20);
	}
}	


