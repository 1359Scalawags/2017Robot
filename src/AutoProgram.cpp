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
	Left,
	Middle,
	Right,
	Test
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
	Stop,
	Pause
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
	float DriveByTime;
	float DriveBackByTime;
	Drive *drive;
	GearHandler *gear;
	AutonState autostate;
	AutonMiddleDirection automiddir;
	float DriveTimeToClearShip;
	float lastDistanceToPeg;
	float lastAngleToPeg;


	//Functionptr currentprocess;

public:
	AutoProgram(Drive *maindrive, GearHandler *gearhandler):
		position(Middle),
		DisFromWall(0),
		RotateAnglePeg(0),
		RotateAngleLine(0),
		RotateAngleClear(0),
		DriveByTime(0),
		DriveBackByTime(0),
		drive(maindrive),
		gear(gearhandler),
		autostate(Driving),
		automiddir(MidRight),
		DriveTimeToClearShip(1.5f),
		lastDistanceToPeg(0),
		lastAngleToPeg(0)
		//currentprocess()
{


}

	void AutonLeft(){
		if(autostate == Driving){
			std::cout << "Driving\n";
			if(ForwardFromWall(0.6f, DriveByTime)){
				ChangeState(Pause);
			}
		}else if(autostate == Pause){
			std::cout << "Pause\n";
			if(drive->Pause(2.0f)){
				ChangeState(TargetPeg);
			}
		}else if(autostate == TurningToPeg){
			std::cout << "Turn to peg\n";
			if(TurnToPeg(RotateAnglePeg)){
				ChangeState(TargetPeg);
			}
		}else if(autostate == TargetPeg){
			std::cout << "TargetPeg\n";
			if(TrackPeg(4.0f)){
				ChangeState(Backing);
			}
		}else if(autostate == Backing){
			std::cout << "Backing\n";
			if(Backward(0.3f, DriveBackByTime)){
				ChangeState(Stop);
			}
		}else{
			drive->ArcadeDrive(0.0f, 0.0f);
		}
	}
	void AutonRight(){
		if(autostate == Driving){
			if(ForwardFromWall(0.6f, DriveByTime)){
				ChangeState(TurningToPeg);
			}
		}else if(autostate == TurningToPeg){
			if(TurnToPeg(RotateAnglePeg)){
				ChangeState(TargetPeg);
			}
		}else if(autostate == TargetPeg){
			if(TrackPeg(4.0f)){
				ChangeState(Backing);
			}
		}else if(autostate == Backing){
			if(Backward(0.3f, DriveBackByTime)){
				ChangeState(Stop);
			}
		}else{
			drive->ArcadeDrive(0.0f, 0.0f);
		}
	}
	void AutonMiddle(){
		if(autostate == Driving){
			if(ForwardFromWall(0.5f, 1.0f)){
				ChangeState(TargetPeg);
			}
		}else if(autostate == TargetPeg){
			if(TrackPeg(4.0f)){
				ChangeState(Backing);
			}
		}else if(autostate == Backing){
			if(Backward(0.3f, DriveBackByTime)){
				ChangeState(Stop);
			}
		}else{
			drive->ArcadeDrive(0.0f, 0.0f);
		}
	}

	void AutoInit(){
		drive->ResetTimer();
		drive->InvertDrive(true);
		if(StartingPosition::Middle){
			ChangeState(Driving);
		}else{
			ChangeState(Driving);
		}
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
			DriveByTime = 3.0f;
			DriveBackByTime = .7f;
			RotateAnglePeg = 0;
			RotateAngleClear = 90;
			RotateAngleLine = -90;

		}else if(position == StartingPosition::Left){
			//need to move froward 16ft
			DisFromWall = 192;
			DriveByTime = 1.0f;
			DriveBackByTime = 3.0f;
			RotateAnglePeg = 60;
			RotateAngleClear = 0;
			RotateAngleLine = -60;
		}else{
			//need to move forward 16ft
			DisFromWall = 192;
			DriveByTime = 1.0f;
			DriveBackByTime = 3.0f;
			RotateAnglePeg = -60;
			RotateAngleClear = 0;
			RotateAngleLine = -60;
		}
	}
	void Auton(){

		if(autostate == Driving) {
			//ForwardFromWall();
		}else if(autostate == Backing){
			//Backward();
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

	bool ForwardFromWall(float speed, float Drivetime){ //Drives robot away from wall
		return drive->DriveForwardByTime(speed, Drivetime);
	}
	void BackwardFromShip(){ //drives away from ship
		//if(drive->DriveToDistance(DisFromWall)){
		//go to next phase
		if(drive->DriveBackwardByTime(0.3f, 1.0f)){
			//currentprocess = &AutoProgram::Rotate;
			ChangeState(AutonState::TurnToClear);
		}else{

		}
	}
	bool Backward(float speed, float Drivetime){ //drives away from ship
		return drive->DriveBackwardByTime(speed, Drivetime);
	}


	bool TrackPeg(float BailTime){ //finds and targets the peg
		float distanceToPeg = (Vision::GetDistanceFromTarget() + lastDistanceToPeg) / 2.0f;
		lastDistanceToPeg = distanceToPeg;
		float Heading = (Vision::GetHeadingToTarget(drive->PullGyroAngle()));
		float speed = (distanceToPeg + 100.0f) / 200.0f;
		speed = std::min(speed, 0.5f);
		speed = std::max(speed, 0.25f);
		//std::cout << Heading << "\n";
		return drive->DriveForwardToHeadingByTime(speed, Heading, BailTime);
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
		if(drive->DriveForwardByTime(0.5, DriveTimeToClearShip)){
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
		if(drive->DriveForwardByTime(0.5f, 1.5f)){
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
