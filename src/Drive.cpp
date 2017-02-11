#include <Constants.h>
#include "WPILib.h"
#include <VictorSP.h>
#include <ADXRS450_Gyro.h>
#include <GripAreaPipeline.h>
#include <unistd.h>
#include <stdio.h>

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

	//grip::GripAreaPipeline gap;



public:
	std::shared_ptr<NetworkTable> table;

	Drive() : mainDrive(LeftA_Motor_ID, LeftB_Motor_ID, RightA_Motor_ID, RightB_Motor_ID),
			Lstick(Left_Joystick_Port),
			Rstick(Right_Joystick_Port),
			DriveForward(true),
			Gyro(),
			Sonar(0),
			autoTimer(new Timer())
	{
		mainDrive.SetExpiration(0.1);
		Sonar.SetAverageBits(4);


	}

	void Safety(){
		mainDrive.SetSafetyEnabled(true);
		Gyro.Reset();
	}


	void TeleOp(){
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
		TargetTrack();
	}

	void AutonStart() {
		Gyro.Reset();
		autoTimer->Reset();
		autoTimer->Start();
	}

	void AutonLeft(){
		float angle = Gyro.GetAngle();
		if(autoTimer->Get() < 1.5f){
			mainDrive.ArcadeDrive(.5f, angle * .5f);
		}else{
			mainDrive.ArcadeDrive(0.0f, angle * .5f);
		}
	}
	void AutonMiddle(){
		float angle = Gyro.GetAngle();
		if(autoTimer->Get() < 1.5f){
			mainDrive.ArcadeDrive(.5f, angle * .5f);
		}else{
			mainDrive.ArcadeDrive(0.0f, angle * .5f);
		}
	}
	void AutonRight(){
		float angle = Gyro.GetAngle();
		if(autoTimer->Get() < 1.5f){
			mainDrive.ArcadeDrive(.5f, angle * .5f);
		}else{
			mainDrive.ArcadeDrive(0.0f, angle * .5f);
		}
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
			//auto gap = NetworkTable::GetTable("grip");
		//gap.Process()
			table = NetworkTable::GetTable("GRIP/myContoursReport");
		       std::vector<double> areas = table->GetNumberArray("area", llvm::ArrayRef<double>());

		       SmartDashboard::PutNumber("TARGETS_FOUND", areas.size());
		       /*double totalArea = 0;
		       for (uint i = 0; i < areas.size(); i++){
		    	   totalArea = totalArea + areas[i];
		       }*/

		       return 0;

		        // Pick whatever target has the biggest area
		        /*double targetArea = -1.0, targetX = 0.0;
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


