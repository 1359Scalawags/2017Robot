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
enum AutonMiddleDirection{
	MidLeft,
	MidRight
};

class AutoProgram{

//typedef void (AutoProgram::*Functionptr)();

private:

	StartingPosition position;
	float DisFromWall;
	float RotateAnglePeg;
	float RotateAngleLine;
	float RotateAngleClear;
	Drive *drive;
	GearHandler *gear;
	AutonState autostate;
	AutonMiddleDirection automiddir;
	float DriveTimeToClearShip;

	//Functionptr currentprocess;

public:
	AutoProgram(Drive *maindrive, GearHandler *gearhandler):
		position(Middle),
		DisFromWall(0),
		RotateAnglePeg(0),
		RotateAngleLine(0),
		RotateAngleClear(0),
		drive(maindrive),
		gear(gearhandler),
		autostate(Driving),
		automiddir(MidRight),
		DriveTimeToClearShip(1.5f)
		//currentprocess()
{


}

	void AutonLeft(){
		if(autostate == Driving){
			if(ForwardFromWall()){
				ChangeState(Backing);
			}
		}else if(autostate == Backing){
			if(Backward()){
				ChangeState(TurningToPeg);
			}
		}else if(autostate == TurningToPeg){
			if(TurnToPeg(RotateAnglePeg)){
				ChangeState(Stop);
			}
		}
	}
	void AutonRight(){

	}
	void AutonMiddle(){

	}

	void AutoInit(){
		drive->ResetTimer();
		ChangeState(Driving);
		drive->InvertDrive(true);
		//currentprocess = &AutoProgram::AutonForward;
	}
	void ChangeState(AutonState newstate){
		drive->ResetTimer();
		autostate = newstate;
	}
	void SetFieldPosition(StartingPosition field_position){
		drive->GyroReset();
		position = field_position;
		if(position == StartingPosition::Middle){
			//need to move forward 3ft
			DisFromWall = 36;
			RotateAnglePeg = 0;
			RotateAngleClear = 90;
			RotateAngleLine = -90;

		}else if(position == StartingPosition::Left){
			//need to move froward 16ft
			DisFromWall = 192;
			RotateAnglePeg = -120;
			RotateAngleClear = 0;
			RotateAngleLine = -60;
		}else{
			//need to move forward 16ft
			DisFromWall = 192;
			RotateAnglePeg = -60;
			RotateAngleClear = 0;
			RotateAngleLine = -60;
		}
	}
	void Auton(){

		if(autostate == Driving) {
			ForwardFromWall();
		}else if(autostate == Backing){
			Backward();
		}else if(autostate == TurningToPeg){
			TurnToPeg(-120);

/*
		}
#ifdef DOGEARDROP
		else if(autostate == TurningToPeg){
			TurnToPeg(RotateAnglePeg);
		}else if(autostate == TargetPeg){
			TrackPeg();
		}else if(autostate == GearPlacing){
			PlaceGear();
		}else if(autostate == DropGear){
			DropingGear();
		}else if(autostate == Backing){
			BackwardFromShip();
		}
#else
		else if(autostate == TurningToPeg || autostate == TargetPeg){
			ChangeState(TurnToClear);
		}
#endif
		else if(autostate == TurnToClear){
			TurnClear(RotateAngleClear);
		}else if(autostate == DriveToClear){
			DriveClear();
		}else if(autostate == TurnToLine){
			TurnLine(RotateAngleLine);
		}else if(autostate == DriveToLine){
			DriveLine();
*/
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

/*	void AutonLeft(){
		drive->TurnToAngle(90);
	}
	void AutonRight(){
		drive->TurnToAngle(-90);
	}*/

	bool TurnToPeg(float angle){ //rotates robot to face peg
		return drive->TurnToAngle(angle);
	}

/*	void AutonMiddle(){
		if(autostate == Driving){
			ForwardFromWall();
		}
	}*/

	bool ForwardFromWall(){ //Drives robot away from wall
		return drive->DriveForwardByTime(6.0f);
	}
	void BackwardFromShip(){ //drives away from ship
		//if(drive->DriveToDistance(DisFromWall)){
		//go to next phase
		if(drive->DriveBackwardByTime(1.0f)){
			//currentprocess = &AutoProgram::Rotate;
			ChangeState(AutonState::TurnToClear);
		}else{

		}
	}
	bool Backward(){ //drives away from ship
		return drive->DriveBackwardByTime(3.0f);
	}

	void TrackPeg(){ //finds and targets the peg
		SmartDashboard::PutNumber("Angle to target", Vision::getAproxAngleToTarget());
		ChangeState(AutonState::GearPlacing);
	}
	void PlaceGear(){ //places the gear
		ChangeState(AutonState::DropGear);
	}
	void DropingGear(){//drops the gear
		gear->OpenDoor();
		ChangeState(AutonState::Backing);
	}
	void TurnClear(float angle){ //rotates robot to clear the ship
		if(drive->TurnToAngle(angle)){
			if(position == Middle){
				ChangeState(AutonState::DriveToClear);
			}else{
				ChangeState(AutonState::TurnToLine);
			}

		}
	}
	void DriveClear(){ //drives robot to clear the ship
#ifdef DEBUG
		if(drive->DriveForwardByTime(DriveTimeToClearShip)){
#else
		if(drive->DriveToDistance()){
#endif

			ChangeState(AutonState::TurnToLine);
		}
	}
	void TurnLine(float angle){ //turns to face the field line
		if(drive->TurnToAngle(angle)){
			autostate = AutonState::DriveToLine;
		}
	}
	void DriveLine(){ //drives across the field line
#ifdef DEBUG
		if(drive->DriveForwardByTime(1.5f)){
#else
		if(drive->DriveToDistance()){
#endif

			ChangeState(AutonState::Stop);
		}
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
