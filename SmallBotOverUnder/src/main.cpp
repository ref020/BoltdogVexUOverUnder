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
static bool skills = false;
static bool red = false;
static bool blue = false;

/*
Subroutines:
Below are the subroutines used in the opcontrol section
The following subroutines are used:
-move distance (feet)
-launch triball
-prime catapult
*/

void movement() {
	int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
	
	int leftP = power + turn;
	int rightP = power - turn;

	int mx = std::max(std::abs(leftP), std::abs(rightP));

	if(mx > 127){
		leftP = (leftP / mx) * 127;
		rightP = (rightP / mx) * 127;
	}

	left = leftP;
	right = rightP;
}

void primeCatapult() {

	while (limitSwitch.get_value() == 0){
		cata.move(50);

		//copy of drive controls, allowing for motion and operation of other subsystems

		movement(); 

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
			movement();
		
		} else if (master.get_digital(DIGITAL_L2)){

			intake.move_velocity(-100);
			movement();

		} else{

			intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			intake.brake();

		}
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
	
	primeCatapult();

	while (true) {

		//Split Arcade control code
		movement();
        
		//Catapult code
		//R1 = Fire Cata
		
        if (master.get_digital(DIGITAL_R1)) {

        	launchTriball();
			movement(); 
			
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
			movement();
		
		} else if (master.get_digital(DIGITAL_L2)){

			intake.move_velocity(-100);
			movement();

		} else{

			intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			intake.brake();

		}
		pros::delay(20);
	}
}	


