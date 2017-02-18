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
	Driving,
	TurningToPeg,
	TargetPeg,
	GearPlacing,
	DropGear,
	Backing,
	TurnToClear,
	DriveToClear,
	TurnToLine,
	DriveToLine,
	Stop
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
		}else if(autostate == TurningToPeg){
			AutonTurn(RotateAngle);
		}else if(autostate == TargetPeg){
			TrackPeg();
		}else if(autostate == GearPlacing){
			PlaceGear();
		}else if(autostate == DropGear){
			DropingGear();
		}else if(autostate == Backing){
			AutonBackward();
		}else if(autostate == TurnToClear){

		}else{
			drive->ArcadeDrive(0.0f, 0.0f);
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
			autostate = TargetPeg;
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
		if(drive->DriveForwardByTime(1.5f)){
			//currentprocess = &AutoProgram::Rotate;
			if(position == Middle){
				autostate = TargetPeg;
			}else if(position == Left || position == Right){
				autostate = TurningToPeg;
			}else if(position == Test){

			}
		}
	}
	void AutonBackward(){
		//if(drive->DriveToDistance(DisFromWall)){
		//go to next phase
		if(drive->DriveBackwardByTime(1.5f)){
			//currentprocess = &AutoProgram::Rotate;
			if(position == Middle){

			}else if(position == Left || position == Right){
				autostate = AutonState::Stop;
			}else if(position == Test){

			}
		}else{

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
		autostate = AutonState::GearPlacing;
	}
	void PlaceGear(){
		autostate = AutonState::DropGear;
	}
	void DropingGear(){
		autostate = AutonState::Backing;
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
