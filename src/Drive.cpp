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
			autoTimer(),
			Drive_straight(0),
			startTime(0)
	{
		mainDrive.SetExpiration(0.1);
		Sonar.SetAverageBits(4);


	}

	void Drive::ResetTimer(){
		autoTimer.Start();
		startTime = autoTimer.Get();
	}

	float Drive::GetTime(){
		return autoTimer.Get() - startTime;
	}

	void Drive::InvertDrive(bool invert){
		mainDrive.SetInvertedMotor(RobotDrive::MotorType::kFrontLeftMotor, invert);
		mainDrive.SetInvertedMotor(RobotDrive::MotorType::kFrontRightMotor, invert);
		mainDrive.SetInvertedMotor(RobotDrive::MotorType::kRearLeftMotor, invert);
		mainDrive.SetInvertedMotor(RobotDrive::MotorType::kRearRightMotor, invert);
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
		setDriveSpeed(1.0f);
		SmartDashboard::PutNumber("Sonar", Sonar.GetAverageValue());
	}

	bool Drive::DriveForwardByTime(float speed, float time){
		float angle = Gyro.GetAngle();
			if(GetTime() < time){
				ArcadeDrive(speed, angle * .5f);
				return false;
			}else{
				ArcadeDrive(0.0f, 0.0f);  //TH: this was still turning the bot
				return true;
			}
	}
	bool Drive::Pause(float time){
			if(GetTime() < time){
				ArcadeDrive(0.0f, 0.0f);
				return false;
			}else{
				ArcadeDrive(0.0f, 0.0f);
				return true;
			}
	}
	bool Drive::DriveForwardByAngleByTime(float speed, float angle, float time){
			if(GetTime() < time){
				ArcadeDrive(speed, angle * .5f);
				return false;
			}else{
				ArcadeDrive(0.0f, 0.0f);  //TH: this was still turning the bot
				return true;
			}
	}
	bool Drive::DriveForwardToHeadingByTime(float speed, float Heading, float time){
		float head = -NormalizeAngle(Heading - PullGyroAngle());
			if(GetTime() < time){
				ArcadeDrive(speed, head * .25);
				return false;
			}else{
				ArcadeDrive(0.0f, 0.0f);  //TH: this was still turning the bot
				return true;
			}
	}
	bool Drive::DriveBackwardByTime(float speed, float time){
			//float angle = Gyro.GetAngle();
			float angle = 0.0f;
				if(GetTime() < time){
					ArcadeDrive(-speed, -angle * .5f);
					return false;
				}else{
					ArcadeDrive(0.0f, 0.0f);  //TH: this was still turning the bot
					return true;
				}
		}

	bool Drive::TurnToAngle(float targetAngle){
		float angle = -NormalizeAngle(targetAngle - PullGyroAngle());
		ArcadeDrive(0.0f, angle * 0.05f);
		if(abs(angle) < ROTATE_TOLERANCE && abs(Gyro.GetRate()) < 5){
			return true;
		}else{
			return false;
		}
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
			//last_rotate_speed = (rotate_speed + last_rotate_speed * AVERAGE_WEIGHT) / (AVERAGE_WEIGHT + 1);
			last_rotate_speed = rotate_speed;
		}
		mainDrive.ArcadeDrive(last_arcade_speed, last_rotate_speed);
	}

	void Drive::DriveAssist(){

	}

	void Drive::setDriveSpeed(float multiplier){
		if(Rstick.GetRawButton(HighGearA_Button_ID) && Lstick.GetRawButton(HighGearB_Button_ID)){ //High gear
			gearing = HighGear;
			SmartDashboard::PutString("Gear", "High");
		}else{ //Low gear
			gearing = LowGear;
			SmartDashboard::PutString("Gear", "Low");
		}
		float LeftStickValue = (-Lstick.GetY());
		float RightStickValue = (-Rstick.GetY());

		//LeftStickValue = pow(LeftStickValue, 3);
		//RightStickValue = pow(RightStickValue, 3);

		if(LeftStickValue >= 0) {
			LeftStickValue = pow(LeftStickValue, 2);
		} else {
			LeftStickValue = -pow(LeftStickValue, 2);
		}
		if(RightStickValue >= 0) {
			RightStickValue = pow(RightStickValue, 2);
		} else {
			RightStickValue = -pow(RightStickValue, 2);
		}

		LeftStickValue = multiplier * gearing * LeftStickValue;
		RightStickValue = multiplier * gearing * RightStickValue;

//		float JoyStickDifference = RightStickValue - RightStickValue;
//		float effect = -0.25 * pow(JoyStickDifference, 2) + 1;
//		float adjust = ((LeftStickValue + RightStickValue) / 2.0f) * Gyro.GetRate() * effect /100.0f;
//		adjust = std::max(-0.1f, std::min(0.1f, adjust));
//
//		RightStickValue = RightStickValue - adjust;
//		LeftStickValue = LeftStickValue + adjust;

		if(DriveForward == true){
					TankDrive(RightStickValue, LeftStickValue);
				}else{
					TankDrive(-LeftStickValue, -RightStickValue);
				}
		//LeftStickValue = pow(LeftStickValue, 3);
		//RightStickValue = pow(RightStickValue, 3);
//		float JoyStickDifference = LeftStickValue - RightStickValue;
//		float JoyStickAverage = (LeftStickValue + RightStickValue) / 2.0f;
//
//		if(abs(LeftStickValue) < 0.1 && abs(RightStickValue) < 0.1){
//			ArcadeDrive(0.0f, 0.0f);
//		}else{
//			float angle = Gyro.GetRate() * 0.1f;
//			if(DriveForward == true){
//				ArcadeDrive(JoyStickAverage, JoyStickDifference / 5 - angle);
//			}else{
//				ArcadeDrive(-JoyStickAverage, JoyStickDifference / 5 + angle);
//			}
//		}


	}

	/*float getJoystickTransform(float input){
		return input;
	}*/

	float Drive::PullGyroAngle(){
		return Gyro.GetAngle();
	}
	float Drive::NormalizeAngle(float angle){
		while(angle > 180){
			angle = angle - 360;
		}
		while(angle < -180){
			angle = angle + 360;
		}
		return angle;
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



