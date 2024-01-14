#include "main.h"

void drivetrainInitialize();

void drivetrainPeriodic(bool override);

void tankDrive(int left, int right);

void arcadeDrive(int moveValue, int rotateValue);

void evenBotWithBeam();

void driveStraightDistance(int distance);

void rotateToHeading(int angle);
 
void rotateToHeadingVoltage(int angle);

void killSwitch();