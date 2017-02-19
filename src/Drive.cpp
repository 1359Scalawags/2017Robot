#include <Constants.h>
#include "WPILib.h"
#include <VictorSP.h>
#include <ADXRS450_Gyro.h>
#include <GripAreaPipeline.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <Drive.h>

// Drive.cpp  Created on: Jan 27, 2017      Author: Destin


	Drive::Drive() : mainDrive(LeftA_Motor_ID, LeftB_Motor_ID, RightA_Motor_ID, RightB_Motor_ID),
			Lstick(Left_Joystick_Port),
			Rstick(Right_Joystick_Port),
			DriveForward(true),
			Gyro(),
			Sonar(SonarLeft_ID),
			autoTimer(new Timer()),
			Drive_straight(0)
	{
		mainDrive.SetExpiration(0.1);
		Sonar.SetAverageBits(4);


	}

	void Drive::ResetTimer(){
		autoTimer->Reset();
		autoTimer->Start();
	}

	void Drive::SetRobotFront(){
		if(Lstick.GetRawButton(DriveForward_Button_ID) || Rstick.GetRawButton(DriveForward_Button_ID)){
			DriveForward = true;
		}else if(Lstick.GetRawButton(DriveBackward_Button_ID) || Rstick.GetRawButton(DriveBackward_Button_ID)){
			DriveForward = false;
		}
	}

	/*void DriveInit(){
		table = NetworkTable::GetTable("GRIP/myContoursReport");
	}*/

	void Drive::GyroReset(){
		Gyro.Reset();
	}
	void Drive::Safety(){
		mainDrive.SetSafetyEnabled(true);
	}

	bool Drive::DriveToDistance(float Distance){
		if(Sonar.GetAverageValue() >= Distance){
			mainDrive.ArcadeDrive(0.0f, 0.0f);
			return true;
		}else{
			float angle = Gyro.GetAngle();
			mainDrive.ArcadeDrive(.5f, angle * .5f);
			return false;
		}
	}

	void Drive::TeleOp(){

		SetRobotFront();
		setDriveSpeed(1.5f);
		SmartDashboard::PutNumber("Sonar", Sonar.GetAverageValue());
	}

	bool Drive::DriveForwardByTime(float time){
		float angle = Gyro.GetAngle();
			if(autoTimer->Get() < time){
				ArcadeDrive(.5f, angle * .5f);
				return false;
			}else{
				ArcadeDrive(0.0f, angle * .5f);
				return true;
			}
	}
	bool Drive::DriveBackwardByTime(float time){
			//float angle = Gyro.GetAngle();
			float angle = 0.0f;
				if(autoTimer->Get() < time){
					ArcadeDrive(-.5f, -angle * .5f);
					return false;
				}else{
					ArcadeDrive(-0.0f, -angle * .5f);
					return true;
				}
		}

	bool Drive::TurnToAngle(float targetAngle){
		float angle = Gyro.GetAngle() - targetAngle;
				if(angle > 10.0f * ROTATE_TOLERANCE){
					ArcadeDrive(0.0f, -.75f);
				}else if(angle > ROTATE_TOLERANCE){
					ArcadeDrive(0.0f, -0.3f);
				}else if(angle < -10.0f * ROTATE_TOLERANCE){
					ArcadeDrive(0.0f, 0.75);
				}else if(angle < -ROTATE_TOLERANCE){
					ArcadeDrive(0.0f, 0.3f);
				}else{
					mainDrive.ArcadeDrive(0.0f, 0.0f);
					return true;
				}
				return false;
	}

	void Drive::TankDrive(float target_left, float target_right){
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

	void Drive::ArcadeDrive(float target_speed, float rotate_speed){
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

	void Drive::setDriveSpeed(float multiplier){
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

	float Drive::GetTargetCenterX(std::vector<cv::Point> target_x){
		float center_x = 0;
		for(uint i = 0; i < target_x.size(); i++){
			center_x = center_x + target_x[i].x;
		}
		return center_x / target_x.size();
	}

	void Drive::TrackTarget(){

	}

	float Drive::PullGyroAngle(){
		return Gyro.GetAngle();
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



