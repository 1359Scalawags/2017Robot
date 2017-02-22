/*
 * Drive.h
 *
 *  Created on: Feb 13, 2017
 *      Author: Destin
 */

#ifndef SRC_DRIVE_H_
#define SRC_DRIVE_H_

#include <Constants.h>
#include "WPILib.h"
#include <VictorSP.h>
#include <ADXRS450_Gyro.h>
#include <GripAreaPipeline.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

// Drive.cpp  Created on: Jan 27, 2017      Author: Destin

class Drive{

private:
	RobotDrive mainDrive;

	Joystick Lstick;
	Joystick Rstick;

	bool DriveForward;

	ADXRS450_Gyro Gyro;
	AnalogInput Sonar;

	Timer* autoTimer;

	float last_arcade_speed = 0;
	float last_rotate_speed = 0;
	float last_left_speed = 0;
	float last_right_speed = 0;

	float Drive_straight = 0;
	float gearing = 1.0f;

	void setDriveSpeed(float multiplier);


public:

	Drive();
	void SetRobotFront();
	void GyroReset();
	void Safety();
	bool DriveToDistance(float Distance);
	void TeleOp();
	void AutonStart();
	void AutonLeft();
	void AutonMiddle();
	void AutonRight();
	void ResetTimer();
	bool TurnToAngle(float targetAngle);
	void TankDrive(float target_left, float target_right);
	void ArcadeDrive(float target_speed, float rotate_speed);
	bool DriveForwardByTime(float time);
	bool DriveBackwardByTime(float time);
	float PullGyroAngle();
	float NormalizeAngle(float angle);
	void DriveAssist();
};






#endif /* SRC_DRIVE_H_ */
