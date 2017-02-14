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


	//grip::GripAreaPipeline gap;



public:
	//std::shared_ptr<NetworkTable> table;

	Drive() : mainDrive(LeftA_Motor_ID, LeftB_Motor_ID, RightA_Motor_ID, RightB_Motor_ID),
			Lstick(Left_Joystick_Port),
			Rstick(Right_Joystick_Port),
			DriveForward(true),
			Gyro(),
			Sonar(0),
			autoTimer(new Timer()),
			Drive_straight(0)
	{
		mainDrive.SetExpiration(0.1);
		Sonar.SetAverageBits(4);


	}

	/*void DriveInit(){
		table = NetworkTable::GetTable("GRIP/myContoursReport");
	}*/

	void GyroReset(){
		Gyro.Reset();
	}
	void Safety(){
		mainDrive.SetSafetyEnabled(true);
	}

	bool DriveToDistance(float Distance){
		if(Sonar.GetAverageValue() >= Distance){
			mainDrive.ArcadeDrive(0.0f, 0.0f);
			return true;
		}else{
			float angle = Gyro.GetAngle();
			mainDrive.ArcadeDrive(.5f, angle * .5f);
			return false;
		}
	}

	void TeleOp(){
		//float angle = Gyro.GetAngle();


		//int large_angle = (int)(angle * 1000);
		//angle = (large_angle % 360000) / 1000.0f;
		//SmartDashboard::PutNumber("GYRO", angle);

		//double Sdis = Sonar.GetAverageValue();
		//SmartDashboard::PutNumber("SONAR", Sdis);

		//float Smult = 0.0005333 * Sdis + 0.4666;

		//if(Sdis <= 500){
		//	setDriveSpeed(1.0);
		//}else{
		//	setDriveSpeed(1.0);
		//}
		//TargetTrack();
		setDriveSpeed(0.5f);
	}

	void AutonStart() {
		Gyro.Reset();
		autoTimer->Reset();
		autoTimer->Start();
	}

	void AutonLeft(){
		TurnToAngle(90);
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
		TurnToAngle(-90);
	}

	bool TurnToAngle(float targetAngle){
		float angle = Gyro.GetAngle() - targetAngle;
				if(angle > 10.0f * ROTATE_TOLERANCE){
					ArcadeDrive(0.0f, .75f);
				}else if(angle > ROTATE_TOLERANCE){
					ArcadeDrive(0.0f, 0.3f);
				}else if(angle < -10.0f * ROTATE_TOLERANCE){
					ArcadeDrive(0.0f, -0.75);
				}else if(angle < -ROTATE_TOLERANCE){
					ArcadeDrive(0.0f, -0.3f);
				}else{
					mainDrive.ArcadeDrive(0.0f, 0.0f);
					return true;
				}
				return false;
	}

	void TankDrive(float target_left, float target_right){
		last_rotate_speed = 0;
		last_arcade_speed = 0;
		if(target_left == 0){
			last_left_speed = 0;
		}else{
			last_left_speed = (target_left + last_left_speed * AVERAGE_WEIGHT) / (AVERAGE_WEIGHT + 1);
		}
		if(target_right == 0){
			last_right_speed = 0;
		}else{
			last_right_speed = (target_right + last_right_speed * AVERAGE_WEIGHT) / (AVERAGE_WEIGHT + 1);
		}
		mainDrive.TankDrive(last_left_speed, last_right_speed);
	}

	void ArcadeDrive(float target_speed, float rotate_speed){
		last_left_speed = 0;
		last_right_speed = 0;
		if(target_speed == 0){
			last_arcade_speed = 0;
		}else{
			last_arcade_speed = (target_speed + last_arcade_speed * AVERAGE_WEIGHT) / (AVERAGE_WEIGHT + 1);
		}
		if(rotate_speed == 0){
			last_rotate_speed = 0;
		}else{
			last_rotate_speed = (rotate_speed + last_rotate_speed * AVERAGE_WEIGHT) / (AVERAGE_WEIGHT + 1);
		}
		mainDrive.ArcadeDrive(last_arcade_speed, last_rotate_speed);
	}

	void setDriveSpeed(float multiplier){
		float LeftStickValue = multiplier * .75 * (-Lstick.GetY());
		float RightStickValue = multiplier * .75 * (-Rstick.GetY());

		/*if(abs(LeftStickValue - RightStickValue) < STRAIT_TOLERANCE){
			if(Drive_straight == 0){
				Drive_straight = Gyro.GetAngle();
			}
			if(DriveForward == true){
				ArcadeDrive(((LeftStickValue + RightStickValue) / 2.0f), Drive_straight * .5f);
			}else{
				ArcadeDrive(-((LeftStickValue + RightStickValue) / 2.0f), Drive_straight * .5f);
			}
		}else{
			Drive_straight = false;

		}*/

		if(DriveForward == true){
					mainDrive.TankDrive(LeftStickValue, RightStickValue);
				}else{
					mainDrive.TankDrive(-LeftStickValue, -RightStickValue);
				}
	}

	/*float getJoystickTransform(float input){
		return input;
	}*/

	float GetTargetCenterX(std::vector<cv::Point> target_x){
		float center_x = 0;
		for(uint i = 0; i < target_x.size(); i++){
			center_x = center_x + target_x[i].x;
		}
		return center_x / target_x.size();
	}

	void TrackTarget(){

	}

	/*inline float TargetTrack(){
			//auto gap = NetworkTable::GetTable("grip");
		//gap.Process()
			//table = NetworkTable::GetTable("GRIP/myContoursReport");
		       std::vector<double> areas = table->GetNumberArray("area", llvm::ArrayRef<double>());

		       SmartDashboard::PutNumber("TARGETS_FOUND", areas.size());
		       double totalArea = 0;
		       for (uint i = 0; i < areas.size(); i++){
		    	   totalArea = totalArea + areas[i];
		       }

		       return 0;

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
		        }
		    }*/

};


