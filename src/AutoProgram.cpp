#include <Constants.h>
#include "WPILib.h"
#include <Drive.h>
#include <GearHandler.h>
#include <Vision.h>
/*
 * Autonomous.cpp
 *
 *  Created on: Feb 12, 2017
 *      Author: Destin
 */

enum StartingPosition{
	Left = 0,
	Middle = 1,
	Right = 2,
	Test = 3
};
enum AutonState{
	Driving = 0,
	Turning = 1,
	GearPlacing = 2,
	Backing = 3,
	Stop = 4
};

class AutoProgram{

//typedef void (AutoProgram::*Functionptr)();

private:

	StartingPosition position;
	float DisFromWall;
	float RotateAngle;
	Drive *drive;
	GearHandler *gear;
	AutonState autostate;

	//Functionptr currentprocess;

public:
	AutoProgram(Drive *maindrive, GearHandler *gearhandler):
		position(Middle),
		DisFromWall(0),
		RotateAngle(0),
		drive(maindrive),
		gear(gearhandler),
		autostate(Driving)
		//currentprocess()
{


}
	void AutoInit(){
		drive->ResetTimer();
		//currentprocess = &AutoProgram::AutonForward;
	}
	void SetFieldPosition(StartingPosition field_position){
		drive->GyroReset();
		position = field_position;
		if(position == StartingPosition::Middle){
			//need to move forward 3ft
			DisFromWall = 36;
			RotateAngle = 0;
		}else if(position == StartingPosition::Left){
			//need to move froward 16ft
			DisFromWall = 192;
			RotateAngle = 120;
		}else if(position == StartingPosition::Right){
			//need to move forward 16ft
			DisFromWall = 192;
			RotateAngle = -120;
		}
	}
	void Auton(){

		if(autostate == Driving) {
			AutonForward();
		}else if(autostate == Turning){
			AutonTurn(RotateAngle);
		}else if(autostate == GearPlacing){
			PlaceGear();
		}
		/*if(position == Middle){
			//(this->*currentprocess)();
			//drive->DriveStraight(1.5f);
			AutonMiddle();
		}else if(position == Left){
			AutonLeft();
		}else if(position == Right){
			AutonRight();
		}else if(position == Test){

		}*/
	}
	void AutonLeft(){
		drive->TurnToAngle(90);
	}
	void AutonRight(){
		drive->TurnToAngle(-90);
	}

	void AutonTurn(float angle){
		if(drive->TurnToAngle(angle)){
			autostate = GearPlacing;
		}
	}
	void AutonMiddle(){
		if(autostate == Driving){
			AutonForward();
		}
	}

	void AutonForward(){
		//if(drive->DriveToDistance(DisFromWall)){
		//go to next phase
		if(drive->DriveStraight(1.5f)){
			//currentprocess = &AutoProgram::Rotate;
			if(position == Middle){
				autostate = GearPlacing;
			}else if(position == Left){
				autostate = Turning;
			}else if(position == Right){
				autostate = Turning;
			}else if(position == Test){

			}
		}
	}
	void Rotate(){
		if(drive->TurnToAngle(RotateAngle)){
			//go to next phase
		}
	}
	void TrackPeg(){
		float centerX = Vision::getAverageCenterX();
		float area = Vision::getLargestArea();
		SmartDashboard::PutNumber("CenterX", centerX);
		SmartDashboard::PutNumber("Area", area);
	}
	void PlaceGear(){

	}
};


/*

		int selected = *(chooser.GetSelected());
if(selected == 0){
				SmartDashboard::PutString("AutoSelector", "Left");
				drive.AutonLeft();
			}else if(selected == 1){
				SmartDashboard::PutString("AutoSelector", "Middle");
				drive.AutonMiddle();
			}else if(selected == 2){
				SmartDashboard::PutString("AutoSelector", "Right");
				drive.AutonRight();
			}else if(selected ==3){
				SmartDashboard::PutString("AutoSelector", "Tracking");
				drive.TrackTarget();
			}*/
