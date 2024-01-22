#include "main.h"
#include <iostream>
using namespace std;

void matchQualsAuto() {
    scoreFirstThreeTriballs();
	rotateToHeading(-15, 255);
	flipLeftWing(400, 600);
	flipRightWing(400, 600);
	pros::delay(2000);
	spinKicker();
	driveStraightDistance(2000, 255);
	flipRightWing(150, 600);
	pros::delay(500);
}

void matchElimsAuto() {
    scoreFirstThreeTriballs();
	flipLeftWing(223, 600);
	flipRightWing(223, 600);
	rotateToHeading(70, 255);
	driveStraightDistance(1500, 255);
	rotateToHeading(-60, 255);
}

void skillsAuto() {
	// flipRightWing(210, 600);	
	// driveStraightDistance(2800, 255);
	// flipRightWing(160, 600);	
	// spinKicker();
	// driveStraightDistance(600, 100);
	// driveStraightDistance(100, 200);
	// flipRightWing(150, 100);
	// driveStraightDistance(300, 100);
	// driveStraightDistance(100, 200);

	// tankDrive(50, 0);
	// pros::delay(300);
	// tankDrive(0, 0);
	for (int i = 0; i <= 2; i++) {
		flipLeftWing(400, 600);	
		pros::delay(300);
		flipLeftWing(40, 600);	
		pros::delay(800);
	}

	rotateToHeading(100, 255);
	driveStraightDistance(800, 255);
	rotateToHeading(45, 255);
	driveStraightDistance(2800, 500);
	driveStraightDistance(-2500, 500);
	rotateToHeading(-90, 255);
	driveStraightDistance(1000, 300);
	rotateToHeading(90, 255);

}

void scoreFirstThreeTriballs() {
	driveStraightDistance(2800, 255);
	spinKicker();
	driveStraightDistance(600, 100);
	driveStraightDistance(100, 200);
	driveStraightDistance(-1500, 255);
	flipLeftWing(223, 600);
	flipRightWing(223, 600);
	rotateToHeading(70, 1000);
	driveStraightDistance(750, 255);
	rotateToHeading(-70, 200);
	spinKicker();
	flipLeftWing(140, 100);
	flipRightWing(140, 100);
	driveStraightDistance(950, 150);
	driveStraightDistance(300, 50);
	// pros::delay(3000);
	driveStraightDistance(100, 255);
	driveStraightDistance(-900, 255);
	stopKicker();
	flipLeftWing(223, 600);
	flipRightWing(223, 600);
	rotateToHeading(40, 255);
	driveStraightDistance(500, 255);
	rotateToHeading(-40, 255);
	spinKicker();
	flipLeftWing(140, 100);
	flipRightWing(140, 100);
	driveStraightDistance(600, 50);
	driveStraightDistance(100, 255);
	driveStraightDistance(-1700, 255);
	stopKicker();
}