#include <Constants.h>
#include "WPILib.h"
#include <VictorSP.h>
#include <ADXRS450_Gyro.h>

// Drive.cpp  Created on: Jan 27, 2017      Author: Destin

class Drive{
	RobotDrive mainDrive;

	Joystick Lstick;
	Joystick Rstick;

	bool DriveForward;
	ADXRS450_Gyro Gyro;

	public: Drive() : mainDrive(LeftA_Motor_ID, LeftB_Motor_ID, RightA_Motor_ID, RightB_Motor_ID),
			Lstick(Left_Joystick_Port),
			Rstick(Right_Joystick_Port),
			DriveForward(true),
			Gyro()
	{
		mainDrive.SetExpiration(0.1);
	}

	void Safety(){
		mainDrive.SetSafetyEnabled(true);
		Gyro.Reset();
	}


	void Tellop(){
		float angle = Gyro.GetAngle();

		setDriveSpeed();

		int large_angle = (int)(angle * 1000);
		angle = (large_angle % 360000) / 1000.0f;
		SmartDashboard::PutNumber("GYRO", angle);
	}

	void setDriveSpeed(){
		float LeftStickValue = .75 * (-getJoystickTransform(Lstick.GetY()));
		float RightStickValue = .75 * (-getJoystickTransform(Rstick.GetY()));

		if(DriveForward == true){
			mainDrive.TankDrive(LeftStickValue, RightStickValue);
		}else{
			mainDrive.TankDrive(-LeftStickValue, RightStickValue);
		}
	}

	float getJoystickTransform(float input){
		return input;
	}

};


