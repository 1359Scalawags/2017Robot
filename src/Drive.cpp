#include <Constants.h>
#include "WPILib.h"
#include <VictorSP.h>
#include <ADXRS450_Gyro.h>
#include <GripAreaPipeline.h>
#include <unistd.h>
#include <stdio.h>

// Drive.cpp  Created on: Jan 27, 2017      Author: Destin

class Drive{
	RobotDrive mainDrive;

	Joystick Lstick;
	Joystick Rstick;

	bool DriveForward;

	ADXRS450_Gyro Gyro;
	AnalogInput Sonar;

	//grip::GripAreaPipeline gap;

	public: Drive() : mainDrive(LeftA_Motor_ID, LeftB_Motor_ID, RightA_Motor_ID, RightB_Motor_ID),
			Lstick(Left_Joystick_Port),
			Rstick(Right_Joystick_Port),
			DriveForward(true),
			Gyro(),
			Sonar(0)
	{
		mainDrive.SetExpiration(0.1);
		Sonar.SetAverageBits(4);

	}

	void Safety(){
		mainDrive.SetSafetyEnabled(true);
		Gyro.Reset();
	}


	void Tellop(){
		float angle = Gyro.GetAngle();

		int large_angle = (int)(angle * 1000);
		angle = (large_angle % 360000) / 1000.0f;
		SmartDashboard::PutNumber("GYRO", angle);

		double Sdis = Sonar.GetAverageValue();
		SmartDashboard::PutNumber("SONAR", Sdis);

		float Smult = 0.0005333 * Sdis + 0.4666;

		if(Sdis <= 500){
			setDriveSpeed(Smult);
		}else{
			setDriveSpeed(Smult);
		}
		SmartDashboard::PutString("Before Target Track", "YES");
		TargetTrack();
		SmartDashboard::PutString("After Target Track", "YES");
	}

	void setDriveSpeed(float multiplier){
		float LeftStickValue = multiplier * .75 * (-getJoystickTransform(Lstick.GetY()));
		float RightStickValue = multiplier * .75 * (-getJoystickTransform(Rstick.GetY()));


		if(DriveForward == true){
			mainDrive.TankDrive(LeftStickValue, RightStickValue);
		}else{
			mainDrive.TankDrive(-LeftStickValue, RightStickValue);
		}
	}

	float getJoystickTransform(float input){
		return input;
	}

	inline float TargetTrack(){
		SmartDashboard::PutString("In Target Track start", "YES");
			auto gap = NetworkTable::GetTable("grip");
			SmartDashboard::PutString("In Target Track post gap", "YES");
		       auto areas = gap->GetNumberArray("targets/area", llvm::ArrayRef<double>());


		       SmartDashboard::PutString("Before For Loop", "YES");
		       double totalArea = 0;
		       for (uint i = 0; i < areas.size(); i++){
		    	   totalArea = totalArea + areas[i];
		       }
		       SmartDashboard::PutString("After For Loop", "YES");
		       SmartDashboard::PutNumber("TARGETS_FOUND", totalArea);
		       return 0;
		       /*
		        // Pick whatever target has the biggest area
		        double targetArea = -1.0, targetX = 0.0;
		        for (uint i = 0; i < areas.size(); i++) {
		            if (areas[i] > targetArea) {
		                targetArea = areas[i];
		                targetX = xs[i];
		            }
		        }


		        // If we didn't find a target, return control to the operator
		        if (targetArea < 0.0) {
		            return 0;
		        }

		        // If we're too far to the left to shoot, move right.  If we're too far
		        // to the right, move left.  If we're spot on, shoot and return.
		        if (targetX < CENTER_X - TOLERANCE_X) {
		            //MoveRobotRight();
		        	return -1;
		        } else if (targetX > CENTER_X + TOLERANCE_X) {
		            //MoveRobotLeft();
		        	return 1;
		        } else {
		            //ShootBoulder();
		            return 0;
		        }*/
		    }

};


